Pod::Spec.new do |spec|
  spec.platform     = :ios, '12.0'
  spec.name         = 'VPNApplicationSDK'
  spec.version      = '3.1.5'
  spec.license      = { :type => 'BSD' }
  spec.homepage     = 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios'
  spec.authors      = { 'Dmitry Denyak' => 'dmitrydenyak@gmail.com' }
  spec.summary      = 'VPN Application SDK.'

  spec.source       = { :git => 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios.git', :branch => 'master' }

  spec.framework    = 'SystemConfiguration'
  spec.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }
  spec.ios.vendored_frameworks = 'VPNApplicationSDK.framework'
  spec.swift_version = '5.0'
  
end