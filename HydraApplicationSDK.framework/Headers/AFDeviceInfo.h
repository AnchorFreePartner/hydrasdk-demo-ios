//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

@import Foundation;

@interface AFDeviceInfo : NSObject
+ (NSString *)UUIDWithCarrierId:(NSString *)carrierId;

- (void)collect:(NSMutableDictionary *)dict forCarrierId:(NSString *)carrierId;
@end
