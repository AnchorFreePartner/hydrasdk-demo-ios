//
//  SDKViewController.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 27.01.2021.
//

import UIKit

class SDKViewController: UITableViewController, VPNViewProtocol {
    @IBOutlet private var vpnCells: [VPNCell]!

    // MARK: - Overrides

    override func viewDidLoad() {
        super.viewDidLoad()
        addNotificationObservers()
        prepareMode()
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        updateView()
    }

    // MARK: - Internal

    func updateView() {
        for cell in vpnCells {
            cell.updateView()
        }
    }

    func prepareMode() {

    }

    // MARK: - Private

    private func addNotificationObservers() {
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(didRequestViewUpdate),
            name: .didRequestViewUpdate,
            object: nil
        )

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(vpnStateDidChange),
            name: .vpnStateDidChange,
            object: nil
        )

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(sdkDidBecomeUnavailable),
            name: VPNConfigurator.willReconfigureNotification,
            object: nil
        )

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(sdkDidBecomeUnavailable),
            name: VPNConfigurator.willSwitchProtocolNotification,
            object: nil
        )

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(sdkDidBecomeAvailable),
            name: VPNConfigurator.didReconfigureNotification,
            object: nil
        )

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(sdkDidBecomeAvailable),
            name: VPNConfigurator.didSwitchProtocolNotification,
            object: nil
        )
    }

    @objc
    private func didRequestViewUpdate() {
        updateView()
    }

    @objc
    private func vpnStateDidChange() {
        updateView()
    }

    @objc
    private func sdkDidBecomeUnavailable() {
        viewState.isSDKUnavailable = true
        updateView()
    }

    @objc
    private func sdkDidBecomeAvailable() {
        viewState.isSDKUnavailable = false
        updateView()
    }
}
