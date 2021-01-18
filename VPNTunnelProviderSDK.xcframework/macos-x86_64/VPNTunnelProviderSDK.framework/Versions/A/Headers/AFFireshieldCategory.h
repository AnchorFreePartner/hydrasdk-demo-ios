//
//  AFCategoryType.h
//  VPNSDK
//
//  Created by Dmitry Denyak on 3/10/20.
//  Copyright © 2020 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AFFireshieldCategoryType : NSObject

+ (instancetype)safe;
+ (instancetype)unsafe;

+ (instancetype)unsafeCustomType:(nonnull NSString *)unsafeCustomType;
+ (instancetype)customType:(nonnull NSString *)customType;

@end

NS_ASSUME_NONNULL_END
