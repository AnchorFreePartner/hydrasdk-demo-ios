# Hydra SDK

Allows to manage VPN connection using custom Hydra protocol and use content categorization service named Fireshield.

## API Documentation

To see all available API, check [API Reference](APIReference.md).

## Table of Contents

- [Integration](#integration)
- [Configure HydraSDK](#configure-hydrasdk)
- [Connecting VPN and obtaining status](#connecting-vpn-and-obtaining-status)
- [Using On Demand mode](#using-on-demand-mode)
  - [On Demand and users with limited traffic](#on-demand-and-users-with-limited-traffic)
- [Categorization service (aka Fireshield)](#categorization-service-aka-fireshield)
  - [Create fireshield config](#create-fireshield-config)
  - [Fireshield configuration](#fireshield-configuration)
  - [Fireshield modes](#fireshield-modes)
  - [Monitoring](#monitoring)
- [Error Handling](#error-handling)
- [Crash Reporting](#crash-reporting)

## Integration

Hydra integration process consists of 2 steps:

1. [Setup application target](ApplicationSetup.md)
2. [Setup network extension target](HydraNetworkExtensionSetup.md)

## Start using HydraSDK

### Configure HydraSDK

To start using the SDK, you need to import `import VPNApplicationSDK` to your file under the application target. 

Initialize SDK using `HydraConfiguration`:

```swift
import VPNApplicationSDK    
// ...
    
let configuration = HydraConfiguration(hostURL: "HOST_URL",
                                       carrierID: "CARRIER_ID",
                                       extensionBundleID: "NETWORK_EXTENSION_BUNDLE_ID,
                                       groupID: "group.GROUP_ID",
                                       profileName: "PROFILE_NAME",
                                       fireshieldConfig: fireshieldConfig,
                                       isVPNIconFixEnabled: true,
                                       isOnDemandEnabled: true)

self.hydra = HydraSDK(configuration: configuration)
```

> **NOTE:** for macOS even though you don't need to enable App Groups, `groupId` property still has to have a value, starting with `group.`.

The best place to put initialization code is you AppDelegate's `application:didFinishLaunchingWithOptions:`.

After SDK is initialized, you need to login to be able to start VPN. If you are using OAuth authentication, provide your own OAuth dialogs UI and receive OAuth access token. Login example with OAuth token:

```swift
import VPNApplicationSDK
// ...

let hydra: HydraSDK
// ...

let authMethod = AuthMethod(type: .oauth, token: "OAUTH_TOKEN")

hydra.login(method: authMethod) { error, user in
    print("isLogged: \(error == nil)")
}
```

See `AuthMethod` reference for more authentication methods.

### Connecting VPN and obtaining status

To connect VPN use `HydraSDK` function `start(location:completion:)`. When VPN is started or an error occurred, completion handler will be called. To obtain VPN connection status you need to subscribe to `vpnStateDidChange` notification provided by SDK. For example:

```swift
NotificationCenter.default.addObserver(forName: .vpnStateDidChange, object: nil, queue: nil) { notification in
    // ...
}
```

When you receive notification, get updated VPN status from `HydraSDK` instance `state` property and handle this status as designed by your app.

You can also switch location using `applyLocationIfConnected(:completion:)` when VPN is in connected status. It will update location in the same network extension (without killing it and starting new one). This method will return error if VPN is not currently connected.

### Using On Demand mode

iOS and macOS, both provide an ability to connect to VPN automatically when certain (preconfigured) coditions are met. This functionality is called **On Demand**. 

Hydra SDK can be configured for On Demand mode with `HydraConfiguration` via `isOnDemandEnabled` and `onDemandRules` properties. The SDK could be initialized with this parameter.

#### On Demand and users with limited traffic

If your service provides limited traffic or a transport error occurs (e.g. credentials to VPN nodes are expired), current session will be killed with `VPNTunnelError` and corresponding code (for instance, `VPNTunnelError.HydraInternalErrorCode.trafficExceed` or `VPNTunnelError.HydraInternalErrorCode.tokenInvalid`). If On Demand mode conditions are met, the System will try to restart Network Extension process, until it is up and running. Due to NetworkExtension framework's limitation, it is not possible to disable On Demand mode from Custom Tunnel Provider extension upon receiving these errors. This makes System trying endlessly reconnect to VPN, while Network Extension is unable to provide VPN service due to the error.

In order to overcome this issue, Hydra SDK disables real tunneling, leaving Network Extension running in Bypass mode. By doing this, iOS can meet On Demand mode conditions while the traffic is routed locally, without VPN server. It means that user will have their real IP address and there will be no traffic protection.

Whenever app starts, it's highly recommended to check if VPN is connected and if user is out of traffic limit. In this case, it's necessary to disconnect current VPN session and optionally show user a message. To check if current VPN connection is running in Bypass mode read `HydraSDK`'s' `isBypassEnabled` property.

In order to catch situation when user is out of traffic without main app running, use `NetworkExtensionDelegate` callback methods.

### Categorization service (aka Fireshield)

Additionally to VPN services, Hydra SDK provides a content categorization service, namely Fireshield. When the SDK is configured to work with Fireshield enabled, the websites' URLs that user visits are checked agains a blacklist. If a website's URL is listed in the blacklist, the traffic to/from it is blocked, otherwise it is passed through. Hydra SDK provides API to configure Fireshield and monitor its work.

#### Create fireshield config

Categorization configuration based on specification of categories and rules for categories.

To create categories you can use one of factory methods of `FireshieldCategory` type:

* `FireshieldCategory.block(category: CategoryType) -> FireshieldCategory` - will create category, with action block(traffic gets blocked).
* `FireshieldCategory.proxy(category: CategoryType) -> FireshieldCategory` - will create category, with action proxy(traffic (encrypted) goes through the tunnel just as payload (for TCP only)).
* `FireshieldCategory.bypasss(category: CategoryType) -> FireshieldCategory` - will create category, with action bypass(traffic goes directly to its destination, without vpn tunnel).
* `FireshieldCategory.alert(category: CategoryType) -> FireshieldCategory` - will create category, with action block(traffic gets blocked) and redirection to Alert Page specified(works for http only).

To create category rules (which domains gets to specified category) you can use factory method of `FireshieldRule` type:

* `FireshieldRule.rule(withFileName: String, category: CategoryType)` - create category rules from file in the application bundle.
* `FireshieldRule.rule(withDomains: [String], category: CategoryType)` - create category rules from list of domains.

To addition to category file configuration it's possible to use online categorization services.

Possible values defined as constants in `FireshieldConfig` header file.

#### Fireshield configuration

Fireshield can be either disabled or enabled with particular mode. The mode is set with `fireshieldMode` property of `FireshieldConfig ` instance. You can pass respective config at the moment of `HydraSDK` initialization (e.g. during the application launch):

```swift
// ...

self.configuration = HydraConfiguration(
    hostURL: "HOST_URL",
    ...
    fireshieldConfig: configureFireshield(),
    ...
)

// Fireshield config example
private func makeFireshieldConfig() -> FireshieldConfig {
    guard isFireshiedEnabled else {
        // just return `.disabled` if you don't need Fireshield at all
        return FireshieldConfig(mode: .disabled)
    }

    let configuration = FireshieldConfig(mode: .vpn)
    fireshieldConfig.add(service: .bitdefender)

    // Indicates that Fireshield started in DNS-mode only, by default set to `false`
    configuration.isDNSModeEnabled = isDNSModeEnabled

    // Indicates that Fireshield should block resources from unsafe category
    configuration.add(category: .block(category: .unsafe))
    
    // Add needed behavior for safe category
    let safeCategory: FireshieldCategory = shouldBypassSafeTraffic ? .bypass(category: .safe) : .proxy(category: .safe)
    configuration.add(category: safeCategory)

    // Black and white lists
    do {
        let blacklistRule = try FireshieldRule.rule(withDomains: ["untrusted-domain.com"], category: .unsafe)
        let whitelistRule = try FireshieldRule.rule(withFileName: "whitelist.txt", category: .safe)
        config.add(rule: blacklistRule)
        config.add(rule: whitelistRule)
    } catch {
        print("Can't create Fireshield rule: \(error.localizedDescription)")
    }

    // Custom categories
    if shouldBlockSocialNetworks {
        config.add(category: .block(category: .custom("safe:socialnetworks")))
    }

    return configuration
}
```
    
##### Important note: You always need to add a safe category to FireshieldConfig to allow safe traffic. 
   
#### Fireshield modes

Fireshield can work in various modes, adding flexibility to your application. For instance, you can blend VPN and Fireshield functionality or hide VPN icon in iOS Status Bar. The modes are represented by `FireshieldMode` type.

* `disabled` — Fireshield is disabled.
* `enabled` — Fireshield is enabled. The VPN icon in Status Bar is displayed, however, the traffic does not go through VPN.
* `silent` — Fireshield is enabled but VPN icon in Status Bar is hidden. The traffic does not go through VPN.
* `vpn` — Blend Fireshield and VPN together. All traffic goes through VPN, while Fireshield blocks access to websites in the blacklist. The VPN icon is Status Bar is displayed. **Default value.**

##### Important note: Fireshield config settings may be overwritten by remote config.

#### Monitoring

Hydra SDK reports its content categorization service's work through `HydraSDK`'s `fireshieldScannedConnections(completion:)` and `lastCategorization` variable (available from Application part of the SDK) and `vpnDidHandleCategorization(_ categorization: VPNCategorization)` of `NetworkExtensionDelegate` (available from Network Extension part of the SDK).

Call `fireshieldScannedConnections(completion:)` to receive number of network connection that have been scanned.

Subscribe to `.hydraCategorizationDidChange` notification. The notification will be sent on every categorization done by the SDK. Check `lastCategorization` variable to get the latest result of categorization upon receiving `.hydraCategorizationDidChange` notification. Alternativelly, read the notification's `userInfo` under `hydraCategorization` key.

Implement `vpnDidHandleCategorization(_ categorization: VPNCategorization)` delegate method in your `NetworkExtensionDelegate` to get the categorization result of latest connection. Hydra SDK will automatically call back on every new categorization being processed. 

> *NOTE:* Because Network Extension process is running when Fireshield is enabled, even when the application is suspended by user or terminated by iOS, `vpnDidHandleCategorization(_ categorization: VPNCategorization)` is a good place to schedule User Notifications. By doing this, users can be notified when particular resource is blocked by Fireshield. Remember, that User Notification permissions have to be obtained via the application before they can be scheduled by Network Extension. For more information, see [Local and Remote Notifications Overview](https://developer.apple.com/library/content/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/).

### Error Handling

Most of the `HydraSDK` calls are accepting completion blocks with errors. If an error occurs, you will receive non-nil `Error` object with an explanation. Errors could be handled by code, that is defined in `APIError`.

If you are just disconnected from VPN session, you could also check `lastTunnelError` property, if there was an error during initialization or session management system disconnected VPN remotely, there will be `VPNTunnelError` case here. You can handle such errors and report if appropriate.

### Crash Reporting

Some project might consider crash reporting integration (such as, [Crashlytics](https://try.crashlytics.com)) for Network Extension side. If your crash reporting framework supports Application Extensions and requires additional code to setup it, put the configuration code inside `NetworkExtensionDelegate`'s `-init` override:

```swift
import VPNTunnelProviderSDK

class ProviderDelegate: NSObject, NetworkExtensionDelegate {
    override init() {
        Fabric.with([Crashlytics.self])
    }
}
```
