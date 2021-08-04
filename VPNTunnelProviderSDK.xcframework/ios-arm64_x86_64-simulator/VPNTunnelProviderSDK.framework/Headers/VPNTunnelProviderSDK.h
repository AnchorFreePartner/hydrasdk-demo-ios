//
//  VPNSDK_NE.h
//  VPNSDK-NE
//
//  Created by Nico on 12/02/2019.
//  Copyright © 2019 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for VPNSDK_NE.
FOUNDATION_EXPORT double VPNSDK_NEVersionNumber;

//! Project version string for VPNSDK_NE.
FOUNDATION_EXPORT const unsigned char VPNSDK_NEVersionString[];

static NSString *const _Nonnull AFTunnelProviderVersion = @"3.2.1";

// In this header, you should import all the public headers of your framework using statements like #import <VPNSDK_NE/PublicHeader.h>

#import "AFHydraConfiguration.h"
#import "AFHydraCategorization.h"
#import "AFHydraTunnelProviderDelegate.h"
#import "AFHydraTunnelProviderInfo.h"
#import "AFHydraTunnelProviderConstants.h"
#import "AFHydraNetworkInfo.h"
#import "AFResolver.h"
#import "AFNetworkExtensionDelegate.h"
#import "AFHydraDataCounter.h"
#import "AFFireshieldController.h"
