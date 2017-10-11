//
// Copyright (c) 2016 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NetworkExtension/NetworkExtension.h>
#import "AFConfig.h"

@class AFConfig;

@interface AFConfigBuilder : NSObject
@property (nonatomic) BOOL debugLogging;

@property (strong, nonatomic) NSString *baseUrl;
@property (strong, nonatomic) NSString *carrierId;
@property (strong, nonatomic) NSString *blacklistPath;
@property (strong, nonatomic) NSString *whitelistPath;
@property (strong, nonatomic) NSString *interfaceName;
@property (strong, nonatomic) NSString *dnsAddr;
@property (strong, nonatomic) NSString *serverAddr;
@property (strong, nonatomic) NSArray <NSString *> *bypassDomains;
@property (strong, nonatomic) NSDictionary *options;
@property (strong, nonatomic) NSString *groupId;
@property (strong, nonatomic) NSString *networkExtensionBundleId;
@property (strong, nonatomic) NSArray<NEIPv4Route *> *excludeRoute; // NEIPv4Route *
@property (nonatomic) BOOL bypass;

- (AFConfig *)build;
@end
