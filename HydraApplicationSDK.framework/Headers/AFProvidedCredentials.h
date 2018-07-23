//
// Created by Igor Glotov on 9/18/17.
// Copyright (c) 2017 northghost. All rights reserved.
//

@import Foundation;

@interface AFServerItem : NSObject
@property(strong, nonatomic) NSString *address;
@property(strong, nonatomic) NSString *name;
@property(strong, nonatomic) NSString *country;
@property(strong, nonatomic) NSNumber *port;

- (NSString *)description;
@end

@interface AFProvidedCredentials : NSObject

@property(strong, nonatomic) NSArray<AFServerItem *> *servers;
@property(strong, nonatomic) NSString *clientIp; // same as userIp in AFCredentials
@property(strong, nonatomic) NSNumber *expireTime;
@property(strong, nonatomic) NSString *serverHash;
@property(strong, nonatomic) NSString *serverUsername;
@property(strong, nonatomic) NSDictionary *raw;
@property (strong, nonatomic) NSString *hydraCert;

- (NSString *)description;
@end
