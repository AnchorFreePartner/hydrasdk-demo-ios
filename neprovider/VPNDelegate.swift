//
//  PacketTunnelProvider.swift
//  neprovider
//
//  Created by Igor Glotov on 9/21/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

import NetworkExtension
import HydraTunnelProviderSDK
import UserNotifications

class VPNDelegate : NSObject, AFNetworkExtensionDelegate {
    func vpnWillStart() {
        print("Reporing VPN will start...")
    }
    
    func vpnDidStart() {
        print("VPN did start! Yay!")
    }
    
    func vpnError(_ error: Error!) {
        let nserror = error as NSError
        print("Oops, it's a VPN error code \(nserror.code)")
        
        let content = UNMutableNotificationContent()
        content.title = "VPN Event"
        content.body = "VPN error: \(nserror.description)"
        
        let request = UNNotificationRequest(identifier: "vpnError", content: content, trigger: nil)
        UNUserNotificationCenter.current().removeAllPendingNotificationRequests()
        UNUserNotificationCenter.current().add(request) {(error) in
            if let error = error {
                print("Uh oh! We had an error: \(error)")
            }
        }
    }
}
