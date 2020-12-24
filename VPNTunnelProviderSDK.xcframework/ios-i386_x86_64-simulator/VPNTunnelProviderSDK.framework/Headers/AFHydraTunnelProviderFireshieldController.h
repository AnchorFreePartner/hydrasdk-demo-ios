//
//  AFHydraTunnelProviderFireshieldController.h
//  AFHydra
//
//  Copyright © 2018 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, AFHydraCustomListCommandType) {
    AFHydraCustomListCommandTypeAdd = 0,
    AFHydraCustomListCommandTypeRemove = 1
};

typedef NS_ENUM(NSInteger, AFHydraCustomListResourceType) {
    AFHydraCustomListResourceTypeDomain = 0,
    AFHydraCustomListResourceTypeURL = 1
};

@protocol AFHydraTunnelProviderFireshieldController

- (nullable NSError*) updateCustomListWithItems: (NSArray<NSString*>*) items withCommand:(AFHydraCustomListCommandType) command withResourceType:(AFHydraCustomListResourceType) resourceType forCategory:(NSString*) category;

// Used to reconfigure hydra during runtime with new routing rules - expects a dictionary that will be converted to JSON and given directly to hydra.
- (nullable NSError*) hydraReconfigure:(NSMutableDictionary *)newHydraConfig;

- (NSUInteger) scannedConnections;

@end
