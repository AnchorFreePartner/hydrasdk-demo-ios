//
//  AFPurchaseResponse.h
//  hydrasdk
//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

@import Foundation;

@interface AFPurchaseResponse : NSObject <NSCoding>
@property(strong, nonatomic) NSString *result;

- (instancetype)initWithCoder:(NSCoder *)coder;

- (void)encodeWithCoder:(NSCoder *)coder;
@end
