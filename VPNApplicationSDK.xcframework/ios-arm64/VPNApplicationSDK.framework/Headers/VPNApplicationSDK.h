#import <Foundation/Foundation.h>
#import "AFHydraNetworkInfo.h"
#import "NSData+Encryption.h"

//! Project version number for VPNApplicationSDK.
FOUNDATION_EXPORT double VPNApplicationSDKVersionNumber;

//! Project version string for VPNApplicationSDK.
FOUNDATION_EXPORT const unsigned char VPNApplicationSDKVersionString[];

static NSString *const _Nonnull AFAPIErrorDomain = @"VPNSDK.APIError";
static NSString *const _Nonnull AFTunnelErrorDomain = @"VPNSDK.TunnelError";
static NSString *const _Nonnull AFTransportErrorDomain = @"VPNSDK.TransportError";
static NSString *const _Nonnull VPNStateDidChange = @"vpnsdk.vpnStateDidChange";
