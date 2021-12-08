//
//  VPNStateCell.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 27.01.2021.
//

import UIKit

class VPNStateCell: VPNCell {
    @IBOutlet private weak var stateLabel: UILabel!
    @IBOutlet private weak var stateSwitch: UISwitch!

    // MARK: - Overrides

    override func updateView() {
        super.updateView()
        setupStateLabel()
        setupStateSwitch()
    }

    // MARK: - Private

    private func setupStateLabel() {
        if viewState.isStartFlowInProgress {
            stateLabel.text = "Connecting..."
            return
        }
        switch vpnService.state {
        case .idle, .invalid, .disconnected:
            stateLabel.text = "Not connected"
        case .connected:
            stateLabel.text = "Connected"
        case .disconnecting:
            stateLabel.text = "Disconnecting..."
        case .connecting:
            stateLabel.text = "Connecting..."
        @unknown default:
            break
        }
    }

    private func setupStateSwitch() {
        if viewState.isStartFlowInProgress {
            stateSwitch.setOn(true, animated: true)
            stateSwitch.isEnabled = false
            return
        }
        switch vpnService.state {
        case .disconnected, .idle, .invalid:
            stateSwitch.isOn = false
            stateSwitch.isEnabled = true
        case .connected:
            stateSwitch.isOn = true
            stateSwitch.isEnabled = true
        case .connecting:
            stateSwitch.setOn(true, animated: true)
            stateSwitch.isEnabled = false
        case .disconnecting:
            stateSwitch.setOn(false, animated: true)
            stateSwitch.isEnabled = false
        @unknown default:
            break
        }
        if viewState.isSDKUnavailable {
            stateSwitch.isEnabled = false
        }
    }

    // MARK: - Actions

    @IBAction private func actionStateSwitchValueChanged() {
        switch vpnService.state {
        case .disconnected, .idle, .invalid:
            startVPN()
        case .connected:
            stopVPN()
        default:
            break
        }
    }
}
