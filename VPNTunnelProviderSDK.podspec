Pod::Spec.new do |spec|
  spec.platform     = :ios, '12.2'
  spec.name         = 'VPNTunnelProviderSDK'
  spec.version      = '3.1.6'
  spec.license      = { :type => 'BSD' }
  spec.homepage     = 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios'
  spec.authors      = { 'Dmitry Denyak' => 'dmitrydenyak@gmail.com' }
  spec.summary      = 'VPN Tunnel Provider SDK.'

  spec.source       = { :git => 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios.git', :tag => '3.1.6' }

  spec.framework    = 'NetworkExtension'
  spec.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }
  spec.ios.vendored_frameworks = 'VPNTunnelProviderSDK.framework'
  spec.libraries = 'z', 'resolv'
  spec.swift_version = '5.0'

  spec.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  spec.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }

# Adding tests with a swift dependency is a workaround in order to make pod lib lint work
# See: https://github.com/CocoaPods/CocoaPods/issues/8649
  spec.test_spec 'Tests' do |spec|
    spec.dependency 'Result', '~> 5.0'
  end  
end