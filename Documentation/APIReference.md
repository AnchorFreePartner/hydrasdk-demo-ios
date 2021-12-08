# API Reference

## Table of Contents

- [VPNSDK](#class-vpnsdk-nsobject)  
  - [HydraSDK](#class-hydrasdk-vpnsdk)
  - [HydraConfiguration](#struct-hydraconfiguration)
  - [IPSecSDK](#class-ipsecsdk-vpnsdk)
  - [IPSecConfiguration](#struct-ipsecconfiguration)
- [ComposedVPNSDK](#class-composedvpnsdk-nsobject)
  - [ManualSwitchingVPNSDK](#class-manualswitchingvpnsdk-composedvpnsdk)
  - [AutoSwitchingVPNSDK](#class-autoswitchingvpnsdk-composedvpnsdk)
  - [ComposedConfiguration](#struct-composedconfiguration)
- [AuthMethod](#struct-authmethod)
- [AuthMethodType](#enum-authmethodtype)
- [User](#struct-user)
- [Subscriber](#struct-subscriber)
- [Bundle](#struct-bundle)
- [SubscriberPurchase](#struct-subscriberpurchase)
- [VirtualLocation](#struct-virtuallocation)
- [TrafficCounters](#struct-trafficcounters)
- [RemainingTraffic](#struct-remainingtraffic)
- [VPNCategorization](#struct-vpncategorization)
  - [CategorizationType](#enum-vpncategorizationcategorizationtype)
  - [CategorizationAction](#enum-vpncategorizationcategorizationaction)
- [NetworkExtensionDelegate](#protocol-networkextensiondelegate)
- [API error](#enum-afapierror)
- [VPNTunnelError](#enum-vpntunnelerror)
  - [HydraInternalErrorCode](#vpntunnelerrorhydrainternalerrorcode)

## `class VPNSDK: NSObject`

#### `static func sdkVersion() -> String`
Version of SDK.

#### `var protocolType: VPNProtocolType`
VPN protocol type of SDK.

#### `var deviceID: String`
Device ID string representation.

#### `var carrierID: String`
Carrier ID provided to SDK config.

#### `var hostURL: String?`
Host URL provided to SDK config.

#### `var isLoggedIn: Bool`
Checks if user is logged in.

#### `var token: String?`
Current access token if user is logged in.

#### `var state: VPNState`
Current state of VPN connection.

#### `var connectedDate: Date?`
Date when VPN connection was established.

#### `var remoteConfig: RemoteConfig?`
Last received remote config. Can be `nil` if remote config wasn't successfully received yet.

#### `func login(method: AuthMethod, completion: @escaping UserCompletion)`
Logins and obtains `User` object that describes VPN user.<br>
Returns `User` on success.

#### `func logout(completion: @escaping LogoutCompletion)`  
Logouts current user.

#### `func currentUser(completion: @escaping UserCompletion)`
Gets current user data from server.<br>
Returns `User` on success.

#### `func virtualLocations(completion: @escaping VirtualLocationsCompletion)`
Gets a list of countries that you can connect to.<br>
Returns `[VirtualLocation]` on success.

#### `func installProfile(completion: @escaping ProfileCompletion)`
Triggers iOS VPN subsystem to create/update VPN profile, showing user permission "Allow / Don't Allow" dialog.
Calling this method is not required. Useful for custom tutorial implementation.<br>
**NOTE**: If you're using onDemand VPN feature, this installed profile **WILL** be triggered by system and VPN will be enabled.

#### `func removeProfile(completion: @escaping ProfileCompletion)`
Removes previous installed system VPN profile.<br>
**NOTE**: VPN services with different protocols can use different VPN profiles (e.g., Hydra and IPSec), and this method will remove **all** installed profiles related to app.

#### `func loadCredentials(location: VirtualLocation, completion: @escaping CredentialsCompletion)`
Gets credentials for location. Usually you don't want to call this method manually, because it's called automatically as part of start flow.<br>
Returns `Credential` on success.

#### `func fetchRemoteConfig(completion: @escaping RemoteConfigCompletion)`
Gets remote config from server. Last loaded config is accessible through `remoteConfig` property.<br>
Returns `RemoteConfig` on success.

#### `func start(location: VirtualLocation?, completion: @escaping StartStateCompletion)`
Starts VPN to automagically chosen server. On first VPN connection, SDK will ask user to Allow or Deny VPN connection.<br>
Use your `VirtualLocation` object from `virtualLocations` function to specify which server country to use or use `nil` to use optimal virtual location.

#### `func stop(completion: @escaping StateCompletion)`
Stops connected VPN.

#### `func getTrafficCounters(completion: @escaping TrafficCountersCompletion)`
Gets current traffic counters from server.<br>
Returns `TrafficCounters` on success.

#### `func remainingTraffic(completion: @escaping RemainingTrafficCompletion)`
Gets current traffic limits from server.<br>
Returns `RemainingTraffic` on success.

#### `func purchase(purchaseToken: String?, type: String, completion: @escaping PurchaseCompletion)`
Validates purchase on server and updates user data that related to subscription (e.g., limits).<br>
Returns `Purchase` on success.

## `class HydraSDK: VPNSDK`

#### `init(configuration: HydraConfiguration)`
Designated initializer. SDK instance should be a singleton instance.<br>
Use `HydraConfiguration` type instance to initialize `HydraSDK`.

#### `var configuration: HydraConfiguration`
Passed Hydra configuration.

#### `var isBypassEnabled: Bool `
Checks is Hydra in bypass mode.

#### `var trafficCounters: TrafficCounters?`
Current traffic counters directly from Hydra service.

#### `var clientNetworkList: ClientNetworkList?`
Current CNL. SDK updates CNL as part of credentials loading.

#### `var currentFireshieldMode: FireshieldConfig.Mode?`
Fireshield mode from Hydra config.

#### `var lastCategorization: VPNCategorization?`
Last categorization registered by Hydra service.

#### `var lastTunnelError: VPNTunnelError?`
Last error that occured in current/last Hydra session.

#### `func fireshieldScannedConnections(completion: @escaping ScannedConnectionsCompletion)`
Number of connection scanned by Fireshield service.<br>
Returns `UInt` on success.

#### `func applyLocationIfConnected(_ newLocation: VirtualLocation?, completion: @escaping ApplyLocationCompletion)`
Switches location in the active network extension (without killing it and starting new one).<br>
Returns error if VPN is not currently connected.<br>

#### `func updateConfiguration(_ configuration: HydraConfiguration) throws`
Updates Hydra configuration without creating a new instance of HydraDSK. <br>
**NOTE** Configuration can't be updated if the connection is started, you need to call `stopVPN` function before updating configuration, otherwise `VPNSDKError.notPermitted` exception will be thrown.<br>
Please note if you want to change the main parameters of configuration (`hostURL`, `carrierID`, `extensionBundleID`, `groupID`), you need to create new instance `HydraSDK` with this configuration, otherwise `VPNSDKError.configurationMismatch` the exception will be thrown.

## `struct HydraConfiguration`

#### `hostURL: String?`
User provided host of the VPN server. Provided by Anchorfree Inc. You can pass `nil` to this value, in this case SDK will use another available hosts. If you pass non-nil value, it will take part in host choosing process, but it's not guaranteed that only this host will be used and that it will have higher priority over another hosts.

#### `carrierID: String`
Your unique service identifier. Provided by Anchorfree Inc.

#### `extensionBundleID: String`
Network Extension target's Bundle Identifier.

#### `groupID: String`
App Group ID that is created for the current application.

#### `profileName: String`
Sets the name for VPN profile that is visible in iOS Settings > General > VPN (Title of profile, subtitle will always be the application name).

#### `debugLogging: Bool`
Enables or disables debug logging. **Don't forget to disable for release build!**

#### `fireshieldConfig: FireshieldConfig`
Config that defines Firesheild service behavior.

#### `serverAddressDisplayName: String?`
Sets the name for VPN server address that is visible in iOS Settings > General > VPN (Server field).

#### `dnsAddress: String?`
Your preferred DNS server to use. If not set, a default one will be used.

#### `isOnDemandEnabled: Bool`
Enables On Demand VPN feature. VPN will be triggered automatically by the System after `startVPN` is triggered. Calling `stop` from application is required to disable On Demand VPN. If VPN connection could not be established because of network environment or interrupted by out of traffic error code, then VPN will switch to bypass mode automatically until user reconnects VPN from main application, VPN icon will not be visible in the status bar.

#### `onDemandRules: [NEOnDemandRule]?`
On demand rules to be used for the VPN connection.

#### `isBypassEnabled: Bool`
Enables bypass mode.

#### `bypassDomains: [String]?`
A list of domains to bypass VPN. Wildcards accepted.<br>
Example: `["*google.com"]` // Google domain and it's subdomains will be accessed directly, without VPN.

#### `isVPNIconFixEnabled: Bool`
Enables fixing of VPN Icon (LTE + VPN when on Wi-Fi) when it detects that it's broken.

#### `isClientListEnabled: Bool`
Indicates will CNL functionality take part in Hydra connection logic.

#### `deviceType: String?`
If value is `nil`, device type will be detected automatically. Otherwise provided value will be used. This string can be used as a parameter for some network requests.

## `class IPSecSDK: VPNSDK`

#### `init(configuration: IPSecConfiguration)`
Designated initializer. SDK instance should be a singleton instance.<br>
Use `IPSecConfiguration` type instance to initialize `IPSecSDK`.

## `struct IPSecConfiguration`

#### `hostURL: String?`  
User provided host of the VPN server. Provided by Anchorfree Inc. You can pass `nil` to this value, in this case SDK will use another available hosts. If you pass non-nil value, it will take part in host choosing process, but it's not guaranteed that only this host will be used and that it will have higher priority over another hosts.

#### `carrierID: String`
Your unique service identifier. Provided by Anchorfree Inc.

#### `debugLogging: Bool`
Enables or disables debug logging. **Don't forget to disable for release build!**

#### `isOnDemandEnabled: Bool`
Enables On Demand VPN feature. VPN will be triggered automatically by the System after `startVPN` is triggered. Calling `stop` from application is required to disable On Demand VPN. If VPN connection could not be established because of network environment or interrupted by out of traffic error code, then VPN will switch to bypass mode automatically until user reconnects VPN from main application, VPN icon will not be visible in the status bar.

#### `onDemandRules: [NEOnDemandRule]?`
On demand rules to be used for the VPN connection.

#### `profileName: String`
Sets the name for VPN profile that is visible in iOS Settings > General > VPN (Title of profile, subtitle will always be the application name).

#### `deviceType: String?`
If value is `nil`, device type will be detected automatically. Otherwise provided value will be used. This string can be used as a parameter for some network requests.

## `class ComposedVPNSDK: NSObject`

#### `var activeProtocolType: VPNProtocolType`
VPN protocol type of active SDK.

#### `var deviceID: String`
Device ID string representation.

#### `var carrierID: String`
Carrier ID provided to SDK.

#### `var hostURL: String?`
Host URL provided to SDK.

#### `var isLoggedIn: Bool`
Checks if user is logged in.

#### `var token: String?`
Current access token if user is logged in.

#### `var state: VPNState`
Current state of VPN connection.<br>
Gets corresponding property value from active SDK.

#### `var remoteConfig: RemoteConfig?`
Last received remote config. Can be `nil` if remote config wasn't successfully received yet.

#### `var hydraConfiguration: HydraConfiguration?`
Configuration of HydraSDK.

#### `var isHydraBypassEnabled: Bool`
Checks is Hydra in bypass mode.

#### `var hydraTrafficCounters: TrafficCounters?`
Current traffic counters directly from Hydra service.<br>
**NOTE**: this property can be non-nil even if active VPN service is not Hydra.

#### `var hydraClientNetworkList: ClientNetworkList?`
Current Hydra CNL. Hydra SDK updates CNL as part of credentials loading.

#### `var currentFireshieldMode: FireshieldConfig.Mode?`
Returns Fireshield mode from Hydra config if active SDK is Hydra, otherwise returns `nil`.

#### `var lastHydraCategorization: VPNCategorization?`
Last categorization registered by Hydra service.

#### `var lastHydraTunnelError: VPNTunnelError?`
Last error that occured in current/last Hydra session.

#### `func login(method: AuthMethod, completion: @escaping UserCompletion)`
Logins and obtains `User` object that describes VPN user. Login is shared between VPN SDKs with different protocols.<br>
Returns `User` on success.

#### `func logout(completion: @escaping LogoutCompletion)`  
Logouts current user.

#### `func currentUser(completion: @escaping UserCompletion)`
Gets current user data from server.<br>
Returns `User` on success.

#### `func virtualLocations(completion: @escaping VirtualLocationsCompletion)`
Gets a list of countries that you can connect to.<br>
Returns `[VirtualLocation]` on success.

#### `func installProfile(completion: @escaping ProfileCompletion)`
Triggers iOS VPN subsystem to create/update VPN profile, showing user permission "Allow / Don't Allow" dialog.<br>
Calling this method is not required. Useful for custom tutorial implementation.<br>
**NOTE**: If you're using onDemand VPN feature, this installed profile **WILL** be triggered by system and VPN will be enabled.

#### `func removeProfile(completion: @escaping ProfileCompletion)`
Removes previous installed system VPN profile.<br>
**NOTE**: VPN services with different protocols can use different VPN profiles (e.g., Hydra and IPSec), and this method will remove all installed profiles related to app.

#### `func loadCredentials(location: VirtualLocation, completion: @escaping CredentialsCompletion)`
Gets credentials for location. Usually you don't want to call this method manually, because it's called automatically as part of start flow.<br>
Returns `Credential` on success.

#### `func fetchRemoteConfig(completion: @escaping RemoteConfigCompletion)`
Gets remote config from server. Last loaded config is accessible through `remoteConfig` property.<br>
Returns `RemoteConfig` on success.

#### `func start(location: VirtualLocation?, completion: @escaping StartStateCompletion)`
Starts VPN to automagically chosen server. On first VPN connection, SDK will ask user to Allow or Deny VPN connection.<br>
Use your `VirtualLocation` object from `virtualLocations` function to specify which server country to use or use `nil` to use optimal virtual location.

#### `func stop(completion: @escaping StateCompletion)`
Stops connected VPN.

#### `func getTrafficCounters(completion: @escaping TrafficCountersCompletion)`
Gets current traffic counters from server.<br>
Returns `TrafficCounters` on success.

#### `func remainingTraffic(completion: @escaping RemainingTrafficCompletion)`
Gets current traffic limits from server.<br>
Returns `RemainingTraffic` on success.

#### `func purchase(purchaseToken: String?, type: String, completion: @escaping PurchaseCompletion)`
Validates purchase on server and updates user data that related to subscription (e.g., limits).<br>
Returns `Purchase` on success.

#### `func fireshieldScannedConnections(completion: @escaping ScannedConnectionsCompletion)`
Gets number of connection scanned by Fireshield service.<br>
Returns `UInt` on success.<br>
**NOTE**: this property can return non-nil data even if active VPN service is not Hydra.

#### `func applyLocationIfHydraConnected(_ newLocation: VirtualLocation?, completion: @escaping ApplyLocationCompletion)`
Switches location in the active network extension (without killing it and starting new one).<br>
Returns error if VPN is not currently connected.<br>
**NOTE**: Does nothing if Hydra isn't active protocol.

#### `func updateHydraConfiguration(_ configuration: HydraConfiguration) throws`
Updates Hydra configuration without creating a new instance of HydraDSK. <br>
**NOTE** Configuration can't be updated if the connection is started, you need to call `stopVPN` function before updating configuration, otherwise `VPNSDKError.notPermitted` exception will be thrown.<br>
Please note if you want to change the main parameters of configuration (`hostURL`, `carrierID`, `extensionBundleID`, `groupID`), you need to create new instance `HydraSDK` with this configuration, otherwise `VPNSDKError.configurationMismatch` the exception will be thrown.

## `class ManualSwitchingVPNSDK: ComposedVPNSDK`

#### `init(configuration: ComposedConfiguration, initialProtocolType: VPNProtocolType)`
Designated initializer. SDK instance should be a singleton instance.<br>
Use `ComposedConfiguration` type instance to initialize `ManualSwitchingVPNSDK`.<br>
Use `initialProtocolType` parameter to specify what VPN protocol should be active right after inititalization.

#### `func switchToProtocol(_ newProtocolType: VPNProtocolType, completion: ((_ error: Error?, _ activeSDK: VPNSDK?) -> Void)?)`
Switches VPN procolol type by user requirement. If VPN is connected at the moment of call, it will be stopped and then reconnected to the same location after protocol change.<br>
Returns new active SDK on success.

## `class AutoSwitchingVPNSDK: ComposedVPNSDK`

#### `init(manualSwitchingSDK: ManualSwitchingVPNSDK, priorityProvider: @escaping PriorityProvider)`
Designated initializer. SDK instance should be a singleton instance.<br>
Use `ManualSwitchingVPNSDK` instance with corresponding config to initialize `AutoSwitchingVPNSDK`.<br>
Use `priorityProvider` parameter to specify which VPN protocol priority will be used during start flow.

## `struct ComposedConfiguration`

#### `hostURL: String?`
User provided host of the VPN server. Provided by Anchorfree Inc. You can pass `nil` to this value, in this case SDK will use another available hosts. If you pass non-nil value, it will take part in host choosing process, but it's not guaranteed that only this host will be used and that it will have higher priority over another hosts.

#### `carrierID: String`
Your unique service identifier. Provided by Anchorfree Inc.

#### `extensionBundleID: String`
Network Extension target's Bundle Identifier.

#### `groupID: String`
App Group ID that is created for the current application.

#### `profileName: String`
Sets the name for VPN profile that is visible in iOS Settings > General > VPN (Title of profile, subtitle will always be the application name).

#### `debugLogging: Bool`
Enables or disables debug logging. **Don't forget to disable for release build!**

#### `fireshieldConfig: FireshieldConfig`
Config that defines Firesheild service behavior.

#### `serverAddressDisplayName: String?`
Sets the name for VPN server address that is visible in iOS Settings > General > VPN (Server field).

#### `dnsAddress: String?`
Your preferred DNS server to use. If not set, a default one will be used.

#### `isOnDemandEnabled: Bool`
Enables On Demand VPN feature. VPN will be triggered automatically by the System after `startVPN` is triggered. Calling `stop` from application is required to disable On Demand VPN. If VPN connection could not be established because of network environment or interrupted by out of traffic error code, then VPN will switch to bypass mode automatically until user reconnects VPN from main application, VPN icon will not be visible in the status bar.

#### `onDemandRules: [NEOnDemandRule]?`
On demand rules to be used for the VPN connection.

#### `isBypassEnabled: Bool`
Enables bypass mode.

#### `bypassDomains: [String]?`
A list of domains to bypass VPN. Wildcards accepted.<br>
Example: `["*google.com"]` // Google domain and it's subdomains will be accessed directly, without VPN.

#### `isVPNIconFixEnabled: Bool`
Enables fixing of VPN Icon (LTE + VPN when on Wi-Fi) when it detects that it's broken.

#### `isClientListEnabled: Bool`
Indicates will CNL functionality take part in Hydra connection logic.

#### `deviceType: String?`
If value is `nil`, device type will be detected automatically. Otherwise provided value will be used. This string can be used as a parameter for some network requests.

## `struct AuthMethod`

#### `static func anonymous() -> AuthMethod`  
Default auth method that does not require any authentication.

#### `init(type: AuthMethodType, token: String?)`
Main initializer. Use this initializator if you want to use different auth method.

## `enum AuthMethodType`

#### `case oauth`  
Most popular OAuth authentication method. OAuth flow should be implemented by your application. After finishing OAuth flow and obtaining OAuth access token, provide it to AuthMethod init function like this:
`AuthMethod(type: .oauth, token: "OAUTH_TOKEN")`

#### `case facebook`  
Authenticate with Facebook SDK.

#### `case google`  
Authenticate with Google SDK.

#### `case twitter`
Authenticate with Twitter SDK.

#### `case github`
Authenticate with GitHub SDK.

#### `case firebase`
Authenticate with Firebase SDK.

#### `case custom(String)`  
Custom auth. If you are using custom authentication scheme, use this case.

## `struct User`

Describes VPN user.

#### `let accessToken: String?`  
HydraSDK access token.

#### `let subscriber: Subscriber`  
Subscription information.

## `struct Subscriber`

Describes user's subscription information.

#### `let subscriberID: Int`  
Subscriber identifier.

#### `let activatedDevices: Int`  
Subscriber activated devices.

#### `let activeSessions: Int`  
Subscriber active sessions.

#### `let name: String`  
Subscriber name.

#### `let extref: String`

#### `let carrierID: String`  
Subscriber carrier ID.

#### `let bundle: Bundle`  
Subscription bundle.

#### `let socialProfiles: [String: String]`
Subscriber hash of social profiles with information.

#### `let purchases: [SubscriberPurchase]`
Array of subscriber purchases.

## `struct Bundle`

Describes subscription bundle information.

#### `let licenseName: String`  
Name of user's license.

#### `let bundleID: Int`  
Name of a purchased bundle.

#### `let devicesLimit: Int`  
Number of devices limit.

#### `let sessionsLimit: Int`  
Number of sessions limit.

## `struct SubscriberPurchase`

Describes subscription information.

#### `let id: Int`

Subscription identifier.

#### `let type: String`

Subscription type on server.

#### `let time: Date`

UNIX timestamp of last subscription validation date. Usually server validates subscription 1 time per day.

#### `let isActive: Bool`

Checks is subscription currently valid and active.

## `struct VirtualLocation`

Describes VPN server location information.

#### `let code: String`  
VPN server country location code.

#### `let serversCount: Int`  
Amount of VPN servers available in this location.

#### `let groupName: String`
Name of private server group name (could be empty).

## `struct TrafficCounters`

#### `let received: UInt64`
Bytes received in current session.

#### `let transmitted: UInt64`  
Bytes transmitted in current session.

## `struct RemainingTraffic`

Represents traffic limits information.

#### `let sessionStartTime: UInt64`  
UNIX timestamp when current session was started.

#### `let trafficUsageLimit: UInt64`  
Amount of bytes available to current User.

#### `let trafficUsed: UInt64`
Amount of bytes user utilized.

#### `let trafficRemaining: UInt64`  
Amount of bytes that is available to User.

## `struct VPNCategorization`

Represents Fireshield categorization.

#### `let resource: String`
Resource URL string.

#### `let type: CategorizationType`
Resource type.

#### `let action: CategorizationAction`
Action performed by Fireshield.

#### `let categoryLabel: String`
Resource category name.

#### `let categoryID: Int`
Resource category ID.

#### `let sources: [String]`
Array of sources used for categorization.

#### `let customLabels: [String]`
Array of additional names.

#### `let proto: Int`
Proto value provided by Fireshield.

#### `let port: Int`
Port value provided by Fireshield.

#### `let timestamp: Date`
Date when resource was handled by Fireshield.

## `enum VPNCategorization.CategorizationType`

#### `case none`
No type provided.

#### `case url`
Resource is a separate URL.

#### `case ip`
Resource is of IP type.

#### `case domain`
Resource is of domain type.

## `enum VPNCategorization.CategorizationAction`

#### `case proxy`
Resource handled by VPN.

#### `case vpn`
Resource handled by VPN (`proxy` case is preffered for this behavior).

#### `case bypass`
Resource was bypassed by Fireshield.

#### `case block`
Resource was blocked by Fireshield.

## `protocol NetworkExtensionDelegate`

Your app's Network Extension provider must implement this protocol. In order to be able to track certain actions like VPN start or errors inside Network Extension, following functions can be overriden:

#### `var fireshieldManager: FireshieldManager? { get set }`
Stored property that will contain Fireshield manager after Hydra init.

#### `func vpnWillStart(with options: StartupOptions)`
Called right before VPN start attempt.

#### `func vpnDidStart()`
Called after successful VPN start.

#### `func vpnWillStop(availableRestartCompletion: ((_ shouldRestart: Bool) -> Void)?)`
This method will be called with non nil `availableRestartCompletion` parameter if VPN is about to stop with an error.
In this case until completion closure will be called, the extension will be in killswitch feature (no out/in going network packets will be delivered/received).
If VPN is about to stop without any error, then this method will be called with nil `availableRestartCompletion` without killswitch feature.
Parameter `availableRestartCompletion` - if it's not nil, pass `true` to the completion block if you want to restart the VPN extension without killing and using the same delegate object, otherwise, the new delegate object will be created.

#### `func vpnWillGoToSleep()`
Called when current vpn session is going to sleep because of OS requirement.

#### `func vpnWillWakeUpFromSleep()`
Called when vpn session was waked up from sleep.

#### `func vpnDidReceiveError(_ error: VPNTunnelError)`
Called when VPN error occured. Do not call long-running async operations here as the process will shut down.

#### `func vpnDidHandleCategorization(_ categorization: VPNCategorization)`
Called when resource is handled by Fireshield.

#### `func vpnDidReceiveTrafficCounters(_ counters: TrafficCounters)`
Called when VPN traffic counters did update.

## `enum AFAPIError`

#### `case undefined = 101`
This is a generic unknown error, please report such errors to developers.

#### `case sessionExceed = 102`
Amount of allowed sessions for this user is exceed.  

#### `case trafficExceed = 103`
Amount of allowed traffic for this user is exceed.  

#### `case unauthorized = 104`
This user is unauthorized or login operation is still pending.

#### `case userSuspended = 105`
This user is suspended.

#### `case vpnServerUnavailable = 106`
Selected server or country code is not available.

#### `case internalServerError = 107`
Server was unable to fetch credentials for this country code.

#### `case deviceExceed = 108`
The amount of allowed devices for this user is exceed.

#### `case networkError = 109`
Internet connection is not available or network request has failed. Feel free to try again.

#### `case invalidPurchase = 110`
The purchase could be validated.

#### `case unknownServerResponse = 111`
This response could mean you don't have latest HydraSDK. Please report to developers.

#### `case notAuthorized = 112`
The token of user is expired.

#### `case badRequest = 113`
Bad request server error.

#### `case failedResult = 114`
Result in server response wasn't successful, but error is unknown.

#### `case invalidCredentials = 115`
Credentials verification failed.

## `enum VPNTunnelError`

#### `case notConfigured`
Hydra is not configured properly.

#### `case interfaceChange`
Network interface was changed during connected state.

#### `case tunInterfaceFailure`
Failed to start packet flow.

#### `case systemCalledStop`
OS called stop.

#### `case systemCalledSleep`
OS called sllep.

#### `case badConfiguration`
Configuration decoding failed.

#### `case connectionTimeout`
Connection timeouted.

#### `case connectionCanceled`
Connection was canceled by user.

#### `case hydraInternalError(code: Int, name: String?)`
SDK catched custom error from Hydra.

#### `case failedToSetNetworkSettings`
Can't prepare network settings.

#### `case delegateRestrictsConnect`
Can't connect because of invalid configuration.

#### `case failedToUpdateFireshieldCustomList`
Attempt to update Fireshield list failed.

#### `case failedToReconfigureHydra`
Hydra reconfiguration initiated for Fireshield list update failed.

#### `case unknown`
Unknown error.

## `VPNTunnelError.HydraInternalErrorCode`

Some codes for `case hydraInternalError(code: Int, name: String?)`

#### `connectionDisrupted = 181`
VPN connection disrupted by broken network connection.

#### `connectionNotEstablished = 182`
VPN client can't connect to VPN node.

#### `tokenInvalid = 186`
VPN is not established due to application error.

#### `trafficExceed = 191`
VPN connection disrupted because the user is out of traffic.<br>
**NOTE:** If `ondemand` feature is used, VPN will be switched to `bypass` mode until user disconnects VPN connection from the application.
