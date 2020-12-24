//
//  AFResolver.h
//  AFHydra
//
//  Copyright © 2018 AnchorFree. All rights reserved.
//
//

#import <Foundation/Foundation.h>


typedef void (^AFResolverCompletion)(NSError *error, NSString *address);

@interface AFResolver : NSObject
+ (void)resolveHostAsIpv4:(NSString *)host completion:(AFResolverCompletion)completion;
@end
