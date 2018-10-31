//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

@import Foundation;

@interface AFDeviceInfo : NSObject
+ (NSString *)UUID;
+ (NSString *)UUIDWithCarrierId:(NSString *)carrierId;

+ (void)resetDeviceId;
- (void)collect:(NSMutableDictionary *)dict forCarrierId:(NSString *)carrierId;
@end
