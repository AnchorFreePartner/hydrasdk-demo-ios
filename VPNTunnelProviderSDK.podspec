Pod::Spec.new do |spec|
  spec.platform     = :ios, '12.2'
  spec.name         = 'VPNTunnelProviderSDK'
  spec.version      = '3.1.5'
  spec.license      = { :type => 'BSD' }
  spec.homepage     = 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios'
  spec.authors      = { 'Dmitry Denyak' => 'dmitrydenyak@gmail.com' }
  spec.summary      = 'VPN Tunnel Provider SDK.'

  spec.source       = { :git => 'https://github.com/AnchorFreePartner/hydrasdk-demo-ios.git', :branch => 'master' }

  spec.framework    = 'NetworkExtension'
  spec.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }
  spec.ios.vendored_frameworks = 'VPNTunnelProviderSDK.framework'
  spec.library = 'z'
  spec.swift_version = '5.0'

# Adding tests with a swift dependency is a workaround in order to make pod lib lint work
# See: https://github.com/CocoaPods/CocoaPods/issues/8649
  spec.test_spec 'Tests' do |spec|
    spec.dependency 'Result', '~> 5.0'
  end  
end