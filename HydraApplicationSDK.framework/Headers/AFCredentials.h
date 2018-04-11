//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

@import Foundation;

@interface AFCredentials : NSObject
@property (strong, nonatomic) NSString *serverHash;
@property (strong, nonatomic) NSString *serverUsername;
@property (strong, nonatomic) NSString *serverAddress;
@property (strong, nonatomic) NSString *resolvedServerAddress;
@property (strong, nonatomic) NSString *serverName;
@property (strong, nonatomic) NSNumber *expireTime;
@property (strong, nonatomic) NSString *country;
@property (strong, nonatomic) NSString *ip;
@property (strong, nonatomic) NSString *userIP;
@property (strong, nonatomic) NSString *hydraCert;

- (void)save;

- (NSString *)description;

+ (AFCredentials *)wakeup;
@end
