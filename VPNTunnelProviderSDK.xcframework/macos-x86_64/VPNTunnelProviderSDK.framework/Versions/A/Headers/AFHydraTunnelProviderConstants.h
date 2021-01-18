//
//  AFHydraTunnelProviderConstants.h
//  AFHydra
//
//  Copyright © 2018 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT NSErrorDomain const AFHydraInternalErrorDomain;

FOUNDATION_EXPORT NSErrorDomain const AFHydraErrorDomain;

NS_ERROR_ENUM(AFHydraErrorDomain)
{
    // Configuration errors
    AFHydraErrorBadConfiguration = 1,
    
    AFHydraErrorRouteSetupFailed = 2,
    AFHydraErrorTunInterfaceFailure = 3,
    AFHydraErrorInterfaceChange = 4,
    AFHydraErrorSystemCalledStop = 5,
    AFHydraErrorSystemCalledSleep = 6,
    AFHydraErrorFromHydra = 7,
    AFHydraErrorConnectionTimeout = 8,
    AFHydraErrorConnectionCancelled = 9,
    
    // Fireshield custom list errors
    AFHydraErrorFireshieldCustomListHydraNotStarted = 10,
    AFHydraErrorFireshieldCustomListNoItems = 11,
    AFHydraErrorFireshieldCustomListNoCategory = 12,
    AFHydraErrorFireshieldCustomListInvalidCategory = 13,
    AFHydraErrorFireshieldCustomListFailedToCreateRequest = 14,
    AFHydraErrorFireshieldCustomListFailedToAddRule = 15,
    AFHydraErrorFireshieldCustomListFailedToApplyRules = 16,
    
    // Hydra reconfigure errors
    AFHydraErrorReconfigureInvalidJSON = 17,
    AFHydraErrorReconfigureHydraNotRunning = 18,
    AFHydraErrorReconfigureHydraError = 19,
    
    AFHydraErrorUnknownFailure = 20
};
