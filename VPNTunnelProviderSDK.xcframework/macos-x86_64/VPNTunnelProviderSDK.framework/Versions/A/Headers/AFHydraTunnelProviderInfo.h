//
//  AFHydraTunnelProviderInfo.h
//  AFHydra
//
//  Copyright © 2018 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol AFHydraTunnelProviderInfo

- (NSArray*) hydraSdGetMainConnInfoSucceeded: (BOOL) succeeded;
- (NSString*) hydraGetVersion;
- (NSString*) hydraGetGlobalSessionId;

@end
