//
//  VPNTunnelProviderSDK.h
//  VPNTunnelProviderSDK
//
//  Created by Dan Vasilev on 12.01.2021.
//  Copyright © 2021 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for VPNTunnelProviderSDK.
FOUNDATION_EXPORT double VPNTunnelProviderSDKVersionNumber;

//! Project version string for VPNTunnelProviderSDK.
FOUNDATION_EXPORT const unsigned char VPNTunnelProviderSDKVersionString[];

static NSString *const _Nonnull AFTunnelProviderVersion = @"3.1.9";

// In this header, you should import all the public headers of your framework using statements like #import <VPNTunnelProviderSDK/PublicHeader.h>

#import "AFHydraConfiguration.h"
#import "AFHydraCategorization.h"
#import "AFHydraTunnelProviderDelegate.h"
#import "AFHydraTunnelProviderInfo.h"
#import "AFHydraTunnelProviderConstants.h"
#import "AFNetworkExtensionDelegate.h"
#import "AFHydraNetworkInfo.h"
#import "AFResolver.h"
#import "AFFireshieldController.h"
#import "AFHydraDataCounter.h"
#import "AFUCRTracker.h"
