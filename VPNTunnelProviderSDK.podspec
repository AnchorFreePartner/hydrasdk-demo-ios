Pod::Spec.new do |spec|
  spec.name         = 'VPNTunnelProviderSDK'
  spec.version      = '4.0.3'
  spec.license      = { :type => 'BSD' }
  spec.homepage     = 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios'
  spec.authors      = { 'Dmitry Denyak' => 'dmitrydenyak@gmail.com' }
  spec.summary      = 'VPN Tunnel Provider SDK.'
  spec.source       = { :git => 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios.git', :tag => spec.version }

  spec.vendored_frameworks = 'VPNTunnelProviderSDK.xcframework'
  spec.framework = 'NetworkExtension'
  spec.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-ObjC' }
  spec.libraries = 'z', 'resolv'
  spec.swift_version = '5.0'

  spec.ios.deployment_target = '11.0'

  spec.ios.user_target_xcconfig = { 'OTHER_LDFLAGS' => '-ObjC', 'SWIFT_INCLUDE_PATHS' => '${PODS_ROOT}/VPNTunnelProviderSDK/VPNTunnelProviderSDK.xcframework/AdditionalModules/ios/** ${PODS_ROOT}/VPNTunnelProviderSDK/VPNTunnelProviderSDK.xcframework/AdditionalModules/ios-simulator/** ${PODS_ROOT}/VPNTunnelProviderSDK/VPNTunnelProviderSDK.xcframework/AdditionalModules/objc/**' }

  spec.osx.deployment_target = '10.12'
  spec.osx.user_target_xcconfig = { 'OTHER_LDFLAGS' => '-ObjC', 'SWIFT_INCLUDE_PATHS' => '${PODS_ROOT}/VPNTunnelProviderSDK/VPNTunnelProviderSDK.xcframework/AdditionalModules/macos/** ${PODS_ROOT}/VPNTunnelProviderSDK/VPNTunnelProviderSDK.xcframework/AdditionalModules/objc/**' }

# Adding tests with a swift dependency is a workaround in order to make pod lib lint work
# See: https://github.com/CocoaPods/CocoaPods/issues/8649
  spec.test_spec 'Tests' do |spec|
    spec.dependency 'Result', '~> 5.0'
  end  
end