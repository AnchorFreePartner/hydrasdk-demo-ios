//
// Copyright (c) 2016 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFConfigBuilder.h"

@class AFCredentials;
@class AFConfigBuilder;
@class AFConfig;

typedef void (^AFConfigBlock)(AFConfigBuilder *);
typedef void (^AFConfigUpdateBlock)(AFConfig *, AFConfigBuilder *);

@interface AFConfig : NSObject
@property (nonatomic) BOOL debugLogging;
@property (strong, nonatomic) NSString *baseUrl;
@property (strong, nonatomic) NSString *carrierId;
@property (strong, nonatomic, readonly) NSDictionary *dictionary;
@property (strong, nonatomic) NSString *networkExtensionBundleId;
@property (strong, nonatomic) NSString *groupId;
@property (strong, nonatomic) NSString *blacklistPath;
@property (strong, nonatomic) NSString *whitelistPath;
@property (strong, nonatomic) NSString *dnsAddr;
@property (nonatomic) BOOL bypass;

- (instancetype)initWithBuilder:(AFConfigBuilder *)builder;

- (void)updateWithCredentials:(AFCredentials *)credentials;

- (NSString *)shareFile:(NSString *)fullPath;

+ (instancetype)configWithBlock:(AFConfigBlock)block;
@end
