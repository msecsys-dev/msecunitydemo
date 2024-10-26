Pod::Spec.new do |spec|
  spec.name               = "MsecSdk"
  spec.version            = "1.0.1"
  spec.platform = :ios, '13.0'
  spec.ios.deployment_target = '13.0'
  spec.summary            = "Msec Sdk for iOS"
  spec.description        = "Msec Sdk Framework for iOS "
  spec.homepage           = "https://msecsys.com"
  spec.documentation_url  = "https://msecsys.com"
  spec.swift_versions = '5.0'
  spec.license = { :type => 'Commercial', :text => 'See msecsys.com"' }
  spec.author             = { "MSecSys" => "..." }
  spec.swift_version      = "5.3"
  spec.source            = { :http => "https://sdk.msecsys.com/ios/MsecSdk_#{spec.version}.zip" }
  spec.library = 'c++','z'
  spec.vendored_frameworks = 'Msec.xcframework'
  spec.xcconfig  =  { 'FRAMEWORK_SEARCH_PATHS' => '"$(PODS_ROOT)/Frameworks"' }
#  spec.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
#  spec.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }
#  spec.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
end
