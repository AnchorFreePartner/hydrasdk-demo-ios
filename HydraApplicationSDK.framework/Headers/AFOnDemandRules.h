//
// Created by Igor Glotov on 10/19/17.
// Copyright (c) 2017 northghost. All rights reserved.
//

@import Foundation;

/*!
 * @class AFOnDemandRules
 * @description On-demand rules customization. If this object is not set in AFHydra initialization, and onDemand is `true`,
 * the default rules are `alwaysOnWiFi = true`
 * `alwaysOnCellular = true`, probe URL will be your backend URL
 */
@interface AFOnDemandRules : NSObject
/*!
 * @property alwaysOnWiFi
 * @description Enable VPN automatically when WiFi is on. Default value is `true`.
 */
@property(nonatomic) BOOL alwaysOnWiFi;
/*!
 * @property alwaysOnCellular
 * @description Enable VPN automatically when cellular data is on (WiFi is off). Default value is `true`.
 */
@property(nonatomic) BOOL alwaysOnCellular;
/*!
 * @property enableProbe
 * @description Probe Internet connection by reaching `probeUrl` URL. Enable VPN if probe URL is reachable (HTTP code 200). Default value is `true`.
 */
@property(nonatomic) BOOL enableProbe;
/*!
 * @property probeUrl
 * @description The URL to check before starting VPN. If URL responds with code 200, VPN is started.
 */
@property(nullable, strong, nonatomic) NSURL *probeUrl;

+ (nonnull AFOnDemandRules *)defaultRules;
@end
