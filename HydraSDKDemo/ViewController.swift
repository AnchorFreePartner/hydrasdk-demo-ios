//
//  ViewController.swift
//  HydraSDKDemo
//
//  Created by Igor Glotov on 9/21/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

import UIKit
import HydraApplicationSDK

class ViewController: UIViewController, CountryControllerProtocol {
    typealias UpdateCompletion = () -> ()
    @IBOutlet weak var loginButton: UIButton!
    @IBOutlet weak var changeCountryButton: UIButton!
    @IBOutlet weak var loginStatus: UILabel!
    @IBOutlet weak var connectionStatus: UILabel!
    @IBOutlet weak var vpnStateSwitch: UISwitch!
    @IBOutlet weak var onDemandSwitch: UISwitch!
    @IBOutlet weak var onDemandLabel: UILabel!
    @IBOutlet weak var countryLabel: UILabel!
    @IBOutlet weak var trafficLimitLabel: UILabel!
    @IBOutlet weak var trafficStatsLabel: UILabel!
    @IBOutlet weak var fireshieldSwitch: UISwitch!
    @IBOutlet weak var connectionsCountLabel: UILabel!
    
    private var isUpdatingScannedConnections: Bool = false
    
    var countryConnectedTo: AFCountry?
    
    var hydraClient : AFHydra {
        get {
            let appDelegate = UIApplication.shared.delegate as! AppDelegate
            return appDelegate.hydraClient
        }
    }
    
    var country : AFCountry? {
        get {
            guard let encodedData = UserDefaults.standard.data(forKey: "country") else { return nil }
            return NSKeyedUnarchiver.unarchiveObject(with: encodedData) as? AFCountry
        }
        set(newCountry) {
            let encodedData = NSKeyedArchiver.archivedData(withRootObject: newCountry as Any)
            UserDefaults.standard.set(encodedData, forKey: "country")
        }
    }
    
    var isVpnConnected: Bool {
        get {
            return hydraClient.vpnStatus() == .connected
        }
    }
    
    var isLoggedIn: Bool {
        get {
            return hydraClient.isLoggedIn()
        }
    }
    
    var statusString: String {
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
    
    private var fireshieldMode: AFConfigFireshieldMode {
        let flags = (isVpnConnected, isFireshieldEnabled)
        switch flags {
        case (false, true):
            return .enabledSilent
        case (true, true):
            return .enabledVPN
        default:
            return .disabled
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.updateUi()
        
        hydraClient.notificationCenter.addObserver(forName: NSNotification.Name.AFVPNStatusDidChange, object: nil, queue: nil) { [unowned self] (notification) in
            self.updateUi()
            if self.isVpnConnected {
                self.startUpdatingScannedConnections()
            }
            
            switch self.hydraClient.vpnStatus() {
            case .invalid, .undefined, .disconnected:
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
            hydraClient.logout({ [unowned self] (e) in
                if let ex = e {
                    print("Logout error: \(ex)")
                } else {
                    print("Logout success")
                }
                
                self.updateUi()
            })
        } else {
            hydraClient.login(AFAuthMethod.anonymous(), completion: { [unowned self] (e, user) in
                if let ex = e {
                    print("Login error: \(ex)")
                } else {
                    print("Login success")
                }
                
                self.updateUi()
            })
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
        stopVPN {
            self.updateHydraConfigAndRestartIfNeeded()
        }
    }
    
    @IBAction func onDemandChanged(_ sender: UISwitch) {
        if self.hydraClient.config.onDemand != sender.isOn && self.isVpnConnected {
            stopVPN()
        }
        
        self.hydraClient.config.onDemand = sender.isOn
    }
    
    @IBAction func toggleFireshield(_ sender: UISwitch) {
        updateHydraConfigAndRestartIfNeeded()
    }
    
    
    func updateUi() {
        self.loginButton.setTitle(self.isLoggedIn ? "Log out" : "Log in", for: .normal)
        self.loginStatus.text = self.isLoggedIn ? "Logged in" : "Logged out"
        self.vpnStateSwitch.isOn = self.isVpnConnected || self.hydraClient.vpnStatus() == .connecting
        self.connectionStatus.text = self.isVpnConnected ? "\(self.statusString) [\(self.countryConnectedTo?.countryCode ?? "???")]" : self.statusString
        self.countryLabel.text = self.country?.countryCode ?? "Optimal"
        self.onDemandLabel.text = self.onDemandSwitch.isOn ? "On-demand enabled" : "On-demand disabled"
        switch self.hydraClient.vpnStatus() {
        case .connecting, .disconnecting, .reconnecting:
            vpnStateSwitch.isEnabled = false
        default:
            vpnStateSwitch.isEnabled = true
        }
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
    
    func countryChanged(newCountry: AFCountry) {
        self.country = newCountry
        updateUi()
    }
    
    //MARK: Fireshield
    
    private func updateHydraConfigAndRestartIfNeeded() {
        self.updateHydraConfig()
        if !self.isVpnConnected {
            self.startVPN()
        } else {
            self.restartVPN()
        }
    }
    
    private func restartVPN() {
        hydraClient.stopVpn({ (e) in
            if let ex = e {
                print("Stop VPN error: \(ex)")
            } else {
                self.updateUi()
                self.startVPN()
            }
        })
    }
    
    private func startVPN() {
        self.hydraClient.startVpn({ (country, e) in
            if let ex = e {
                print("Restart VPN error: \(ex)")
            } else {
                print("Restart VPN success, country: \(country?.countryCode ?? "unknown")")
            }
            self.countryConnectedTo = country
            self.updateUi()
        })
    }
    
    private func stopVPN(completion: (() ->())? = nil) {
        hydraClient.stopVpn({ (e) in
            if let ex = e {
                print("Stop VPN error: \(ex)")
            } else {
                print("Stop VPN success")
            }
            completion?()
        })
    }
    
    private func updateHydraConfig() {
        self.hydraClient.updateConfig(AFConfig.init(block: { [weak self] (builder) in
            guard let `self` = self else { return }
            builder.fireshieldMode = self.fireshieldMode
        }))
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
}

