# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

# [Unreleased]

## [3.1.4] - 2020-04-05
## Implemented

## Fixed
- Fixed the `Connecting` state issue which can occur right after updating from the older SDK (3.0.x) if the VPN connection was established.

## [3.1.3] - 2020-08-04
## Implemented

- Implemented the KillSwitch feature. 
When Hydra has occurred error and if the delegate method `vpnWillStopWith:(nonnull void(^)(BOOL restart))completion` is implemented, then until completion callback is called Hydra will run in the killswitch mode, please refer to the documentation about the restart parameter.

- Implemented providing of the `VirtualLocation` in the callback of `startVPN` function.

## Fixed
- Fixed the receiving of Hydra state from proper `VPNManger` object.

- Fixed issue with Fireshield when users unble to use netowkr messengers (stuck in the Connecting state).

## [3.1.2] - 2020-11-03
## Updated
- Improved `FireshieldController` and Fireshield categories, implemented the possibility of adding custom categories to the fireshield.

- Enabled BitCode support.

- Added `StartupOptions` to the `vpnWillStart` delegate method.

## Updated
- Updated Hydra library with fixed whitelisting crash.

## [3.1.1] - 2020-04-02
## Updated
- Updated Hydra library with added battery saving mode, which enables Fireshield is DNS-only mode, this option can be found in `FireshieldConfig`.

## [3.1.0] - 2019-19-12
## Impemented
- Added ad-mob section to remote config.

## Fixed
- Fixed issue with parsing subscriber model during login.

## [3.0.9] - 2019-31-10
## Updated
- Updated logic to update credentials during sleep to resolve issue with 196 error.
- Disabled silentMode in Fireshield configuration, setting the Fireshield mode to .silent will not affect on the configuration.

## [3.0.8] - 2019-09-09
## Updated
- Updated remote-config logic to resolve issue with alert-page.

## [3.0.7] - 2019-09-09
## Fixed
- Fixed token migrating from previous version of SDK.

## [3.0.6] - 2019-09-09
## Updated
- Updated logic in storing failed errors in network extension target.

## [3.0.5] - 2019-05-09
## Fixed
- Fixed issue remote configuration mapping.

## [3.0.4] - 2019-19-08
## Fixed
- Fixed issue with mapping RemainingTraffic object after spending all traffic.

## [3.0.3] - 2019-01-08
## Implemented
- Implemented currentFireshieldMode variable in HydraSDK class

## Fixed 
- Fixed issue with visible VPN icon when Fireshield mode is set to .silent
- Fixed issue with FireshieldController variable assigment in Network Extension Delegate.

## [3.0.2] - 2019-25-07
## Implemented
- Implemented deviceType variable in Hydra configuration.

## Fixed
- Fixed issue with Fireshield, that not blocking unsafe sites.
- Fixed `vpnDataCounterDidUpdate` delegate method in network extension target.

## [3.0.1] - 2019-22-07
## Updated
- Updated error messsage representation for connection error event report.

## [3.0.0] - 2019-16-07
## Implemeted
- Rewritten SDK in Swift and included analytics, with the ability to support multiple VPN protocols.

## [0.4.17] - 2019-06-06
### Fixed
- Fixed issue with dynamic whitelist when after unblocking URL it still blocked.

## [0.4.16] - 2019-04-25
### Updated
- Improved dynamic whitelist feature, added possibility to add/remove URL from list.

### Fixed
- Fixed issue with updating from older version of SDK to current without connection issues.
- Fixed issue with bypass connection status after traffic exceed.

## [0.4.15] - 2019-04-05
### Updated
- Improved dynamic whitelist feature
### Added
- Added support of remote bypass list feature

### Fixed
- Fixed issue with auto-reconnecting in onDemand mode if at first time connection not established

## [0.4.14] - 2019-03-18
### Added
- Added fireshield controller to AFNetworkExtensionDelegate, to make dynamic changes into Fireshield white/black list

## [0.4.13] - 2019-02-20
### Added
- Added traffic data counter delegate function to AFNetworkExtensionDelegate

## [0.4.12] - 2019-02-13
### Updated
- Updated device id generation

## [0.4.11] - 2019-01-31
### Fixed
- Fixed that bypass mode isn't working if bypass config variable set to true

## [0.4.10] - 2018-12-12
### Updated
- Rewrited fireshield configuration, now it's more flexible
- Implemented Remote config feature, now Hydra config can be overwritten via remote config

## [0.4.9] - 2018-09-11
### Fixed
- Preparing connection state management

## [0.4.8] - 2018-09-05
### Updated
- `trafficCounters` is now a read-only property 
- `AFVPNCategorizationDidChangeNotification` notification's user info now contains `AFHydraCategorization` object

## [0.4.7] - 2018-08-09
### Fixed
- Completion block is called upon Permission Denied error

## [0.4.6] - 2018-08-03
### Updated
- Public API improvements
- `updateConfig:` can be used to change Fireshield mode and On Demand value

## [0.4.5] - 2018-07-31
### Fixed
- Earlier NE delegate instantiation

## [0.4.4] - 2018-07-24
### Updated
- Fireshield server response timeout fix (for cases, when Fireshield is not supported on the server-side)

