//
//  AFFireshieldController.h
//  HydraTunnelProviderSDK
//
//  Created by Dmitry Denyak on 3/13/19.
//  Copyright © 2019 northghost. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFFireshieldCategory.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, AFFireshieldListResourceType) {
    AFFireshieldListResourceTypeDomain = 0,
    AFFireshieldListResourceTypeURL = 1
};

@interface AFFireshieldController : NSObject

- (nullable NSError *)addItems:(NSArray<NSString *>*)items
                      resourceType:(AFFireshieldListResourceType)resourceType
                   forCategory:(AFFireshieldCategoryType *)category;

- (nullable NSError *)removeItems:(NSArray<NSString *>*)items
                         resourceType:(AFFireshieldListResourceType)resourceType
                     fromCategory:(AFFireshieldCategoryType *)category;

@end

NS_ASSUME_NONNULL_END
