//
//  AFUCRTracker.h
//  UCRTracker
//
//  Created by Dan Vasilev on 17.06.2020.
//  Copyright © 2020 anchorfree. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - AFUCRConfiguration

@interface AFUCRConfiguration : NSObject

- (nonnull instancetype)initWithReportName:(nonnull NSString *)reportName
                                  appGroup:(nullable NSString *)appGroup
                       keychainAccessGroup:(nullable NSString *)keychainAccessGroup
                          isLoggingEnabled:(BOOL)isLoggingEnabled;

- (nonnull instancetype)init __unavailable;
+ (nonnull instancetype)new __unavailable;

@end

#pragma mark - AFUCREvent

@interface AFUCREvent : NSObject

- (nonnull instancetype)initWithName:(nonnull NSString *)name
                          properties:(nullable NSDictionary<NSString *, id> *)properties;

- (nonnull instancetype)init __unavailable;
+ (nonnull instancetype)new __unavailable;

@end

#pragma mark - AFUCRTracker

@interface AFUCRTracker : NSObject

- (nonnull instancetype)initWithConfiguration:(nonnull AFUCRConfiguration *)configuration;

/// Configures shared instance.
/// Should be called before first access to shared instance.
+ (void)configureSharedWithConfiguration:(nonnull AFUCRConfiguration *)configuration;

/// Shared instance.
+ (nonnull AFUCRTracker *)shared;

/// Registers app name. Will be included in auto collected properties.
/// Isn’t persisted between launches.
- (void)registerAppName:(nonnull NSString *)newValue;

/// Registers vpn protocol. Will be included in auto collected properties.
/// Isn’t persisted between launches.
- (void)registerServerProtocol:(nonnull NSString *)newValue;

/// Registers user token. Will be included in auto collected properties.
/// Isn’t persisted between launches.
- (void)registerServerToken:(nonnull NSString *)newValue;

/// Registers super properties. These properties have higher priority then
/// auto collected properties and lower priority then properties passed with event.
/// Aren’t persisted between launches.
- (void)registerProperties:(nullable NSDictionary<NSString *, id> *)newValue;

/// Sets automatic event sending timer interval.
/// Values less or equal to <code>0</code>mean disable timer.
- (void)setSendEventsInterval:(NSTimeInterval)newValue;

/// Enables/disables automatic event sending when app enters background.
- (void)setShouldSendEventsOnBackground:(BOOL)newValue;

/// Adds event to queue.
/// \param completion
/// Completion handler with result. Will be dispatched to the main queue.
- (void)trackEvent:(nonnull NSString *)event
    withProperties:(nullable NSDictionary<NSString *, id> *)properties
        completion:(void (^ _Nullable)(NSError * _Nullable))completion;

/// Adds events to queue.
/// \param completion
/// Completion handler with result. Will be dispatched to the main queue.
- (void)trackEvents:(nonnull NSArray<AFUCREvent *> *)events
     withCompletion:(void (^ _Nullable)(NSError * _Nullable))completion;

/// Sends collected events to the server.
/// \param completion
/// Completion handler with result. Will be dispatched to the main queue.
/// <code>Int</code> value represents count of sended events.
- (void)sendEventsWithCompletion:(void (^ _Nullable)(NSInteger, NSError * _Nullable))completion;

- (nonnull instancetype)init __unavailable;
+ (nonnull instancetype)new __unavailable;

@end

NS_ASSUME_NONNULL_END
