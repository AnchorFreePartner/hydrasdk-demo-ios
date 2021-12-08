# Hydra network extension setup

You should already have prepared application target in order to continue, if you haven't done it yet, please check [this](ApplicationSetup.md).

### Create network extension target

Go to *Project -> Targets*, and in menu bar select *Editor > Add Target*. Select needed platform (iOS or macOS), then choose *Network Extension* type, provide the name and bundle ID for this [**Network Extension**](https://developer.apple.com/reference/networkextension) target. 

> **NOTE:** It is recommended to give distinctive names to your targets and bundle IDs, for example:
> * Application target: MyApp, com.blabla.myapp
> * Network extension target: MyApp Hydra Provider, com.blabla.myapp.hydraprovider

### Install tunnel provider SDK

At this point you have to have at least two targets: 
* **Application** target
* **Network Extension** target

Now you should link tunnel provider SDK to the **Network Extension** target. It can be done using CocoaPods or manually. We're providing SDK packed as `xcframework`, which means it can be used both for iOS and macOS apps.

#### [CocoaPods](https://guides.cocoapods.org/using/using-cocoapods.html)

```ruby
# Podfile
use_frameworks!

target 'YOUR_APP_TARGET_NAME' do
    pod 'VPNApplicationSDK'
end

target 'YOUR_NE_PROVIDER_TARGET_NAME' do
    pod 'VPNTunnelProviderSDK'
end
```

Replace target names with valid ones and then, in the `Podfile` directory, type:

```bash
$ pod install
```

#### Manual

1. Copy **VPNTunnelProviderSDK.xcframework** file to some place inside your project folder on disk.
2. Go to *Project -> Network Extension Target -> General* and drag copied framework to *Frameworks, Libraries and Embedded Content* section.
4. Link **NetworkExtension** system framework to the **Network Extension** target.
5. Link **libz.tbd** and **libresolv.tbd** libraries to the **Network Extension** target.
6. Go to *Project -> Network Extension Target -> Build Settings* and:
- Set *Enable Bitcode* to **NO**;
- [Add](https://developer.apple.com/library/content/qa/qa1490/_index.html) `-ObjC` to *Other Linker Flags*.
7. Staying in the same place, perform *Import paths* setting setup:

#### iOS
- Add `${PROJECT_DIR}/your-path-to-sdk/VPNTunnelProviderExtendedSDK.xcframework/AdditionalModules/ios`
- Add `${PROJECT_DIR}/your-path-to-sdk/VPNTunnelProviderExtendedSDK.xcframework/AdditionalModules/ios-simulator`
- Add `${PROJECT_DIR}/your-path-to-sdk/VPNTunnelProviderExtendedSDK.xcframework/AdditionalModules/objc`
- Replace `your-path-to-sdk` with correct path inside your project on disk
- Select `recursive` for all paths

#### macOS
- Add `${PROJECT_DIR}/your-path-to-sdk/VPNTunnelProviderExtendedSDK.xcframework/AdditionalModules/macos`
- Add `${PROJECT_DIR}/your-path-to-sdk/VPNTunnelProviderExtendedSDK.xcframework/AdditionalModules/objc`
- Replace `your-path-to-sdk` with correct path inside your project on disk
- Select `recursive` for all paths

### Subclass Packet Tunnel Provider

After the **Network Extension** target is created, you should observe that new class is added to your project (file *PacketTunnelProvider.swift*). Go to the *PacketTunnelProvider.swift* and make this class implement `NetworkExtensionDelegate` instead of `NEPacketTunnelProvider`. It should now look like:
    
```swift
import VPNTunnelProviderSDK

class ProviderDelegate: NSObject, NetworkExtensionDelegate {
	// ...
}
```

Remove Xcode-generated empty `PacketTunnelProvider`'s implementation.

### Setup Info.plist

Staying in **Network Extension** target, set `NSExtensionPrincipalClass` in `NSExtension` dictionary of `Info.plist` to `AFHydraTunnelProvider`, also add new key to a plist root: `NetworkExtensionDelegate` with a value that is your provider delegate class from the previous step. For example, if your class named `ProviderDelegate`, then the value would be `$(PRODUCT_MODULE_NAME).ProviderDelegate`.

Read more about [Creating a Packet Tunnel Provider Extension](https://developer.apple.com/reference/networkextension/nepackettunnelprovider#2110153) from Apple docs.

### Setup App ID

Next you need to perform all needed setup on [Apple developer portal](https://developer.apple.com).

#### Setup on developer portal

You should already have app ID for **Application** target, now you need another one for **Network Extension** target. Go to *Apple developer portal->Certificates, Identifiers & Profiles->Identifiers* and add new identifier for your Network Extension. Turn on following capabilities for both app IDs (**Application** and **Network Extension**):

#### iOS

* App Groups (this will be configured in the next step)
* Network Extensions
* Personal VPN

#### macOS

* Network Extensions
* Personal VPN

#### Create App Group (only for iOS)

Since HydraSDK is mostly a Network Extension you also have to create an App Group and provide group ID to the SDK to allow Hydra to interact with Packet Tunnel Provider Extension. See [Adding an App to an App Group](https://developer.apple.com/library/content/documentation/Miscellaneous/Reference/EntitlementKeyReference/Chapters/EnablingAppSandbox.html#//apple_ref/doc/uid/TP40011195-CH4-SW19) for more information about how to create app group. 

You need to assign this group to both, the **Application** and the **Network Extension** targets and App IDs.

#### Turn on capabilities in project

For both, **Application** and **Network Extension** targets, go to *Project -> Target -> Capabilities* and enable the following capabilities:

#### iOS

* Personal VPN
* Network Extensions
  * Packet Tunnel
* App Groups

#### macOS

* App Sandbox
  * Incoming Connections (Server)
  * Outgoing Connections (Client)
* Personal VPN
* Network Extensions
  * Packet Tunnel

> **NOTE:** Make sure that respective **.entitlement** files are added to the project for both targets.

### Re/Generate Provision Profiles

Application and Network Extension, both have to have its respective Provision Profiles generated from the Developer Portal. When creating and/or regenerating Provision Profiles, make sure you select Network Extension entitlement.

> **NOTE:** The Provision Profiles' entitlements must corresponds to entitlements configured through Xcode's project Capabilities tab. If there is a missconfiguration between the two, VPN connection will not be established.

#### macOS

> **NOTE:** On the Mac, Developer ID apps cannot host Network Extension providers. Only Mac App Store apps can host Network Extension providers. That's why, you cannot create a Developer ID Provision Profile with Network Extension entitlements attached to it.

### Integration Checklist & Troubleshooting

Checklist that should help you to verify correct integration:

- Make sure that you've created Network extension.
- **VPNApplicationSDK.framework** is added to the Application target, **VPNTunnelProviderSDK.framework** is added to the Extension target.
- **libz.tbd** and **libresolv.tbd** added to the Extension target.
- *Enable Bitcode* is set to "No" and `-ObjC` is present in "Other linker flags" for both targets.
- *Import paths* is configured inside build settings.
- You have created and enabled App Groups (General > Capabilities) for both targets, active App Group is set to "builder.groupId" (App Groups is enabled for both bundle ids (Application and Extension) in Apple Developer Portal).
- Personal VPN (General > Capabilities) is enabled for both targets (Personal VPN is enabled for both bundle ids (Application and Extension) in Apple Developer Portal).
- You have added Network Extension (iOS) entitlement for both Application and Extension provisioning profiles.
- `HydraSDK` instance is configured with correct `groupID`, `extensionBundleID`.
