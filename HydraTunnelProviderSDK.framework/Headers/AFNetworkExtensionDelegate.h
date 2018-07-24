//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

@import Foundation;
@class AFHydraCategorization;

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
- (void)vpnWillStart;
- (void)vpnDidStart;
- (void)vpnError:(NSError *)error;
- (void)resourceBlocked:(AFHydraCategorization *)categorization;
@end
