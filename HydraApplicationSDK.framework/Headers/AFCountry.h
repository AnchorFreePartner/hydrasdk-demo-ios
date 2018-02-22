//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

@import Foundation;

@interface AFCountry : NSObject <NSCoding>
@property (strong, nonatomic) NSString *countryCode; // country
@property (strong, nonatomic) NSNumber *serversCount;

@property (nonatomic, assign, readonly, getter=isOptimal) BOOL optimal;

+ (instancetype)optimal;
@end
