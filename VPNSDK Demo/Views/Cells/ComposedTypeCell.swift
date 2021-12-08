//
//  ComposedTypeCell.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 31.01.2021.
//

import UIKit

class ComposedTypeCell: VPNCell {
    var mode: VPNConfigurator.ComposedMode? {
        nil
    }

    override func updateView() {
        super.updateView()

        if case .composed(let composedMode) = configurator.currentMode, composedMode == mode {
            accessoryType = .checkmark
        } else {
            accessoryType = .none
        }

        isUserInteractionEnabled = !viewState.isSDKUnavailable &&
            (vpnService.state != .connecting) &&
            (vpnService.state != .disconnecting)
    }
}

class HydraComposedTypeCell: ComposedTypeCell {
    override var mode: VPNConfigurator.ComposedMode? {
        .manual(selectedProtocol: .hydra)
    }
}

class IPSecComposedTypeCell: ComposedTypeCell {
    override var mode: VPNConfigurator.ComposedMode? {
        .manual(selectedProtocol: .ipsec)
    }
}

class AutoComposedTypeCell: ComposedTypeCell {
    override var mode: VPNConfigurator.ComposedMode? {
        .auto(protocolPriority: [.hydra, .ipsec])
    }
}
