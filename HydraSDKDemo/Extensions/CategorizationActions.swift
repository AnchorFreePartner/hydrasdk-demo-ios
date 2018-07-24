import HydraTunnelProviderSDK
import HydraApplicationSDK

public extension AFHydraCategorization {
    var actionEmoji: String {
        switch self.action {
        case .proxy:
            return "🅿️"
        case .VPN:
            return "🛡"
        case .bypass:
            return "✅"
        case .block:
            return "🛑"
        }
    }
}
