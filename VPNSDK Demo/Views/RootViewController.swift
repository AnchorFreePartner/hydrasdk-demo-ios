//
//  RootViewController.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 26.01.2021.
//

import UIKit
import VPNApplicationSDK

class RootViewController: UITableViewController {
    @IBOutlet private weak var versionLabel: UILabel!

    override func viewDidLoad() {
        super.viewDidLoad()
        versionLabel.text = "VPNSDK v\(VPNSDK.sdkVersion())"
    }
}
