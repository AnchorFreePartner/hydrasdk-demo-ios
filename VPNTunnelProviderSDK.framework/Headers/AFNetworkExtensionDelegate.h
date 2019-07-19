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

- (void)vpnWillStart;
- (void)vpnDidStart;
- (void)vpnWillStop;
- (void)vpnError:(NSError *)error;
- (void)resourceBlocked:(AFHydraCategorization *)categorization;
- (void)vpnDataCounterDidUpdate:(AFHydraDataCounter *)dataCounter;
@end
