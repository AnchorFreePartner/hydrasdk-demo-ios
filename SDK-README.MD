# HydraSDK for iOS & macOS

HydraSDK for iOS and macOS provides client API to authorize users and connect them to backend VPN services.

Changelog:

- [HydraSDK for iOS & macOS changelog](https://raw.githubusercontent.com/AnchorFreePartner/hydrasdk-demo-ios/master/SDK-CHANGELOG.MD)

Download latest SDK: 

- [HydraSDK for iOS](https://firebasestorage.googleapis.com/v0/b/web-portal-for-partners.appspot.com/o/products%2FHydraSDK%20iOS%200.4.14.zip?alt=media&token=136bd098-72f5-44b5-9ac3-653d563e0976)

- [HydraSDK for macOS](https://firebasestorage.googleapis.com/v0/b/web-portal-for-partners.appspot.com/o/products%2FHydra%20macOS%20SDK_v0_4_10.zip?alt=media)

# Prerequisites

* Requires iOS 9+ or macOS 10.12+
* Xcode 9.3

# Setup

### Creating Packet Tunnel Provider Extension

To start application development, you need to create a Xcode iOS/macOS application project. 

Once the application is created, go to *Project > Targets*, and in menu bar select *Editor > Add Target*. Choose *Packet Tunnel Provider Extension*, provide the name and bundle ID for this [**Network Extension**](https://developer.apple.com/reference/networkextension) target. 

> **NOTE:** Xcode 8.2 and newer do not have this template, [see the workaround on Apple Developer Forum](https://forums.developer.apple.com/message/187336#187336).

At the end of this step, you have to have at least two targets: 
* **Application** target
* **Network Extension** target

Read more about [Creating a Packet Tunnel Provider Extension](https://developer.apple.com/reference/networkextension/nepackettunnelprovider#2110153) from Apple docs.

### Configure Build Settings

For both, the **Application** and the **Network Extension** targets, do the following

1. Add these system frameworks to your project dependencies:
- NetworkExtension
- Security
- libz.tbd

2. In your project: *Project > Build Settings*:
- Set *Enable Bitcode* to "NO"
- [Set](https://developer.apple.com/library/content/qa/qa1490/_index.html) *Other Linker Flags* to `$(OTHER_LDFLAGS) -ObjC`.

### Add HydraSDK

The SDK consists of two frameworks:
* **HydraApplicationSDK.framework** (*iOS*) or **HydraApplicationSDKmacOS.framework** (*macOS*) for **Application** target
* **HydraTunnelProviderSDK.framework** (*iOS*) or **HydraTunnelProviderSDKmacOS.framework** (*macOS*) for **Network Extension** target

To integrate HydraSDK into your project, do the following:

1. Add **HydraApplicationSDK.framework** (or **HydraApplicationSDKmacOS.framework** for macOS) to the Xcode project, and add this framework to your **Application** target. 
2. Add **HydraTunnelProviderSDK.framework** (or **HydraTunnelProviderSDKmacOS.framework** for macOS) to your project and then add this framework to your **Network Extension** target. 
3. Make sure both of these frameworks are properly added by going to *Project > General*, and double-checking that frameworks are in place under *Linked Frameworks and Libraries* section of respective targets.

### Subclassing Packet Tunnel Provider

After the **Network Extension** target is created, you should observe that new class is added to your project (file *PacketTunnelProvider.h*/*.m*). Go to the *PacketTunnelProvider.h* (which extends `NETunnelProvider`) and make this class extends `AFPacketTunnelProvider` instead of `NETunnelProvider`. It should now look like:

#import <HydraTunnelProviderSDK/HydraTunnelProviderSDK.h>
@interface PacketTunnelProvider : AFPacketTunnelProvider
// ...
@end

Remove Xcode-generated empty `PacketTunnelProvider`'s implementation inside *.m* file.

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

To start using the SDK, you need to import `#import <HydraApplicationSDK/HydraApplicationSDK.h>` to your file under the application target. Alternatively, you could import only required headers.

To initialize Hydra do the following:

#import <HydraApplicationSDK/AFHydra.h>
#import <HydraApplicationSDK/AFConfig.h>

// ...

self.hydraClient = [AFHydra withConfig:[AFConfig configWithBlock:^(AFConfigBuilder \*builder) {
builder.baseUrl = @"MY_HOST_URL";
builder.carrierId = @"MY_CARRIER_ID";
builder.groupId = @"group.MY_APP_GROUP";
builder.networkExtensionBundleId = @"BUNDLE_ID";
builder.vpnProfileName = @"YOUR_VPN_PROFILE_NAME";
}]];

> **NOTE:** for macOS even though you don't need to enable App Groups, `groupId` property still has to have a value, starting with `group.`.

The best place to put initialization code is you AppDelegate's `application:didFinishLaunchingWithOptions:`.

After SDK is initialized, you need to login to be able to start VPN. If you are using OAuth authentication, provide your own OAuth dialogs UI and receive OAuth access token. Login example with OAuth token:

#import <HydraApplicationSDK/HydraApplicationSDK.h>
// ...
@property (nonatomic, strong, nonnull) AFHydra *hydraClient;

// ...

[self.hydraClient login:[AFAuthMethod OAuth:@"OAUTH_ACCESS_TOKEN"]
completion:^(NSError *error, AFUser *user) {
NSLog(@"App login success: %d", error == nil);
}];

See `AFAuthMethod` reference for more authentication methods.

### Connecting VPN and obtaining status

To connect VPN use AFHydra function `startVpn:(nullable void (^)(NSError * __nullable error))completion`. When VPN is started or an error occurred, completion will be called. To obtain VPN connection status you need to subscribe to the default `NSNotificationCenter`. For example:

[[NSNotificationCenter defaultCenter] addObserver:self
selector:@selector(connectionChanged:)
name:AFVPNStatusDidChangeNotification
object:nil];

When you receive notification, get updated VPN status from `AFHydra` instance status property and handle this status as designed by your app.

### Using On Demand mode

iOS and macOS, both provide an ability to connect to VPN automatically when certain (preconfigured) coditions are met. This functionality is called "On Demand". 

Hydra SDK can be configured for On Demand mode with `AFConfig` via `onDemand` property. The SDK could be initialized with this parameter or this property can be changed at any time before VPN connection (via `-updateConfig:` of `AFHydra`).

#### On Demand and users with limited traffic

If your service provides limited traffic or a transport error occurs (e.g. credentials to VPN nodes are expired), current session will be killed with `AFHydraErrorCode` code (for instance, `AFHydraErrorCodeTrafficExceed` or `AFHydraErrorCodeTokenInvalid`). If On Demand mode conditions are met, the System will try to restart Network Extension process, until it is up and running. Due to NetworkExtension framework's limitation, it is not possible to disable On Demand mode from Custom Tunnel Provider extension upon receiving these errors. This makes System trying endlessly reconnect to VPN, while Network Extension is unable to provide VPN service due to the error.

In order to overcome this issue, Hydra SDK dissables real tunneling, leaving Network Extension running in Bypass mode. By doing this, iOS can meet On Demand mode conditions while the traffic is routed locally, without VPN server. It means that user will have their real IP address and there will be no traffic protection.

Whenever app starts, it's highly recommended to check if VPN is connected and if user is out of traffic limit. In this case, it's necessary to disconnect current VPN session and optionally show user a message. To check if current VPN connection is running in Bypass mode read `AFHydra`'s' `isBypassEnabled` property.

In order to catch situation when user is out of traffic without main App running, see `AFNetworkExtensionDelegate` documentation.

See Demo application project for code examples.

### Categorization service (aka Fireshield)

Additionally to VPN services, Hydra SDK provides a content categorization service, namely Fireshield. When the SDK is configured to work with Fireshield enabled, the websites' URLs that user visits are checked agains a blacklist. If a website's URL is listed in the blacklist, the traffic to/from it is blocked, otherwise it is passed through. Hydra SDK provides API to configure Fireshield and monitor its work.

#### Create fireshield config

Categorization configuration based on specification of categories and rules for categories

To create categories you can use one of factory methods of `AFFireshieldCategory` class

* `+ (AFFireshieldCategory *)block:(AFFireshieldCategories)category;` - will create category, with action block(traffic gets blocked)
* `+ (AFFireshieldCategory *)proxy:(AFFireshieldCategories)category;` - will create category, with action proxy(traffic (encrypted) goes through the tunnel just as payload (for TCP only))
* `+ (AFFireshieldCategory *)bypass:(AFFireshieldCategories)category;` - will create category, with action bypass(traffic goes directly to its destination, without vpn tunnel)
* `+ (AFFireshieldCategory *)alert:(AFFireshieldCategories)category;` - will create category, with action block(traffic gets blocked) and redirection to Alert Page specified(works for http only)

To create category rules(which domains gets to specified category) you can use factory method of `AFFireshieldRule` class

`+ (instancetype)fileRule:(NSString *)fileName withCategory:(AFFireshieldCategories)category;` - create category rules from file in the application bundle

To addition to category file configuration its possible to use online categorization services

Possible values defined as constants in `AFFireshieldConfig.h` header file

#### Fireshield configuration

Fireshield can be either disabled or enabled with particular mode. The mode is set with `fireshieldMode` property of `AFFireshieldConfig` instance. Initialize `AFHydra` instance with respective config (e.g. during the application launch):

[AFHydra withConfig:[AFConfig configWithBlock:^(AFConfigBuilder *builder) {
/////
AFFireshieldConfig *fireshieldConfig = [[AFFireshieldConfig alloc] initWithFireshieldMode:AFConfigFireshieldModeEnabledVPN];

AFFireshieldCategory *safeCategory = [AFFireshieldCategory bypass:AFFireshieldCategorySafe]; //need to add safe category to allow safe traffic
AFFireshieldCategory *unsafeCategory = [AFFireshieldCategory alert:AFFireshieldCategoryUnsafe];
AFFireshieldRule *safeRule = [AFFireshieldRule fileRule:@"bitdefender-whitelist.txt" withCategory:AFFireshieldCategorySafe];

[fireshieldConfig addCategory:safeCategory];
[fireshieldConfig addCategory:unsafeCategory];
[fireshieldConfig addRule:safeRule];
[fireshieldConfig addService:AFFireshieldServiceBitdefender];

builder.fireshieldConfig = fireshieldConfig;
////
}]];

##### Important note: You always need to add a safe category to FireshieldConfig to allow safe traffic. 

Later, during runtime, Fireshield mode can be changed or disabled at all. Because `AFHydra` is already instanciated at this time, `AFHydra`'s `- (BOOL)updateConfig:(AFConfig *)config` function has to be used instead. Pass an `AFConfig` instance where `fireshieldConfig.fireshieldMode` is set to desired value. If VPN state is `.connected`, before updating the configuration, VPN should be stopped. Then, VPN can be started again. After sucessfull start, Hydra SDK will work in respective Fireshield mode. 

[hydraClient updateConfig:[AFConfig configWithBlock:^(AFConfigBuilder *builder) {
builder.fireshieldMode = AFConfigFireshieldModeDisabled;
}];

> *NOTE:* Only `fireshieldMode` and `onDemand` are supported currently with `- (BOOL)updateConfig:(AFConfig *)config`. Updating other parameter has not effect.

#### Modes

Fireshield can work in various modes, adding flexibility to your application. For instance, you can blend VPN and Fireshield functionality or hide VPN icon in iOS Status Bar. The modes are represented by `AFConfigFireshieldMode` type.

* `.disabled` — Fireshield is disabled.
* `.enabled` — Fireshield is enabled. The VPN icon in Status Bar is displayed, however, the traffic does not go through VPN.
* `.enabledSilent` — Fireshield is enabled but VPN icon in Status Bar is hidden. The traffic does not go through VPN.
* `.enabledVPN` — Blend Fireshield and VPN together. All traffic goes through VPN, while Fireshield blocks access to websites in the blacklist. The VPN icon is Status Bar is displayed. **Default value.**

##### Important note: Fireshield config settings may be overwritten by remote config.

#### Monitoring

Hydra SDK reports its content categorization service's work through `AFHydra`'s `getScannedConnections(_ completion: @escaping (UInt, Error?)` and `lastCategorization()` (available from Application part of the SDK) and `resourceBlocked(_ categorization: AFHydraCategorization!)` of `AFNetworkExtensionDelegate` (available from Network Extension part of the SDK).

Call `getScannedConnections(_ completion: @escaping (UInt, Error?)` to receive number of network connection that have been scanned.

Subscribe to `AFVPNCategorizationDidChange` notification. The notification will be sent on every categorization done by the SDK. Call `lastCategorization()` to get the latest result of categorization upon receiving `AFVPNCategorizationDidChange` notification. Alternativelly, ready the notification's `userInfo` under `categorization` key.

Implement  `resourceBlocked(_ categorization: AFHydraCategorization!)` delegate method in your `AFNetworkExtensionDelegate` to get the categorization result of latest connection. Hydra SDK will automatically call back on every new categorization being processed. 

> *NOTE:* Because Network Extension process is running, when Fireshield is enabled, while an application may be suspended by user and subsequently terminated by iOS, `resourceBlocked(_ categorization: AFHydraCategorization!)` is a good place to schedule User Notificaions. By doing this, users can be notified when particular resource is blocked by Fireshield. Remember, that User Notification permissions have to be obtained via the application before they can be scheduled by Network Extension. For mo information, see [Local and Remote Notifications Overview](https://developer.apple.com/library/content/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/).


### Error Handling

Most of the `AFHydra` calls are accepting completion blocks with errors. If an error occurs, you will receive non-nil `NSError` object with an explanation. Errors could be handled by code, that is defined in `AFHydraApiErrorCode`. See *AFHydra.h* for more info.

If you are just disconnected from VPN session, you could also check `hydraClient.lastError` property, if there was an error during initialization or session management system disconnected VPN remotely, there will be `NSError` object here. You must handle such errors and report if appropriate.

### Crash Reporting

Some project might consider crash reporting integration (such as, [Crashlytics](https://try.crashlytics.com)) for Network Extension side. If your crash reporting framework supports Application Extensions and requires additional code to setup it, put the configuration code inside `AFNetworkExtensionDelegate`'s `-init` override:

@interface MYNEDelegate : NSObject <AFNetworkExtensionDelegate>

- (instancetype)init {
self = [super init];
if (self) {
[Fabric with:@[[Crashlytics class]]];
// ...
}
return self;
}

// ...

@end



# API Documentation

### AFHydra

`@property (strong, nonatomic, nullable, readonly) AFTrafficCounters *trafficCounters;`
Retrieve current traffic counters.

`- (nonnull instancetype)initWithConfig:(AFConfig * __nonnull)config;`
`+ (nonnull instancetype)withConfig:(AFConfig * __nonnull)config;`

Main constructor and factory. AFHydra instance should be a singleton instance. Use AFConfig object instance to initialize HydraSDK. The fastest way to create AFConfig object instance is to use `[AFConfig configWithBlock:]`.

`- (BOOL)updateConfig:(AFConfig *)config;`  
Update Hydra configuration without restarting VPN session. **NOTE** Only `fireshieldMode` and `onDemand` are supported currently. Updating other parameter has not effect.

`- (void)login:(AFAuthMethod * __nonnull)method completion:(nonnull AFHydraLoginCompletion)completion;`  
Login and obtain AFUser object that describes Hydra VPN user.

`- (void)logout:(nonnull AFHydraLogoutCompletion)completion;`  
Log out.

`- (BOOL)isLoggedIn;`  
Check if user has logged in.

`- (void)availableCountries:(nonnull AFHydraCountriesCompletion)completion;`  
Retrieve a list of available countries to connect to. Returns `NSArray <AFCountry *>.`

`- (void)remainingTraffic:(nonnull AFHydraRemainingTrafficCompletion)completion;`  
Retrieve current traffic limits.

`- (void)installVpnProfile:(nullable void (^)(NSError *__nullable))completion;`
Triggers iOS VPN subsystem to create/update VPN profile, showing user permission "Allow / Don't Allow" dialog.
Calling this method is not required. Useful for custom tutorial implementation.
**NOTE**: If you're using onDemand VPN feature, this installed profile **WILL** be triggered by system and VPN will be enabled.

`- (void)startVpn:(nullable void (^)(AFCountry *__nullable country, NSError *__nullable error))completion;`  
Start VPN to automagically chosen server. On first VPN connection, SDK will ask user to Allow or Deny VPN connection.

`- (void)startVpnWithCountry:(AFCountry * __nullable)country completion:(nullable void (^)(NSError * __nullable error))completion;`  

Use your AFCountry object from `availableCountries:` function to specify which server country to use.

`- (void)stopVpn:(nullable void (^)(NSError * __nullable error))completion;`  
Stop VPN.

`- (AFVPNManagerStatus)vpnStatus;`  
Get current VPN status.

`- (void)purchase:(nonnull NSString *)receipt completion:(nonnull AFHydraPurchaseCompletion)completion;`  
Validates purchase with current backend.

`- (NSError *)lastError;`  
Obtain last error that occured in current/last session.

### AFAuthMethod

`+ (instancetype)anonymous;`  
Default auth method that does not require any authentication.

`+ (instancetype)OAuth:(NSString *)accessToken;`  
Most popular OAuth authentication method. OAuth flow should be implemented by your application. After finishing OAuth flow and obtaining OAuth access token, provide it to this factory.

`+ (instancetype)facebook:(NSString *)accessToken;`  
Authenticate with Facebook SDK.

`+ (instancetype)google:(NSString *)accessToken;`  
Authenticate with Google SDK.

`+ (instancetype)twitter:(NSString *)accessToken;`  
Authenticate with Twitter SDK.

`+ (instancetype)github:(NSString *)accessToken;`  
Authenticate with GitHub SDK.

`+ (instancetype)custom:(NSString *)methodName token:(NSString *)accessToken;`  
Custom auth. If you are using custom authentication scheme, use this method.

### AFConfig

`AFConfig` is a class that configures `AFHydra` instance. Created by `AFConfigBuilder`


### AFConfigBuilder

Creates AFConfig instance. There are 4 mandatory properties you need to configure:

`@property BOOL debugLogging;`  
Enable or disable debug logging. **Don't forget to disable for release build!**

`@property NSString *baseUrl;`  
This is a Host URL of the primary server. Provided by Anchorfree Inc.

`@property NSString *carrierId;`  
This is your unique service identifier. Provided by Anchorfree Inc.

`@property NSString *groupId;`  
App Group ID that is created for the current application.

`@property BOOL bypass;`  
Enable bypass mode. See Appendix for more information about the bypass.

`@property NSString *networkExtensionBundleId;`  
Packet Tunnel Provider Extension main target's Bundle Identifier. See Project > [YOUR_TARGET] > Bundle Identifier for more info.

`@property NSString *vpnProfileName`
Sets the name for VPN profile that is visible in Settings > General > VPN (Title of profile, subtitle will always be the application name).

`@property NSString *dnsAddr;`  
Your preferred DNS server to use. If not set, a default one will be used.

`@property NSArray <NSString *> *bypassDomains;`
A list of domains to bypass VPN. Wildcards accepted. 
Example: `cfg.bypassDomains = @[@"*google.com"];` // Google domain and it's subdomains will be accessed directly, without VPN.

`@property BOOL onDemand;`
Enables On Demand VPN feature. VPN will be triggered automatically by the System after `startVpn` is triggered. Calling `stopVpn` from application is required to disable On Demand VPN. If VPN connection could not be established because of network environment or interrupted by out of traffic error code, then VPN will switch to bypass mode automatically until user reconnects VPN from main application, VPN icon will not be visible in the status bar. 

`@property NSString *serverAddressDisplayName`
Sets the name for VPN server address that is visible in Settings > General > VPN (Server field).

### AFUser

Describes VPN user.

`@property(strong, nonatomic) NSString *accessToken;`  
HydraSDK access token.

`@property(strong, nonatomic) AFSubscriber *subscriber;`  
Subscription information.

### AFSubscriber

Describes User's subscription information.

`@property(strong, nonatomic) AFBundle *bundle;`  
Subscription bundle.

`@property(strong, nonatomic) NSNumber *subscriberId;`  
Subscriber identifier.

### AFBundle

Describes subscription bundle information.

`@property(strong, nonatomic) NSString *registrationTime;`  
Time when current User is registered.

`@property(strong, nonatomic) NSString *licenseName;`  
Name of User's license.

`@property(strong, nonatomic) NSNumber *bundleId;`  
Name of a purchased bundle.

`@property(strong, nonatomic) NSString *carrierId;`  
Name of carrier id where the user is registered.

### AFCountry

Describes VPN server location information

`@property (strong, nonatomic) NSString *countryCode;`  
VPN server country location

`@property (strong, nonatomic) NSNumber *serversCount;`  
Amount of VPN servers available in this location.

### AFTrafficCounters

`@property (strong, nonatomic) NSNumber *bytesRx;`  
Bytes received in current session

`@property (strong, nonatomic) NSNumber *bytesTx;`  
Bytes transmitted in current session

`@property (strong, nonatomic) NSDate *updateTime;`
Last counters update time

### AFRemainingTraffic

`@property (strong, nonatomic) NSNumber *sessionStartTime;`  
UNIX timestamp when current session was started.

`@property (strong, nonatomic) NSNumber *trafficUsageLimit;`  
Amount of bytes available to current User

`@property (strong, nonatomic) NSNumber *trafficUsed;`  
Amount of bytes User utilized.

`@property (strong, nonatomic) NSNumber *trafficRemaining;`  
Amount of bytes that is available to User.

## AFPacketTunnelProvider

Your app's Network Extension provider must extend this class. In order to be able to track certain actions like VPN start or errors inside Network Extension, following functions can be overriden:

`- (void)vpnWillStart;` // Called right before VPN start attempt
`- (void)vpnDidStart;` // Called after successful VPN start
`- (void)vpnError:(NSError *)error;` // Called when VPN error occured. Do not call long-running async operations here as the process will shut down.

There is no need calling `super` implementation.

NOTE: DO NOT override system NEPacketTunnelProvider functions as it will break `AFPacketTunnelProvider` implementation.

## Error codes

### AFHydra

`AFHydraApiErrorCodeUndefined` This is a generic unknown error, please report such errors to developers
`AFHydraApiErrorCodeSessionsExceed` Amount of allowed sessions for this user is exceed
`AFHydraApiErrorCodeTrafficExceed` Amount of allowed traffic for this user is exceed
`AFHydraApiErrorCodeUnauthorized` This user is unauthorized or login operation is still pending
`AFHydraApiErrorCodeUserSuspended` This user is suspended
`AFHydraApiErrorCodeRequestedVPNServerUnavailable` Selected server or country code is not available
`AFHydraApiErrorCodeCredentialsInternalError` Server was unable to fetch credentials for this country code
`AFHydraApiErrorCodeDevicesExceed` The amount of allowed devices for this user is exceed
`AFHydraApiErrorCodeNetworkError` The Internets are not available or network request has failed. Feel free to try again
`AFHydraApiErrorCodeUnknownServerResponse` This response could mean you don't have latest HydraSDK. Please report to developers.

### AFPacketTunnelProvider

Error domain: `AFHydraDomain`

`AFHydraErrorCodeTimeout` VPN timeout
`AFHydraErrorCodeIllegalState` VPN is not established due to application error
`AFHydraErrorCodeConnectionDisrupted` VPN connection disrupted by broken network connection
`AFHydraErrorCodeConnectionNotEstablished` VPN client can't connect to VPN node
`AFHydraErrorCodeTrafficExceed` VPN connection disrupted because the user is out of traffic. NOTE: If `ondemand` feature is used, VPN will be switched to `bypass` mode until user disconnects VPN connection from the application.

# Appendix

# Integration Checklist & Troubleshooting

The configuration of iOS application with HydraSDK could be quite complex since there is a lot to configure. That's why we've created following checklist that should help you to verify correct integration.

- Make sure that you've created Packet Tunnel Provider extension
- Default implementation of PacketTunnelProvider class is removed from .m file
- **HydraApplicationSDK.framework** is added to the Application target, **HydraTunnelProviderSDK.framework** is added to the Extension target
- Your `PacketTunnelProvider` is extending `AFPacketTunnelProvider` class instead of `NEPacketTunnelProvider`
- **libz.tbd** is added to the Extension target
- *Enable Bitcode* is set to "No" and `-ObjC` is present in "Other linker flags" for both targets
- You have created and enabled App Groups (General > Capabilities) for both targets, active App Group is set to "builder.groupId" (App Groups is enabled for both bundle ids (Application and Extension) in Apple Developer Portal)
- Personal VPN (General > Capabilities) is enabled for both targets (Personal VPN is enabled for both bundle ids (Application and Extension) in Apple Developer Portal)
- You have added Network Extension (iOS) entitlement for both Application and Extension provisioning profiles
- `AFHydra` instance is configured with correct `groupId`, `networkExtensionBundleId`

# Migration to 0.4.0

## HydraApplicationSDK

There are no required changes

## AFPacketTunnelProvider

1. There is no `AFPacketTunnelProvider` now to extend, so your PacketTunnelProvider class is not needed anymore (it will be replaced by Delegate, see 2)
2. Create your Delegate class implementing `AFNetworkExtensionDelegate`, the functions will remain the same as in AFPacketTunnelProvider (`vpnWillStart` etc.)
3. Your Network Extension Info.plist should always have `NSExtensionPrincipalClass` set to `AFHydraTunnelProvider`
4. Add a new key to a plist root: `AFNetworkExtensionDelegate` with a value that is your VPN Delegate class. For example, if you're using Swift, and your delegate named VPNDelegate, then the value would be `(PRODUCT_MODULE_NAME).VPNDelegate`
5. Double-check you have "-ObjC" in your Other Liker Flags in a XCode build settings.

This is how your class may look:

// Swift 4.x

import HydraTunnelProviderSDK

class PacketTunnelProviderDelegate: NSObject { }

extension PacketTunnelProviderDelegate: AFNetworkExtensionDelegate {
func vpnWillStart() {
print("Reporing vpnWillStart")
}

func vpnDidStart() {
print("Reporing vpnDidStart")
}

func vpnError(_ error: Error!) {
print("Reporing vpnError: \(error.localizedDescription)")
}

func resourceBlocked(_ categorization: AFHydraCategorization!) {
print("Reporing resourceBlocked: \(categorization.prettyDescription())")
}
}

