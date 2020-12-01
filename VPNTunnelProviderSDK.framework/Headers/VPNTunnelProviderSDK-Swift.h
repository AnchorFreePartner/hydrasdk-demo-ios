#if 0
#elif defined(__arm64__) && __arm64__
// Generated by Apple Swift version 5.3.1 (swiftlang-1200.0.41 clang-1200.0.32.8)
#ifndef VPNTUNNELPROVIDERSDK_SWIFT_H
#define VPNTUNNELPROVIDERSDK_SWIFT_H
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat"

#if !defined(__has_include)
# define __has_include(x) 0
#endif
#if !defined(__has_attribute)
# define __has_attribute(x) 0
#endif
#if !defined(__has_feature)
# define __has_feature(x) 0
#endif
#if !defined(__has_warning)
# define __has_warning(x) 0
#endif

#if __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wauto-import"
#include <Foundation/Foundation.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if !defined(SWIFT_TYPEDEFS)
# define SWIFT_TYPEDEFS 1
# if __has_include(<uchar.h>)
#  include <uchar.h>
# elif !defined(__cplusplus)
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
# endif
typedef float swift_float2  __attribute__((__ext_vector_type__(2)));
typedef float swift_float3  __attribute__((__ext_vector_type__(3)));
typedef float swift_float4  __attribute__((__ext_vector_type__(4)));
typedef double swift_double2  __attribute__((__ext_vector_type__(2)));
typedef double swift_double3  __attribute__((__ext_vector_type__(3)));
typedef double swift_double4  __attribute__((__ext_vector_type__(4)));
typedef int swift_int2  __attribute__((__ext_vector_type__(2)));
typedef int swift_int3  __attribute__((__ext_vector_type__(3)));
typedef int swift_int4  __attribute__((__ext_vector_type__(4)));
typedef unsigned int swift_uint2  __attribute__((__ext_vector_type__(2)));
typedef unsigned int swift_uint3  __attribute__((__ext_vector_type__(3)));
typedef unsigned int swift_uint4  __attribute__((__ext_vector_type__(4)));
#endif

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif
#if !defined(SWIFT_CLASS_PROPERTY)
# if __has_feature(objc_class_property)
#  define SWIFT_CLASS_PROPERTY(...) __VA_ARGS__
# else
#  define SWIFT_CLASS_PROPERTY(...)
# endif
#endif

