GitHub project: https://github.com/AnchorFreePartner/hydrasdk-demo-ios

# Anchorfree Hydra VPN SDK demo for iOS
This is a demo application for iOS with basic usage of Hydra VPN SDK.

# Compatibility

- iOS 9 or newer

# SDK Quick Installation Guide

Download latest SDK: [HydraSDK for iOS](https://firebasestorage.googleapis.com/v0/b/web-portal-for-partners.appspot.com/o/products%2FVPNSDK%20iOS%203.1.1.zip?alt=media&token=d650984d-4929-4fa3-9ba6-9fecadd4a724)

## Prepare Application
Create iOS application and additional Network Extension target, so you'll have:

* **Application** target
* **Network Extension** target

For both, the **Application** and the **Network Extension** targets, do the following

1. Add following system frameworks to your project dependencies:
- NetworkExtension
- Security
- libz.tbd

2. In your project: *Project > Build Settings*:
- Set *Enable Bitcode* to "NO"
- Set *Other Linker Flags* to `-ObjC`.

3. Enable Network Extension and Personal VPN entitlements for both application and network extension targets, create App Group that will be used on both targets.

## Install Hydra SDK

* Add **HydraApplicationSDK.framework** for **Application** target
* Add **HydraTunnelProviderSDK.framework** for **Network Extension** target

Make your PacketTunnelProvider class from **Network Extension** target extend AFPacketTunnelProvider and remove stub class implementation.

    // PacketTunnelProvider.swift
    import HydraTunnelProviderSDK

    class PacketTunnelProvider: AFPacketTunnelProvider {}


In your AppDelegate or other shared Singleton object initialize Hydra SDK:

    // AppDelegate.swift or your own Hydra holding singleton
    import HydraApplicationSDK
    // ...
    lazy var hydraClient : AFHydra = {
        AFHydra.withConfig(AFConfig.init(block: { (builder) in
            builder.baseUrl = "BASE_URL";
            builder.carrierId = "CARRIER_ID";
            builder.groupId = "group.YOUR.GROUP.NAME";
            builder.networkExtensionBundleId = "com.yourcompany.AWESOME_APP.neprovider";
        }))
    }()

Replace placeholders with your values obtained from developer portal and your XCode or Apple Developer Portal configuration.

    hydraClient.login(AFAuthMethod.anonymous(), completion: { [unowned self] (e, user) in
        // Process result
    })

After you're logged in, you're good to go start VPN:

    hydraClient.startVpn({ (country, error) in
        // VPN is being started to server in country `country`
        // Rely on notification center status notifications for exact VPN state
    })

Handle VPN state notifications:

    hydraClient.notificationCenter.addObserver(forName: NSNotification.Name.AFVPNStatusDidChange, object: nil, queue: nil) { [unowned self] (notification) in
        // Process VPN status changes here
        if hydraClient.vpnStatus() == .connected {
            // Do stuff
        }
    }

If you have to choose VPN server country before connecting, you can call `availableCountries` and then `startVpn` with specific country.

    // Get a list of countries 
    hydraClient.availableCountries { [weak self] (e, countries) in
        // Do stuff
        self.someCountry = countries[0]
    }

    // Start VPN with different country
    hydraClient.startVpn(with: self.someCountry, completion: { (country, e) in

    })

For more detailed information refer to Hydra SDK documentation: https://developer.anchorfree.com/?#/docs/hydrasdkforiososx
