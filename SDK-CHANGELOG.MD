# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

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
