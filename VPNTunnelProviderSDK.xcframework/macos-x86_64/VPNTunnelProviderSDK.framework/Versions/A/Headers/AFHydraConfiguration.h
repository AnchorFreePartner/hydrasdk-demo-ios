//
//  AFHydraConfiguration.h
//  AFHydra
//
//  Copyright © 2018 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NetworkExtension/NetworkExtension.h>

typedef NS_OPTIONS(NSInteger, AFHydraLoggingType) {
    AFHydraLoggingTypeNone = 1 << 0,
    AFHydraLoggingTypeObjC = 1 << 1,
    AFHydraLoggingTypeHydra = 1 << 2
};

@interface AFHydraSDPayload : NSObject

// The following parameters described by https://confluence.anchorfree.net/display/HD/Hydra+SD+API document

// 2 Letter country code for desired VL
@property (nonatomic, strong) NSString* virtualLocation;

// 3 digit reason code (https://confluence.anchorfree.net/pages/viewpage.action?pageId=73695459)
@property (nonatomic) NSInteger reason;

// Normal client hash
@property (nonatomic, strong) NSString* deviceHash;

// Channel ex: HSSCNL000001
@property (nonatomic, strong) NSString* channel;

// Application version (integer, "4.15.4" i.e. 4154)
@property (nonatomic) NSUInteger appVersion;

// Platform id - Android, iOS, etc
@property (nonatomic, strong) NSString* platform;

// DNS server to use when domain resolution is made outside of the tunnel
@property (nonatomic, strong) NSString* bypassDNSServer;

@end

@interface AFHydraConfiguration : NSObject <NSSecureCoding>

- (instancetype) initWithDict: (NSDictionary*) configDict;
- (instancetype) initWithSDPayload: (AFHydraSDPayload*) sdPayload;

// Hydra Config dictionary from initWithDict. Will be converted and provided as JSON to hydra
@property (nonatomic, readonly) NSMutableDictionary* configDict;

// Hydra SD Payload from initWithSDPayload. Will be converted and provided as JSON to hydra
@property (nonatomic, readonly) AFHydraSDPayload* sdPayload;

// (MANDATORY) Address to be used for DNS requests that go outside of the tunnel (can also be set through hydra config dict)
@property (nonatomic, strong) NSString* bypassDNSServer;

// (OPTIONAL) Server Address name displayed in iOS Settings -> VPN for this connection
@property (nonatomic, strong) NSString* serverAddressDisplayName;

// App Group Id for shared container. Will be set by VPN manager when starting VPN
@property (nonatomic, readonly) NSString* appGroupId;

//
// Additional options for plugin / platform specific code
//

// (OPTIONAL) Bypass all traffic by not accepting any packets from the system (no routes to utun) (no VPN icon)
@property (nonatomic) BOOL tunBypassMode;

// (OPTIONAL) Bypass all traffic except for DNS (only DNS will be routed to tun)
@property (nonatomic) BOOL dnsOnlyMode;

// (OPTIONAL) Hard connection time limit for hydra to connect (default will be 0 - no timeout)
@property (nonatomic) NSUInteger timeoutSeconds;

// (OPTIONAL) On demand rules to be used for the VPN connection
@property (nonatomic, strong) NSArray<NEOnDemandRule*>* onDemandRules;

// (OPTIONAL) Provide custom cert for hydra connection
@property (nonatomic, strong) NSString* hydraCert;

// (OPTIONAL) Provide custom session id for hydra (This field should be a 15-byte session id encoded into base64 string)
@property (nonatomic, strong) NSString* sessionId;

// (OPTIONAL) Hydra should stay connected during sleep and not shut down the plugin. Default is NO.
// By settings this to YES, the result will be that hydra transport tcp keep alive sent from server will cause the device to wake up to handle them, then go back to sleep. Current defaults have this at around ~1 minute.
@property (nonatomic) BOOL stayConnectedDuringDeviceSleep;


//
// Advanced options (leave as default unless you understand that you need them)
//

// (OPTIONAL) Fixes VPN Icon (LTE + VPN when on Wi-Fi) when it detects that it's broken
@property (nonatomic) BOOL enableVPNIconFix;

// (OPTIONAL) Hides VPN Icon
@property (nonatomic) BOOL fireshieldInvisibleMode;

// (OPTIONAL) VPN + Proxy configuration for User-Agent / CONNECT string parsing
@property (nonatomic, readonly) NSUInteger remoteHTTPProxyPort;
@property (nonatomic, readonly) NSString* remoteHTTPProxyAddress;
@property (nonatomic, readonly) NSUInteger remoteHTTPSProxyPort;
@property (nonatomic, readonly) NSString* remoteHTTPSProxyAddress;

// (OPTIONAL) Opens hydra to be able to accept packets over UDP, acting as a remote tun
@property (nonatomic) BOOL remoteTunEnabled;


@end
