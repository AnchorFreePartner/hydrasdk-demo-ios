//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN
@interface AFBundle : NSObject <NSCoding>
@property(strong, nonatomic) NSString *registrationTime;
@property(strong, nonatomic) NSString *licenseName;
@property(strong, nonatomic) NSNumber *bundleId;
@property(strong, nonatomic) NSNumber *devicesLimit;
@property(strong, nonatomic) NSNumber *sessionsLimit;
@property(strong, nonatomic) NSString *carrierId;

- (NSString *)description;

- (instancetype)initWithCoder:(NSCoder *)coder;

- (void)encodeWithCoder:(NSCoder *)coder;

@end

@interface AFSubscriber : NSObject <NSCoding>
@property(strong, nonatomic) AFBundle *bundle;
@property(strong, nonatomic) NSNumber *subscriberId;
@property(strong, nonatomic) NSNumber *activatedDevices;
@property(strong, nonatomic) NSNumber *activeSessions;
@property(strong, nonatomic) NSString *name;
@property(strong, nonatomic, nullable) NSDictionary *socialProfiles;

- (instancetype)initWithCoder:(NSCoder *)coder;

- (void)encodeWithCoder:(NSCoder *)coder;

- (NSString *)description;

@end

@interface AFUser : NSObject <NSCoding>
@property(strong, nonatomic) NSString *accessToken;
@property(strong, nonatomic) AFSubscriber *subscriber;

- (NSString *)description;

- (instancetype)initWithCoder:(NSCoder *)coder;

- (void)encodeWithCoder:(NSCoder *)coder;

@end
NS_ASSUME_NONNULL_END