//
// Copyright (c) 2016 Anchorfree Inc. All rights reserved.
//

@import Foundation;
@import NetworkExtension;

@class AFConfigBuilder;

#import "AFFireshieldConfig.h"

NS_ASSUME_NONNULL_BEGIN
typedef void (^AFConfigBlock)(AFConfigBuilder *);

@interface AFConfig : NSObject
@property (assign, nonatomic, readonly) BOOL debugLogging;
// If onDemand is enabled but `onDemandRules` are not set, default rules will apply to both WiFi and Cellular networks
@property (assign, nonatomic, readonly) BOOL onDemand;
@property (strong, nonatomic, nullable, readonly) NSArray<NEOnDemandRule *> *onDemandRules;
@property (copy, nonatomic, nonnull, readonly) NSString *baseUrl;
@property (copy, nonatomic, nonnull, readonly) NSString *carrierId;
@property (copy, nonatomic, nonnull, readonly) NSString *networkExtensionBundleId;
@property (copy, nonatomic, nonnull, readonly) NSString *groupId;
@property (strong, nonatomic, nullable, readonly) NSArray <NSString *> *bypassDomains;
@property (copy, nonatomic, nullable, readonly) NSString *dnsAddr;
@property (copy, nonatomic, nullable, readonly) NSString *vpnProfileName;
@property (copy, nonatomic, nullable, readonly) NSString *serverAddressDisplayName;
@property (assign, nonatomic, readonly) BOOL bypass;
// Experimental feature that may help with Wi-Fi/VPN icon disappearance when on-demand is ON
@property (assign, nonatomic, readonly) BOOL forceInterface;

@property (strong, nonatomic, nullable, readonly) AFFireshieldConfig *fireshieldConfig;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithBuilder:(AFConfigBuilder *)builder NS_DESIGNATED_INITIALIZER;
+ (instancetype)configWithBlock:(AFConfigBlock)block;

@end
NS_ASSUME_NONNULL_END
