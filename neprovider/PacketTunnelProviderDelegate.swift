//
//  PacketTunnelProvider.swift
//  neprovider
//
//  Created by Igor Glotov on 9/21/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

import HydraTunnelProviderSDK
import UserNotifications

class PacketTunnelProviderDelegate: NSObject {
    private let categorizationProcess = CategorizationProcessor()
}

extension PacketTunnelProviderDelegate: AFNetworkExtensionDelegate {
    func vpnWillStart() {
        print("Reporing vpnWillStart")
    }

    func vpnDidStart() {
        print("Reporing vpnDidStart")
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


    func resourceBlocked(_ categorization: AFHydraCategorization!) {
        if Preferences.isFireshieldNotificationsEnabled {
            categorizationProcess.process(categorization)
        }
    }
}
