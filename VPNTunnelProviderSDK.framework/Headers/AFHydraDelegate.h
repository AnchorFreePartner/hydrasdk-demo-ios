//
//  AFHydraDelegate.h
//

#import <Foundation/Foundation.h>
#import "AFHydraTunnelProviderDelegate.h"

void AFNSLog(NSString *format, ...) {
    va_list args;
    va_start(args, format);
    NSString *newFormat = [@"[AFHydra] " stringByAppendingString:format];
    NSLogv(newFormat, args);
    va_end(args);
}


@interface AFHydraDelegate : NSObject <AFHydraTunnelProviderDelegate>

@end
