//
// Created by Igor Glotov on 1/19/18.
// Copyright (c) 2018 northghost. All rights reserved.
//

#import <Foundation/Foundation.h>
@class AFHydraCategorization;

typedef NS_ENUM(NSInteger, AFNEErrorCode) {
    AFNEErrorCodeNoConfig = 1,
    AFNEErrorCodeNoGroupId = 2,
    AFNEErrorCodeInterfaceDidChange = 11,
};
typedef NS_ENUM(NSInteger, AFHydraErrorCode) {
    AFHydraErrorCodeTimeout = 10,
    AFHydraErrorCodeIllegalState = 11,
    AFHydraErrorCodeConnectionDisrupted = 181,
    AFHydraErrorCodeConnectionNotEstablished = 182,
    AFHydraErrorCodeTokenInvalid = 186,
    AFHydraErrorCodeTrafficExceed = 191
};

static NSString *const AFHydraDomain = @"AFHydraDomain";
static NSString *const AFNEErrorDomain = @"AFNEErrorDomain";

@protocol AFNetworkExtensionDelegate <NSObject>
@optional
- (void)vpnWillStart;
- (void)vpnDidStart;
- (void)vpnError:(NSError *)error;
- (void)resourceBlocked:(AFHydraCategorization *)categorization;
@end