#if __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if __has_attribute(swift_name)
# define SWIFT_COMPILE_NAME(X) __attribute__((swift_name(X)))
#else
# define SWIFT_COMPILE_NAME(X)
#endif
#if __has_attribute(objc_method_family)
# define SWIFT_METHOD_FAMILY(X) __attribute__((objc_method_family(X)))
#else
# define SWIFT_METHOD_FAMILY(X)
#endif
#if __has_attribute(noescape)
# define SWIFT_NOESCAPE __attribute__((noescape))
#else
# define SWIFT_NOESCAPE
#endif
#if __has_attribute(ns_consumed)
# define SWIFT_RELEASES_ARGUMENT __attribute__((ns_consumed))
#else
# define SWIFT_RELEASES_ARGUMENT
#endif
#if __has_attribute(warn_unused_result)
# define SWIFT_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
# define SWIFT_WARN_UNUSED_RESULT
#endif
#if __has_attribute(noreturn)
# define SWIFT_NORETURN __attribute__((noreturn))
#else
# define SWIFT_NORETURN
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_ENUM_EXTRA)
# define SWIFT_ENUM_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if __has_attribute(objc_subclassing_restricted)
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif
#if !defined(SWIFT_RESILIENT_CLASS)
# if __has_attribute(objc_class_stub)
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME) __attribute__((objc_class_stub))
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_class_stub)) SWIFT_CLASS_NAMED(SWIFT_NAME)
# else
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME)
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) SWIFT_CLASS_NAMED(SWIFT_NAME)
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
# define SWIFT_PROTOCOL_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if !defined(SWIFT_ENUM_ATTR)
# if defined(__has_attribute) && __has_attribute(enum_extensibility)
#  define SWIFT_ENUM_ATTR(_extensibility) __attribute__((enum_extensibility(_extensibility)))
# else
#  define SWIFT_ENUM_ATTR(_extensibility)
# endif
#endif
#if !defined(SWIFT_ENUM)
# define SWIFT_ENUM(_type, _name, _extensibility) enum _name : _type _name; enum SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# if __has_feature(generalized_swift_name)
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) enum _name : _type _name SWIFT_COMPILE_NAME(SWIFT_NAME); enum SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# else
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) SWIFT_ENUM(_type, _name, _extensibility)
# endif
#endif
#if !defined(SWIFT_UNAVAILABLE)
# define SWIFT_UNAVAILABLE __attribute__((unavailable))
#endif
#if !defined(SWIFT_UNAVAILABLE_MSG)
# define SWIFT_UNAVAILABLE_MSG(msg) __attribute__((unavailable(msg)))
#endif
#if !defined(SWIFT_AVAILABILITY)
# define SWIFT_AVAILABILITY(plat, ...) __attribute__((availability(plat, __VA_ARGS__)))
#endif
#if !defined(SWIFT_WEAK_IMPORT)
# define SWIFT_WEAK_IMPORT __attribute__((weak_import))
#endif
#if !defined(SWIFT_DEPRECATED)
# define SWIFT_DEPRECATED __attribute__((deprecated))
#endif
#if !defined(SWIFT_DEPRECATED_MSG)
# define SWIFT_DEPRECATED_MSG(...) __attribute__((deprecated(__VA_ARGS__)))
#endif
#if __has_feature(attribute_diagnose_if_objc)
# define SWIFT_DEPRECATED_OBJC(Msg) __attribute__((diagnose_if(1, Msg, "warning")))
#else
# define SWIFT_DEPRECATED_OBJC(Msg) SWIFT_DEPRECATED_MSG(Msg)
#endif
#if !defined(IBSegueAction)
# define IBSegueAction
#endif
#if __has_feature(modules)
#if __has_warning("-Watimport-in-framework-header")
#pragma clang diagnostic ignored "-Watimport-in-framework-header"
#endif
@import Foundation;
@import ObjectiveC;
#endif

#import <VPNTunnelProviderSDK/VPNTunnelProviderSDK.h>

#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"
#if __has_warning("-Wpragma-clang-attribute")
# pragma clang diagnostic ignored "-Wpragma-clang-attribute"
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wnullability"

#if __has_attribute(external_source_symbol)
# pragma push_macro("any")
# undef any
# pragma clang attribute push(__attribute__((external_source_symbol(language="Swift", defined_in="VPNTunnelProviderSDK",generated_declaration))), apply_to=any(function,enum,objc_interface,objc_category,objc_protocol))
# pragma pop_macro("any")
#endif


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK14AFCategoryType")
@interface AFCategoryType : NSObject
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) AFCategoryType * _Nonnull safe;)
+ (AFCategoryType * _Nonnull)safe SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) AFCategoryType * _Nonnull unsafe;)
+ (AFCategoryType * _Nonnull)unsafe SWIFT_WARN_UNUSED_RESULT;
@property (nonatomic, readonly, copy) NSString * _Nonnull representation;
- (nonnull instancetype)initWithCustom:(NSString * _Nonnull)custom OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)initWithUnsafeCustom:(NSString * _Nonnull)unsafeCustom OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

enum AFClientNetworkConfigurationAction : NSInteger;

SWIFT_CLASS("_TtC20VPNTunnelProviderSDK28AFClientNetworkConfiguration")
@interface AFClientNetworkConfiguration : NSObject
@property (nonatomic, readonly) enum AFClientNetworkConfigurationAction action;
@property (nonatomic, readonly, copy) NSString * _Nullable networkType;
@property (nonatomic, readonly, copy) NSArray<NSString *> * _Nullable ssid;
@property (nonatomic, readonly, copy) NSArray<NSString *> * _Nullable bssid;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

