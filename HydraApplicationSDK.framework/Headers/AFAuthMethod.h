//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, AFAuthMethodType) {
    AFAuthMethodTypeAnonymous,
    AFAuthMethodTypeOAuth,
    AFAuthMethodTypeFacebook,
    AFAuthMethodTypeGoogle,
    AFAuthMethodTypeTwitter,
    AFAuthMethodTypeGithub,
    AFAuthMethidTypeFirebase
};

@interface AFAuthMethod : NSObject

@property (nonatomic) AFAuthMethodType type;
@property (nonatomic) NSString *accessToken;

+ (instancetype)anonymous;

+ (instancetype)OAuth:(NSString *)accessToken;

+ (instancetype)facebook:(NSString *)accessToken;

+ (instancetype)google:(NSString *)accessToken;

+ (instancetype)twitter:(NSString *)accessToken;

+ (instancetype)github:(NSString *)accessToken;

+ (instancetype)firebase:(NSString *)accessToken;

- (NSString *)authMethodString;
@end
