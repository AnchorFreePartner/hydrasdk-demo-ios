//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

@import Foundation;

@interface AFTrafficCounters : NSObject <NSCoding>
@property (strong, nonatomic) NSNumber *bytesRx;
@property (strong, nonatomic) NSNumber *bytesTx;
@property (strong, nonatomic) NSDate *updateTime;
- (NSString *)description;

- (instancetype)initWithCoder:(NSCoder *)coder;

- (void)encodeWithCoder:(NSCoder *)coder;
@end
