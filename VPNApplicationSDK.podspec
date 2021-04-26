Pod::Spec.new do |spec|
  spec.name         = 'VPNApplicationSDK'
  spec.version      = '3.2.0'
  spec.license      = { :type => 'BSD' }
  spec.homepage     = 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios'
  spec.authors      = { 'Dmitry Denyak' => 'dmitrydenyak@gmail.com' }
  spec.summary      = 'VPN Application SDK.'
  spec.source       = { :git => 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios.git', :tag => spec.version }

  spec.vendored_frameworks = 'VPNApplicationSDK.xcframework'
  spec.framework = 'SystemConfiguration'
  spec.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }
  spec.user_target_xcconfig = { 'OTHER_LDFLAGS' => '-ObjC' }
  spec.swift_version = '5.0'

  spec.ios.deployment_target = '10.0'
  spec.ios.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  spec.ios.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64', 'SWIFT_INCLUDE_PATHS' => '${PODS_ROOT}/VPNApplicationSDK/VPNApplicationSDK.xcframework/AdditionalModules/ios/** ${PODS_ROOT}/VPNApplicationSDK/VPNApplication.xcframework/AdditionalModules/ios-simulator/**' }

  spec.osx.deployment_target = '10.12'
  spec.osx.pod_target_xcconfig = { 'EXCLUDED_ARCHS' => 'arm64' }
  spec.osx.user_target_xcconfig = { 'EXCLUDED_ARCHS' => 'arm64', 'SWIFT_INCLUDE_PATHS' => '${PODS_ROOT}/VPNApplicationSDK/VPNApplicationSDK.xcframework/AdditionalModules/macos/** }' }
end