typedef SWIFT_ENUM(NSInteger, AFClientNetworkConfigurationAction, open) {
  AFClientNetworkConfigurationActionEnable = 0,
  AFClientNetworkConfigurationActionDisable = 1,
  AFClientNetworkConfigurationActionEmpty = 2,
};


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK19AFClientNetworkList")
@interface AFClientNetworkList : NSObject
@property (nonatomic, readonly, copy) NSArray<AFClientNetworkConfiguration *> * _Nonnull configurations;
- (AFClientNetworkConfiguration * _Nullable)findWithSsid:(NSString * _Nonnull)ssid SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK20AFFireshieldCategory")
@interface AFFireshieldCategory : NSObject
+ (AFFireshieldCategory * _Nonnull)blockWithCategory:(AFCategoryType * _Nonnull)category SWIFT_WARN_UNUSED_RESULT;
+ (AFFireshieldCategory * _Nonnull)proxyWithCategory:(AFCategoryType * _Nonnull)category SWIFT_WARN_UNUSED_RESULT;
+ (AFFireshieldCategory * _Nonnull)bypassWithCategory:(AFCategoryType * _Nonnull)category SWIFT_WARN_UNUSED_RESULT;
+ (AFFireshieldCategory * _Nonnull)alertWithCategory:(AFCategoryType * _Nonnull)category SWIFT_WARN_UNUSED_RESULT;
+ (NSString * _Nonnull)categoryNameFrom:(AFCategoryType * _Nonnull)category SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

typedef SWIFT_ENUM(NSInteger, Action, open) {
  ActionProxy = 0,
  ActionBypass = 1,
  ActionBlock = 2,
  ActionAlert = 3,
};


@interface AFHydraConfiguration (SWIFT_EXTENSION(VPNTunnelProviderSDK))
@property (nonatomic, readonly, copy) NSString * _Nullable configurationHash;
@property (nonatomic, readonly, copy) NSArray<NSDictionary<NSString *, NSArray<NSDictionary<NSString *, NSString *> *> *> *> * _Nullable sections;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK13CNLRepository")
@interface CNLRepository : NSObject
@property (nonatomic) BOOL isClientListEnabled;
- (nonnull instancetype)initWithSuitName:(NSString * _Nonnull)suitName OBJC_DESIGNATED_INITIALIZER;
@property (nonatomic, readonly, strong) AFClientNetworkList * _Nullable list;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_PROTOCOL("_TtP20VPNTunnelProviderSDK9LogSource_")
@protocol LogSource
- (void)logWithString:(NSString * _Nonnull)string;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK16ConsoleLogSource")
@interface ConsoleLogSource : NSObject <LogSource>
- (void)logWithString:(NSString * _Nonnull)string;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK17CredentialManager")
@interface CredentialManager : NSObject
- (nonnull instancetype)initWithSuitName:(NSString * _Nonnull)suitName OBJC_DESIGNATED_INITIALIZER;
- (void)verifyCredentialsWithCompletion:(void (^ _Nonnull)(NSError * _Nullable))completion;
- (void)updateCredentialsFor:(NSDictionary<NSString *, id> * _Nonnull)config completion:(void (^ _Nonnull)(NSError * _Nullable, NSDictionary<NSString *, id> * _Nullable))completion;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK13FileLogSource")
@interface FileLogSource : NSObject <LogSource>
- (nonnull instancetype)initWithFileURL:(NSURL * _Nonnull)fileURL OBJC_DESIGNATED_INITIALIZER;
- (void)logWithString:(NSString * _Nonnull)string;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


@interface FileLogSource (SWIFT_EXTENSION(VPNTunnelProviderSDK))
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, copy) NSString * _Nonnull extensionFileName;)
+ (NSString * _Nonnull)extensionFileName SWIFT_WARN_UNUSED_RESULT;
@end



SWIFT_CLASS("_TtC20VPNTunnelProviderSDK17NetworkIdentifier")
@interface NetworkIdentifier : NSObject
@property (nonatomic, readonly, copy) NSString * _Nullable ssid;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK14StartupOptions")
@interface StartupOptions : NSObject
@property (nonatomic, readonly) BOOL isBypassEnabled;
- (nonnull instancetype)initWithIsBypassEnabled:(BOOL)isBypassEnabled OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK22UserDefaultsRepository")
@interface UserDefaultsRepository : NSObject
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

@class NSNumber;

