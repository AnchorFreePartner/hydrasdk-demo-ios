//
//  AFHydra.h
//
//  Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFConfig.h"
#import "AFAuthMethod.h"
#import "AFUser.h"
#import "AFCredentials.h"
#import "AFCountry.h"
#import "AFRemainingTraffic.h"
#import "AFTrafficCounters.h"

typedef NS_ENUM(NSInteger, AFVPNManagerStatus) {
    AFVPNManagerStatusUndefined = -1,
    AFVPNManagerStatusInvalid = 0,
    AFVPNManagerStatusDisconnected = 1,
    AFVPNManagerStatusConnecting = 2,
    AFVPNManagerStatusConnected = 3,
    AFVPNManagerStatusReconnecting = 4,
    AFVPNManagerStatusDisconnecting = 5,
};

typedef NS_ENUM(NSInteger, AFHydraApiErrorCode) {
    /*! @const AFHydraApiErrorCodeUndefined This is a generic unknown error, please report such errors to developers */
    AFHydraApiErrorCodeUndefined = 101,
    /*! @const AFHydraApiErrorCodeSessionsExceed Amount of allowed sessions for this user is exceed */
    AFHydraApiErrorCodeSessionsExceed = 102,
    /*! @const AFHydraApiErrorCodeTrafficExceed Amount of allowed traffic for this user is exceed */
    AFHydraApiErrorCodeTrafficExceed = 103,
    /*! @const AFHydraApiErrorCodeUnauthorized This user is unauthorized or login operation is still pending */
    AFHydraApiErrorCodeUnauthorized = 104,
    /*! @const AFHydraApiErrorCodeUserSuspended This user is suspended */
    AFHydraApiErrorCodeUserSuspended = 105,
    /*! @const AFHydraApiErrorCodeRequestedVPNServerUnavailable Selected server or country code is not available */
    AFHydraApiErrorCodeRequestedVPNServerUnavailable = 106,
    /*! @const AFHydraApiErrorCodeCredentialsInternalError Server was unable to fetch credentials for this country code */
    AFHydraApiErrorCodeCredentialsInternalError = 107,
    /*! @const AFHydraApiErrorCodeDevicesExceed The amount of allowed devices for this user is exceed */
    AFHydraApiErrorCodeDevicesExceed = 108,
    /*! @const AFHydraApiErrorCodeNetworkError The Internets are not available or network request has failed. Feel free to try again */
    AFHydraApiErrorCodeNetworkError = 109,
    /*! @const AFHydraApiErrorCodeUnknownServerResponse This response could mean you don't have latest HydraSDK. Please report to developers.*/
    AFHydraApiErrorCodeUnknownServerResponse = 110,
};

typedef NS_ENUM(NSInteger, AFVPNManagerErrorCode) {
    /*! @const AFVPNManagerErrorCode This is a generic unknown error, please report such errors to developers */
    AFVPNManagerErrorCodeUndefined = 201,
    /*! @const AFVPNManagerErrorCodeTrafficCounters error during retrieving traffic counters */
    AFVPNManagerErrorCodeTrafficCounters = 202,
    /*! @const AFVPNManagerErrorCodeStartVPNTunnelFailed NETunnelProviderSession failed to start, see NSUnderlyingErrorKey for detailed reason */
    AFVPNManagerErrorCodeStartVPNTunnelFailed = 203,
    /*! @const AFVPNManagerErrorCodeNoProfile VPN profile does not exist */
    AFVPNManagerErrorCodeNoProfile = 204,
    /*! @const AFVPNManagerErrorCodeNoProfile VPN is already connected */
    AFVPNManagerErrorCodeAlreadyConnected = 205,
    /*! @const AFVPNManagerErrorCodeNoProfile VPN is already disconnected */
    AFVPNManagerErrorCodeAlreadyDisconnected = 206
};

NS_ASSUME_NONNULL_BEGIN

extern NSString *kAFHydraApiErrorDomain;
extern NSString *kAFVPNManagerErrorDomain;
extern NSString *AFVPNStatusDidChangeNotification;

