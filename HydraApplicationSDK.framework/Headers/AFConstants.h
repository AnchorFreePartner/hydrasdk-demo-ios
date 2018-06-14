//
//  AFConstants.h
//  hydrasdk
//
//  Created by Igor Glotov on 2/1/18.
//  Copyright © 2018 northghost. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "AFConfig.h"
#import "AFAuthMethod.h"
#import "AFUser.h"
#import "AFCredentials.h"
#import "AFCountry.h"
#import "AFRemainingTraffic.h"
#import "AFTrafficCounters.h"
#import "AFProvidedCredentials.h"
#import "AFPurchaseResponse.h"

NS_ASSUME_NONNULL_BEGIN

typedef void (^AFHydraLoginCompletion)(NSError *__nullable error, AFUser *__nullable user);

typedef void (^AFHydraCredentialsCompletion)(NSError *__nullable error, AFCredentials *__nullable credentials);

typedef void (^AFHydraCountriesCompletion)(NSError *__nullable error, NSArray<AFCountry *> *__nullable countries);

typedef void (^AFHydraLogoutCompletion)(NSError *__nullable error);

typedef void (^AFHydraRemainingTrafficCompletion)(NSError *__nullable error, AFRemainingTraffic *__nullable remainingTraffic);

typedef void (^AFHydraTrafficCountersCompletion)(NSError *__nullable error, AFTrafficCounters *__nullable trafficCounters);

typedef void (^AFHydraPurchaseCompletion)(NSError *__nullable error);

typedef void (^AFHydraCurrentUserCompletion)(NSError *__nullable error, AFUser *__nullable user);

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
    /*! @const AFHydraApiErrorCodeInvalidPurchase The receipt you are trying to verify is invalid.*/
    AFHydraApiErrorCodeInvalidPurchase = 110,
    /*! @const AFHydraApiErrorCodeUnknownServerResponse This response could mean you don't have latest HydraSDK. Please report to developers.*/
    AFHydraApiErrorCodeUnknownServerResponse = 111
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
    /*! @const AFVPNManagerErrorCodeAlreadyConnected VPN is already connected */
    AFVPNManagerErrorCodeAlreadyConnected = 205,
    /*! @const AFVPNManagerErrorCodeAlreadyDisconnected VPN is already disconnected */
    AFVPNManagerErrorCodeAlreadyDisconnected = 206,
    /*! @const AFVPNManagerErrorCodeConnectionInProgress VPN is already connecting */
    AFVPNManagerErrorCodeConnectionInProgress = 207

};


extern NSString *kAFHydraApiErrorDomain;
extern NSString *kAFVPNManagerErrorDomain;
extern NSString *kAFPacketTunnelProviderErrorDomain;
extern NSNotificationName const AFVPNStatusDidChangeNotification;
extern NSNotificationName const AFVPNCategorizationDidChangeNotification;

extern NSString *AFHydraVersion;

/*! @const AFPurchaseTypeApple Default purchase type for iOS devices. Production or development environment will be detected automatically */
extern NSString *AFPurchaseTypeApple;
extern NSString *AFHydraCommit;
extern NSString *AFHydraVersion;

@interface AFConstants : NSObject

@end

NS_ASSUME_NONNULL_END
