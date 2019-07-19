//
//  AFFireshieldConfig.h
//  HydraApplicationSDK
//
//  Created by Dmitry Denyak on 10/9/18.
//  Copyright © 2018 northghost. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFFireshieldCategory.h"
#import "AFFireshieldRule.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, AFFireshieldService) {
    AFFireshieldServiceIP,
    AFFireshieldServiceBitdefender,
    AFFireshieldServiceSophos
};

typedef NS_ENUM(NSUInteger, AFConfigFireshieldMode) {
    AFConfigFireshieldModeDisabled,
    AFConfigFireshieldModeEnabled,
    AFConfigFireshieldModeEnabledSilent,
    AFConfigFireshieldModeEnabledVPN,
};

@interface AFFireshieldConfig : NSObject 

@property (nonatomic, assign) AFConfigFireshieldMode fireshieldMode;

+ (AFFireshieldConfig *)defaultConfig;
+ (AFFireshieldConfig *)defaultConfigWithFireshieldMode:(AFConfigFireshieldMode)mode;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithFireshieldMode:(AFConfigFireshieldMode)fireshieldMode;

- (void)addService:(AFFireshieldService)service NS_SWIFT_NAME(addService(service:));
- (void)addCategory:(AFFireshieldCategory *)category NS_SWIFT_NAME(addCategory(category:));
- (void)addRule:(AFFireshieldRule *)rule NS_SWIFT_NAME(addRule(rule:));;

@end

NS_ASSUME_NONNULL_END
