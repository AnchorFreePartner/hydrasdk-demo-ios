import Foundation

final class Preferences {
    static let sharedUserDefaults = UserDefaults.shared
    
    class var isFireshieldNotificationsEnabled: Bool {
        get {
            return sharedUserDefaults.bool(forKey: "pref-enable-fireshield-user-notifications-key")
        }
        set {
            #if NETWORK_EXTENSION_TARGET
            assert(false, "setter is disallowed for network extension target")
            #endif
            sharedUserDefaults.set(newValue, forKey: "pref-enable-fireshield-user-notifications-key")
            sharedUserDefaults.synchronize()
        }
    }
}

fileprivate extension UserDefaults {
    class var shared: UserDefaults {
        get {
            return UserDefaults(suiteName: "group.com.anchorfree.HydraTestApp")!
        }
    }
}
