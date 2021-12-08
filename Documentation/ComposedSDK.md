# Composed SDK

Allows to use different VPN protocols inside one app and switch between them more easily.

## API Documentation

To see all available API, check [API Reference](APIReference.md).

## Table of Contents

- [Integration](#integration)
- [Manual switching SDK](#manual-switching-sdk)
  - [Configure manual switching SDK](#configure-manual-switching-sdk)
  - [Switch VPN protocol manually](#switch-vpn-protocol-manually)
- [Auto switching SDK](#auto-switching-sdk)
  - [Configure auto switching SDK](#configure-auto-switching-sdk)
- [Loggin in](#loggin-in)
- [Connecting VPN and obtaining status](#connecting-vpn-and-obtaining-status)
- [Active VPN protocol autocorrection](#active-vpn-protocol-autocorrection)
- [Hydra features](#hydra-features)

## Integration

Composed SDK currently working with 2 VPN protocols under the hood: Hydra and IPSec. So intergation process requires setup for both protocols and includes 2 steps:

1. [Setup application target](ApplicationSetup.md)
2. [Setup Hydra network extension target](HydraNetworkExtensionSetup.md)

## Start using Composed SDK

There are 2 ways how you can use Composed SDK: manual protocol switching (through `ManualSwitchingVPNSDK`) and auto switching (through `AutoSwitchingVPNSDK`).

### Manual switching SDK

Manual switching SDK provides ability to change VPN protocol at any moment by user requirement.

#### Configure manual switching SDK

To start using the SDK, you need to import `import VPNApplicationSDK` to your file under the application target. 

Initialize SDK using `ComposedConfiguration`:

```swift
import VPNApplicationSDK
// ...
    
let configuration = ComposedConfiguration(hostURL: "HOST_URL",
                                          carrierID: "CARRIER_ID",
                                          extensionBundleID: "NETWORK_EXTENSION_BUNDLE_ID,
                                          groupID: "group.GROUP_ID",
                                          profileName: "PROFILE_NAME",
                                          fireshieldConfig: fireshieldConfig,
                                          isVPNIconFixEnabled: true,
                                          isOnDemandEnabled: true)

let initialProtocolType = VPNProtocolType.hydra // This protocol will be set as active after SDK init

self.composedSDK = ManualSwitchingVPNSDK(configuration: configuration, initialProtocolType: initialProtocolType)
```

The best place to put initialization code is you AppDelegate's `application:didFinishLaunchingWithOptions:`.

#### Switch VPN protocol manually

You can use `func switchToProtocol(_ newProtocolType: VPNProtocolType, completion: ((_ error: Error?, _ activeSDK: VPNSDK?) -> Void)?)` method to change VPN protocol. If VPN is connected at the moment of call, it will be stopped and then reconnected to the same location after protocol change. This method also provides logic that helps to resolve some annoying problems related to protocols changing (e.g., unwanted **On Demand** functionality from old protocol).

### Auto switching SDK

Auto switching SDK modifies VPN start flow in a way when it can fallback to different VPN protocols depending on provided protocol priority.

#### Configure auto switching SDK

Auto switching SDK is build upon manual switching SDK and uses it to switch between VPN protocols when needed. So you should initialize `ManualSwitchingVPNSDK` and use it with priority provider as parameters for `AutoSwitchingVPNSDK` init:

```swift
import VPNApplicationSDK
// ...
    
let manualSwitchingSDK = // ...

// This closure will be called at the beginning of start flow to determine
// vpn protocols order
let priorityProvider: AutoSwitchingVPNSDK.PriorityProvider = {
	return [.hydra, .ipsec]
}

self.composedSDK = AutoSwitchingVPNSDK(manualSwitchingSDK: manualSwitchingSDK, priorityProvider: priorityProvider)
```

### Loggin in

After SDK is initialized, you need to login to be able to start VPN. If you are using OAuth authentication, provide your own OAuth dialogs UI and receive OAuth access token. Login example with OAuth token:

```swift
import VPNApplicationSDK
// ...

let composedSDK: ManualSwitchingVPNSDK // or AutoSwitchingVPNSDK
// ...

let authMethod = AuthMethod(type: .oauth, token: "OAUTH_TOKEN")

composedSDK.login(method: authMethod) { error, user in
    print("isLogged: \(error == nil)")
}
```

See `AuthMethod` in API reference for more authentication methods.

### Connecting VPN and obtaining status

To connect VPN you can use function `start(location:completion:)` (the same as for standalone Hydra and IPSec SDKs). When VPN is started or an error occurred, completion handler will be called. To obtain VPN connection status you need to subscribe to `vpnStateDidChange` notification provided by SDK. For example:

```swift
NotificationCenter.default.addObserver(forName: .vpnStateDidChange, object: nil, queue: nil) { notification in
    // ...
}
```

When you receive notification, get updated VPN status from SDK instance `state` property and handle this status as designed by your app.

### Active VPN protocol autocorrection

Sometimes you can face situation when value of active protocol type inside SDK became out of sync with actual active protocol type (for example, if you've set active protocol to `.hydra`, but then user started IPSec connection from iOS settings). In such cases SDK will automatically change value of active protocol type to the actual value.

### Detection of protocol change

You can observe VPN protocol changes (both manual and auto) by subscribing to `vpnProtocolDidChange` notification. When you receive notification, get updated protocol type from  `activeProtocolType` SDK instance property.

### Hydra features

You can use all additional Hydra functionality like Fireshield through Composed SDK API, but it will work only if current VPN connection uses Hydra protocol. To read more about Hydra capabilities, check [Hydra documentation page](#Hydra.md).
