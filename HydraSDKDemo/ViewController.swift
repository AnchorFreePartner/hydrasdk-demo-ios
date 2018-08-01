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
    @IBOutlet weak var changeCountryButton: UIButton!
    @IBOutlet weak var loginStatus: UILabel!
    @IBOutlet weak var connectionStatus: UILabel!
    @IBOutlet weak var vpnSwitch: UISwitch!
    @IBOutlet weak var onDemandSwitch: UISwitch!
    @IBOutlet weak var onDemandLabel: UILabel!
    @IBOutlet weak var countryLabel: UILabel!
    @IBOutlet weak var trafficLimitLabel: UILabel!
    @IBOutlet weak var trafficStatsLabel: UILabel!
    @IBOutlet weak var fireshieldSwitch: UISwitch!
    @IBOutlet weak var fireshieldCategoryzationLabel: UILabel!
    @IBOutlet weak var connectionsCountLabel: UILabel!
    @IBOutlet weak var fireshiledNotificationsSwitch: UISwitch!

    private var isUpdatingScannedConnections: Bool = false
    
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
        self.observerApplicationDidBecomeActive()
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
        }
    }
    
    private func observerApplicationDidBecomeActive() {
        NotificationCenter.default.addObserver(forName: NSNotification.Name.UIApplicationDidBecomeActive, object: nil, queue: nil) { _ in
            self.updateCategorizationLabel()
        }
    }
    
    private func updateCategorizationLabel() {
        guard let categorizationResource = hydraClient.lastCategorization().resource else { return }
        let categorization = hydraClient.lastCategorization()
        let categoriationDescription = "\(categorization.actionEmoji) \(categorizationResource)"
        
        self.fireshieldCategoryzationLabel.text = categoriationDescription
    }
    
    private func reloadData() {
        guard isVpnConnected else { return }
        
        self.updateTrafficStats() {
            self.updateTrafficLimits() {
                self.updateScannedConnections() {
                    self.reloadData()
                }
            }
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
    
    @IBAction func changeCountry(_ sender: UIButton) {
        let controller = self.storyboard?.instantiateViewController(withIdentifier: "CountryController") as! CountryController
        controller.currentCountry = self.country
        controller.delegate = self
        self.present(controller, animated: true, completion: nil)
    }

    @IBAction func hydraPreferencesValueChanged(_ sender: UISwitch) {
        guard sender == fireshieldSwitch || sender == onDemandSwitch || sender == vpnSwitch else {
            return
        }

        func _restoreState(of control: UISwitch, animated: Bool) {
            DispatchQueue.main.async {
                control.setOn(!control.isOn, animated: animated)
            }
        }

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

            self.hydraClient.config.onDemand = props.isOnDemand
            self.hydraClient.updateConfig(AFConfig.init(block: { builder in
                builder.fireshieldMode = fireshieldMode
            }))

            print("Did update Hydra config")
        }

        func _connectToHydra() {
            self.lockControls()
            self.hydraClient.startVpn { [unowned self] (country, error) in
                if let e = error {
                    print("Failed to connect to Hydra. Error was: \(e)")
                    _restoreState(of: sender, animated: false)
                }
                else {
                    print("Connected to Hydra with server location country code: \(country?.countryCode ?? "<unknown>")")
                    self.countryConnectedTo = country
                }
                self.unlockControls()
                self.updateUI()
            }
        }

        let isVPN = vpnSwitch.isOn
        let isFireshield = fireshieldSwitch.isOn
        let isOnDemand = onDemandSwitch.isOn

        let hydraConnectionState = self.hydraClient.vpnStatus()
        switch hydraConnectionState {
        case .connected:
            self.lockControls()
            self.hydraClient.stopVpn { [unowned self] error in
                guard error == nil else {
                    print("Failed to disconnect from Hydra. Error was: \(error!)")
                    _restoreState(of: sender, animated: false)
                    self.unlockControls()
                    self.updateUI()
                    return
                }
                _updateHydraConfig(with: (isVPN, isFireshield, isOnDemand))
                _connectToHydra()
            }
            break
        case .disconnected, .invalid:
            _updateHydraConfig(with: (isVPN, isFireshield, isOnDemand))
            _connectToHydra()
            break
        default:
            _restoreState(of: sender, animated: false)
            return
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
        self.onDemandLabel.text = self.onDemandSwitch.isOn ? "On-demand enabled" : "On-demand disabled"
        self.fireshiledNotificationsSwitch.isOn = Preferences.isFireshieldNotificationsEnabled
    }

    private func lockControls() {
        self.vpnSwitch.isEnabled = false
        self.onDemandLabel.isEnabled = false
        self.fireshieldSwitch.isEnabled = false
    }

    private func unlockControls() {
        self.vpnSwitch.isEnabled = true
        self.onDemandLabel.isEnabled = true
        self.fireshieldSwitch.isEnabled = true
    }
    
    @objc func updateTrafficStats(completion: UpdateCompletion? = nil) {
        guard isVpnConnected else {
            completion?()
            return
        }
        
        hydraClient.trafficCounters { [unowned self] (e, counters) in
            guard let counters = counters else {
                self.completeUpdate(with: completion)
                return
            }
        
            let ul = ByteCountFormatter.string(fromByteCount: counters.bytesTx.int64Value, countStyle: .file)
            let dl = ByteCountFormatter.string(fromByteCount: counters.bytesRx.int64Value, countStyle: .file)
            let string = "UL: \(ul), DL: \(dl)"
            self.trafficStatsLabel.text = string
            self.completeUpdate(with: completion)
        }
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
