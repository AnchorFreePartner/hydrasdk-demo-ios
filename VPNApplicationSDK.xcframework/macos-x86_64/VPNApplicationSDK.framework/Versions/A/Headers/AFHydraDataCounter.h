//
//  AFHydraDataCounter.h
//  AFHydra
//
//  Copyright © 2018 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AFHydraDataCounter : NSObject <NSSecureCoding>

@property (nonatomic, readonly) uint64_t bytesSent;
@property (nonatomic, readonly) uint64_t bytesReceived;
@property (nonatomic, readonly) NSDate* updateTime;

- (instancetype) initWithBytesSent: (uint64_t) sent withBytesReceived: (uint64_t) received withUpdateTime: (NSDate*) updateTime;

@end
