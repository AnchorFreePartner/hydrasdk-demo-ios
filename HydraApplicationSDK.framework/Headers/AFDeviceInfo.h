//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

@import Foundation;

@interface AFDeviceInfo : NSObject
+ (NSString *)UUID;

+ (void)resetDeviceId;
- (void)collect:(NSMutableDictionary *)dict;
@end
