//
//  VPNConfigurator.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 26.01.2021.
//

import Foundation
import VPNApplicationSDK

class VPNConfigurator {
    static let willReconfigureNotification = Notification.Name("VPNConfigurator.willReconfigureNotification")
    static let didReconfigureNotification = Notification.Name("VPNConfigurator.didReconfigureNotification")

    static let willSwitchProtocolNotification = Notification.Name("VPNConfigurator.willSwitchProtocolNotification")
    static let didSwitchProtocolNotification = Notification.Name("VPNConfigurator.didSwitchProtocolNotification")

    static let shared = VPNConfigurator()

    private(set) var activeService: VPNService!
    private let configPreserver = VPNConfigurationPreserver()

    var currentMode: Mode {
        didSet {
            didSetCurrentMode(oldValue: oldValue)
        }
    }

    var isFireshiedEnabled: Bool {
        get {
            configPreserver.isFireshiedEnabled
        }
        set {
            if isFireshiedEnabled != newValue {
                configPreserver.isFireshiedEnabled = newValue
                reconfigureSDK()
            }
        }
    }

    var isBypassEnabled: Bool {
        get {
            configPreserver.isBypassEnabled
        }
        set {
            if isBypassEnabled != newValue {
                configPreserver.isBypassEnabled = newValue
                reconfigureSDK()
            }
        }
    }

    var isBypassSafeTrafficEnabled: Bool {
        get {
            configPreserver.isBypassSafeTrafficEnabled
        }
        set {
            if isBypassSafeTrafficEnabled != newValue {
                configPreserver.isBypassSafeTrafficEnabled = newValue
                reconfigureSDK()
            }
        }
    }

    var isDNSModeEnabled: Bool {
        get {
            configPreserver.isDNSModeEnabled
        }
        set {
            if isDNSModeEnabled != newValue {
                configPreserver.isDNSModeEnabled = newValue
                reconfigureSDK()
            }
        }
    }

    // MARK: - Initialization

    init() {
        currentMode = configPreserver.currentMode
        initSDK()
    }

    // MARK: - Private

    private func didSetCurrentMode(oldValue: Mode) {
        guard currentMode != oldValue else {
            return
        }

        configPreserver.currentMode = currentMode

        if let manualSwitchingSDK = activeService as? ManualSwitchingVPNSDK,
           let newProtocol = newProtocolForManualSwitch(oldMode: oldValue) {
            switchProtocol(to: newProtocol, using: manualSwitchingSDK)
        } else {
            reconfigureSDK()
        }
    }

    private func newProtocolForManualSwitch(oldMode: Mode) -> VPNProtocolType? {
        guard
            case .composed(let oldComposedMode) = oldMode,
            case .manual(let oldProtocol) = oldComposedMode,
            case .composed(let newComposedMode) = currentMode,
            case .manual(let newProtocol) = newComposedMode,
            oldProtocol != newProtocol
        else {
            return nil
        }
        return newProtocol
    }

    private func switchProtocol(to newProtocol: VPNProtocolType, using manualSwitchingSDK: ManualSwitchingVPNSDK) {
        NotificationCenter.default.post(
            name: Self.willSwitchProtocolNotification,
            object: nil
        )
        manualSwitchingSDK.switchToProtocol(newProtocol) { _, _ in
            NotificationCenter.default.post(
                name: Self.didSwitchProtocolNotification,
                object: nil
            )
        }
    }

    private func reconfigureSDK(completion: (() -> Void)? = nil) {
        NotificationCenter.default.post(
            name: Self.willReconfigureNotification,
            object: nil
        )
        guard let activeService = activeService else {
            performReinit(shouldReconnect: false, completion: completion)
            return
        }
        let shouldReconnect = (activeService.state == .connected)
        activeService.stop { [weak self] _ in
            self?.performReinit(shouldReconnect: shouldReconnect, completion: completion)
        }
    }

