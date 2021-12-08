//
//  VPNViewProtocol.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 27.01.2021.
//

import VPNApplicationSDK

protocol VPNViewProtocol: AnyObject {
    func updateView()
}

// MARK: - Internal

extension VPNViewProtocol {
    var configurator: VPNConfigurator {
        VPNConfigurator.shared
    }

    var vpnService: VPNService {
        configurator.activeService
    }

    var viewState: VPNViewState {
        VPNViewState.shared
    }

    func startVPN(completion: ((Error?) -> Void)? = nil) {
        viewState.isStartFlowInProgress = true
        postViewUpdateRequest()

        performStartVPN { error in
            self.viewState.isStartFlowInProgress = false
            self.postViewUpdateRequest()
            completion?(error)
        }
    }

    private func performStartVPN(completion: ((Error?) -> Void)?) {
        vpnService.login(method: .anonymous()) { [vpnService] loginError, _ in
            if let loginError = loginError {
                completion?(loginError)
                return
            }
            vpnService.start(location: nil) { startError, _ in
                completion?(startError)
            }
        }
    }

    func stopVPN(completion: ((Error?) -> Void)? = nil) {
        vpnService.stop { error in
            completion?(error)
        }
    }
}

// MARK: - Notifications

extension VPNViewProtocol {
    func postViewUpdateRequest() {
        NotificationCenter.default.post(name: .didRequestViewUpdate, object: nil)
    }
}

extension Notification.Name {
    static let didRequestViewUpdate = Self(rawValue: "didRequestViewUpdate")
}

// MARK: - View state

class VPNViewState {
    static let shared = VPNViewState()
    var isSDKUnavailable = false
    var isStartFlowInProgress = false
}
