//
// Copyright (c) 2016 Anchorfree Inc. All rights reserved.
//

@import Foundation;
@import NetworkExtension;

#import "AFConfig.h"

NS_ASSUME_NONNULL_BEGIN
@interface AFConfigBuilder : NSObject
@property (assign, nonatomic) BOOL debugLogging;
@property (assign, nonatomic) BOOL onDemand;
@property (strong, nonatomic, nullable) NSArray<NEOnDemandRule *> *onDemandRules;
@property (copy, nonatomic, nonnull) NSString *baseUrl;
@property (copy, nonatomic, nonnull) NSString *carrierId;
@property (copy, nonatomic, nonnull) NSString *networkExtensionBundleId;
@property (copy, nonatomic, nonnull) NSString *groupId;
@property (strong, nonatomic, nullable) NSArray <NSString *> *bypassDomains;
@property (copy, nonatomic, nullable) NSString *dnsAddr;
@property (copy, nonatomic, nullable) NSString *vpnProfileName;
@property (copy, nonatomic, nullable) NSString *serverAddressDisplayName;
@property (assign, nonatomic) BOOL bypass;
@property (assign, nonatomic) BOOL forceInterface;
@property (strong, nonatomic, nonnull) AFFireshieldConfig *fireshieldConfig;

- (AFConfig *)build;
@end
NS_ASSUME_NONNULL_END
