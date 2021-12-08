//
//  VPNConfigurationPreserver.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 26.01.2021.
//

import Foundation

class VPNConfigurationPreserver {
    private var defaults: UserDefaults {
        .standard
    }

    private lazy var decoder = JSONDecoder()
    private lazy var encoder = JSONEncoder()

    var currentMode: VPNConfigurator.Mode {
        get {
            guard
                let data = defaults.data(forKey: Key.currentMode),
                let mode = try? decoder.decode(VPNConfigurator.Mode.self, from: data)
            else {
                return .single(.hydra)
            }
            return mode
        }
        set {
            guard let data = try? encoder.encode(newValue) else {
                return
            }
            defaults.set(data, forKey: Key.currentMode)
        }
    }

    var isFireshiedEnabled: Bool {
        get {
            defaults.bool(forKey: Key.fireshieldEnabled)
        }
        set {
            defaults.set(newValue, forKey: Key.fireshieldEnabled)
        }
    }

    var isBypassEnabled: Bool {
        get {
            defaults.bool(forKey: Key.bypassEnabled)
        }
        set {
            defaults.set(newValue, forKey: Key.bypassEnabled)
        }
    }

    var isBypassSafeTrafficEnabled: Bool {
        get {
            defaults.bool(forKey: Key.bypassSafeTrafficEnabled)
        }
        set {
            defaults.set(newValue, forKey: Key.bypassSafeTrafficEnabled)
        }
    }

    var isDNSModeEnabled: Bool {
        get {
            defaults.bool(forKey: Key.dnsModeEnabled)
        }
        set {
            defaults.set(newValue, forKey: Key.dnsModeEnabled)
        }
    }
}

private extension VPNConfigurationPreserver {
    enum Key {
        static let currentMode = "vpn.configurator.current.mode"
        static let fireshieldEnabled = "fireshield.enabled"
        static let bypassSafeTrafficEnabled = "fireshield.bypass_safe.enabled"
        static let dnsModeEnabled = "fireshield.dns.enabled"
        static let bypassEnabled = "bypass.enabled"
    }
}
