#import <Foundation/Foundation.h>

@interface TunnelHelperObjC : NSObject

+ (void)sendPackets:(NSArray<NSData *> *)packets;

+ (int)persistantStorageCallbackWithPath:(char *)path
                                pathSize:(unsigned *)pathSize;

+ (void)cmdCallbackWithCode:(int)cmdCode
                        arg:(int)cmdArg
                       data:(const void *)data;

+ (NSArray<NSDictionary *> *)getHydraSdMainConnInfoSucceeded:(BOOL)succeeded;

+ (NSString *)getHydraVersion;

+ (NSString *)getHydraGlobalSessionId;

+ (void)systemDNSServersIPv4:(NSArray<NSString *> **)ipv4 ipv6:(NSArray<NSString *> **)ipv6;

@end
