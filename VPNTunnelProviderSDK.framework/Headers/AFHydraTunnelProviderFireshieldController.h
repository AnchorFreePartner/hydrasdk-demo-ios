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

@end
