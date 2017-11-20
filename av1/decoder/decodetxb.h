/*
 * Copyright (c) 2017, Alliance for Open Media. All rights reserved
 *
 * This source code is subject to the terms of the BSD 2 Clause License and
 * the Alliance for Open Media Patent License 1.0. If the BSD 2 Clause License
 * was not distributed with this source code in the LICENSE file, you can
 * obtain it at www.aomedia.org/license/software. If the Alliance for Open
 * Media Patent License 1.0 was not distributed with this source code in the
 * PATENTS file, you can obtain it at www.aomedia.org/license/patent.
 */

#ifndef DECODETXB_H_
#define DECODETXB_H_

#include "./aom_config.h"
#include "av1/common/blockd.h"
#include "av1/common/onyxc_int.h"
#include "av1/common/txb_common.h"
#include "aom_dsp/bitreader.h"

uint8_t av1_read_coeffs_txb(const AV1_COMMON *const cm, MACROBLOCKD *const xd,
                            aom_reader *const r, const int blk_row,
                            const int blk_col, const int block, const int plane,
                            tran_low_t *const tcoeffs,
                            const TXB_CTX *const txb_ctx, const TX_SIZE tx_size,
                            int16_t *const max_scan_line, int *const eob);

uint8_t av1_read_coeffs_txb_facade(AV1_COMMON *cm, MACROBLOCKD *xd,
                                   aom_reader *r, int row, int col, int block,
                                   int plane, tran_low_t *tcoeffs,
                                   TX_SIZE tx_size, int16_t *max_scan_line,
                                   int *eob);
#endif  //  DECODETXB_H_
