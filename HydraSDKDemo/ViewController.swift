//
//  ViewController.swift
//  HydraSDKDemo
//
//  Created by Igor Glotov on 9/21/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

import UIKit
import VPNApplicationSDK
import UserNotifications

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
    @IBOutlet weak var fireshieldCategoryzationLabel: UILabel!
    @IBOutlet weak var fireshiledNotificationsSwitch: UISwitch! 
    @IBOutlet weak var fireshieldSwitch: UISwitch!
    @IBOutlet weak var connectionsCountLabel: UILabel!
    @IBOutlet weak var connectButton: UIButton!
    
    private var isUpdatingScannedConnections: Bool = false
    
    var countryConnectedTo: VirtualLocation?
    
    var hydraClient : HydraSDK {
        get {
            let appDelegate = UIApplication.shared.delegate as! AppDelegate
            return appDelegate.hydraClient
        }
    }
    
    var country : VirtualLocation? {
        get {
            guard let encodedData = UserDefaults.standard.data(forKey: "country") else { return nil }
            return try? JSONDecoder().decode(VirtualLocation.self, from: encodedData)
        }
        set(newCountry) {
            let encodedData = try! JSONEncoder().encode(newCountry)
            UserDefaults.standard.set(encodedData, forKey: "country")
        }
    }
    
    var isVpnConnected: Bool {
        get {
            return hydraClient.state == .connected
        }
    }
    
    var isLoggedIn: Bool {
        get {
            return hydraClient.isLoggedIn
        }
    }
    
    var statusString: String {
        switch hydraClient.state {
        case .disconnecting:
            return "Disconnecting"
        case .connecting:
            return "Connecting"
        case .connected:
            return "Connected"
        case .invalid, .disconnected, .idle:
            return "Disconnected"
        }
    }
    
    private var isFireshieldEnabled: Bool {
        return fireshieldSwitch.isOn
    }
    
    private var fireshieldMode: FireshieldConfig.Mode {
        return isFireshieldEnabled ? .vpn : .disabled
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.updateUi()

        NotificationCenter.default.addObserver(forName: .HydraStatusDidChange, object: nil, queue: nil) { [unowned self] (notification) in
            self.updateUi()
            if self.isVpnConnected {
                self.startUpdatingScannedConnections()
            }
            
            switch self.hydraClient.state {
            case .invalid, .disconnected:
                self.stopUpdatingScannedConnections()
            default: break
            }
            
            self.reloadData()
        }
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

    @IBAction func toggleLogin(_ sender: UIButton) {
        if self.isLoggedIn {
            hydraClient.logout { [unowned self] (e) in
                if let ex = e {
                    print("Logout error: \(ex)")
                } else {
                    print("Logout success")
                }
                
                self.updateUi()
            }
        } else {
            hydraClient.login(method: AuthMethod.anonymous()) { (e, user) in
                if let ex = e {
                    print("Login error: \(ex)")
                } else {
                    print("Login success")
                }

                self.updateUi()
            }
        }
    }
    
    @IBAction func changeCountry(_ sender: UIButton) {
        let controller = self.storyboard?.instantiateViewController(withIdentifier: "CountryController") as! CountryController
        controller.currentCountry = self.country
        controller.delegate = self
        self.present(controller, animated: true, completion: nil)
    }
    
    
    @IBAction func toggleVPN(_ sender: UISwitch) {
        if !self.isVpnConnected {
            startVPN()
        } else if isFireshieldEnabled {
            presentDisableOptionsAlert()
        } else {
            stopVPN()
        }
    }
    
    private func presentDisableOptionsAlert() {
        let alertController = UIAlertController(title: "VPN Connection",
                                                message: "Fireshiled is still enabled\ndo you want to run VPN in silent mode with Fireshield? ",
                                                preferredStyle: .alert)
        
        let enabledAction = UIAlertAction(title: "Enable silent VPN", style: .default) { _ in
            self.restartConnectionWithFireshield()
        }
        let disableAction = UIAlertAction(title: "Disable VPN and Fireshield", style: .destructive) { _ in
            self.stopVPN()
            self.fireshieldSwitch.isOn = false
            self.updateHydraConfig()
        }
        
        [enabledAction, disableAction].forEach { alertController.addAction($0) }
        
        self.present(alertController, animated: true, completion: nil)
    }
    
    private func restartConnectionWithFireshield() {
        stopVPN { _ in
            self.updateHydraConfigAndRestartIfNeeded()
        }
    }
    
    @IBAction func onDemandChanged(_ sender: UISwitch) {
        if self.isVpnConnected {
            stopVPN() { _ in
                self.set(onDemandEnabled: sender.isOn)
            }
        } else {
            set(onDemandEnabled: sender.isOn)
        }
    }

    private func set(onDemandEnabled: Bool) {
        let configuration = buildConfig(onDemandEnabled: onDemandEnabled, fireshieldMode: self.fireshieldMode)
        update(config: configuration)
    }

    private func update(config: HydraConfiguration) {
        do {
            try self.hydraClient.update(configuration: config)
        } catch {
            print("Unable to update configuration: \(error)")
        }
    }

    private func buildConfig(onDemandEnabled: Bool, fireshieldMode: FireshieldConfig.Mode) -> HydraConfiguration {
        let appDelegate = UIApplication.shared.delegate as! AppDelegate
        return appDelegate.configuration(onDemandEnabled: onDemandEnabled, fireshieldMode: fireshieldMode)
    }
    
    @IBAction func toggleFireshield(_ sender: UISwitch) {
        updateHydraConfigAndRestartIfNeeded()
    }
    
    
    func updateUi() {
        self.loginButton.setTitle(self.isLoggedIn ? "Log out" : "Log in", for: .normal)
        self.loginStatus.text = self.isLoggedIn ? "Logged in" : "Logged out"
        self.vpnSwitch.isOn = self.isVpnConnected || self.hydraClient.state == .connecting
        self.connectionStatus.text = self.isVpnConnected ? "\(self.statusString) [\(self.countryConnectedTo?.code ?? "???")]" : self.statusString
        self.countryLabel.text = self.country?.code ?? "Optimal"
        self.onDemandLabel.text = self.onDemandSwitch.isOn ? "On-demand enabled" : "On-demand disabled"
        switch self.hydraClient.state {
        case .connecting, .disconnecting:
            vpnSwitch.isEnabled = false
        default:
            vpnSwitch.isEnabled = true
        }
    }
    
    @objc func updateTrafficStats(completion: UpdateCompletion? = nil) {
        guard isVpnConnected else {
            completion?()
            return
        }
        
        hydraClient.getTrafficCounters { [unowned self] (counters) in
            guard let counters = counters else {
                self.completeUpdate(with: completion)
                return
            }
        
            let ul = ByteCountFormatter.string(fromByteCount: Int64(counters.transmitted), countStyle: .file)
            let dl = ByteCountFormatter.string(fromByteCount: Int64(counters.received), countStyle: .file)
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
                print("remainingTraffic success: \(String(describing: remainingTraffic))")
            }
            
            guard let traffic = remainingTraffic else {
                self.completeUpdate(with: completion)
                return
            }
            var string : String = ByteCountFormatter.string(fromByteCount: Int64(traffic.trafficRemaining), countStyle: .file)
            string += " of "
            string += ByteCountFormatter.string(fromByteCount: Int64(traffic.trafficUsageLimit), countStyle: .file)
            string += " remaining"
            self.trafficLimitLabel.text = string
            self.completeUpdate(with: completion)
        }
    }
    
    func countryChanged(newCountry: VirtualLocation) {
        self.country = newCountry
        updateUi()
    }
    
    //MARK: Fireshield
    
    private func updateHydraConfigAndRestartIfNeeded() {
        if self.isVpnConnected {
            stopVPN() { _ in
                self.updateHydraConfig()
                self.startVPN()
            }
        } else {
            self.updateHydraConfig()
            self.startVPN()
        }
    }

    
    private func restartVPN() {
        stopVPN { (e) in
            if let ex = e {
                print("Stop VPN error: \(ex)")
            } else {
                self.updateUi()
                self.startVPN()
            }
        }
    }
    
    private func startVPN() {
        self.hydraClient.start(location: country) { (e, _) in
            if let ex = e {
                print("Restart VPN error: \(ex)")
            } else {
                print("Restart VPN success, country: \(self.country?.code ?? "unknown")")
            }
            self.countryConnectedTo = self.country
            self.updateUi()
        }
    }
    
    private func stopVPN(completion: ((Error?) ->())? = nil) {
        hydraClient.stop { (e) in
            if let ex = e {
                print("Stop VPN error: \(ex)")
            } else {
                print("Stop VPN success")
            }
            completion?(e)
        }
    }
    
    private func updateHydraConfig() {
        let configuration = self.buildConfig(onDemandEnabled: onDemandSwitch.isOn, fireshieldMode: self.fireshieldMode)
        update(config: configuration)
    }
    
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
        
        hydraClient.requestScannedConnections { [unowned self] (error, connections) in
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

    @IBAction func hydraPreferencesValueChanged(_ sender: UISwitch) {
        func _updateHydraConfig(with props: (isVPN: Bool, isFireshield: Bool, isOnDemand: Bool) ) {

           set(onDemandEnabled: onDemandSwitch.isOn)

            print("Did update Hydra config")
        }

        guard sender == fireshieldSwitch || sender == onDemandSwitch || sender == vpnSwitch else {
            return
        }

        if (!hydraClient.isLoggedIn) {
            return
        }

        let isVPN = vpnSwitch.isOn
        let isFireshield = fireshieldSwitch.isOn
        let isOnDemand = onDemandSwitch.isOn

        let hydraConnectionState = self.hydraClient.state
        switch hydraConnectionState {
        case .disconnected, .invalid:
            _updateHydraConfig(with: (isVPN, isFireshield, isOnDemand))
        default:
            print("Ignore -connectButtonDidPress action")
            break
        }
    }

    @IBAction func connectButtonDidPress(_ sender: Any) {
        if (!hydraClient.isLoggedIn) {
            print("Login before starting a connection")
            return
        }

        let hydraConnectionState = self.hydraClient.state
        switch hydraConnectionState {
        case .connected:
            self.connectButton.isEnabled = false
            self.hydraClient.stop { [unowned self] error in
                self.connectButton.isEnabled = true
                guard error == nil else {
                    print("Failed to disconnect from Hydra. Error was: \(error!)")
                    self.updateUi()
                    return
                }
                self.updateUi()
            }
        case .disconnected, .invalid:
            self.connectButton.isEnabled = false
            self.hydraClient.start(location: self.country) { [unowned self] error, _ in
                self.connectButton.isEnabled = true
                guard error == nil else {
                    print("Failed to connect to Hydra. Error was: \(error!)")
                    self.updateUi()
                    return
                }
                print("Connected to Hydra with server location country code: \(self.country?.code ?? "<unknown>")")
                self.updateUi()
            }
        default:
            print("Ignore -connectButtonDidPress action")
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

