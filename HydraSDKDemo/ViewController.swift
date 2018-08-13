//
//  ViewController.swift
//  HydraSDKDemo
//
//  Created by Igor Glotov on 9/21/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

import UIKit
import UserNotifications
import HydraApplicationSDK

class ViewController: UIViewController, CountryControllerProtocol {
    typealias UpdateCompletion = () -> ()
    
    @IBOutlet weak var loginButton: UIButton!
    @IBOutlet weak var loginStatus: UILabel!

    @IBOutlet weak var connectionStatus: UILabel!
    @IBOutlet weak var vpnSwitch: UISwitch!
    @IBOutlet weak var onDemandSwitch: UISwitch!
    @IBOutlet weak var fireshieldSwitch: UISwitch!
    @IBOutlet weak var connectButton: UIButton!

    @IBOutlet weak var fireshieldCategoryzationLabel: UILabel!
    @IBOutlet weak var connectionsCountLabel: UILabel!
    @IBOutlet weak var fireshiledNotificationsSwitch: UISwitch!

    @IBOutlet weak var changeCountryButton: UIButton!
    @IBOutlet weak var countryLabel: UILabel!

    @IBOutlet weak var trafficLimitLabel: UILabel!
    @IBOutlet weak var trafficStatsLabel: UILabel!

    private var isUpdatingScannedConnections: Bool = false
    private var updateConnectionControlsToken: Bool = false
    private var countryConnectedTo: AFCountry?
    
    private var hydraClient : AFHydra {
        get {
            let appDelegate = UIApplication.shared.delegate as! AppDelegate
            return appDelegate.hydraClient
        }
    }
    
    private var country : AFCountry? {
        get {
            guard let encodedData = UserDefaults.standard.data(forKey: "country") else { return nil }
            return NSKeyedUnarchiver.unarchiveObject(with: encodedData) as? AFCountry
        }
        set(newCountry) {
            let encodedData = NSKeyedArchiver.archivedData(withRootObject: newCountry as Any)
            UserDefaults.standard.set(encodedData, forKey: "country")
        }
    }
    
    private var isVpnConnected: Bool {
        get {
            return hydraClient.vpnStatus() == .connected
        }
    }
    
    private var statusString: String {
        switch hydraClient.vpnStatus() {
        case .disconnecting:
            return "Disconnecting"
        case .connecting:
            return "Connecting"
        case .connected:
            return "Connected"
        case .reconnecting:
            return "Reconnecting"
        case .invalid, .undefined, .disconnected:
            return "Disconnected"
        }
    }
    
    private var isFireshieldEnabled: Bool {
        return fireshieldSwitch.isOn
    }

    // MARK: View Lifecycle

    override func viewDidLoad() {
        super.viewDidLoad()
        self.updateUI()
        self.observerStatusChange()
        self.observerCategorizationDidChange()
    }
    
    private func observerStatusChange() {
        NotificationCenter.default.addObserver(forName: NSNotification.Name.AFVPNStatusDidChange, object: nil, queue: nil) { [unowned self] (notification) in
            self.updateUI()

            switch self.hydraClient.vpnStatus() {
            case .connected:
                self.startUpdatingScannedConnections()
            case .invalid, .undefined, .disconnected:
                self.stopUpdatingScannedConnections()
            default: break
            }
            
            self.reloadData()

            self.updateConnectionControlsOnceIfNeeded()
        }
    }

    private func observerCategorizationDidChange() {
        NotificationCenter.default.addObserver(forName: NSNotification.Name.AFVPNCategorizationDidChange, object: nil, queue: OperationQueue.main) { [unowned self] notification in
            guard notification.userInfo != nil else {
                self.updateCategorizationLabel(with: self.hydraClient.lastCategorization())
                return
            }
            guard let payloadCategorization: AFHydraCategorization = notification.userInfo?["categorization"] as? AFHydraCategorization else { return }
            self.updateCategorizationLabel(with: payloadCategorization)
        }
    }
    
    private func updateCategorizationLabel(with categorization: AFHydraCategorization?) {
        guard let categorization = categorization else { return }
        guard let categorizationResource: String = categorization.resource else { return }
        let categoriationDescription = "\(categorization.actionEmoji) \(categorizationResource)"
        self.fireshieldCategoryzationLabel.text = categoriationDescription
    }
    
    private func reloadData() {
        guard isVpnConnected else { return }
        
        self.updateTrafficStats()
        self.updateTrafficLimits() {
            self.updateScannedConnections() {
                self.reloadData()
            }
        }
    }

    private func updateConnectionControlsOnceIfNeeded() {
        guard !updateConnectionControlsToken else {
            return
        }

        updateConnectionControlsToken = true

        let currentIsOnDemand = self.hydraClient.isOnDemandEnabled
        let currentFireshieldMode = self.hydraClient.currentFireshieldMode;

        self.onDemandSwitch.setOn(currentIsOnDemand, animated: false)

        if currentFireshieldMode == .disabled {
            vpnSwitch.setOn((hydraClient.vpnStatus() == .connected), animated: false)
        }
        else if currentFireshieldMode == .enabledVPN {
            vpnSwitch.setOn(true, animated: false)
            fireshieldSwitch.setOn(true, animated: false)
        }
        else if currentFireshieldMode == .enabledSilent || currentFireshieldMode == .enabled {
            vpnSwitch.setOn(false, animated: false)
            fireshieldSwitch.setOn(true, animated: false)
        }
    }

