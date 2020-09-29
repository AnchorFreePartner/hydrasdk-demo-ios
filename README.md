# Hydra VPN SDK for iOS

HydraSDK for iOS and macOS provides client API to authorize users and connect them to backend VPN services.

Changelog:

- [HydraSDK for iOS ](https://raw.githubusercontent.com/AnchorFreePartner/hydrasdk-demo-ios/master/CHANGELOG.md)

Download latest SDK:

[HydraSDK for iOS](https://firebasestorage.googleapis.com/v0/b/web-portal-for-partners.appspot.com/o/products%2FVPNSDK%20iOS%203.1.5.zip?alt=media&token=e91d7308-e881-4331-8712-fb4128b74cf6)

[HydraSDK for macOS](https://firebasestorage.googleapis.com/v0/b/web-portal-for-partners.appspot.com/o/products%2FVPNSDK%20macOS%203.1.1.zip?alt=media&token=17c0f5d5-199)

# Prerequisites

* Requires iOS 10+ or macOS 10.12+
* Xcode 10.2.1

# Setup

### Creating Network Extension

To start application development, you need to create a Xcode iOS/macOS application project. 

Once the application is created, go to *Project > Targets*, and in menu bar select *Editor > Add Target*. Choose *Network Extension*, provide the name and bundle ID for this [**Network Extension**](https://developer.apple.com/reference/networkextension) target. 

Set `NSExtensionPrincipalClass` in `NSExtension` dictionary of `Info.plist` to `AFHydraTunnelProvider`, also add new key to a plist root: `AFNetworkExtensionDelegate` with a value that is your VPN Delegate class. For example, if your delegate named VPNDelegate, then the value would be `$(PRODUCT_MODULE_NAME).VPNDelegate`

At the end of this step, you have to have at least two targets: 
* **Application** target
* **Network Extension** target

Read more about [Creating a Packet Tunnel Provider Extension](https://developer.apple.com/reference/networkextension/nepackettunnelprovider#2110153) from Apple docs.

### Configure Build Settings

For both, the **Application** and the **Network Extension** targets, do the following

1. Add *NetworkExtension* system framework to your project dependencies

2. In your project: *Project > Build Settings*:
- Set *Enable Bitcode* to "NO"
- [Set](https://developer.apple.com/library/content/qa/qa1490/_index.html) *Other Linker Flags* to `$(OTHER_LDFLAGS) -ObjC`.

### Add HydraSDK

The SDK consists of two frameworks:
* **VPNApplicationSDK.framework** (*iOS*) or **VPNApplicationSDKmacOS.framework** (*macOS*) for **Application** target
* **VPNTunnelProviderSDK.framework** (*iOS*) or **VPNTunnelProviderSDKmacOS.framework** (*macOS*) for **Network Extension** target

To integrate VPNSDSK into your project, do the following:

1. Add ** VPNSDK.framework** (or **VPNApplicationSDKmacOS.framework** for macOS) to the Xcode project, and add this framework to your **Application** target. 
2. Add **VPNTunnelProviderSDK.framework** (or **VPNTunnelProviderSDKmacOS.framework** for macOS) to your project and then add this framework to your **Network Extension** target. 
3. Make sure both of these frameworks are properly added by going to *Project > General*, and double-checking that frameworks are in place under *Embedded Binaries* and *Linked Frameworks and Libraries* section of respective targets.
4. Link **libz.tbd** and **libresolv.tbd** libraries to the **Network Extension** target 

### Subclassing Packet Tunnel Provider

After the **Network Extension** target is created, you should observe that new class is added to your project (file *PacketTunnelProvider.swift*). Go to the *PacketTunnelProvider.swift* and make this class implement `AFNetworkExtensionDelegate` instead of `NEPacketTunnelProvider`. It should now look like:
    
    import VPNTunnelProviderSDK

	class ProviderDelegate : NSObject, AFNetworkExtensionDelegate {
	  // ...
    }

Remove Xcode-generated empty `PacketTunnelProvider`'s implementation.

### Implementing 

### Configure App ID

It is required to have two separate application IDs created on Apple Developer Portal, one for the **Application** target and other for the **Network Extension** target. 

In the *Certificates, Identifiers & Profiles* section of the [developer web site](https://developer.apple.com/), when you add or edit an App ID, you’ll see *Network Extensions* service.  You should enable that service in your App ID:

#### iOS

Make sure *iOS, tvOS, watchOS* filter is selected and create (if not yet created) two application IDs under *Identifiers > App IDs* section.

Also, enable the following services for both IDs:
* App Groups (this will be configured in the next step)
* Network Extensions
* Personal VPN

#### macOS

Select *macOS* filter and create (if not yet created) two application IDs under *Identifiers > App IDs* section.

Enable the following services for both IDs:
* Network Extensions
* Personal VPN

#### iOS & macOS

> **NOTE:** It is recommended to give distinctive names to your App IDs, for example:
> * MyApp Application
> * MyApp NetworkExtension

### Creating App Group 

#### iOS

Since HydraSDK is mostly a Network Extension you also have to create an App Group and provide group ID to the SDK to allow Hydra to interact with Packet Tunnel Provider Extension. See [Adding an App to an App Group](https://developer.apple.com/library/content/documentation/Miscellaneous/Reference/EntitlementKeyReference/Chapters/EnablingAppSandbox.html#//apple_ref/doc/uid/TP40011195-CH4-SW19) for more information about how to create app group. 

You need to assign this group to both, the **Application** and the **Network Extension** targets and App IDs.

#### macOS

For *macOS* this step is not needed.

### Enabling Capabilities

For both, **Application**  and **Network Extension** targets, go to *Project > Capabilities* and Enable the following capabilities:

#### iOS

* Personal VPN
* Network Extensions
* App Groups

#### macOS

* App Sandbox
  * Incoming Connections (Server)
  * Outgoing Connections (Client)
* Personal VPN
* Network Extensions
  * Packet Tunnel

#### iOS & macOS

> **NOTE:** Make sure that respective **.entitlement** files are added to the project for both, **Application**  and **Network Extension** targets.

### Re/Generate Provision Profiles

Application and Network Extension, both have to have its respective Provision Profiles generated from the Developer Portal. When creating and/or regenerating Provision Profiles, make sure you select Network Extension entitlement.

> **NOTE:** The Provision Profiles' Network Extension entitlements must corresponds to Network Extension entitlements configured through Xcode's project Capabilities tab. If there is a missconfiguration between the two, VPN connection will not be established.

#### macOS

> **NOTE:** On the Mac, Developer ID apps cannot host Network Extension providers. Only Mac App Store apps can host Network Extension providers. That's why, you cannot create a Developer ID Provision Profile with Network Extension entitlements attached to it.

# Start using HydraSDK

### Configure HydraSDK

To start using the SDK, you need to import `import VPNApplicationSDK` to your file under the application target. 

To initialize Hydra do the following:

    import VPNApplicationSDK    
    	 // ...
    
	self.configuration = HydraConfiguration(hostURL: "HOST_URL",
                                        carrierID: "CARRIER_ID",
                                        extensionBundleID: "NETWORK_EXTENSION_BUNDLE_ID,
                                        groupID: "group.GROUP_ID",
                                        profileName: "PROFILE_NAME"
                                        fireshieldConfig: fireshieldConfig,
                                        isVPNIconFixEnabled: true,
                                        isOnDemandEnabled: true)

	self.hydra = HydraSDK(configuration: configuration!)
                                                

> **NOTE:** for macOS even though you don't need to enable App Groups, `groupId` property still has to have a value, starting with `group.`.

The best place to put initialization code is you AppDelegate's `application:didFinishLaunchingWithOptions:`.

After SDK is initialized, you need to login to be able to start VPN. If you are using OAuth authentication, provide your own OAuth dialogs UI and receive OAuth access token. Login example with OAuth token:

    import VPNApplicationSDK    
    // ...
    let hydra: HydraSDK
    // ...
    
	let authMethod = AuthMethod(type: .oauth, token: "OAUTH_TOKEN")
        hydra.login(method: authMethod) { (error, user) in
            print("isLogged: \(error == nil)")
        }

See `AuthMethod` reference for more authentication methods.

### Connecting VPN and obtaining status

To connect VPN use HydraDSK function `start(location: VirtualLocation?, completion: StateCompletion?)`. When VPN is started or an error occurred, completion will be called. To obtain VPN connection status you need to subscribe to the default `NSNotificationCenter`. For example:

        NotificationCenter.default.addObserver(forName: .HydraStatusDidChange, object: nil, queue: nil) { notification in
        }

When you receive notification, get updated VPN status from `HydraSDK` instance status property and handle this status as designed by your app.

### Using On Demand mode

iOS and macOS, both provide an ability to connect to VPN automatically when certain (preconfigured) coditions are met. This functionality is called "On Demand". 

Hydra SDK can be configured for On Demand mode with `HydraConfiguration` via `onDemand` property. The SDK could be initialized with this parameter.

#### On Demand and users with limited traffic

If your service provides limited traffic or a transport error occurs (e.g. credentials to VPN nodes are expired), current session will be killed with `AFHydraErrorCode` code (for instance, `AFHydraErrorCodeTrafficExceed` or `AFHydraErrorCodeTokenInvalid`). If On Demand mode conditions are met, the System will try to restart Network Extension process, until it is up and running. Due to NetworkExtension framework's limitation, it is not possible to disable On Demand mode from Custom Tunnel Provider extension upon receiving these errors. This makes System trying endlessly reconnect to VPN, while Network Extension is unable to provide VPN service due to the error.

In order to overcome this issue, Hydra SDK dissables real tunneling, leaving Network Extension running in Bypass mode. By doing this, iOS can meet On Demand mode conditions while the traffic is routed locally, without VPN server. It means that user will have their real IP address and there will be no traffic protection.

Whenever app starts, it's highly recommended to check if VPN is connected and if user is out of traffic limit. In this case, it's necessary to disconnect current VPN session and optionally show user a message. To check if current VPN connection is running in Bypass mode read `HydraSDSK`'s' `isBypassEnabled` property.

In order to catch situation when user is out of traffic without main App running, see `AFNetworkExtensionDelegate` documentation.

### Categorization service (aka Fireshield)

Additionally to VPN services, Hydra SDK provides a content categorization service, namely Fireshield. When the SDK is configured to work with Fireshield enabled, the websites' URLs that user visits are checked agains a blacklist. If a website's URL is listed in the blacklist, the traffic to/from it is blocked, otherwise it is passed through. Hydra SDK provides API to configure Fireshield and monitor its work.

#### Create fireshield config

Categorization configuration based on specification of categories and rules for categories

To create categories you can use one of factory methods of `FireshieldCategory` class

* `FireshieldCategory.block(category: CategoryType) -> FireshieldCategory` - will create category, with action block(traffic gets blocked)
* `FireshieldCategory.proxy(category: CategoryType) -> FireshieldCategory` - will create category, with action proxy(traffic (encrypted) goes through the tunnel just as payload (for TCP only))
* `FireshieldCategory.bypasss(category: CategoryType) -> FireshieldCategory` - will create category, with action bypass(traffic goes directly to its destination, without vpn tunnel)
* `FireshieldCategory.alert(category: CategoryType) -> FireshieldCategory` - will create category, with action block(traffic gets blocked) and redirection to Alert Page specified(works for http only)

To create category rules(which domains gets to specified category) you can use factory method of `FireshieldRule` class

* `FireshieldRule.rule(withFileName: String, category: CategoryType)` - create category rules from file in the application bundle

* `FireshieldRule.rule(withDomains: [String], category: CategoryType)` - create category rules from list of domains

To addition to category file configuration its possible to use online categorization services

Possible values defined as constants in `FireshieldConfig` header file

#### Fireshield configuration

Fireshield can be either disabled or enabled with particular mode. The mode is set with `fireshieldMode` property of `FireshieldConfig ` instance. Initialize `HydraSDSK` instance with respective config (e.g. during the application launch):

    // ...
    
   	self.configuration = HydraConfiguration(hostURL: "HOST_URL",
											...
                                            fireshieldConfig: configureFireshield(),
                                            ...)

	private func configureFireshield() -> FireshieldConfig {
	    let fireshieldConfig = FireshieldConfig(mode: .vpn)

        fireshieldConfig.add(category: FireshieldCategory.alert(category: .unsafe))
        fireshieldConfig.add(category: FireshieldCategory.proxy(category: .safe))
        fireshieldConfig.add(service: .bitdefender)
        
        fireshieldConfig.add(rule: .rule(withDomains: ["unsafedomain.com"], category: .unsafe))
        
        return fireshieldConfig
    }
    
##### Important note: You always need to add a safe category to FireshieldConfig to allow safe traffic. 
   
#### Modes

Fireshield can work in various modes, adding flexibility to your application. For instance, you can blend VPN and Fireshield functionality or hide VPN icon in iOS Status Bar. The modes are represented by `AFConfigFireshieldMode` type.

* `disabled` — Fireshield is disabled.
* `enabled` — Fireshield is enabled. The VPN icon in Status Bar is displayed, however, the traffic does not go through VPN.
* `silent` — Fireshield is enabled but VPN icon in Status Bar is hidden. The traffic does not go through VPN.
* `vpn` — Blend Fireshield and VPN together. All traffic goes through VPN, while Fireshield blocks access to websites in the blacklist. The VPN icon is Status Bar is displayed. **Default value.**

##### Important note: Fireshield config settings may be overwritten by remote config.

#### Monitoring

Hydra SDK reports its content categorization service's work through `HydraSDK`'s `requestScannedConnections(completion: @escaping (Error?, UInt?) -> ())` and `lastCategorization` variable (available from Application part of the SDK) and `resourceBlocked(_ categorization: AFHydraCategorization!)` of `AFNetworkExtensionDelegate` (available from Network Extension part of the SDK).

Call `requestScannedConnections(completion: @escaping (Error?, UInt?)` to receive number of network connection that have been scanned.

Subscribe to `.HydraCategorizationDidChange` notification. The notification will be sent on every categorization done by the SDK. Check `lastCategorization` variable to get the latest result of categorization upon receiving `.HydraCategorizationDidChange` notification. Alternativelly, ready the notification's `userInfo` under `categorization` key.

Implement  `resourceBlocked(_ categorization: AFHydraCategorization!)` delegate method in your `AFNetworkExtensionDelegate` to get the categorization result of latest connection. Hydra SDK will automatically call back on every new categorization being processed. 

> *NOTE:* Because Network Extension process is running, when Fireshield is enabled, while an application may be suspended by user and subsequently terminated by iOS, `resourceBlocked(_ categorization: AFHydraCategorization!)` is a good place to schedule User Notificaions. By doing this, users can be notified when particular resource is blocked by Fireshield. Remember, that User Notification permissions have to be obtained via the application before they can be scheduled by Network Extension. For mo information, see [Local and Remote Notifications Overview](https://developer.apple.com/library/content/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/).


### Error Handling

Most of the `HydraSDK` calls are accepting completion blocks with errors. If an error occurs, you will receive non-nil `Error` object with an explanation. Errors could be handled by code, that is defined in `APIError`.

If you are just disconnected from VPN session, you could also check `lastError` property, if there was an error during initialization or session management system disconnected VPN remotely, there will be `Error` object here. You must handle such errors and report if appropriate.

### Crash Reporting

Some project might consider crash reporting integration (such as, [Crashlytics](https://try.crashlytics.com)) for Network Extension side. If your crash reporting framework supports Application Extensions and requires additional code to setup it, put the configuration code inside `AFNetworkExtensionDelegate`'s `-init` override:

    import VPNTunnelProviderSDK

	class ProviderDelegate : NSObject, AFNetworkExtensionDelegate {
    	override init() {
       	  Fabric.with([Crashlytics.self])
    	}
    }



# API Documentation

### HydraSDK

`public var trafficCounters: TrafficCounters?`
Retrieve current traffic counters.

`public var isLoggedIn: Bool`  
Check if user has logged in.

`public var connectedDate: Date?`  
Date when VPN connection is established  

`public var state: VPNState`  
State of VPN connection

`public var deviceID: String`  
DeviceID representation

`public var isBypassEnabled: Bool`  
Indicates if bypass is enabled or not

`public static func sdkVersion() -> String`  
Version of SDK 

`public var lastError: Error?`  
Obtain last error that occured in current/last session.

`public init(configuration: HydraConfiguration)`  

Main constructor and factory. HydraSDK instance should be a singleton instance. Use HydraConfiguration object instance to initialize HydraSDK.

`public func login(method: AuthMethod, completion: @escaping UserCompletion)`  
Login and obtain User object that describes Hydra VPN user.

` public func logout(completion: @escaping LogoutCompletion)`  
Log out.

`public func virtualLocations(completion: @escaping VirtualLocationsCompletion)`  
Retrieve a list of available countries to connect to. Returns `[VirtualLocation]`

` public func remainingTraffic(completion: @escaping RemainingTrafficCompletion)`  
Retrieve current traffic limits.

`public func installProfile(completion: @escaping ProfileCompletion)`
Triggers iOS VPN subsystem to create/update VPN profile, showing user permission "Allow / Don't Allow" dialog.
Calling this method is not required. Useful for custom tutorial implementation.
**NOTE**: If you're using onDemand VPN feature, this installed profile **WILL** be triggered by system and VPN will be enabled.

`public func start(location: VirtualLocation?, completion: @escaping StateCompletion)`  
Start VPN to automagically chosen server. On first VPN connection, SDK will ask user to Allow or Deny VPN connection. Use your VirtualLocation object from `virtualLocations` function to specify which server country to use or use `nil` to use optimal virtual location.

`public func stop(completion: @escaping StateCompletion)`  
Stop VPN.

`public func purchase(purchaseToken: String?, type: String, completion: @escaping PurchaseCompletion)`  
Validates purchase with current backend.

`public func update(configuration: HydraConfiguration) throws`
Update Hydra configuration without creating a new instance of HydraDSK. **NOTE** Configuration can't be updated if the connection is started, you need to call `stopVPN` function before updating configuration, otherwise `VPNSDKError.notPermitted` exception will be thrown. Please note if you want to change the main parameters of configuration (`hostURL`, `carrierID`, `extensionBundleID`, `groupID`), you need to create new instance `HydraSDK` with this configuration, otherwise `VPNSDKError.configurationMismatch` the exception will be thrown.

### AuthMethod

`public static func anonymous() -> AuthMethod`  
Default auth method that does not require any authentication.

Use `public init(type: AuthMethodType, token: String?)` initializator if you wish to use different auth method.

### AuthMethodType

`case oauth`  
Most popular OAuth authentication method. OAuth flow should be implemented by your application. After finishing OAuth flow and obtaining OAuth access token, provide it to AuthMethod init function like this:
`AuthMethod(type: .oauth, token: "OAUTH_TOKEN")`

`case facebook`  
Authenticate with Facebook SDK.

`case google`  
Authenticate with Google SDK.

`case twitter`
Authenticate with Twitter SDK.

`case github`
Authenticate with GitHub SDK.

`case firebase`
Authenticate with Firebase SDK.

`case custom(String)`  
Custom auth. If you are using custom authentication scheme, use this case.

### HydraConfiguration

`HydraConfiguration ` is a struct that configures `HydraDSK` instance.

`public let hostURL: String`  
This is a Host URL of the primary server. Provided by Anchorfree Inc.

`public let carrierID: String`  
This is your unique service identifier. Provided by Anchorfree Inc.

`public let extensionBundleID: String`  
Network Extension target's Bundle Identifier. See Project > [YOUR_TARGET] > Bundle Identifier for more info.

`public let groupID: String`  
App Group ID that is created for the current application.

`public let isBypassEnabled: Bool`  
Enable bypass mode. See Appendix for more information about the bypass.

`public let profileName: String`
Sets the name for VPN profile that is visible in Settings > General > VPN (Title of profile, subtitle will always be the application name).

`public let debugLoggingEnabled: Bool`  
Enable or disable debug logging. **Don't forget to disable for release build!**

`public let serverAddressDisplayName: String?`
Sets the name for VPN server address that is visible in Settings > General > VPN (Server field).

` public let dnsAddress: String?`  
Your preferred DNS server to use. If not set, a default one will be used.

`public let bypassDomains: [String]?`
A list of domains to bypass VPN. Wildcards accepted. 
Example: `["*google.com"]` // Google domain and it's subdomains will be accessed directly, without VPN.

`public let isOnDemandEnabled: Bool`
Enables On Demand VPN feature. VPN will be triggered automatically by the System after `startVPN` is triggered. Calling `stop` from application is required to disable On Demand VPN. If VPN connection could not be established because of network environment or interrupted by out of traffic error code, then VPN will switch to bypass mode automatically until user reconnects VPN from main application, VPN icon will not be visible in the status bar. 

### User

Describes VPN user.

`public let accessToken: String?`  
HydraSDK access token.

`public let subscriber: Subscriber`  
Subscription information.

### Subscriber

Describes User's subscription information.

`public let subscriberID: Int`  
Subscriber identifier.

`public let activatedDevices: Int`  
Subscriber activated devices.

`public let activeSessions: Int`  
Subscriber active sessions.

`public let name: String`  
Subscriber name.

`public let carrierID: String`  
Subscriber carrier ID.

`public let socialProfiles: [String : String]`  
Subscriber hash of social profiles with information.


`public let bundle: Bundle`  
Subscription bundle.

### Bundle

Describes subscription bundle information.

`public let licenseName: String`  
Name of User's license.

`public let bundleID: Int`  
Name of a purchased bundle.

`public let devicesLimit: Int`  
Number of devices limit.

`public let sessionsLimit: Int`  
Number of sessions limit.

### VirtualLocation

Describes VPN server location information

`public let code: String`  
VPN server country location

`public let serversCount: Int`  
Amount of VPN servers available in this location.

`public let groupName: String`  
Name of private server group name (could be empty).

### TrafficCounters

`public let received: UInt64`  
Bytes received in current session

`public let transmitted: UInt64`  
Bytes transmitted in current session

### RemainingTraffic

`public let sessionStartTime: UInt64`  
UNIX timestamp when current session was started.

`public let trafficUsageLimit: UInt64`  
Amount of bytes available to current User

`public let trafficUsed: UInt64`  
Amount of bytes User utilized.

`public let trafficRemaining: UInt64`  
Amount of bytes that is available to User.

## AFNetworkExtensionDelegate

Your app's Network Extension provider must implement this protocol. In order to be able to track certain actions like VPN start or errors inside Network Extension, following functions can be overriden:

`- (void)vpnWillStartWithOptions:;` // Called right before VPN start attempt  
`- (void)vpnDidStart;` // Called after successful VPN start  
`- (void)vpnError:(NSError *)error;` // Called when VPN error occured. Do not call long-running async operations here as the process will shut down  
`- (void)resourceBlocked:(AFHydraCategorization *)categorization;` // Caled when resource is blocked by Fireshield  
`- (void)vpnDataCounterDidUpdate:(AFHydraDataCounter *)dataCounter;` // Called when VPN traffic counters did update  
`- (void)vpnWillStopWith:(nonnull void(^)(BOOL restart))completion;` // Called when an error has occurred during the VPN connection until the completion callback will be called Hydra will run in the killswitch mode.   

## Error codes

### AFAPIError

`undefined` This is a generic unknown error, please report such errors to developers.  
`sessionExceed`  Amount of allowed sessions for this user is exceed.  
`trafficExceed` Amount of allowed traffic for this user is exceed.  
`unauthorized` This user is unauthorized or login operation is still pending. 
`userSuspended` This user is suspended.  
`vpnServerUnavailable` Selected server or country code is not available.  
`internalServerError` Server was unable to fetch credentials for this country code.  
`deviceExceed` The amount of allowed devices for this user is exceed.  
`networkError` The Internets are not available or network request has failed. Feel free to try again.  
`invalidPurchase` The purchase could be validated.  
`unknownServerResponse` This response could mean you don't have latest HydraSDK. Please report to   developers.  
`notAuthorized` The token of user is expired.   

### AFNetworkExtensionDelegate

Error domain: `AFHydraDomain`

`AFHydraErrorCodeTimeout` VPN timeout
`AFHydraErrorCodeIllegalState` VPN is not established due to application error
`AFHydraErrorCodeConnectionDisrupted` VPN connection disrupted by broken network connection
`AFHydraErrorCodeConnectionNotEstablished` VPN client can't connect to VPN node
`AFHydraErrorCodeTrafficExceed` VPN connection disrupted because the user is out of traffic. NOTE: If `ondemand` feature is used, VPN will be switched to `bypass` mode until user disconnects VPN connection from the application.

# Appendix

# Integration Checklist & Troubleshooting

The configuration of iOS application with HydraSDK could be quite complex since there is a lot to configure. That's why we've created following checklist that should help you to verify correct integration.

- Make sure that you've created Network extension
- **VPNApplicationSDK.framework** is added to the Application target, **VPNTunnelProviderSDK.framework** is added to the Extension target
- **libz.tbd** and **libresolv.tbd** added to the Extension target
- *Enable Bitcode* is set to "No" and `-ObjC` is present in "Other linker flags" for both targets
- You have created and enabled App Groups (General > Capabilities) for both targets, active App Group is set to "builder.groupId" (App Groups is enabled for both bundle ids (Application and Extension) in Apple Developer Portal)
- Personal VPN (General > Capabilities) is enabled for both targets (Personal VPN is enabled for both bundle ids (Application and Extension) in Apple Developer Portal)
- You have added Network Extension (iOS) entitlement for both Application and Extension provisioning profiles
- `HydraSDK` instance is configured with correct `groupID`, `extensionBundleID`
