//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface AFCountry : NSObject <NSCoding>
@property (strong, nonatomic) NSString *countryCode; // country
@property (strong, nonatomic) NSNumber *serversCount;

- (NSString *)description;

- (instancetype)initWithCoder:(NSCoder *)coder;

- (void)encodeWithCoder:(NSCoder *)coder;
@end
