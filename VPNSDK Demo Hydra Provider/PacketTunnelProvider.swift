//
//  PacketTunnelProvider.swift
//  VPNSDK Demo Hydra Provider
//
//  Created by Dan Vasilev on 26.01.2021.
//

import VPNTunnelProviderSDK

class PacketTunnelProvider: NSObject, NetworkExtensionDelegate {
    private let categorizationProcessor = CategorizationProcessor.default()

    var fireshieldManager: FireshieldManager?

    func vpnDidHandleCategorization(_ categorization: VPNCategorization) {
        categorizationProcessor.process(categorization)
    }
}
