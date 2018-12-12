//
//  AFFireshieldCategory.h
//  HydraApplicationSDK
//
//  Created by Dmitry Denyak on 10/9/18.
//  Copyright © 2018 northghost. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, AFFireshieldCategories) {
    AFFireshieldCategorySafe,
    AFFireshieldCategoryUnsafe,
    AFFireshieldCategoryUnsafeMalware
};

@interface AFFireshieldCategory : NSObject

+ (NSString *)categoryNameFor:(AFFireshieldCategories)category;

+ (AFFireshieldCategory *)block:(AFFireshieldCategories)category;
+ (AFFireshieldCategory *)proxy:(AFFireshieldCategories)category;
+ (AFFireshieldCategory *)bypass:(AFFireshieldCategories)category;
+ (AFFireshieldCategory *)alert:(AFFireshieldCategories)category;

@end

NS_ASSUME_NONNULL_END
