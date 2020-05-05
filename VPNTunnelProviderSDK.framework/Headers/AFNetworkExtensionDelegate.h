//
//  AFHydraTunnelProviderDelegate.h
//  VPNSDK-NE
//
//  Created by Dmitry Denyak on 2/18/19.
//  Copyright © 2019 Anchorfree Inc. All rights reserved.
//

@import Foundation;
@class AFHydraCategorization;
@class AFHydraDataCounter;
@class AFFireshieldController;
@class StartupOptions;

typedef NS_ENUM(NSInteger, AFNEErrorCode) {
    AFNEErrorCodeNoConfig = 1,
    AFNEErrorCodeNoGroupId = 2,
    AFNEErrorCodeInterfaceDidChange = 11,
};

typedef NS_ENUM(NSInteger, AFHydraErrorCode) {
    // custom
    AFHydraErrorCodeTimeout = 10,
    AFHydraErrorCodeIllegalState = 11,
    // hydra
    AFHydraErrorCodeConnectionDisrupted = 181,
    AFHydraErrorCodeConnectionNotEstablished = 182,
    AFHydraErrorCodeTokenInvalid = 186,
    AFHydraErrorCodeTrafficExceed = 191
};

@protocol AFNetworkExtensionDelegate <NSObject>
@optional
@property (strong, nonatomic) AFFireshieldController *fireshieldController;

- (void)vpnWillStartWithOptions:(StartupOptions *)options;
- (void)vpnDidStart;
- (void)vpnWillStop;
- (void)vpnWillGoToSleep;
- (void)vpnWillWakeUpFromSleep;
- (void)vpnError:(NSError *)error;
- (void)resourceBlocked:(AFHydraCategorization *)categorization;
- (void)vpnDataCounterDidUpdate:(AFHydraDataCounter *)dataCounter;

/*!
   @discussion This method only will be called if VPN is stopped with an error until completion block will be called, the extension will be in killswitch feature (no out/in going network packets will be delivered/received.
   If this method isn't implemented, then by default method `vpnWillStop` will be called without the killswitch feature.
   @param  completion pass `true` to the completion block if you want to restart the VPN extension without killing and using the same delegate object, otherwise, the new delegate object will be created.

*/
- (void)vpnWillStopWith:(nonnull void(^)(BOOL restart))completion;
@end
