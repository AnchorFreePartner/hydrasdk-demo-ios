//
// Copyright (c) 2016 Anchorfree Inc. All rights reserved.
//

@import Foundation;
@import NetworkExtension;

@class AFCredentials;
@class AFConfigBuilder;
@class AFConfig;
@class AFProvidedCredentials;

NS_ASSUME_NONNULL_BEGIN
typedef void (^AFConfigBlock)(AFConfigBuilder *);
typedef void (^AFConfigUpdateBlock)(AFConfig *, AFConfigBuilder *);

typedef NS_ENUM(NSUInteger, AFConfigFireshieldMode) {
    AFConfigFireshieldModeDisabled,
    AFConfigFireshieldModeEnabled,
    AFConfigFireshieldModeEnabledSilent,
    AFConfigFireshieldModeEnabledVPN,
};

@interface AFConfig : NSObject
@property (nonatomic) BOOL debugLogging;
// If onDemand is enabled but `onDemandRules` are not set, default rules will apply to both WiFi and Cellular networks
@property (nonatomic) BOOL onDemand;
@property (nonatomic) BOOL advancedOnDemand;
@property (nullable, nonatomic) NSArray<NEOnDemandRule *> *onDemandRules;
@property (copy, nonatomic, nonnull) NSString *baseUrl;
@property (copy, nonatomic, nonnull) NSString *carrierId;
@property (copy, nonatomic, nonnull) NSString *networkExtensionBundleId;
@property (copy, nonatomic, nonnull) NSString *groupId;
@property (copy, nonatomic, nullable) NSString *blacklistPath;
@property (copy, nonatomic, nullable) NSString *whitelistPath;
@property (strong, nonatomic, nullable) NSArray <NSString *> *bypassDomains;
@property (copy, nonatomic, nullable) NSString *dnsAddr;
@property (copy, nonatomic, nullable) NSString *vpnProfileName;
@property (copy, nonatomic, nullable) NSString *serverAddressDisplayName;
@property (nonatomic) BOOL bypass;
// Experimental feature that may help with Wi-Fi/VPN icon disappearance when on-demand is ON
@property (nonatomic) BOOL forceInterface;

@property (nonatomic, assign) AFConfigFireshieldMode fireshieldMode;

- (instancetype)initWithBuilder:(AFConfigBuilder *)builder;

- (void)updateWithCredentials:(AFProvidedCredentials *)credentials;

- (NSString *)shareFile:(NSString *)fullPath;

+ (instancetype)configWithBlock:(AFConfigBlock)block;

- (NSString *)pkiCert;

- (NSString *)jsonString;
@end
NS_ASSUME_NONNULL_END