SWIFT_CLASS("_TtC20VPNTunnelProviderSDK17VPNConnectionData")
@interface VPNConnectionData : NSObject
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VPNConnectionData * _Nonnull instance;)
+ (VPNConnectionData * _Nonnull)instance SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@property (nonatomic, copy) NSString * _Nonnull appGroup;
@property (nonatomic, readonly) BOOL hasActiveSession;
- (void)registerStartAttemptWithTriggeredByUser:(BOOL)triggeredByUser;
- (void)registerDidStart;
- (void)registerWillStopWithTriggeredByUser:(BOOL)triggeredByUser;
- (void)setConnectionInfoWithServerIP:(NSString * _Nullable)serverIP sessionID:(NSString * _Nullable)sessionID;
- (void)setCountryCode:(NSString * _Nullable)newValue;
- (void)setTrafficInfoWithBytesIn:(NSNumber * _Nullable)bytesIn bytesOut:(NSNumber * _Nullable)bytesOut;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK6VPNLog")
@interface VPNLog : NSObject
+ (void)setLogSourceWithArray:(NSArray<id <LogSource>> * _Nonnull)array;
+ (void)verbose:(NSString * _Nonnull)string;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK10VPNTracker")
@interface VPNTracker : NSObject
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VPNTracker * _Nonnull instance;)
+ (VPNTracker * _Nonnull)instance SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
- (void)setupWithAppGroup:(NSString * _Nullable)appGroup sdkVersion:(NSString * _Nullable)sdkVersion hydraVersion:(NSString * _Nullable)hydraVersion projectID:(NSString * _Nullable)projectID;
- (void)setSendEventsInterval:(NSTimeInterval)interval;
- (void)reportConnectionStartWithError:(NSError * _Nullable)error isStartedFromSleep:(BOOL)isStartedFromSleep;
- (void)reportConnectionEndWithError:(NSError * _Nullable)error isGoingToSleep:(BOOL)isGoingToSleep completion:(void (^ _Nullable)(void))completion;
@end

#if __has_attribute(external_source_symbol)
# pragma clang attribute pop
#endif
#pragma clang diagnostic pop
#endif

#elif defined(__ARM_ARCH_7A__) && __ARM_ARCH_7A__
// Generated by Apple Swift version 5.3.1 (swiftlang-1200.0.41 clang-1200.0.32.8)
#ifndef VPNTUNNELPROVIDERSDK_SWIFT_H
#define VPNTUNNELPROVIDERSDK_SWIFT_H
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat"

#if !defined(__has_include)
# define __has_include(x) 0
#endif
#if !defined(__has_attribute)
# define __has_attribute(x) 0
#endif
#if !defined(__has_feature)
# define __has_feature(x) 0
#endif
#if !defined(__has_warning)
# define __has_warning(x) 0
#endif

#if __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wauto-import"
#include <Foundation/Foundation.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if !defined(SWIFT_TYPEDEFS)
# define SWIFT_TYPEDEFS 1
# if __has_include(<uchar.h>)
#  include <uchar.h>
# elif !defined(__cplusplus)
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
# endif
typedef float swift_float2  __attribute__((__ext_vector_type__(2)));
typedef float swift_float3  __attribute__((__ext_vector_type__(3)));
typedef float swift_float4  __attribute__((__ext_vector_type__(4)));
typedef double swift_double2  __attribute__((__ext_vector_type__(2)));
typedef double swift_double3  __attribute__((__ext_vector_type__(3)));
typedef double swift_double4  __attribute__((__ext_vector_type__(4)));
typedef int swift_int2  __attribute__((__ext_vector_type__(2)));
typedef int swift_int3  __attribute__((__ext_vector_type__(3)));
typedef int swift_int4  __attribute__((__ext_vector_type__(4)));
typedef unsigned int swift_uint2  __attribute__((__ext_vector_type__(2)));
typedef unsigned int swift_uint3  __attribute__((__ext_vector_type__(3)));
typedef unsigned int swift_uint4  __attribute__((__ext_vector_type__(4)));
#endif

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif
#if !defined(SWIFT_CLASS_PROPERTY)
# if __has_feature(objc_class_property)
#  define SWIFT_CLASS_PROPERTY(...) __VA_ARGS__
# else
#  define SWIFT_CLASS_PROPERTY(...)
# endif
#endif

