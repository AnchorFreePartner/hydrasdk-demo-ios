//
//  AFHydraTunnelProviderDelegate.h
//  AFHydra
//
//  Copyright © 2018 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NetworkExtension/NetworkExtension.h>
#import "AFHydraTunnelProviderInfo.h"
#import "AFHydraTunnelProviderFireshieldController.h"
#import "AFHydraConfiguration.h"

@class AFHydraDataCounter;
@class AFHydraCategorization;

@protocol AFHydraTunnelProviderDelegate

@optional
- (void) hydraTunnelProviderDidInitialize: (id<AFHydraTunnelProviderInfo>) hydraInfo withFireshieldController:(id<AFHydraTunnelProviderFireshieldController>) fireshieldController;
- (void) connectionWillStartWithConfiguration:(AFHydraConfiguration*)configuration withOptions: (NSDictionary*)options withProvider:(NETunnelProvider*)provider withCompletion: (void (^)(NSError* error, AFHydraConfiguration* newConfiguration)) completion;
- (void) connectionDidStartWithConfiguration:(AFHydraConfiguration*)configuration;
- (void) connectionWillEndWithConfiguration:(AFHydraConfiguration*)configuration withError:(NSError*) error withCompletion:(dispatch_block_t) completion;
- (void) categorizationBlockedConnection: (AFHydraCategorization*) categorization withProvider:(NEProvider*) provider;
- (void) hydraDataCounterUpdate: (AFHydraDataCounter*) dataCounter;
- (void) didReceiveMessage: (NSString*) message withUserInfo: (NSDictionary*) userInfo responseCompletion:(void (^)(NSDictionary * responseDictionary))response;
- (void) logMessage: (NSString*) logMessage withType:(AFHydraLoggingType) type;
@end

