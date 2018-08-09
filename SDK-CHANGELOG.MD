# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

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
