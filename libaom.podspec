#
# Be sure to run `pod lib lint TestLibrary.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'libaom'
  s.version          = '1.0.3'
  s.summary          = 'AV1 Codec Library.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
Codec library for encoding and decoding AV1 video streams
                       DESC

  s.homepage         = 'https://aomedia.googlesource.com/aom/'
  s.license          = { :type => 'BSD' }
  s.author           = { 'Alliance for Open Media' => 'https://aomedia.org' }
  s.source           = { :git => 'https://github.com/dreampiggy/aom.git', :tag => 'v' + s.version.to_s }

  s.ios.deployment_target = '8.0'
  s.osx.deployment_target = '10.7'
  s.tvos.deployment_target = '9.0'
  s.watchos.deployment_target = '2.0'

  s.source_files = 'aom/**/*.{h,c}', 'aom_dsp/**/*.{h,c}', 'aom_mem/**/*.{h,c}', 'aom_ports/**/*.{h,c}', 'aom_scale/**/*.{h,c}', 'aom_util/**/*.{h,c}', 'av1/**/*.{h,c}', 'third_party/vector/*.{h,c}', 'third_party/fastfeat/*.{h,c}'
  s.public_header_files = 'aom/*.h'
  s.exclude_files = 'av1/common/x86', 'av1/encoder/x86', 'aom_dsp/x86', 'aom_dsp/mips', 'aom_dsp/arm', 'aom_dsp/simd', 'aom_scale/mips', 'av1/common/arm', 'av1/common/ppc', 'av1/encoder/mips', 'av1/encoder/arm', 'aom_dsp/ssim.{h,c}', 'aom_dsp/buf_ans.{h,c}', 'aom_ports/ppc*.{h,c}', 'aom_ports/arm*.{h,c}', 'av1/decoder/inspection.{h,c}'

  # config the libaom build version string in `de265_version.h`, update when bumped version
  # s.prepare_command = <<-CMD
  #                     cp './libaom/de265-version.h.in' './libaom/de265-version.h'
  #                     sed -i.bak 's/@NUMERIC_VERSION@/0x01000300/g' './libaom/de265-version.h'
  #                     sed -i.bak 's/@PACKAGE_VERSION@/1.0.3/g' './libaom/de265-version.h'
  #                     CMD
  s.xcconfig = {
    'CLANG_X86_VECTOR_INSTRUCTIONS' => 'avx2',
    'HEADER_SEARCH_PATHS' => '$(inherited) ${PODS_ROOT}/libaom ${PODS_TARGET_SRCROOT}/ ${PODS_ROOT}/libaom/generate ${PODS_TARGET_SRCROOT}/generate',
    'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES'
  }
  s.preserve_paths = 'aom', 'aom_dsp', 'aom_mem', 'aom_ports', 'aom_scale', 'aom_util', 'av1', 'third_party', 'generate'
end