    // MARK: Interface Builder Actions

    @IBAction func toggleLogin(_ sender: UIButton) {
        if hydraClient.isLoggedIn() {
            hydraClient.logout({ [unowned self] (e) in
                if let ex = e {
                    print("Logout error: \(ex)")
                } else {
                    print("Logout success")
                }
                
                self.updateUI()
            })
        } else {
            hydraClient.login(AFAuthMethod.anonymous(), completion: { [unowned self] (e, user) in
                if let ex = e {
                    print("Login error: \(ex)")
                } else {
                    print("Login success")
                }
                
                self.updateUI()
            })
        }
    }

    private func isSupportedConnectionConfiguration() -> Bool {
        let isVPN = vpnSwitch.isOn
        let isFireshield = fireshieldSwitch.isOn
        if (!isVPN && !isFireshield) {
            AlertController.presentAlert(withTitle: "Cannot Connect", body: "Either VPN or Fireshield switch (or both) should be turned ON", in: self, cancelButtonTitle: "OK", cancelActionHandler: {
                /* do nothing */
            })
            return false
        }
        return true
    }
    
    @IBAction func connectButtonDidPress(_ sender: Any) {
        if (!hydraClient.isLoggedIn()) {
            print("Login before starting a connection")
            return
        }

        if (!isSupportedConnectionConfiguration()) {
            return
        }

        let hydraConnectionState = self.hydraClient.vpnStatus()
        switch hydraConnectionState {
        case .connected:
            self.updateConnectionControlsToken = true
            self.connectButton.isEnabled = false
            self.hydraClient.stopVpn { [unowned self] error in
                self.connectButton.isEnabled = true
                guard error == nil else {
                    print("Failed to disconnect from Hydra. Error was: \(error!)")
                    self.updateUI()
                    return
                }
                self.unlockConnectionConfigurationControls()
                self.updateUI()
            }
        case .disconnected, .invalid:
            self.updateConnectionControlsToken = true
            self.connectButton.isEnabled = false
            lockConnectionConfigurationControls()
            self.hydraClient.startVpn { [unowned self] (country, error) in
                self.connectButton.isEnabled = true
                guard error == nil else {
                    print("Failed to connect to Hydra. Error was: \(error!)")
                    self.unlockConnectionConfigurationControls()
                    self.updateUI()
                    return
                }
                print("Connected to Hydra with server location country code: \(country?.countryCode ?? "<unknown>")")
                self.countryConnectedTo = country
                self.updateUI()
            }
        default:
            print("Ignore -connectButtonDidPress action")
            return
        }
    }

    @IBAction func changeCountry(_ sender: UIButton) {
        let controller = self.storyboard?.instantiateViewController(withIdentifier: "CountryController") as! CountryController
        controller.currentCountry = self.country
        controller.delegate = self
        self.present(controller, animated: true, completion: nil)
    }

    @IBAction func hydraPreferencesValueChanged(_ sender: UISwitch) {
        func _updateHydraConfig(with props: (isVPN: Bool, isFireshield: Bool, isOnDemand: Bool) ) {
            var fireshieldMode: AFConfigFireshieldMode = .disabled
            switch props {
            case (false, true, _):
                fireshieldMode = .enabledSilent
            case (true, true, _):
                fireshieldMode = .enabledVPN
            default:
                fireshieldMode = .disabled
            }

            self.hydraClient.updateConfig(AFConfig.init(block: { builder in
                builder.fireshieldMode = fireshieldMode
                builder.onDemand = props.isOnDemand
            }))

            print("Did update Hydra config")
        }

        guard sender == fireshieldSwitch || sender == onDemandSwitch || sender == vpnSwitch else {
            return
        }

        if (!hydraClient.isLoggedIn()) {
            return
        }

        let isVPN = vpnSwitch.isOn
        let isFireshield = fireshieldSwitch.isOn
        let isOnDemand = onDemandSwitch.isOn

        let hydraConnectionState = self.hydraClient.vpnStatus()
        switch hydraConnectionState {
        case .disconnected, .invalid:
            _updateHydraConfig(with: (isVPN, isFireshield, isOnDemand))
        default:
            print("Ignore -connectButtonDidPress action")
            break
        }
    }
    
    @IBAction func toggleFireshieldNotifications(_ sender: UISwitch) {
        Preferences.isFireshieldNotificationsEnabled = sender.isOn
        if Preferences.isFireshieldNotificationsEnabled {
            requestUserNotificationsPermissionsIfNeeded {
                if $0 == false {
                    self.presentNotificationsAccessDeclinedAlert()
                }
            }
        }
    }

