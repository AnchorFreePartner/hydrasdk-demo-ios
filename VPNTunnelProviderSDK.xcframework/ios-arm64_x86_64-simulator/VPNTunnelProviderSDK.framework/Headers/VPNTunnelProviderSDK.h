#import <Foundation/Foundation.h>
#import "AFHydraTunnelProvider.h"
#import "AFHydraNetworkInfo.h"
#import "NSData+Encryption.h"
#import "TunnelHelperObjC.h"
#import "hydra.h"
#import "hydra_sd.h"
#import "hydra_sd_compat.h"

//! Project version number for VPNTunnelProviderSDK.
FOUNDATION_EXPORT double VPNTunnelProviderSDKVersionNumber;

//! Project version string for VPNTunnelProviderSDK.
FOUNDATION_EXPORT const unsigned char VPNTunnelProviderSDKVersionString[];

static NSString *const _Nonnull AFTunnelProviderVersion = @"4.0.3";
static NSString *const _Nonnull AFTunnelErrorDomain = @"VPNSDK.TunnelError";
