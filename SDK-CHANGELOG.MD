# Change Log

## 0.2.9 (11/14/2017)

- Fixed VPN on-demand issues when network was changed between WiFi and Cellular

## 0.2.8 (11/9/2017)

**Fixes**

- Fixed issue that caused network extension to crash with on-demand rules enabled

## 0.2.7 (11/06/2017)

**Fixes**

- Minor fixes and improvements

## 0.2.6 (11/03/2017)

**Fixes**

- Minor fixes and improvements

## 0.2.5 (10/20/2017)

**API changes**

- Changed startVpn and startVpnWithCountry callback parameters, now including AFCountry instance VPN connected to
- Added optional `installVpnProfile` function to better control VPN installation flow for tutorial purposes

**Features**

- Added on-demand mode (See AFConfig / AFConfigBuilder, AFOnDemandRules)
- Added SDK version (AFHydraVersion constant)

**Fixes**

- Fixed issue when VPN couldn't disconnect automatically on WiFi change
- Improved Swift compatibility
