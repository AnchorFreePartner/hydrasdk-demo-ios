//
//  IPSecViewController.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 27.01.2021.
//

import UIKit

class IPSecViewController: SDKViewController {
    override func prepareMode() {
        configurator.currentMode = .single(.ipsec)
    }
}
