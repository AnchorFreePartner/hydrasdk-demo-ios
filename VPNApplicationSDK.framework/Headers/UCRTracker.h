#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@interface AFSDKPrefixUCRTracker : NSObject
/*!
 @class
 AFSDKPrefixUCRTracker

 @abstract
 For documentation, see the Tracker.h 

 @discussion
 This header is copied to the resulting folder, when static lib target is built.
 Notice, that the name of the component is altered according to "Other C Flags"
 build settings. 
 */
+ (AFSDKPrefixUCRTracker *)sharedInstance;
+ (void)configureWithReportName:(NSString *)reportName;
+ (void)configureWithReportName:(NSString *)reportName keychainAccessGroup:(NSString *)keychainAccessGroup;
- (void)track:(NSString *)event;
- (void)track:(NSString *)event properties:(nullable NSDictionary *)properties;
- (void)track:(NSString *)event properties:(NSDictionary *)properties waitTime:(NSUInteger)secondsToWait withCompletion:(dispatch_block_t)completion;
- (void)registerSuperProperties:(NSDictionary *)properties;
- (void)registerSuperPropertiesOnce:(NSDictionary *)properties;
- (void)registerSuperPropertiesOnce:(NSDictionary *)properties defaultValue:(id)defaultValue;
- (void)unregisterSuperProperty:(NSString *)propertyName;
- (void)clearSuperProperties;
- (void)flush;
- (void)flush:(void(^)(void))completion;
- (void)archive;
- (NSString *)IFA;
- (NSString *)libVersion;
- (NSString *)defaultDistinctId;
- (NSString *)deviceIdentifier;
- (void)setServerProtocol:(nullable NSString *)serverProtocol;
- (nullable NSString *)serverProtocol;
- (void)setAppName:(nullable NSString *)appName;
- (nullable NSString *)appName;
- (void)setFlushInterval:(NSUInteger)flushInterval;
@end
NS_ASSUME_NONNULL_END