#if __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if __has_attribute(swift_name)
# define SWIFT_COMPILE_NAME(X) __attribute__((swift_name(X)))
#else
# define SWIFT_COMPILE_NAME(X)
#endif
#if __has_attribute(objc_method_family)
# define SWIFT_METHOD_FAMILY(X) __attribute__((objc_method_family(X)))
#else
# define SWIFT_METHOD_FAMILY(X)
#endif
#if __has_attribute(noescape)
# define SWIFT_NOESCAPE __attribute__((noescape))
#else
# define SWIFT_NOESCAPE
#endif
#if __has_attribute(ns_consumed)
# define SWIFT_RELEASES_ARGUMENT __attribute__((ns_consumed))
#else
# define SWIFT_RELEASES_ARGUMENT
#endif
#if __has_attribute(warn_unused_result)
# define SWIFT_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
# define SWIFT_WARN_UNUSED_RESULT
#endif
#if __has_attribute(noreturn)
# define SWIFT_NORETURN __attribute__((noreturn))
#else
# define SWIFT_NORETURN
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_ENUM_EXTRA)
# define SWIFT_ENUM_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if __has_attribute(objc_subclassing_restricted)
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif
#if !defined(SWIFT_RESILIENT_CLASS)
# if __has_attribute(objc_class_stub)
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME) __attribute__((objc_class_stub))
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_class_stub)) SWIFT_CLASS_NAMED(SWIFT_NAME)
# else
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME)
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) SWIFT_CLASS_NAMED(SWIFT_NAME)
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
# define SWIFT_PROTOCOL_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if !defined(SWIFT_ENUM_ATTR)
# if defined(__has_attribute) && __has_attribute(enum_extensibility)
#  define SWIFT_ENUM_ATTR(_extensibility) __attribute__((enum_extensibility(_extensibility)))
# else
#  define SWIFT_ENUM_ATTR(_extensibility)
# endif
#endif
#if !defined(SWIFT_ENUM)
# define SWIFT_ENUM(_type, _name, _extensibility) enum _name : _type _name; enum SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# if __has_feature(generalized_swift_name)
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) enum _name : _type _name SWIFT_COMPILE_NAME(SWIFT_NAME); enum SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# else
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) SWIFT_ENUM(_type, _name, _extensibility)
# endif
#endif
#if !defined(SWIFT_UNAVAILABLE)
# define SWIFT_UNAVAILABLE __attribute__((unavailable))
#endif
#if !defined(SWIFT_UNAVAILABLE_MSG)
# define SWIFT_UNAVAILABLE_MSG(msg) __attribute__((unavailable(msg)))
#endif
#if !defined(SWIFT_AVAILABILITY)
# define SWIFT_AVAILABILITY(plat, ...) __attribute__((availability(plat, __VA_ARGS__)))
#endif
#if !defined(SWIFT_WEAK_IMPORT)
# define SWIFT_WEAK_IMPORT __attribute__((weak_import))
#endif
#if !defined(SWIFT_DEPRECATED)
# define SWIFT_DEPRECATED __attribute__((deprecated))
#endif
#if !defined(SWIFT_DEPRECATED_MSG)
# define SWIFT_DEPRECATED_MSG(...) __attribute__((deprecated(__VA_ARGS__)))
#endif
#if __has_feature(attribute_diagnose_if_objc)
# define SWIFT_DEPRECATED_OBJC(Msg) __attribute__((diagnose_if(1, Msg, "warning")))
#else
# define SWIFT_DEPRECATED_OBJC(Msg) SWIFT_DEPRECATED_MSG(Msg)
#endif
#if !defined(IBSegueAction)
# define IBSegueAction
#endif
#if __has_feature(modules)
#if __has_warning("-Watimport-in-framework-header")
#pragma clang diagnostic ignored "-Watimport-in-framework-header"
#endif
@import Foundation;
@import ObjectiveC;
#endif

#import <VPNTunnelProviderSDK/VPNTunnelProviderSDK.h>

