//
//  HydraConfigCells.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 31.01.2021.
//

import UIKit

class BypassCell: VPNCell {
    @IBOutlet private weak var enabledSwitch: UISwitch!

    override func updateView() {
        super.updateView()
        enabledSwitch.isOn = configurator.isBypassEnabled
    }

    @IBAction private func actionEnabledSwitchValueChanged() {
        configurator.isBypassEnabled = enabledSwitch.isOn
    }
}
