//
//  AFHydra.h
//
//  Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

@import Foundation;

#import "AFVPNSession.h"
#import "AFHydraCategorization.h"
#import "AFConstants.h"

/*!
 * For constants such as error Domains, Notifications and others
 * See AFConstants.h
 */

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class AFHydra
 * @description All NSError objects are of kAFHydraApiErrorDomain domain by default, if not declared otherwise.
 */
@interface AFHydra : NSObject
@property(strong, nonatomic, readonly) NSNotificationCenter *notificationCenter;
@property(strong, nonatomic, readonly) AFConfig *config;
@property(readonly) AFVPNSession *vpnSession;

- (nonnull instancetype)initWithConfig:(AFConfig *)config;

+ (nonnull instancetype)withConfig:(AFConfig *)config;

/*!
 * @method updateConfig
 * @description Updates VPN configuration in realtime without restarting VPN session.
 * Only blacklistPath, whitelistPath and fireshieldMode are now supported.
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
 * @description Provides traffic counters for current session, in bytes.
 * @param completion NSError is of kAFVPNManagerErrorDomain.
 */
- (void)trafficCounters:(nonnull AFHydraTrafficCountersCompletion)completion;

- (void)currentUser:(nonnull AFHydraCurrentUserCompletion)completion;

/*!
 * @method installVpnProfile
 * @discussion Triggers iOS VPN subsystem to create/update VPN profile, showing user permission "Allow / Don't Allow" dialog.
 * Calling this method is not required. Useful for custom tutorial implementation.
 * NOTE: If you're using onDemand VPN feature, this installed profile WILL be triggered by system and VPN will be enabled.
 * @param completion NSError is of kAFVPNManagerErrorDomain.
 */
- (void)installVpnProfile:(nullable void (^)(NSError *__nullable))completion;

- (void)startVpn:(nullable void (^)(AFCountry *__nullable country, NSError *__nullable error))completion;

- (void)startVpnWithCountry:(AFCountry *__nullable)country completion:(nullable void (^)(AFCountry *__nullable, NSError *__nullable))completion;

- (void)stopVpn:(nullable void (^)(NSError *__nullable error))completion;

- (NSDate *)connectedDate;

/*!
 * @method removeProfile
 * @description Removes VPN profile from device. Current VPN connection will be interrupted. Useful for troubleshooting end-user issues.
 * @param completion NSError is of kAFVPNManagerErrorDomain.
 */
- (void)removeProfile:(void (^)(NSError *__nullable error))completion;

- (AFVPNManagerStatus)vpnStatus;

- (nullable NSError *)lastError;

- (void)purchase:(NSString *)receipt type:(NSString *)type completion:(AFHydraPurchaseCompletion)completion;

- (nullable NSString *)accessToken;

- (nonnull NSString *)deviceId;

- (AFHydraCategorization *)lastCategorization;
- (void)getScannedConnections:(nonnull void (^)(NSUInteger scannedConnections, NSError *__nullable error))completion;

@end

NS_ASSUME_NONNULL_END