## [0.4.3] - 2018-07-24
### Updated
- `vpnProfileName` is now a required parameter for Hydra iOS SDK configuration

## [0.4.2] - 2018-07-23
### Updated
- Small updates to public interface documentation

## [0.4.1] - 2018-07-23
### Updated
- Put it all together

## [0.4.0] - 2018-07-11
### Added
- Categorization service (aka Fireshield) client API

## [0.3.9.21] - 2018-07-10
### Fixed
- Fix gaming issue

## [0.3.9.20] - 2018-07-05
### Fixed
- Temp workaround for fast disconnected state that might be received from the SDK during Connecting

## [0.3.9.19] - 2018-07-04
### Fixed
- Happy 4th of July!

## [0.3.9.18] - 2018-07-03
### Fixed
- Fix "Disconnecting" state is sent after "Connecting" has been sent (via workaround, for now)

## [0.3.9.17] - 2018-07-03
### Removed
- Revert to old approach, where SDK analyzes only last session's error and switches to bypass accordingly

## [0.3.9.16] - 2018-07-03
### Fixed
- Fix "Disconnecting" state is sent after "Connecting" has been sent (more improvements)

## [0.3.9.15] - 2018-07-02
### Fixed
- Fix "Disconnecting" state is sent after "Connecting" has been sent

## [0.3.9.14] - 2018-06-22
### Fixed
- `-isBypassEnabled` now returns correct value

## [0.3.9.13] - 2018-06-18
### Added
- SDK switches to bypass after numer of sessions with errors exceedes 3 (three). This behavior is only applied to configurations with On-Demand rules.

## [0.3.9.12] - 2018-06-14
### Fixed
- Fix correctly handle traffic exceed (191) error

## [0.3.9.11] - 2018-06-11
### Added
- Add `-shouldStartVPN` method
- Add `AFNEErrorCodeCancelled` error
### Fixed
- Fix correctly handle token expired (196) error
### Updated
- Change `-vpnDidStart` to `-vpnDidStartWithOptions:` 

## [0.3.9.10] - 2018-06-01
### Fixed
- Fix vpnWillStop is called upon network interface change
- Fix exception due to unbalanced KVO call

## [0.3.9.9] - 2018-05-31
### Fixed
- Misc improvements macOS SDK

## [0.3.9.8] - 2018-05-30
### Added
- Default willStop implementation of tunnel provider delegate

## [0.3.9.7] - 2018-05-25
### Fixed
- Fix crash during hydra state logging

## [0.3.9.6] - 2018-05-22
### Added
- GDPR support

## [0.3.9.5] - 2018-05-22
### Fixed
- Fix `Exception: +[NSError neStopReason:]: unrecognized selector sent to class`

## [0.3.9.4] - 2018-05-22
### Fixed
- Update libHydra

## [0.3.9.3] - 2018-05-10
### Fixed
- Fix invalid token error processing

## [0.3.9.2] - 2018-05-09
### Fixed
- Update libHydra
- Fix VoIP Issue

## [0.3.9.1] - 2018-05-05
### Added
- Added support for code 186
### Fixed
- Updated libhydra to the latest patch version fixing upload issue

## [0.3.9] - 2018-04-19
### Fixed
- Prevent multiple startVPN calls
- Fixed sleepTunnel.. call in NetworkExtension - shouldn't generate crash on tunnel sleep anymore

## [0.3.8] - 2018-04-10
### Added
- PKI support is enabled by default
- Timezone support for login method to make traffic counting more precise

## [0.3.7] - 2018-04-03
### Added
- VPN protocol library versioning
### Removed
- IDFA usage is removed from both UCR and HydraSDK
### Updated
- UCR library updated

## [0.3.6] - 2018-03-30
### Fixed
- Updated VPN protocol library

## [0.3.5] - 2018-03-15
### Added
- Added vpnProfileName property to AFConfig allowing to set VPN profile name visible in iOS Settings > VPN

## [0.3.4] - 2018-02-13
### Changed
- On-demand is now configured with NetworkExtension API
### Fixed
- String config parameters are now copied by default
### Removed
- Removed AFOnDemandRules

## [0.3.3] - 2018-02-07
### Fixed
- Fixed an issue when bypass mode switched back to non-bypass in out of traffic situation

## [0.3.2] - 2018-01-20
### Added
- Improved Swift compatibility

## [0.2.9] - 2017-11-14
### Fixed
- VPN on-demand issues when network was changed between WiFi and Cellular

## [0.2.8] - 2017-11-09
### Fixed
- Fixed issue that caused network extension to crash with on-demand rules enabled

## [0.2.7] - 2017-11-06
### Fixed
- Minor fixes and improvements

## [0.2.6] - 2017-11-03
### Fixed
- Minor fixes and improvements

## [0.2.5] - 2017-10-20
### Added
- Added on-demand mode (See AFConfig / AFConfigBuilder, AFOnDemandRules)
- Added SDK version (AFHydraVersion constant)

### Changed
- Changed startVpn and startVpnWithCountry callback parameters, now including AFCountry instance VPN connected to
- Added optional `installVpnProfile` function to better control VPN installation flow for tutorial purposes

### Fixed
- Fixed issue when VPN couldn't disconnect automatically on WiFi change
- Improved Swift compatibility
