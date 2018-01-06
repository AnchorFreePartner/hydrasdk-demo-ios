//
//  AFVPNSession.h
//  hydrasdk
//
//  Created by Igor Glotov on 12/15/17.
//  Copyright © 2017 northghost. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AFConfig;

typedef NS_ENUM(NSInteger, AFVPNManagerStatus);

@interface AFVPNSession : NSObject
@property(nonatomic) BOOL bypassEnabled;
@property(nonatomic) AFVPNManagerStatus status;
- (instancetype)initWithConfig:(AFConfig *)config;
@end
