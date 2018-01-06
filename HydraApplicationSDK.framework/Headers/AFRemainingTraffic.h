//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AFRemainingTraffic : NSObject <NSCoding>

@property (strong, nonatomic) NSNumber *sessionStartTime; // traffic_start: UNIX timestamp
@property (strong, nonatomic) NSNumber *trafficUsageLimit; // traffic_limit: limit for traffic usage in bytes
@property (strong, nonatomic) NSNumber *trafficUsed; // traffic_used: used traffic for current User
@property (strong, nonatomic) NSNumber *trafficRemaining;

- (NSString *)description;

- (instancetype)initWithCoder:(NSCoder *)coder;

- (void)encodeWithCoder:(NSCoder *)coder; // traffic_remaining: remaining traffic in bytes

@end
