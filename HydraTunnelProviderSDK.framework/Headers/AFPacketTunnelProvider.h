//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//

@import Foundation;
@import NetworkExtension;

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
    AFHydraErrorCodeTrafficExceed = 191
};

static NSString *const AFHydraDomain = @"AFHydraDomain";
static NSString *const AFNEErrorDomain = @"AFNEErrorDomain";

@interface AFPacketTunnelProvider : NEPacketTunnelProvider
- (void)vpnWillStart;
- (void)vpnDidStart;
- (void)vpnError:(NSError *)error;
@end