/*! @const AFPurchaseTypeApple Default purchase type for iOS devices. Production or development environment will be detected automatically */
extern NSString *AFPurchaseTypeApple;

typedef void (^AFHydraLoginCompletion)(NSError *__nullable error, AFUser *__nullable user);

typedef void (^AFHydraCredentialsCompletion)(NSError *__nullable error, AFCredentials *__nullable credentials);

typedef void (^AFHydraCountriesCompletion)(NSError *__nullable error, NSArray<AFCountry *> *__nullable countries);

typedef void (^AFHydraLogoutCompletion)(NSError *__nullable error);

typedef void (^AFHydraRemainingTrafficCompletion)(NSError *__nullable error, AFRemainingTraffic *__nullable remainingTraffic);

typedef void (^AFHydraTrafficCountersCompletion)(NSError *__nullable error, AFTrafficCounters *__nullable trafficCounters);

typedef void (^AFHydraPurchaseCompletion)(NSError *error);

typedef void (^AFHydraCurrentUserCompletion)(NSError *__nullable error, AFUser *__nullable user);

typedef void (^AFHydraBlockedDomainsCompletion)(NSDictionary<NSString *, NSNumber *> *domainsCount);

/*!
 * @class AFHydra
 * @discussion All NSError objects are of kAFHydraApiErrorDomain domain by default, if not declared otherwise.
 */
@interface AFHydra : NSObject
@property(strong, nonatomic) NSNotificationCenter *notificationCenter;

- (nonnull instancetype)initWithConfig:(AFConfig *)config;

+ (nonnull instancetype)withConfig:(AFConfig *)config;

/*!
 * @method updateConfig
 * @discussion Updates VPN configuration in realtime without restarting VPN session.
 * Only blacklistPath and whitelistPath are now supported.
 * @param config A config with parameters to update. If you want to remove some parameter, set it to `nil`.
 */
- (BOOL)updateConfig:(AFConfig *)config;

- (void)login:(AFAuthMethod *)method completion:(nonnull AFHydraLoginCompletion)completion;

- (void)logout:(nonnull AFHydraLogoutCompletion)completion;

- (BOOL)isLoggedIn;

- (void)availableCountries:(nonnull AFHydraCountriesCompletion)completion;

- (void)remainingTraffic:(nonnull AFHydraRemainingTrafficCompletion)completion;

/*!
 * @method trafficCounters
 * @discussion Provides traffic counters for current session, in bytes.
 * @param completion NSError is of kAFVPNManagerErrorDomain.
 */
- (void)trafficCounters:(nonnull AFHydraTrafficCountersCompletion)completion;

- (void)currentUser:(nonnull AFHydraCurrentUserCompletion)completion;

- (void)startVpn:(nullable void (^)(NSError *__nullable error))completion;

- (void)startVpnWithCountry:(AFCountry *__nullable)country completion:(nullable void (^)(NSError *__nullable error))completion;

- (void)stopVpn:(nullable void (^)(NSError *__nullable error))completion;

- (NSDate *)connectedDate;

/*!
 * @method removeProfile
 * @discussion Removes VPN profile from device. Current VPN connection will be interrupted. Useful for troubleshooting end-user issues.
 * @param completion NSError is of kAFVPNManagerErrorDomain.
 */
- (void)removeProfile:(void (^)(NSError *))completion;

- (AFVPNManagerStatus)vpnStatus;

- (NSError *)lastError;

// Purchase server validation

- (void)purchase:(NSString *)receipt type:(NSString *)type completion:(AFHydraPurchaseCompletion)completion;

// Ad blocking management

/*!
 * @method blockedDomains
 * @discussion Get domains list that got blocked by blacklist rules. Returns NSDictionary, key is a FQDN, value is a NSNumber,
 * how many times this domain was blocked.
 * @param completion completionBlock
 */
- (void)blockedDomains:(AFHydraBlockedDomainsCompletion)completion;

- (nullable NSString *)accessToken;

- (nonnull NSString *)deviceId;
@end

NS_ASSUME_NONNULL_END
