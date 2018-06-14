//
//  AFHydraConfiguration.h
//  HydraSDK
//
//  Created by Sean Ghiocel on 11/27/17.
//  Copyright © 2017 Sean Ghiocel. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NetworkExtension/NetworkExtension.h>

@interface AFHydraConfiguration : NSObject

- (instancetype) initWithDict: (NSDictionary*) configDict;

@property (nonatomic, strong) NSMutableDictionary* configDict;

// Convenience functions for configDict (hydra config json)
@property (nonatomic, strong) NSString* appGroupId;
@property (nonatomic, readonly) NSString* remoteHost;
@property (nonatomic, readonly) BOOL hydraBypassMode;
@property (nonatomic, strong) NSString* bypassDNSServer;
@property (nonatomic) BOOL fireshieldInvisibleMode;

// Additional options for plugin / platform specific code
@property (nonatomic) BOOL tunBypassMode;
@property (nonatomic) NSUInteger timeoutSeconds;
@property (nonatomic, strong) NSArray<NEOnDemandRule*>* onDemandRules;
@property (nonatomic, strong) NSString* hydraCert;

@property (nonatomic, readonly) NSUInteger remoteHTTPProxyPort;
@property (nonatomic, readonly) NSString* remoteHTTPProxyAddress;
@property (nonatomic, readonly) NSUInteger remoteHTTPSProxyPort;
@property (nonatomic, readonly) NSString* remoteHTTPSProxyAddress;

// Advanced options (leave as default unless you understand that you need them)
@property (nonatomic) BOOL enableVPNIconFix;

// Uses static 8.8.8.8 for DNS bypass instead of dynamically reading from the System settings
@property (nonatomic) BOOL enableStaticDNSBypass;

typedef NS_OPTIONS(NSInteger, AFHydraLoggingType) {
    AFHydraLoggingTypeNone = 0,
    AFHydraLoggingTypeConsole = 1 << 0,
    AFHydraLoggingTypeDisk = 1 << 1
};

// Writes hydra logs to file - Note: This requires a debug version of hydra lib
@property (nonatomic) AFHydraLoggingType enableHydraLogs;

// Path to hydra log file on disk in shared container - Note: This requires a debug version of hydra lib
+ (NSURL*) hydraLogFilePathForContainerId: (NSString*) appGroupId;

@property (nonatomic) BOOL remoteTunEnabled;


@end