#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"
#if __has_warning("-Wpragma-clang-attribute")
# pragma clang diagnostic ignored "-Wpragma-clang-attribute"
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wnullability"

#if __has_attribute(external_source_symbol)
# pragma push_macro("any")
# undef any
# pragma clang attribute push(__attribute__((external_source_symbol(language="Swift", defined_in="VPNTunnelProviderSDK",generated_declaration))), apply_to=any(function,enum,objc_interface,objc_category,objc_protocol))
# pragma pop_macro("any")
#endif


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK14AFCategoryType")
@interface AFCategoryType : NSObject
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) AFCategoryType * _Nonnull safe;)
+ (AFCategoryType * _Nonnull)safe SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) AFCategoryType * _Nonnull unsafe;)
+ (AFCategoryType * _Nonnull)unsafe SWIFT_WARN_UNUSED_RESULT;
@property (nonatomic, readonly, copy) NSString * _Nonnull representation;
- (nonnull instancetype)initWithCustom:(NSString * _Nonnull)custom OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)initWithUnsafeCustom:(NSString * _Nonnull)unsafeCustom OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

enum AFClientNetworkConfigurationAction : NSInteger;

SWIFT_CLASS("_TtC20VPNTunnelProviderSDK28AFClientNetworkConfiguration")
@interface AFClientNetworkConfiguration : NSObject
@property (nonatomic, readonly) enum AFClientNetworkConfigurationAction action;
@property (nonatomic, readonly, copy) NSString * _Nullable networkType;
@property (nonatomic, readonly, copy) NSArray<NSString *> * _Nullable ssid;
@property (nonatomic, readonly, copy) NSArray<NSString *> * _Nullable bssid;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

typedef SWIFT_ENUM(NSInteger, AFClientNetworkConfigurationAction, open) {
  AFClientNetworkConfigurationActionEnable = 0,
  AFClientNetworkConfigurationActionDisable = 1,
  AFClientNetworkConfigurationActionEmpty = 2,
};


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK19AFClientNetworkList")
@interface AFClientNetworkList : NSObject
@property (nonatomic, readonly, copy) NSArray<AFClientNetworkConfiguration *> * _Nonnull configurations;
- (AFClientNetworkConfiguration * _Nullable)findWithSsid:(NSString * _Nonnull)ssid SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK20AFFireshieldCategory")
@interface AFFireshieldCategory : NSObject
+ (AFFireshieldCategory * _Nonnull)blockWithCategory:(AFCategoryType * _Nonnull)category SWIFT_WARN_UNUSED_RESULT;
+ (AFFireshieldCategory * _Nonnull)proxyWithCategory:(AFCategoryType * _Nonnull)category SWIFT_WARN_UNUSED_RESULT;
+ (AFFireshieldCategory * _Nonnull)bypassWithCategory:(AFCategoryType * _Nonnull)category SWIFT_WARN_UNUSED_RESULT;
+ (AFFireshieldCategory * _Nonnull)alertWithCategory:(AFCategoryType * _Nonnull)category SWIFT_WARN_UNUSED_RESULT;
+ (NSString * _Nonnull)categoryNameFrom:(AFCategoryType * _Nonnull)category SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

typedef SWIFT_ENUM(NSInteger, Action, open) {
  ActionProxy = 0,
  ActionBypass = 1,
  ActionBlock = 2,
  ActionAlert = 3,
};


