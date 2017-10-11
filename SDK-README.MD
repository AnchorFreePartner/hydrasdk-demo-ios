# HydraSDK for iOS & macOS

Download latest SDK: 
- [HydraSDK for iOS](https://firebasestorage.googleapis.com/v0/b/web-portal-for-partners.appspot.com/o/products%2FHydraSDK-iOS.zip?alt=media)
- [HydraSDK for macOS](https://firebasestorage.googleapis.com/v0/b/web-portal-for-partners.appspot.com/o/products%2FHydraSDK-macOS.zip?alt=media)

HydraSDK for iOS (The SDK) is a part of AnchorFree SDK. It contains client-side libraries and server-side applications needed to implement custom VPN infrastructure.

The SDK provides API to authorize client users and gives them an ability to connect to backend VPN services.

# Prerequisites

* Requires iOS 9+ or macOS X 10.12 to run (10.13 if an app is not distributed through AppStore).
* Xcode 8.3.2

Read more about [Network Extensions](https://developer.apple.com/reference/networkextension) on Apple Developer website.

# Setup

### Creating Packet Tunnel Provider Extension

To start application development, you need to create a XCode iOS application project. 

Once the application is created, go to *Project > Targets*, and in menu bar select *Editor > Add Target*. Choose *Packet Tunnel Provider Extension*, provide the name and bundle ID for this **Network Extension** target. 

> **NOTE:** Xcode 8.2 and newer do not have this template, [see the workaround on Apple Developer Forum](https://forums.developer.apple.com/message/187336#187336).

Read more about [Creating a Packet Tunnel Provider Extension](https://developer.apple.com/reference/networkextension/nepackettunnelprovider#2110153) from Apple docs.

At the end of this step, you have to have at least two targets: 
* **Application** target
* **Network Extension** target

### Configure Build Settings

For both, the **Application** and the **Network Extension** targets, do the following

1. Add following system frameworks to your project dependencies:
- NetworkExtension
- Security
- libz.tbd

2. In your project: *Project > Build Settings*:
- Set *Enable Bitcode* to "NO"
- Set *Other Linker Flags* to `-ObjC`.

### Add HydraSDK

The consists of two frameworks:
* **HydraApplicationSDK.framework** (for **Application** target)
* **HydraTunnelProviderSDK.framework** (for **Network Extension** target)

To integrate HydraSDK to your project, do the following:

1. Add **HydraApplicationSDK.framework** to the Xcode project, and add this framework for your **Application** target. 
2. Add **HydraTunnelProviderSDK.framework** to your project and then add this framework for your **Network Extension** target. 
3. Make sure both of these frameworks are properly added by going to *Project > General*, and double-checking that frameworks are in place under *Linked Frameworks and Libraries* section of respective targets.

### Subclassing Packet Tunnel Provider

After the **Network Extension** target is created, you should observe that new class is added to your project (file *PacketTunnelProvider.h*/*.m*). Go to the *PacketTunnelProvider.h* (which extends `NETunnelProvider`) and make this class extends `AFPacketTunnelProvider` instead of `NETunnelProvider`. It should now look like:

    #import <HydraTunnelProviderSDK/HydraTunnelProviderSDK.h>
    @interface PacketTunnelProvider : AFPacketTunnelProvider
    // ...
    @end

Remove Xcode-generated empty `PacketTunnelProvider`'s implementation inside *.m* file.

### Configure App ID

It is required to have two separate application IDs created on Apple Developer Portal, one for the **Application** target and other for the **Network Extension** target. 

Go to [Apple Developer Portal](https://developer.apple.com/) and create (if not yet created) two application IDs under *Identifiers > App IDs* section.

Also, enable the following services for both IDs:
* App Groups (this will be configured in the next step)
* Network Extensions
* Personal VPN

> **NOTE:** It is recommended to give distinctive names to your App IDs, for example:
> * MyApp Application
> * MyApp NetworkExtension

### Creating App Group

Since HydraSDK is mostly a Network Extension you also have to create an App Group and provide group ID to the SDK to allow Hydra to interact with Packet Tunnel Provider Extension. See [Adding an App to an App Group](https://developer.apple.com/library/content/documentation/Miscellaneous/Reference/EntitlementKeyReference/Chapters/EnablingAppSandbox.html#//apple_ref/doc/uid/TP40011195-CH4-SW19) for more information about how to create app group. 

You need to assign this group to both, the **Application** and the **Network Extension** targets and App IDs.

### Enabling Capabilities

For both, **Application**  and **Network Extension** targets, go to *Project > Capabilities* and Enable the following capabilities:

* Personal VPN
* Network Extensions
* App Groups

> **NOTE:** Make sure that respective **.entitlement** files are added to the project for both, **Application**  and **Network Extension** targets.

### Re/Generate Provision Profiles

Application and Network Extension have to have its respective Provision Profiles generated from the Developer Portal. When creating and/or regenerating Provision Profiles, make sure you select Network Extension entitlement.

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
    }]];

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

To connect VPN use AFHydra function `startVpn:(nullable void (^)(NSError * __nullable error))completion`. When VPN is started or an error occurred, completion will be called. To obtain VPN connection status you need to subscribe to `NSNotificationCenter` provided in `AFHydra` instance. For example:

    [self.hydraClient.notificationCenter addObserver:self
                                            selector:@selector(connectionChanged:)
                                                name:AFVPNStatusDidChangeNotification
                                              object:nil];

When you receive notification, get updated VPN status from `AFHydra` instance status property and handle this status as designed by your app.

### Error Handling

Most of the `AFHydra` calls are accepting completion blocks with errors. If an error occurs, you will receive non-nil `NSError` object with an explanation. Errors could be handled by code, that is defined in `AFHydraApiErrorCode`. See *AFHydra.h* for more info.

If you are just disconnected from VPN session, you could also check `hydraClient.lastError` property, if there was an error during initialization or session management system disconnected VPN remotely, there will be `NSError` object here. You must handle such errors and report if appropriate.

# API Documentation

### AFHydra


`- (nonnull instancetype)initWithConfig:(AFConfig * __nonnull)config;`
`+ (nonnull instancetype)withConfig:(AFConfig * __nonnull)config;`

Main constructor and factory. AFHydra instance should be a singleton instance. Use AFConfig object instance to initialize HydraSDK. The fastest way to create AFConfig object instance is to use `[AFConfig configWithBlock:]`.

`- (BOOL)updateConfig:(AFConfig *)config;`  
Update Hydra configuration without restarting VPN session. **NOTE** currently works only with blacklistPath and whitelistPath.

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

`- (void)trafficCounters:(nonnull AFHydraTrafficCountersCompletion)completion;`  
Retrieve current traffic counters.

`- (void)startVpn:(nullable void (^)(NSError * __nullable error))completion;`  
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

`- (void)blockedDomainsCount:(AFHydraDomainsCountCompletion)completion;`  
**Ad blocking feature**. Get the amount of domain hits that were blocked by ad block subsystem.

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

`@property (nonatomic) BOOL debugLogging;`  
Enable or disable debug logging. **Don't forget to disable for release build!**

`@property (strong, nonatomic) NSString *baseUrl;`  
This is a Host URL of the primary server. Provided by Anchorfree Inc.

`@property (strong, nonatomic) NSString *carrierId;`  
This is your unique service identifier. Provided by Anchorfree Inc.

`@property (strong, nonatomic) NSString *groupId;`  
App Group ID that is created for the current application.

`@property (nonatomic) BOOL bypass;`  
Enable bypass mode. See Appendix for more information about the bypass.

`@property (strong, nonatomic) NSString *networkExtensionBundleId;`  
Packet Tunnel Provider Extension main target's Bundle Identifier. See Project > [YOUR_TARGET] > Bundle Identifier for more info.

`@property (strong, nonatomic) NSString *blacklistPath;`  
A list of domains (with wildcards, like *.example.*) that should be blocked by Hydra. To obtain amount of blocked domains by these rules, see `AFHydra.blockedDomainsCount` method.

`@property (strong, nonatomic) NSString *whitelistPath;`  
A list of domains (without wildcards) that should not be blocked by blacklist rules.

`@property (strong, nonatomic) NSString *dnsAddr;`  
Your preferred DNS server to use. If not set, a default one will be used.

`@property (strong, nonatomic) NSArray <NSString *> *bypassDomains;`
A list of domains to bypass VPN. Wildcards accepted. 
Example: `cfg.bypassDomains = @[@"*google.com"];` // Google domain and it's subdomains will be accessed directly, without VPN.

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

### Error codes

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

# Appendix

# Bypass & Ad blocking

Hydra supports VPN configuration where there is no real VPN server connection. Such connections work in local-only mode, but iOS will treat this VPN connection as a real one. This is a way to implement ad blocking functionality for your application. Below is an example of such configuration.

    self.hydraClient = [AFHydra withConfig:[AFConfig configWithBlock:^(AFConfigBuilder *builder) {
        builder.bypass = true,
        builder.groupId = @"group.MY_APP_GROUP";
        builder.networkExtensionBundleId = @"BUNDLE_ID";
        builder.blacklistPath = [[NSBundle mainBundle] pathForResource:@"blocklist"
                                                                ofType:@"txt"];
        builder.whitelistPath = [[NSBundle mainBundle] pathForResource:@"whitelist"
                                                                ofType:@"txt"];
    }]];

Note, that `builder.bypass` should be `true`, and at least `builder.blacklistPath` should be set with an initial list of rules. If you need to update your lists without VPN reconnection, use `AFHydra.updateConfig` method. Below is an example of updating lists.

    [AppDelegate.instance.hydraClient updateConfig:[AFConfig configWithBlock:^(AFConfigBuilder *builder) {
        builder.blacklistPath = [[NSBundle mainBundle] pathForResource:@"blocklist_update"
                                                                ofType:@"txt"];
        builder.whitelistPath = [[NSBundle mainBundle] pathForResource:@"whitelist_update"
                                                                  ofType:@"txt"];
    }]];

Note that at `builder.blacklistPath` should be set. If both set as `nil`, then lists are removed from VPN configuration and blocking functionality stops working.

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