    private func performReinit(shouldReconnect: Bool, completion: (() -> Void)? = nil) {
        initSDK()
        guard shouldReconnect else {
            didReconfigureSDK(completion: completion)
            return
        }
        activeService.start(location: nil) { [weak self] _, _ in
            self?.didReconfigureSDK(completion: completion)
        }
    }

    private func didReconfigureSDK(completion: (() -> Void)?) {
        completion?()
        NotificationCenter.default.post(
            name: Self.didReconfigureNotification,
            object: nil
        )
    }

    private func initSDK() {
        switch currentMode {
        case .single(let currentProtocol):
            initSingleSDK(with: currentProtocol)
        case .composed(let composedMode):
            initComposedSDK(with: composedMode)
        }
    }

    private func initSingleSDK(with protocolType: VPNProtocolType) {
        switch protocolType {
        case .hydra:
            activeService = HydraSDK(configuration: makeHydraConfig())
        case .ipsec:
            activeService = IPSecSDK(configuration: makeIPSecConfig())
        @unknown default:
            break
        }
    }

    private func initComposedSDK(with composedMode: ComposedMode) {
        switch composedMode {
        case .manual(let selectedProtocol):
            activeService = ManualSwitchingVPNSDK(
                configuration: makeComposedSDK(),
                initialProtocolType: selectedProtocol
            )
        case .auto(let protocolPriority):
            guard let initialProtocol = protocolPriority.first else {
                return
            }
            let manualSwitchingSDK = ManualSwitchingVPNSDK(
                configuration: makeComposedSDK(),
                initialProtocolType: initialProtocol
            )
            activeService = AutoSwitchingVPNSDK(manualSwitchingSDK: manualSwitchingSDK, priorityProvider: { [weak self] in
                self?.autoProtocolPriority ?? []
            })
        }
    }

    private var autoProtocolPriority: [VPNProtocolType] {
        guard
            case .composed(let composedMode) = currentMode,
            case .auto(let priority) = composedMode
        else {
            return []
        }
        return priority
    }

    private func makeHydraConfig() -> HydraConfiguration {
        HydraConfiguration(
            hostURL: Self.hostURL,
            carrierID: Self.carrierID,
            extensionBundleID: Self.hydraProviderBundleID,
            groupID: Self.groupID,
            profileName: Self.profileName,
            debugLogging: true,
            fireshieldConfig: makeFireshieldConfig(),
            isBypassEnabled: isBypassEnabled,
            isVPNIconFixEnabled: true,
            tunnelDNSServers: ["8.8.8.8"]
        )
    }

    private func makeIPSecConfig() -> IPSecConfiguration {
        IPSecConfiguration(
            hostURL: Self.hostURL,
            carrierID: Self.carrierID,
            profileName: Self.profileName
        )
    }

    private func makeComposedSDK() -> ComposedConfiguration {
        ComposedConfiguration(
            hostURL: Self.hostURL,
            carrierID: Self.carrierID,
            extensionBundleID: Self.hydraProviderBundleID,
            groupID: Self.groupID,
            profileName: Self.profileName,
            fireshieldConfig: makeFireshieldConfig(),
            isBypassEnabled: isBypassEnabled,
            isVPNIconFixEnabled: true
        )
    }

    private func makeFireshieldConfig() -> FireshieldConfig {
        guard isFireshiedEnabled else {
            return FireshieldConfig(mode: .disabled)
        }
        let configuration = FireshieldConfig(mode: .vpn)
        configuration.isDNSModeEnabled = isDNSModeEnabled
        configuration.add(category: .block(category: .unsafe))
        let safeCategory: FireshieldCategory = isBypassSafeTrafficEnabled ? .bypass(category: .safe) : .proxy(category: .safe)
        configuration.add(category: safeCategory)
        return configuration
    }
}

// MARK: - Constants

private extension VPNConfigurator {
    static let hostURL = "https://backend.northghost.com"
    static let carrierID = "afdemo"
    static let hydraProviderBundleID = "com.pango.vpnsdk-demo.neprovider"
    static let groupID = "group.com.pango.vpnsdk-demo"
    static let profileName = "VPNSDK Demo"
}
