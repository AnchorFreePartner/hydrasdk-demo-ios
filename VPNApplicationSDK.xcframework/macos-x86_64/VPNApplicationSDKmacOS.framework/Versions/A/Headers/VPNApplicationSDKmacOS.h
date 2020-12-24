//
//  VPNSDK_OSX.h
//  VPNSDK-OSX
//
//  Created by Nico on 31/01/2019.
//  Copyright © 2019 Anchorfree Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

//! Project version number for VPNSDK_OSX.
FOUNDATION_EXPORT double VPNSDK_OSXVersionNumber;

//! Project version string for VPNSDK_OSX.
FOUNDATION_EXPORT const unsigned char VPNSDK_OSXVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <VPNSDK_OSX/PublicHeader.h>

static NSString *const AFAPIErrorDomain = @"VPNSDK.APIError";
static NSString *const HydraStatusDidChange = @"hydrasdk.hydraStateDidChange";

#import "AFHydraSDK.h"
#import "AFHydraTunnelProviderConstants.h"
#import "AFUCRTracker.h"
