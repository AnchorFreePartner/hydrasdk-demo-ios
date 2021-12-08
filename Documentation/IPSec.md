# IPSec SDK

Allows to use default Apple implementation of IPSec (IKEv2).

## API Documentation

To see all available API, check [API Reference](APIReference.md).

## Table of Contents

- [Integration](#integration)
- [Configure IPSecSDK](#configure-ipsecsdk)
- [Connecting VPN and obtaining status](#connecting-vpn-and-obtaining-status)
- [Using On Demand mode](#using-on-demand-mode)
- [Error Handling](#error-handling)

## Integration

IPSec SDK intergations process includes just one step, [application target setup](ApplicationSetup.md). If you're planning to use IPSec protocol only, you don't need to setup network extension target. 

## Start using IPSecSDK

### Configure IPSecSDK

To start using the SDK, you need to import `import VPNApplicationSDK` to your file under the application target. 

Initialize SDK using `IPSecConfiguration`:

```swift
import VPNApplicationSDK    
// ...
    
let configuration = IPSecConfiguration(hostURL: "HOST_URL",
                                       carrierID: "CARRIER_ID",
                                       isOnDemandEnabled: true,
                                       profileName: "PROFILE_NAME")

self.ipsec = IPSecSDK(configuration: configuration)
```

The best place to put initialization code is you AppDelegate's `application:didFinishLaunchingWithOptions:`.

After SDK is initialized, you need to login to be able to start VPN. If you are using OAuth authentication, provide your own OAuth dialogs UI and receive OAuth access token. Login example with OAuth token:

```swift
import VPNApplicationSDK
// ...

let ipsec: IPSecSDK
// ...

let authMethod = AuthMethod(type: .oauth, token: "OAUTH_TOKEN")

ipsec.login(method: authMethod) { error, user in
    print("isLogged: \(error == nil)")
}
```

See `AuthMethod` reference for more authentication methods.

### Connecting VPN and obtaining status

To connect VPN use `IPSecSDK` function `start(location:completion:)`. When VPN is started or an error occurred, completion handler will be called. To obtain VPN connection status you need to subscribe to `vpnStateDidChange` notification provided by SDK. For example:

```swift
NotificationCenter.default.addObserver(forName: .vpnStateDidChange, object: nil, queue: nil) { notification in
    // ...
}
```

When you receive notification, get updated VPN status from `IPSecSDK` instance `state` property and handle this status as designed by your app.

### Using On Demand mode

iOS and macOS, both provide an ability to connect to VPN automatically when certain (preconfigured) coditions are met. This functionality is called **On Demand**. 

IPSec SDK can be configured for On Demand mode with `IPSecConfiguration` via `isOnDemandEnabled` and `onDemandRules` properties. The SDK could be initialized with this parameter.

### Error Handling

Most of the `IPSecSDK` calls are accepting completion blocks with errors. If an error occurs, you will receive non-nil `Error` object with an explanation.
