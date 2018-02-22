//
// Copyright (c) 2017 northghost. All rights reserved.
//

@import Foundation;
#import "AFHydra.h"

@interface AFHydra (AFHash)
- (void)login:(AFAuthMethod *)method afHash:(NSString *)afHash completion:(AFHydraLoginCompletion)completion;
@end
