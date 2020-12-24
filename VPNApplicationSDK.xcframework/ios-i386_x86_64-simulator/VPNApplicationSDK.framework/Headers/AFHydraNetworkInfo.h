//
//  AFHydraNetworkInfo.h
//  AFHydra
//
//  Copyright © 2018 AnchorFree. All rights reserved.
//
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <CoreTelephony/CTTelephonyNetworkInfo.h>
#import <CoreTelephony/CTCarrier.h>
#endif

@interface AFHydraNetworkInfo : NSObject

// Get the current interface name
+ (NSString *) currentInterfaceName;
#if !TARGET_OS_IPHONE
// Get current non-virtual interface name even if tunnel is up
+ (NSString *) currentInterfaceNameWithoutTunnel;
#endif
// Get current available non-virtual interfaces
+ (NSArray *) currentInterfacesExcludingTunnels;

// Get tunnel interface name based on its assigned ip
+ (NSString *) tunnelInterfaceMatchingIPAddress: (NSString*) ipAddress;

// List of interfaces and their flags and properties
+ (NSArray *) interfaceListDetailed;
// Printable version of interface list
+ (NSString *) interfaceListPrintable;

// Routing table
+ (NSArray*) routingTable;

+ (NSArray*) routingTableAll;
+ (NSArray*) routingTableIPv4;
+ (NSArray*) routingTableIPv6;

// Printable version of routing table for IPv4
+ (NSString *) routingTablePrintable;
// Printable version of routing table for IPv6
+ (NSString *) routingTableIPv6Printable;

#if TARGET_OS_IPHONE
// Wifi dictionary from CaptiveNetwork framework available on iOS
+ (NSDictionary *) wifiSSIDDict;
+ (CTTelephonyNetworkInfo*) mobileNetworkInfo;
#endif
// Current SSID
+ (NSString *) wifiSSID;

+ (NSString *)gatewayAddress;
//+ (NSArray *)dnsAddresses;
+ (NSArray *)ipAddressWithMask;

+ (BOOL)isIPv6Only;

@end
