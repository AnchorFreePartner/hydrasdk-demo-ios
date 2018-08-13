//
//  AFHydraCategorization.h
//  HydraSDK
//
//
// Copyright (c) 2017 Anchorfree Inc. All rights reserved.
//
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, AFHydraCategorizationResourceType) {
    AFHydraCategorizationResourceTypeNone = 0,
    AFHydraCategorizationResourceTypeURL = 1,
    AFHydraCategorizationResourceTypeIP = 2,
    AFHydraCategorizationResourceTypeDomain = 3
};

typedef NS_ENUM(NSInteger, AFHydraCategorizationResourceActionType) {
    AFHydraCategorizationResourceActionTypeProxy = 0,
    AFHydraCategorizationResourceActionTypeVPN = 1,
    AFHydraCategorizationResourceActionTypeBypass = 2,
    AFHydraCategorizationResourceActionTypeBlock = 3
};

@interface AFHydraCategorization : NSObject <NSSecureCoding>

@property (nonatomic, strong) NSString* resource;
@property (nonatomic) AFHydraCategorizationResourceType type;
@property (nonatomic, strong) NSString* category_label;
@property (nonatomic) NSUInteger category_id;
@property (nonatomic, strong) NSArray<NSString*>* sources;
@property (nonatomic) AFHydraCategorizationResourceActionType action;
@property (nonatomic, strong) NSDate* timestamp;

- (NSString*) stringRepresentationForType;
- (NSString*) stringRepresentationForAction;
- (NSString*) prettyDescription;


@end
