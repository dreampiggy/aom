/*
 * Copyright (c) 2019, Alliance for Open Media. All rights reserved
 *
 * This source code is subject to the terms of the BSD 2 Clause License and
 * the Alliance for Open Media Patent License 1.0. If the BSD 2 Clause License
 * was not distributed with this source code in the LICENSE file, you can
 * obtain it at www.aomedia.org/license/software. If the Alliance for Open
 * Media Patent License 1.0 was not distributed with this source code in the
 * PATENTS file, you can obtain it at www.aomedia.org/license/patent.
 */
#include <memory>

#include "third_party/googletest/src/googletest/include/gtest/gtest.h"

#include "test/codec_factory.h"
#include "test/encode_test_driver.h"
#include "test/util.h"
#include "test/y4m_video_source.h"
#include "test/yuv_video_source.h"

namespace {
// Speed settings tested
static const int kCpuUsedVectors[] = {
  1,
  2,
  3,
  4,
};

class LevelTest
    : public ::libaom_test::CodecTestWith2Params<libaom_test::TestMode, int>,
      public ::libaom_test::EncoderTest {
 protected:
  LevelTest()
      : EncoderTest(GET_PARAM(0)), encoding_mode_(GET_PARAM(1)),
        cpu_used_(GET_PARAM(2)), target_level_(31) {}

  virtual ~LevelTest() {}

  virtual void SetUp() {
    InitializeConfig();
    SetMode(encoding_mode_);
    if (encoding_mode_ != ::libaom_test::kRealTime) {
      cfg_.g_lag_in_frames = 5;
      cfg_.rc_end_usage = AOM_VBR;
    } else {
      cfg_.g_lag_in_frames = 0;
      cfg_.rc_end_usage = AOM_CBR;
      cfg_.rc_buf_sz = 1000;
      cfg_.rc_buf_initial_sz = 500;
      cfg_.rc_buf_optimal_sz = 600;
    }
  }

  virtual void PreEncodeFrameHook(::libaom_test::VideoSource *video,
                                  ::libaom_test::Encoder *encoder) {
    if (video->frame() == 0) {
      encoder->Control(AOME_SET_CPUUSED, cpu_used_);
      if (encoding_mode_ != ::libaom_test::kRealTime) {
        encoder->Control(AOME_SET_ENABLEAUTOALTREF, 1);
        encoder->Control(AOME_SET_ARNR_MAXFRAMES, 7);
        encoder->Control(AOME_SET_ARNR_STRENGTH, 5);
      }
    }
  }

  libaom_test::TestMode encoding_mode_;
  int cpu_used_;
  int target_level_;
};

TEST_P(LevelTest, TestTargetLevelApi) {
  static const aom_codec_iface_t *codec = &aom_codec_av1_cx_algo;
  aom_codec_ctx_t enc;
  aom_codec_enc_cfg_t cfg;
  EXPECT_EQ(AOM_CODEC_OK, aom_codec_enc_config_default(codec, &cfg, 0));
  EXPECT_EQ(AOM_CODEC_OK, aom_codec_enc_init(&enc, codec, &cfg, 0));
  for (int operating_point = 0; operating_point <= 32; ++operating_point) {
    for (int level = 0; level <= 32; ++level) {
      const int target_level = operating_point * 100 + level;
      if ((level >= 0 && level <= 23) || level == 31 || operating_point > 31) {
        EXPECT_EQ(AOM_CODEC_OK,
                  aom_codec_control(&enc, AV1E_SET_TARGET_SEQ_LEVEL_IDX,
                                    target_level));
      } else {
        EXPECT_EQ(AOM_CODEC_INVALID_PARAM,
                  aom_codec_control(&enc, AV1E_SET_TARGET_SEQ_LEVEL_IDX,
                                    target_level));
      }
    }
  }
  EXPECT_EQ(AOM_CODEC_OK, aom_codec_destroy(&enc));
}

AV1_INSTANTIATE_TEST_CASE(LevelTest,
                          ::testing::Values(::libaom_test::kTwoPassGood),
                          ::testing::ValuesIn(kCpuUsedVectors));
}  // namespace
