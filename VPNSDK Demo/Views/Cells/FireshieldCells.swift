//
//  FireshieldEnabledCell.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 31.01.2021.
//

import UIKit

class FireshieldEnabledCell: VPNCell {
    @IBOutlet private weak var enabledSwitch: UISwitch!

    override func updateView() {
        super.updateView()
        enabledSwitch.isOn = configurator.isFireshiedEnabled
    }

    @IBAction private func actionEnabledSwitchValueChanged() {
        configurator.isFireshiedEnabled = enabledSwitch.isOn
    }
}

class DNSModeCell: VPNCell {
    @IBOutlet private weak var enabledSwitch: UISwitch!

    override func updateView() {
        super.updateView()
        enabledSwitch.isOn = configurator.isDNSModeEnabled
        enabledSwitch.isEnabled = configurator.isFireshiedEnabled
    }

    @IBAction private func actionEnabledSwitchValueChanged() {
        configurator.isDNSModeEnabled = enabledSwitch.isOn
    }
}

class BypassSafeTrafficCell: VPNCell {
    @IBOutlet private weak var enabledSwitch: UISwitch!

    override func updateView() {
        super.updateView()
        enabledSwitch.isOn = configurator.isBypassSafeTrafficEnabled
        enabledSwitch.isEnabled = configurator.isFireshiedEnabled
    }

    @IBAction private func actionEnabledSwitchValueChanged() {
        configurator.isBypassSafeTrafficEnabled = enabledSwitch.isOn
    }
}
