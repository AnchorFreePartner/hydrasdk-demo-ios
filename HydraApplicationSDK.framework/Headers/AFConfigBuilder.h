//
// Copyright (c) 2016 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NetworkExtension/NetworkExtension.h>
#import "AFConfig.h"

NS_ASSUME_NONNULL_BEGIN
@class AFConfig;
@class AFOnDemandRules;

@interface AFConfigBuilder : NSObject
@property (nonatomic) BOOL debugLogging;
@property (nonatomic) BOOL onDemand;
@property (nonatomic) BOOL advancedOnDemand; // Only can be enabled if onDemand is `true`
@property (strong, nonatomic, nullable) AFOnDemandRules *onDemandRules;
@property (strong, nonatomic) NSString *baseUrl;
@property (strong, nonatomic) NSString *carrierId;
@property (strong, nonatomic, nullable) NSString *blacklistPath;
@property (strong, nonatomic, nullable) NSString *whitelistPath;
@property (strong, nonatomic, nullable) NSString *interfaceName;
@property (strong, nonatomic, nullable) NSString *dnsAddr;
@property (strong, nonatomic, nullable) NSString *serverAddr;
@property (strong, nonatomic, nullable) NSArray <NSString *> *bypassDomains;
@property (strong, nonatomic, nullable) NSDictionary *options;
@property (strong, nonatomic) NSString *groupId;
@property (strong, nonatomic) NSString *networkExtensionBundleId;
@property (strong, nonatomic, nullable) NSArray<NEIPv4Route *> *excludeRoute; // NEIPv4Route *
@property (nonatomic) BOOL bypass;

- (AFConfig *)build;
@end
NS_ASSUME_NONNULL_END