    // MARK: UI

    private func updateUI() {
        self.loginButton.setTitle(hydraClient.isLoggedIn() ? "Log out" : "Log in", for: .normal)
        self.loginStatus.text = hydraClient.isLoggedIn() ? "Logged in" : "Logged out"
        self.connectionStatus.text = self.isVpnConnected ? "\(self.statusString) [\(self.countryConnectedTo?.countryCode ?? "???")]" : self.statusString
        self.countryLabel.text = self.country?.countryCode ?? "Optimal"
        self.fireshiledNotificationsSwitch.isOn = Preferences.isFireshieldNotificationsEnabled
        let connectbuttonTitle = self.isVpnConnected ? "Disconnect" : "Connect"
        self.connectButton.setTitle(connectbuttonTitle, for: .normal)
        self.connectButton.setTitle(connectbuttonTitle, for: .highlighted)
    }

    private func lockConnectionConfigurationControls() {
        self.vpnSwitch.isEnabled = false
        self.onDemandSwitch.isEnabled = false
        self.fireshieldSwitch.isEnabled = false
    }

    private func unlockConnectionConfigurationControls() {
        self.vpnSwitch.isEnabled = true
        self.onDemandSwitch.isEnabled = true
        self.fireshieldSwitch.isEnabled = true
    }
    
    private func updateTrafficStats() {
        guard isVpnConnected else {
            return
        }

        guard let counters: AFTrafficCounters = hydraClient.trafficCounters else {
            return
        }

        let ul = ByteCountFormatter.string(fromByteCount: counters.bytesTx.int64Value, countStyle: .file)
        let dl = ByteCountFormatter.string(fromByteCount: counters.bytesRx.int64Value, countStyle: .file)
        let string = "UL: \(ul), DL: \(dl)"
        self.trafficStatsLabel.text = string
    }
    
    @objc func updateTrafficLimits(completion: UpdateCompletion? = nil) {
        guard isVpnConnected else {
            completion?()
            return
        }
        
        self.hydraClient.remainingTraffic { (e, remainingTraffic) in
            if let ex = e {
                if ex.localizedDescription == "UNLIMITED" {
                    self.trafficLimitLabel.text = "Traffic is unlimited"
                } else {
                    print("remainingTraffic error: \(ex)")
                }
            } else {
                print("remainingTraffic success: \(String(describing: remainingTraffic?.description()))")
            }
            
            guard let traffic = remainingTraffic else {
                self.completeUpdate(with: completion)
                return
            }
            var string : String = ByteCountFormatter.string(fromByteCount: traffic.trafficRemaining.int64Value, countStyle: .file)
            string += " of "
            string += ByteCountFormatter.string(fromByteCount: traffic.trafficUsageLimit.int64Value, countStyle: .file)
            string += " remaining"
            self.trafficLimitLabel.text = string
            self.completeUpdate(with: completion)
        }
    }

    // MARK: Country Controller Delegate

    func countryChanged(newCountry: AFCountry) {
        self.country = newCountry
        updateUI()
    }

    // MARK: Scanned Connections Monitor

    private func startUpdatingScannedConnections() {
        if isFireshieldEnabled {
            isUpdatingScannedConnections = true
        }
    }
    
    private func stopUpdatingScannedConnections() {
        isUpdatingScannedConnections = false
        self.connectionsCountLabel.text = "--"
    }
    
    private func updateScannedConnections(completion: UpdateCompletion? = nil) {
        guard isFireshieldEnabled, isUpdatingScannedConnections else {
            completion?()
            return
        }
        
        hydraClient.getScannedConnections { [unowned self] (connections, error) in
            if let e = error {
                self.connectionsCountLabel.text = "Error: \(e.localizedDescription)"
                self.completeUpdate(with: completion)
                return
            }
            self.connectionsCountLabel.text = "\(connections)"
            
            self.completeUpdate(with: completion)
        }
    }
    
    private func completeUpdate(with completion: UpdateCompletion?) {
        guard let completion = completion else { return }
        DispatchQueue.main.asyncAfter(deadline: .now() + 2) {
            completion()
        }
    }

    // MARK: User Notifications

    private func requestUserNotificationsPermissionsIfNeeded(_ completion: @escaping (Bool) -> ()) {
        let center = UNUserNotificationCenter.current()
        center.requestAuthorization(options: [.alert, .sound]) { (isGranted, error) in
            if let error = error {
                print("Unable to request authorization: \(error)")
            }
            
            completion(isGranted)
        }
    }

    private func presentNotificationsAccessDeclinedAlert() {
        AlertController.presentAlert(withTitle: "Notification Presmission",
                                     body: "Notification access is declined, please change access in Settings to enable Fireshield notifications",
                                     in: self,
                                     cancelButtonTitle: "OK",
                                     cancelActionHandler: {
                                        Preferences.isFireshieldNotificationsEnabled = false
                                        self.fireshieldSwitch.isOn = false
        })
    }
}
