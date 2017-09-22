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
    @IBOutlet weak var loginButton: UIButton!
    @IBOutlet weak var connectButton: UIButton!
    @IBOutlet weak var changeCountryButton: UIButton!
    @IBOutlet weak var loginStatus: UILabel!
    @IBOutlet weak var connectionStatus: UILabel!
    @IBOutlet weak var countryLabel: UILabel!
    @IBOutlet weak var trafficLimitLabel: UILabel!
    @IBOutlet weak var trafficStatsLabel: UILabel!
    
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
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.updateUi()
        
        hydraClient.notificationCenter.addObserver(forName: NSNotification.Name.AFVPNStatusDidChange, object: nil, queue: nil) { [unowned self] (notification) in
            self.updateUi()
            if self.isVpnConnected {
                self.updateTrafficStats()
                self.updateTrafficLimits()
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
    
    @IBAction func toggleConnect(_ sender: UIButton) {
        if !self.isVpnConnected {
            hydraClient.startVpn(with: self.country, completion: { (e) in
                if let ex = e {
                    print("Start VPN error: \(ex)")
                } else {
                    print("Start VPN success")
                }
            })
        } else {
            hydraClient.stopVpn({ (e) in
                if let ex = e {
                    print("Stop VPN error: \(ex)")
                } else {
                    print("Stop VPN success")
                }
            })
        }
    }
    
    @IBAction func changeCountry(_ sender: UIButton) {
        let controller = self.storyboard?.instantiateViewController(withIdentifier: "CountryController") as! CountryController
        controller.currentCountry = self.country
        controller.delegate = self
        self.present(controller, animated: true, completion: nil)
    }
    
    func updateUi() {
        self.loginButton.setTitle(self.isLoggedIn ? "Log out" : "Log in", for: .normal)
        self.loginStatus.text = self.isLoggedIn ? "Logged in" : "Logged out"
        self.connectButton.setTitle(self.isVpnConnected ? "Stop VPN" : "Start VPN", for: .normal)
        self.connectionStatus.text = self.statusString
        self.countryLabel.text = self.country?.countryCode ?? "Optimal"
    }
    
    @objc func updateTrafficStats() {
        if !isVpnConnected { return }
        hydraClient.trafficCounters { [unowned self] (e, counters) in
            guard let counters = counters else { return }
        
            let ul = ByteCountFormatter.string(fromByteCount: counters.bytesTx.int64Value, countStyle: .file)
            let dl = ByteCountFormatter.string(fromByteCount: counters.bytesRx.int64Value, countStyle: .file)
            let string = "UL: \(ul), DL: \(dl)"
            self.trafficStatsLabel.text = string
            self.perform(#selector(self.updateTrafficStats), with: nil, afterDelay: 2.0)
        }
    }
    
    func updateTrafficLimits() {
        self.hydraClient.remainingTraffic { (e, remainingTraffic) in
            if let ex = e {
                if ex.localizedDescription == "UNLIMITED" {
                    self.trafficLimitLabel.text = "Traffic is unlimited"
                } else {
                    print("remainingTraffic error: \(ex)")
                }
            } else {
                print("remainingTraffic success")
            }
            
            guard let traffic = remainingTraffic else { return }
            var string : String = ByteCountFormatter.string(fromByteCount: traffic.trafficRemaining.int64Value, countStyle: .file)
            string += " of "
            string += ByteCountFormatter.string(fromByteCount: traffic.trafficUsageLimit.int64Value, countStyle: .file)
            string += " remaining"
            self.trafficLimitLabel.text = string
        }
    }
    
    func countryChanged(newCountry: AFCountry) {
        self.country = newCountry
        updateUi()
    }
}