@interface AFHydraConfiguration (SWIFT_EXTENSION(VPNTunnelProviderSDK))
@property (nonatomic, readonly, copy) NSString * _Nullable configurationHash;
@property (nonatomic, readonly, copy) NSArray<NSDictionary<NSString *, NSArray<NSDictionary<NSString *, NSString *> *> *> *> * _Nullable sections;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK13CNLRepository")
@interface CNLRepository : NSObject
@property (nonatomic) BOOL isClientListEnabled;
- (nonnull instancetype)initWithSuitName:(NSString * _Nonnull)suitName OBJC_DESIGNATED_INITIALIZER;
@property (nonatomic, readonly, strong) AFClientNetworkList * _Nullable list;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_PROTOCOL("_TtP20VPNTunnelProviderSDK9LogSource_")
@protocol LogSource
- (void)logWithString:(NSString * _Nonnull)string;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK16ConsoleLogSource")
@interface ConsoleLogSource : NSObject <LogSource>
- (void)logWithString:(NSString * _Nonnull)string;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK17CredentialManager")
@interface CredentialManager : NSObject
- (nonnull instancetype)initWithSuitName:(NSString * _Nonnull)suitName OBJC_DESIGNATED_INITIALIZER;
- (void)verifyCredentialsWithCompletion:(void (^ _Nonnull)(NSError * _Nullable))completion;
- (void)updateCredentialsFor:(NSDictionary<NSString *, id> * _Nonnull)config completion:(void (^ _Nonnull)(NSError * _Nullable, NSDictionary<NSString *, id> * _Nullable))completion;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK13FileLogSource")
@interface FileLogSource : NSObject <LogSource>
- (nonnull instancetype)initWithFileURL:(NSURL * _Nonnull)fileURL OBJC_DESIGNATED_INITIALIZER;
- (void)logWithString:(NSString * _Nonnull)string;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


@interface FileLogSource (SWIFT_EXTENSION(VPNTunnelProviderSDK))
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, copy) NSString * _Nonnull extensionFileName;)
+ (NSString * _Nonnull)extensionFileName SWIFT_WARN_UNUSED_RESULT;
@end



SWIFT_CLASS("_TtC20VPNTunnelProviderSDK17NetworkIdentifier")
@interface NetworkIdentifier : NSObject
@property (nonatomic, readonly, copy) NSString * _Nullable ssid;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK14StartupOptions")
@interface StartupOptions : NSObject
@property (nonatomic, readonly) BOOL isBypassEnabled;
- (nonnull instancetype)initWithIsBypassEnabled:(BOOL)isBypassEnabled OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK22UserDefaultsRepository")
@interface UserDefaultsRepository : NSObject
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

@class NSNumber;

SWIFT_CLASS("_TtC20VPNTunnelProviderSDK17VPNConnectionData")
@interface VPNConnectionData : NSObject
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VPNConnectionData * _Nonnull instance;)
+ (VPNConnectionData * _Nonnull)instance SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@property (nonatomic, copy) NSString * _Nonnull appGroup;
@property (nonatomic, readonly) BOOL hasActiveSession;
- (void)registerStartAttemptWithTriggeredByUser:(BOOL)triggeredByUser;
- (void)registerDidStart;
- (void)registerWillStopWithTriggeredByUser:(BOOL)triggeredByUser;
- (void)setConnectionInfoWithServerIP:(NSString * _Nullable)serverIP sessionID:(NSString * _Nullable)sessionID;
- (void)setCountryCode:(NSString * _Nullable)newValue;
- (void)setTrafficInfoWithBytesIn:(NSNumber * _Nullable)bytesIn bytesOut:(NSNumber * _Nullable)bytesOut;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK6VPNLog")
@interface VPNLog : NSObject
+ (void)setLogSourceWithArray:(NSArray<id <LogSource>> * _Nonnull)array;
+ (void)verbose:(NSString * _Nonnull)string;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS("_TtC20VPNTunnelProviderSDK10VPNTracker")
@interface VPNTracker : NSObject
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) VPNTracker * _Nonnull instance;)
+ (VPNTracker * _Nonnull)instance SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
- (void)setupWithAppGroup:(NSString * _Nullable)appGroup sdkVersion:(NSString * _Nullable)sdkVersion hydraVersion:(NSString * _Nullable)hydraVersion projectID:(NSString * _Nullable)projectID;
- (void)setSendEventsInterval:(NSTimeInterval)interval;
- (void)reportConnectionStartWithError:(NSError * _Nullable)error isStartedFromSleep:(BOOL)isStartedFromSleep;
- (void)reportConnectionEndWithError:(NSError * _Nullable)error isGoingToSleep:(BOOL)isGoingToSleep completion:(void (^ _Nullable)(void))completion;
@end

#if __has_attribute(external_source_symbol)
# pragma clang attribute pop
#endif
#pragma clang diagnostic pop
#endif

#endif
