//
//  VPNSDK.h
//  VPNSDK
//
//  Created by Dmitry Denyak on 12/4/18.
//  Copyright © 2018 Anchorfree Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for VPNSDK.
FOUNDATION_EXPORT double VPNSDKVersionNumber;

//! Project version string for VPNSDK.
FOUNDATION_EXPORT const unsigned char VPNSDKVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <VPNSDK/PublicHeader.h>

static NSString *const AFAPIErrorDomain = @"VPNSDK.APIError";
static NSString *const HydraStatusDidChange = @"hydrasdk.hydraStateDidChange";

#import "AFHydraSDK.h"
#import "AFHydraTunnelProviderConstants.h"
