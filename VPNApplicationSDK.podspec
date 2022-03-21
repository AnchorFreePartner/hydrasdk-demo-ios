Pod::Spec.new do |spec|
  spec.name         = 'VPNApplicationSDK'
  spec.version      = '4.0.1'
  spec.license      = { :type => 'BSD' }
  spec.homepage     = 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios'
  spec.authors      = { 'Dmitry Denyak' => 'dmitrydenyak@gmail.com' }
  spec.summary      = 'VPN Application SDK.'
  spec.source       = { :git => 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios.git', :tag => spec.version }

  spec.vendored_frameworks = 'VPNApplicationSDK.xcframework'
  spec.framework = 'SystemConfiguration'
  spec.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-ObjC' }
  spec.swift_version = '5.0'

  spec.ios.deployment_target = '11.0'
  spec.ios.user_target_xcconfig = { 'OTHER_LDFLAGS' => '-ObjC' }

  spec.osx.deployment_target = '10.12'
  spec.osx.user_target_xcconfig = { 'OTHER_LDFLAGS' => '-ObjC' }
end