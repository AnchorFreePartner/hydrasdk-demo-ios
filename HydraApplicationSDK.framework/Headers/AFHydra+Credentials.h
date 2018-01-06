//
// Copyright (c) 2017 northghost. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFHydra.h"

@class AFProvidedCredentials;

@interface AFHydra (Credentials)
@property (strong, nonatomic) AFProvidedCredentials *credentials;
@end