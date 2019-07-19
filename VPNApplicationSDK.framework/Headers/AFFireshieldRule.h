//
//  AFFireshieldRule.h
//  HydraApplicationSDK
//
//  Created by Dmitry Denyak on 10/17/18.
//  Copyright © 2018 northghost. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFFireshieldCategory.h"

NS_ASSUME_NONNULL_BEGIN

@interface AFFireshieldRule : NSObject

@property (nonatomic, copy, readonly) NSString *filePath;
@property (nonatomic, assign, readonly) AFFireshieldCategories category;

+ (instancetype)fileRule:(NSString *)fileName withCategory:(AFFireshieldCategories)category;
+ (instancetype)domainsRule:(NSArray<NSString *> *)domains withCategory:(AFFireshieldCategories)category;

@end

NS_ASSUME_NONNULL_END
