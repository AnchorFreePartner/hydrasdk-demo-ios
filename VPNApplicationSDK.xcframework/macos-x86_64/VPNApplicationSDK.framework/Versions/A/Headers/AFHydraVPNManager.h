//
//  AFHydraVPNManager.h
//  AFHydra
//
//  Copyright © 2018 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NetworkExtension/NetworkExtension.h>

#import "AFHydraConfiguration.h"
#import "AFHydraCategorization.h"
#import "AFHydraDataCounter.h"

extern NSNotificationName const AFHydraVPNStatusDidChangeNotification;

@interface AFHydraVPNManager : NSObject

- (instancetype) initWithExtensionBundleId: (NSString*) extensionBundleId
                      extensionDescription: (NSString*) extensionDescription
                                appGroupId: (NSString*) appGroupId
                               loggingType: (AFHydraLoggingType) loggingType
                           loggingCallback: (void (^)(NSString* logString, AFHydraLoggingType type)) loggingCallback;

@property (nonatomic) NEVPNStatus vpnStatus;

- (void) startVPNWithConfiguration: (AFHydraConfiguration*) configuration completion: (void (^)(NSError* error)) completion;
- (void) stopVpn:(void (^)(NSError* error))completion;
- (void) installVpnProfile: (void (^)(NSError* error)) completion;
- (void) removeVpnProfile: (void (^)(NSError* error)) completion;
- (NSDate*) connectedDate;

+ (BOOL) isSupported;

//
//
// PLUGIN MESSAGING
//
//
// Specific messages that are handled natively by Hydra SDK

// Provide the number of scanned connections from fireshield service
- (void) pluginMessageGetScannedConnections:(void (^)(NSUInteger scannedConnections, NSError* error))completion;

// Custom user messages - will be sent to plugin's delegate to be handled by the user of the SDK
- (void) pluginMessage: (NSString*) command withUserInfo:(NSDictionary*) userInfo withCompletion: (void (^)(NSDictionary *responseDictionary, NSError* error))completion;

//
//
// PERSISTENT STORAGE
//
//
@property (nonatomic, readonly) NSError* lastHydraError;
@property (nonatomic, readonly) AFHydraConfiguration* lastSuccessfulConfiguration;

@property (nonatomic, readonly) AFHydraCategorization* lastHydraCategorization;
- (void) registerForCategorizationChanges: (void (^)(AFHydraCategorization* categorization)) callback;

@property (nonatomic, readonly) AFHydraDataCounter* dataCounter;

FOUNDATION_EXPORT NSErrorDomain const AFHydraVPNManagerErrorDomain;

NS_ERROR_ENUM(AFHydraVPNManagerErrorDomain)
{
    AFHydraVPNManagerErrorDomainStart = 1,
    AFHydraVPNManagerErrorDomainCancel = 2,
    AFHydraVPNManagerErrorDomainStop = 3,
    AFHydraVPNManagerErrorDomainConnectFailed = 4,
    AFHydraVPNManagerErrorDomainIPCFailed = 5,
};


// DEBUG MESSAGES BELOW

// Flips the switch on routing (on/off) - plugin may decide to change based on events
// DEBUG ONLY
- (void) pluginMessageToggleRouting:(void (^)(NSDictionary* responseDict, NSError* error)) completion;

// Restart hydra (without restarting plugin) using the same configuration (will change ipv6 only still)
// DEBUG ONLY
- (void) pluginMessageRestartHydra:(void (^)(NSError* error)) completion;

// Get the final config that hydra is connected with
// DEBUG ONLY
- (void) pluginMessageFetchConfig:(void (^)(AFHydraConfiguration* config, NSError* error)) completion;

// Get fireshield categorization stats
// DEBUG ONLY
- (void) pluginMessageFireshieldStats:(void (^)(NSDictionary* stats, NSError* error)) completion;

@end
