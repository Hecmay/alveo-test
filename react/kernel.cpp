// HASH:1078003788
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_math.h>
#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <hls_math.h>
#include <math.h>
#include <stdint.h>
#include "const.h"


extern "C" {
void test(ap_fixed<32, 20> input_image[1][3][32][32], ap_fixed<32, 20> fc[1][10]) {
    #pragma HLS INTERFACE m_axi port=input_image offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=fc offset=slave bundle=gmem0
    #pragma HLS INTERFACE s_axilite port=input_image bundle=control
    #pragma HLS INTERFACE s_axilite port=fc bundle=control
    #pragma HLS INTERFACE s_axilite port=return bundle=control
      ap_fixed<32, 20> conv1_pad[1][3][34][34];
      ap_fixed<32, 20> conv1_pad_pipe_1[1][3][34][34];
      #pragma HLS stream variable=conv1_pad_pipe_1 depth=1
      #pragma HLS dataflow
      conv1_pad_not_zero: for (ap_int<32> not_zero = 0; not_zero < 3; ++not_zero) {
        conv1_pad_index_tuple: for (ap_int<32> index_tuple = 0; index_tuple < 34; ++index_tuple) {
          conv1_pad_i: for (ap_int<32> i = 0; i < 34; ++i) {
        #pragma HLS pipeline
            ap_fixed<32, 20> conv1_pad_temp;
            conv1_pad_temp = (((((1 <= index_tuple) && (index_tuple < 33)) && (1 <= i)) && (i < 33)) ? ((ap_fixed<32, 20>)input_image[0][not_zero][(index_tuple + -1)][(i + -1)]) : ((ap_fixed<32, 20>)0));
            conv1_pad_pipe_1[0][not_zero][index_tuple][i] = conv1_pad_temp;
            conv1_pad[0][not_zero][index_tuple][i] = conv1_pad_temp;
          }
        }
      }
      ap_fixed<32, 20> conv1_LB[1][3][3][34];
      #pragma array_partition variable=conv1_LB dim=3 complete
      ap_fixed<32, 20> conv1_WB[1][3][3][3];
      #pragma array_partition variable=conv1_WB dim=3 complete
      #pragma array_partition variable=conv1_WB dim=4 complete
      ap_fixed<32, 20> conv1_pipe_2[1][16][32][32];
      #pragma HLS stream variable=conv1_pipe_2 depth=2
      conv1_ff: for (ap_int<32> ff = 0; ff < 16; ++ff) {
        conv1_yy_reuse: for (ap_int<32> yy_reuse = 0; yy_reuse < 34; ++yy_reuse) {
          conv1_xx_reuse: for (ap_int<32> xx_reuse = 0; xx_reuse < 34; ++xx_reuse) {
            conv1_pad_2: for (ap_int<32> conv1_pad_2 = 0; conv1_pad_2 < 3; ++conv1_pad_2) {
          #pragma HLS pipeline
              conv1_pad_1: for (ap_int<32> conv1_pad_1 = 0; conv1_pad_1 < 2; ++conv1_pad_1) {
                conv1_LB[0][conv1_pad_2][conv1_pad_1][xx_reuse] = conv1_LB[0][conv1_pad_2][(conv1_pad_1 + 1)][xx_reuse];
              }
              ap_fixed<32, 20> conv1_pad_temp1;
              conv1_pad_temp1 = conv1_pad_pipe_1[0][conv1_pad_2][yy_reuse][xx_reuse];
              conv1_LB[0][conv1_pad_2][2][xx_reuse] = conv1_pad_temp1;
            }
            if (2 <= yy_reuse) {
              conv1_LB_1: for (ap_int<32> conv1_LB_1 = 0; conv1_LB_1 < 3; ++conv1_LB_1) {
                conv1_LB_2: for (ap_int<32> conv1_LB_2 = 0; conv1_LB_2 < 3; ++conv1_LB_2) {
                  conv1_LB_0: for (ap_int<32> conv1_LB_0 = 0; conv1_LB_0 < 2; ++conv1_LB_0) {
                    conv1_WB[0][conv1_LB_2][conv1_LB_1][conv1_LB_0] = conv1_WB[0][conv1_LB_2][conv1_LB_1][(conv1_LB_0 + 1)];
                  }
                  conv1_WB[0][conv1_LB_2][conv1_LB_1][2] = conv1_LB[0][conv1_LB_2][conv1_LB_1][xx_reuse];
                }
              }
              if (2 <= xx_reuse) {
                ap_fixed<32, 20> sum;
                sum = ((ap_fixed<32, 20>)0);
                conv1_rc: for (ap_int<32> rc = 0; rc < 3; ++rc) {
                  conv1_ry: for (ap_int<32> ry = 0; ry < 3; ++ry) {
                    conv1_rx: for (ap_int<32> rx = 0; rx < 3; ++rx) {
                      sum = ((ap_fixed<32, 20>)(((ap_fixed<65, 41>)(((ap_fixed<64, 52>)conv1_WB[0][rc][ry][rx]) * ((ap_fixed<64, 52>)w_conv1[ff][rc][ry][rx]))) + ((ap_fixed<65, 41>)sum)));
                    }
                  }
                }
                ap_fixed<32, 20> conv1_temp;
                conv1_temp = sum;
                conv1_pipe_2[0][ff][(yy_reuse + -2)][(xx_reuse + -2)] = conv1_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> bn1_pipe_3[1][16][32][32];
      #pragma HLS stream variable=bn1_pipe_3 depth=3
      ap_fixed<32, 20> bn1_pipe_115[1][16][32][32];
      #pragma HLS stream variable=bn1_pipe_115 depth=115
      bn1_args0: for (ap_int<32> args0 = 0; args0 < 16; ++args0) {
        bn1_args1: for (ap_int<32> args1 = 0; args1 < 32; ++args1) {
          bn1_args2: for (ap_int<32> args2 = 0; args2 < 32; ++args2) {
          #pragma HLS pipeline
            ap_fixed<32, 20> conv1_temp1;
            conv1_temp1 = conv1_pipe_2[0][args0][args1][args2];
            ap_fixed<32, 20> bn1_temp;
            bn1_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(conv1_temp1 - w_bn1_3[args0]))) / sqrt((((float)w_bn1_4[args0]) + 1.000000e-07f))) * ((float)w_bn1_1[args0])) + ((float)w_bn1_2[args0])));
            bn1_pipe_115[0][args0][args1][args2] = bn1_temp;
            bn1_pipe_3[0][args0][args1][args2] = bn1_temp;
          }
        }
      }
      ap_int<8> layer1_0_rsign1_pipe_4[1][16][32][32];
      #pragma HLS stream variable=layer1_0_rsign1_pipe_4 depth=4
      layer1_0_rsign1_cc: for (ap_int<32> cc = 0; cc < 16; ++cc) {
        layer1_0_rsign1_ww: for (ap_int<32> ww = 0; ww < 32; ++ww) {
          layer1_0_rsign1_hh: for (ap_int<32> hh = 0; hh < 32; ++hh) {
          #pragma HLS pipeline
            ap_fixed<32, 20> bn1_temp1;
            bn1_temp1 = bn1_pipe_3[0][cc][ww][hh];
            ap_int<8> layer1_0_rsign1_temp;
            layer1_0_rsign1_temp = ((ap_int<8>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)bn1_temp1) + ((ap_fixed<33, 21>)w_layer1_0_rsign1[cc])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer1_0_rsign1_pipe_4[0][cc][ww][hh] = layer1_0_rsign1_temp;
          }
        }
      }
      ap_int<8> layer1_0_conv1_pad[1][16][34][34];
      ap_int<8> layer1_0_conv1_pad_pipe_5[1][16][34][34];
      #pragma HLS stream variable=layer1_0_conv1_pad_pipe_5 depth=5
      layer1_0_conv1_pad_not_zero1: for (ap_int<32> not_zero1 = 0; not_zero1 < 16; ++not_zero1) {
        layer1_0_conv1_pad_index_tuple1: for (ap_int<32> index_tuple1 = 0; index_tuple1 < 34; ++index_tuple1) {
          layer1_0_conv1_pad_i1: for (ap_int<32> i1 = 0; i1 < 34; ++i1) {
        #pragma HLS pipeline
            ap_int<8> layer1_0_rsign1_temp1;
            layer1_0_rsign1_temp1 = layer1_0_rsign1_pipe_4[0][not_zero1][(index_tuple1 + -1)][(i1 + -1)];
            ap_int<8> layer1_0_conv1_pad_temp;
            layer1_0_conv1_pad_temp = (((((1 <= index_tuple1) && (index_tuple1 < 33)) && (1 <= i1)) && (i1 < 33)) ? ((ap_int<8>)layer1_0_rsign1_temp1) : ((ap_int<8>)0));
            layer1_0_conv1_pad_pipe_5[0][not_zero1][index_tuple1][i1] = layer1_0_conv1_pad_temp;
            layer1_0_conv1_pad[0][not_zero1][index_tuple1][i1] = layer1_0_conv1_pad_temp;
          }
        }
      }
      ap_int<8> layer1_0_conv1_LB[1][16][3][34];
      #pragma HLS array_partition variable=layer1_0_conv1_LB dim=3 complete
      ap_int<8> layer1_0_conv1_WB[1][16][3][3];
      #pragma HLS array_partition variable=layer1_0_conv1_WB dim=3 complete
      #pragma HLS array_partition variable=layer1_0_conv1_WB dim=4 complete
      ap_int<8> layer1_0_conv1_pipe_6[1][16][32][32];
      #pragma HLS stream variable=layer1_0_conv1_pipe_6 depth=6
      layer1_0_conv1_ff1: for (ap_int<32> ff1 = 0; ff1 < 16; ++ff1) {
        layer1_0_conv1_yy_reuse1: for (ap_int<32> yy_reuse1 = 0; yy_reuse1 < 34; ++yy_reuse1) {
          layer1_0_conv1_xx_reuse1: for (ap_int<32> xx_reuse1 = 0; xx_reuse1 < 34; ++xx_reuse1) {
            layer1_0_conv1_pad_2: for (ap_int<32> layer1_0_conv1_pad_2 = 0; layer1_0_conv1_pad_2 < 16; ++layer1_0_conv1_pad_2) {
          #pragma HLS pipeline
              layer1_0_conv1_pad_1: for (ap_int<32> layer1_0_conv1_pad_1 = 0; layer1_0_conv1_pad_1 < 2; ++layer1_0_conv1_pad_1) {
                layer1_0_conv1_LB[0][layer1_0_conv1_pad_2][layer1_0_conv1_pad_1][xx_reuse1] = layer1_0_conv1_LB[0][layer1_0_conv1_pad_2][(layer1_0_conv1_pad_1 + 1)][xx_reuse1];
              }
              ap_int<8> layer1_0_conv1_pad_temp1;
              layer1_0_conv1_pad_temp1 = layer1_0_conv1_pad_pipe_5[0][layer1_0_conv1_pad_2][yy_reuse1][xx_reuse1];
              layer1_0_conv1_LB[0][layer1_0_conv1_pad_2][2][xx_reuse1] = layer1_0_conv1_pad_temp1;
            }
            if (2 <= yy_reuse1) {
              layer1_0_conv1_LB_1: for (ap_int<32> layer1_0_conv1_LB_1 = 0; layer1_0_conv1_LB_1 < 3; ++layer1_0_conv1_LB_1) {
                layer1_0_conv1_LB_2: for (ap_int<32> layer1_0_conv1_LB_2 = 0; layer1_0_conv1_LB_2 < 16; ++layer1_0_conv1_LB_2) {
                  layer1_0_conv1_LB_0: for (ap_int<32> layer1_0_conv1_LB_0 = 0; layer1_0_conv1_LB_0 < 2; ++layer1_0_conv1_LB_0) {
                    layer1_0_conv1_WB[0][layer1_0_conv1_LB_2][layer1_0_conv1_LB_1][layer1_0_conv1_LB_0] = layer1_0_conv1_WB[0][layer1_0_conv1_LB_2][layer1_0_conv1_LB_1][(layer1_0_conv1_LB_0 + 1)];
                  }
                  layer1_0_conv1_WB[0][layer1_0_conv1_LB_2][layer1_0_conv1_LB_1][2] = layer1_0_conv1_LB[0][layer1_0_conv1_LB_2][layer1_0_conv1_LB_1][xx_reuse1];
                }
              }
              if (2 <= xx_reuse1) {
                ap_int<8> layer1_0_conv1_sum;
                layer1_0_conv1_sum = (ap_int<8>)0;
                layer1_0_conv1_rc1: for (ap_int<32> rc1 = 0; rc1 < 16; ++rc1) {
                  layer1_0_conv1_ry1: for (ap_int<32> ry1 = 0; ry1 < 3; ++ry1) {
                    layer1_0_conv1_rx1: for (ap_int<32> rx1 = 0; rx1 < 3; ++rx1) {
                      layer1_0_conv1_sum = ((ap_int<8>)(((ap_int<33>)(((((((ap_int<33>)1 - ((ap_int<33>)rx1)) <= ((ap_int<33>)(xx_reuse1 + -2))) && (((ap_int<33>)(xx_reuse1 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)rx1)))) && (((ap_int<33>)1 - ((ap_int<33>)ry1)) <= ((ap_int<33>)(yy_reuse1 + -2)))) && (((ap_int<33>)(yy_reuse1 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)ry1)))) ? ((ap_int<32>)((((1 - ((ap_int<32>)layer1_0_conv1_WB[0][rc1][ry1][rx1])) ^ w_layer1_0_conv1[ff1][rc1][ry1][rx1]) << 1) + -1)) : ((ap_int<32>)0))) + ((ap_int<33>)layer1_0_conv1_sum)));
                    }
                  }
                }
                ap_int<8> layer1_0_conv1_temp;
                layer1_0_conv1_temp = layer1_0_conv1_sum;
                layer1_0_conv1_pipe_6[0][ff1][(yy_reuse1 + -2)][(xx_reuse1 + -2)] = layer1_0_conv1_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer1_0_bn1_pipe_7[1][16][32][32];
      #pragma HLS stream variable=layer1_0_bn1_pipe_7 depth=7
      layer1_0_bn1_args01: for (ap_int<32> args01 = 0; args01 < 16; ++args01) {
        layer1_0_bn1_args11: for (ap_int<32> args11 = 0; args11 < 32; ++args11) {
          layer1_0_bn1_args21: for (ap_int<32> args21 = 0; args21 < 32; ++args21) {
          #pragma HLS pipeline
            ap_int<8> layer1_0_conv1_temp1;
            layer1_0_conv1_temp1 = layer1_0_conv1_pipe_6[0][args01][args11][args21];
            ap_fixed<32, 20> layer1_0_bn1_temp;
            layer1_0_bn1_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer1_0_conv1_temp1) - w_layer1_0_bn1_11[args01]))) / sqrt((((float)w_layer1_0_bn1_12[args01]) + 1.000000e-07f))) * ((float)w_layer1_0_bn1_9[args01])) + ((float)w_layer1_0_bn1_10[args01])));
            layer1_0_bn1_pipe_7[0][args01][args11][args21] = layer1_0_bn1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_0_residual1_pipe_8[1][16][32][32];
      #pragma HLS stream variable=layer1_0_residual1_pipe_8 depth=8
      layer1_0_residual1_cc1: for (ap_int<32> cc1 = 0; cc1 < 16; ++cc1) {
        layer1_0_residual1_ww1: for (ap_int<32> ww1 = 0; ww1 < 32; ++ww1) {
          layer1_0_residual1_hh1: for (ap_int<32> hh1 = 0; hh1 < 32; ++hh1) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_0_bn1_temp1;
            layer1_0_bn1_temp1 = layer1_0_bn1_pipe_7[0][cc1][ww1][hh1];
            ap_fixed<32, 20> layer1_0_residual1_temp;
            ap_fixed<32, 20> bn1_temp2;
            bn1_temp2 = bn1_pipe_115[0][cc1][ww1][hh1];
            layer1_0_residual1_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer1_0_bn1_temp1) + ((ap_fixed<33, 21>)bn1_temp2)));
            layer1_0_residual1_pipe_8[0][cc1][ww1][hh1] = layer1_0_residual1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_0_rprelu1_pipe_9[1][16][32][32];
      #pragma HLS stream variable=layer1_0_rprelu1_pipe_9 depth=9
      ap_fixed<32, 20> layer1_0_rprelu1_pipe_116[1][16][32][32];
      #pragma HLS stream variable=layer1_0_rprelu1_pipe_116 depth=116
      layer1_0_rprelu1_cc2: for (ap_int<32> cc2 = 0; cc2 < 16; ++cc2) {
        layer1_0_rprelu1_ww2: for (ap_int<32> ww2 = 0; ww2 < 32; ++ww2) {
          layer1_0_rprelu1_hh2: for (ap_int<32> hh2 = 0; hh2 < 32; ++hh2) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_0_residual1_temp1;
            layer1_0_residual1_temp1 = layer1_0_residual1_pipe_8[0][cc2][ww2][hh2];
            ap_fixed<32, 20> layer1_0_rprelu1_temp;
            layer1_0_rprelu1_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_0_residual1_temp1) + ((ap_fixed<33, 21>)w_layer1_0_rprelu1_0[cc2])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer1_0_residual1_temp1) + ((ap_fixed<33, 21>)w_layer1_0_rprelu1_0[cc2])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer1_0_rprelu1_2[cc2]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer1_0_residual1_temp1) + ((ap_fixed<33, 21>)w_layer1_0_rprelu1_0[cc2]))))))) + ((ap_fixed<66, 42>)w_layer1_0_rprelu1_1[cc2])));
            layer1_0_rprelu1_pipe_116[0][cc2][ww2][hh2] = layer1_0_rprelu1_temp;
            layer1_0_rprelu1_pipe_9[0][cc2][ww2][hh2] = layer1_0_rprelu1_temp;
          }
        }
      }
      ap_uint<1> layer1_0_rsign2_pipe_10[1][16][32][32];
      #pragma HLS stream variable=layer1_0_rsign2_pipe_10 depth=10
      layer1_0_rsign2_cc3: for (ap_int<32> cc3 = 0; cc3 < 16; ++cc3) {
        layer1_0_rsign2_ww3: for (ap_int<32> ww3 = 0; ww3 < 32; ++ww3) {
          layer1_0_rsign2_hh3: for (ap_int<32> hh3 = 0; hh3 < 32; ++hh3) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_0_rprelu1_temp1;
            layer1_0_rprelu1_temp1 = layer1_0_rprelu1_pipe_9[0][cc3][ww3][hh3];
            ap_uint<1> layer1_0_rsign2_temp;
            layer1_0_rsign2_temp = ((ap_uint<1>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_0_rprelu1_temp1) + ((ap_fixed<33, 21>)w_layer1_0_rsign2[cc3])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer1_0_rsign2_pipe_10[0][cc3][ww3][hh3] = layer1_0_rsign2_temp;
          }
        }
      }
      ap_uint<1> layer1_0_conv2_pad[1][16][34][34];
      ap_uint<1> layer1_0_conv2_pad_pipe_11[1][16][34][34];
      #pragma HLS stream variable=layer1_0_conv2_pad_pipe_11 depth=11
      layer1_0_conv2_pad_not_zero2: for (ap_int<32> not_zero2 = 0; not_zero2 < 16; ++not_zero2) {
        layer1_0_conv2_pad_index_tuple2: for (ap_int<32> index_tuple2 = 0; index_tuple2 < 34; ++index_tuple2) {
          layer1_0_conv2_pad_i2: for (ap_int<32> i2 = 0; i2 < 34; ++i2) {
        #pragma HLS pipeline
            ap_uint<1> layer1_0_rsign2_temp1;
            layer1_0_rsign2_temp1 = layer1_0_rsign2_pipe_10[0][not_zero2][(index_tuple2 + -1)][(i2 + -1)];
            ap_uint<1> layer1_0_conv2_pad_temp;
            layer1_0_conv2_pad_temp = (((((1 <= index_tuple2) && (index_tuple2 < 33)) && (1 <= i2)) && (i2 < 33)) ? ((ap_uint<1>)layer1_0_rsign2_temp1) : ((ap_uint<1>)0));
            layer1_0_conv2_pad_pipe_11[0][not_zero2][index_tuple2][i2] = layer1_0_conv2_pad_temp;
            layer1_0_conv2_pad[0][not_zero2][index_tuple2][i2] = layer1_0_conv2_pad_temp;
          }
        }
      }
      ap_uint<1> layer1_0_conv2_LB[1][16][3][34];
      #pragma HLS array_partition variable=layer1_0_conv2_LB dim=3 complete
      ap_uint<1> layer1_0_conv2_WB[1][16][3][3];
      #pragma HLS array_partition variable=layer1_0_conv2_WB dim=3 complete
      #pragma HLS array_partition variable=layer1_0_conv2_WB dim=4 complete
      ap_int<8> layer1_0_conv2_pipe_12[1][16][32][32];
      #pragma HLS stream variable=layer1_0_conv2_pipe_12 depth=12
      layer1_0_conv2_ff2: for (ap_int<32> ff2 = 0; ff2 < 16; ++ff2) {
        layer1_0_conv2_yy_reuse2: for (ap_int<32> yy_reuse2 = 0; yy_reuse2 < 34; ++yy_reuse2) {
          layer1_0_conv2_xx_reuse2: for (ap_int<32> xx_reuse2 = 0; xx_reuse2 < 34; ++xx_reuse2) {
            layer1_0_conv2_pad_2: for (ap_int<32> layer1_0_conv2_pad_2 = 0; layer1_0_conv2_pad_2 < 16; ++layer1_0_conv2_pad_2) {
          #pragma HLS pipeline
              layer1_0_conv2_pad_1: for (ap_int<32> layer1_0_conv2_pad_1 = 0; layer1_0_conv2_pad_1 < 2; ++layer1_0_conv2_pad_1) {
                layer1_0_conv2_LB[0][layer1_0_conv2_pad_2][layer1_0_conv2_pad_1][xx_reuse2] = layer1_0_conv2_LB[0][layer1_0_conv2_pad_2][(layer1_0_conv2_pad_1 + 1)][xx_reuse2];
              }
              ap_uint<1> layer1_0_conv2_pad_temp1;
              layer1_0_conv2_pad_temp1 = layer1_0_conv2_pad_pipe_11[0][layer1_0_conv2_pad_2][yy_reuse2][xx_reuse2];
              layer1_0_conv2_LB[0][layer1_0_conv2_pad_2][2][xx_reuse2] = layer1_0_conv2_pad_temp1;
            }
            if (2 <= yy_reuse2) {
              layer1_0_conv2_LB_1: for (ap_int<32> layer1_0_conv2_LB_1 = 0; layer1_0_conv2_LB_1 < 3; ++layer1_0_conv2_LB_1) {
                layer1_0_conv2_LB_2: for (ap_int<32> layer1_0_conv2_LB_2 = 0; layer1_0_conv2_LB_2 < 16; ++layer1_0_conv2_LB_2) {
                  layer1_0_conv2_LB_0: for (ap_int<32> layer1_0_conv2_LB_0 = 0; layer1_0_conv2_LB_0 < 2; ++layer1_0_conv2_LB_0) {
                    layer1_0_conv2_WB[0][layer1_0_conv2_LB_2][layer1_0_conv2_LB_1][layer1_0_conv2_LB_0] = layer1_0_conv2_WB[0][layer1_0_conv2_LB_2][layer1_0_conv2_LB_1][(layer1_0_conv2_LB_0 + 1)];
                  }
                  layer1_0_conv2_WB[0][layer1_0_conv2_LB_2][layer1_0_conv2_LB_1][2] = layer1_0_conv2_LB[0][layer1_0_conv2_LB_2][layer1_0_conv2_LB_1][xx_reuse2];
                }
              }
              if (2 <= xx_reuse2) {
                ap_int<8> layer1_0_conv2_sum;
                layer1_0_conv2_sum = (ap_int<8>)0;
                layer1_0_conv2_rc2: for (ap_int<32> rc2 = 0; rc2 < 16; ++rc2) {
                  layer1_0_conv2_ry2: for (ap_int<32> ry2 = 0; ry2 < 3; ++ry2) {
                    layer1_0_conv2_rx2: for (ap_int<32> rx2 = 0; rx2 < 3; ++rx2) {
                      layer1_0_conv2_sum = ((ap_int<8>)(((ap_int<34>)(((((((ap_int<33>)1 - ((ap_int<33>)rx2)) <= ((ap_int<33>)(xx_reuse2 + -2))) && (((ap_int<33>)(xx_reuse2 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)rx2)))) && (((ap_int<33>)1 - ((ap_int<33>)ry2)) <= ((ap_int<33>)(yy_reuse2 + -2)))) && (((ap_int<33>)(yy_reuse2 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)ry2)))) ? ((ap_uint<32>)((((1U - ((ap_uint<32>)layer1_0_conv2_WB[0][rc2][ry2][rx2])) ^ w_layer1_0_conv2[ff2][rc2][ry2][rx2]) << 1) - 1U)) : ((ap_uint<32>)0U))) + ((ap_int<34>)layer1_0_conv2_sum)));
                    }
                  }
                }
                ap_int<8> layer1_0_conv2_temp;
                layer1_0_conv2_temp = layer1_0_conv2_sum;
                layer1_0_conv2_pipe_12[0][ff2][(yy_reuse2 + -2)][(xx_reuse2 + -2)] = layer1_0_conv2_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer1_0_bn2_pipe_13[1][16][32][32];
      #pragma HLS stream variable=layer1_0_bn2_pipe_13 depth=13
      layer1_0_bn2_args02: for (ap_int<32> args02 = 0; args02 < 16; ++args02) {
        layer1_0_bn2_args12: for (ap_int<32> args12 = 0; args12 < 32; ++args12) {
          layer1_0_bn2_args22: for (ap_int<32> args22 = 0; args22 < 32; ++args22) {
          #pragma HLS pipeline
            ap_int<8> layer1_0_conv2_temp1;
            layer1_0_conv2_temp1 = layer1_0_conv2_pipe_12[0][args02][args12][args22];
            ap_fixed<32, 20> layer1_0_bn2_temp;
            layer1_0_bn2_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer1_0_conv2_temp1) - w_layer1_0_bn2_16[args02]))) / sqrt((((float)w_layer1_0_bn2_17[args02]) + 1.000000e-07f))) * ((float)w_layer1_0_bn2_14[args02])) + ((float)w_layer1_0_bn2_15[args02])));
            layer1_0_bn2_pipe_13[0][args02][args12][args22] = layer1_0_bn2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_0_residual2_pipe_14[1][16][32][32];
      #pragma HLS stream variable=layer1_0_residual2_pipe_14 depth=14
      layer1_0_residual2_cc4: for (ap_int<32> cc4 = 0; cc4 < 16; ++cc4) {
        layer1_0_residual2_ww4: for (ap_int<32> ww4 = 0; ww4 < 32; ++ww4) {
          layer1_0_residual2_hh4: for (ap_int<32> hh4 = 0; hh4 < 32; ++hh4) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_0_bn2_temp1;
            layer1_0_bn2_temp1 = layer1_0_bn2_pipe_13[0][cc4][ww4][hh4];
            ap_fixed<32, 20> layer1_0_residual2_temp;
            ap_fixed<32, 20> layer1_0_rprelu1_temp2;
            layer1_0_rprelu1_temp2 = layer1_0_rprelu1_pipe_116[0][cc4][ww4][hh4];
            layer1_0_residual2_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer1_0_bn2_temp1) + ((ap_fixed<33, 21>)layer1_0_rprelu1_temp2)));
            layer1_0_residual2_pipe_14[0][cc4][ww4][hh4] = layer1_0_residual2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_0_rprelu2_pipe_15[1][16][32][32];
      #pragma HLS stream variable=layer1_0_rprelu2_pipe_15 depth=15
      ap_fixed<32, 20> layer1_0_rprelu2_pipe_117[1][16][32][32];
      #pragma HLS stream variable=layer1_0_rprelu2_pipe_117 depth=117
      layer1_0_rprelu2_cc5: for (ap_int<32> cc5 = 0; cc5 < 16; ++cc5) {
        layer1_0_rprelu2_ww5: for (ap_int<32> ww5 = 0; ww5 < 32; ++ww5) {
          layer1_0_rprelu2_hh5: for (ap_int<32> hh5 = 0; hh5 < 32; ++hh5) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_0_residual2_temp1;
            layer1_0_residual2_temp1 = layer1_0_residual2_pipe_14[0][cc5][ww5][hh5];
            ap_fixed<32, 20> layer1_0_rprelu2_temp;
            layer1_0_rprelu2_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_0_residual2_temp1) + ((ap_fixed<33, 21>)w_layer1_0_rprelu2_3[cc5])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer1_0_residual2_temp1) + ((ap_fixed<33, 21>)w_layer1_0_rprelu2_3[cc5])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer1_0_rprelu2_5[cc5]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer1_0_residual2_temp1) + ((ap_fixed<33, 21>)w_layer1_0_rprelu2_3[cc5]))))))) + ((ap_fixed<66, 42>)w_layer1_0_rprelu2_4[cc5])));
            layer1_0_rprelu2_pipe_117[0][cc5][ww5][hh5] = layer1_0_rprelu2_temp;
            layer1_0_rprelu2_pipe_15[0][cc5][ww5][hh5] = layer1_0_rprelu2_temp;
          }
        }
      }
      ap_int<8> layer1_1_rsign1_pipe_16[1][16][32][32];
      #pragma HLS stream variable=layer1_1_rsign1_pipe_16 depth=16
      layer1_1_rsign1_cc6: for (ap_int<32> cc6 = 0; cc6 < 16; ++cc6) {
        layer1_1_rsign1_ww6: for (ap_int<32> ww6 = 0; ww6 < 32; ++ww6) {
          layer1_1_rsign1_hh6: for (ap_int<32> hh6 = 0; hh6 < 32; ++hh6) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_0_rprelu2_temp1;
            layer1_0_rprelu2_temp1 = layer1_0_rprelu2_pipe_15[0][cc6][ww6][hh6];
            ap_int<8> layer1_1_rsign1_temp;
            layer1_1_rsign1_temp = ((ap_int<8>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_0_rprelu2_temp1) + ((ap_fixed<33, 21>)w_layer1_1_rsign1[cc6])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer1_1_rsign1_pipe_16[0][cc6][ww6][hh6] = layer1_1_rsign1_temp;
          }
        }
      }
      ap_int<8> layer1_1_conv1_pad[1][16][34][34];
      ap_int<8> layer1_1_conv1_pad_pipe_17[1][16][34][34];
      #pragma HLS stream variable=layer1_1_conv1_pad_pipe_17 depth=17
      layer1_1_conv1_pad_not_zero3: for (ap_int<32> not_zero3 = 0; not_zero3 < 16; ++not_zero3) {
        layer1_1_conv1_pad_index_tuple3: for (ap_int<32> index_tuple3 = 0; index_tuple3 < 34; ++index_tuple3) {
          layer1_1_conv1_pad_i3: for (ap_int<32> i3 = 0; i3 < 34; ++i3) {
        #pragma HLS pipeline
            ap_int<8> layer1_1_rsign1_temp1;
            layer1_1_rsign1_temp1 = layer1_1_rsign1_pipe_16[0][not_zero3][(index_tuple3 + -1)][(i3 + -1)];
            ap_int<8> layer1_1_conv1_pad_temp;
            layer1_1_conv1_pad_temp = (((((1 <= index_tuple3) && (index_tuple3 < 33)) && (1 <= i3)) && (i3 < 33)) ? ((ap_int<8>)layer1_1_rsign1_temp1) : ((ap_int<8>)0));
            layer1_1_conv1_pad_pipe_17[0][not_zero3][index_tuple3][i3] = layer1_1_conv1_pad_temp;
            layer1_1_conv1_pad[0][not_zero3][index_tuple3][i3] = layer1_1_conv1_pad_temp;
          }
        }
      }
      ap_int<8> layer1_1_conv1_LB[1][16][3][34];
      #pragma HLS array_partition variable=layer1_1_conv1_LB dim=3 complete
      ap_int<8> layer1_1_conv1_WB[1][16][3][3];
      #pragma HLS array_partition variable=layer1_1_conv1_WB dim=3 complete
      #pragma HLS array_partition variable=layer1_1_conv1_WB dim=4 complete
      ap_int<8> layer1_1_conv1_pipe_18[1][16][32][32];
      #pragma HLS stream variable=layer1_1_conv1_pipe_18 depth=18
      layer1_1_conv1_ff3: for (ap_int<32> ff3 = 0; ff3 < 16; ++ff3) {
        layer1_1_conv1_yy_reuse3: for (ap_int<32> yy_reuse3 = 0; yy_reuse3 < 34; ++yy_reuse3) {
          layer1_1_conv1_xx_reuse3: for (ap_int<32> xx_reuse3 = 0; xx_reuse3 < 34; ++xx_reuse3) {
            layer1_1_conv1_pad_2: for (ap_int<32> layer1_1_conv1_pad_2 = 0; layer1_1_conv1_pad_2 < 16; ++layer1_1_conv1_pad_2) {
          #pragma HLS pipeline
              layer1_1_conv1_pad_1: for (ap_int<32> layer1_1_conv1_pad_1 = 0; layer1_1_conv1_pad_1 < 2; ++layer1_1_conv1_pad_1) {
                layer1_1_conv1_LB[0][layer1_1_conv1_pad_2][layer1_1_conv1_pad_1][xx_reuse3] = layer1_1_conv1_LB[0][layer1_1_conv1_pad_2][(layer1_1_conv1_pad_1 + 1)][xx_reuse3];
              }
              ap_int<8> layer1_1_conv1_pad_temp1;
              layer1_1_conv1_pad_temp1 = layer1_1_conv1_pad_pipe_17[0][layer1_1_conv1_pad_2][yy_reuse3][xx_reuse3];
              layer1_1_conv1_LB[0][layer1_1_conv1_pad_2][2][xx_reuse3] = layer1_1_conv1_pad_temp1;
            }
            if (2 <= yy_reuse3) {
              layer1_1_conv1_LB_1: for (ap_int<32> layer1_1_conv1_LB_1 = 0; layer1_1_conv1_LB_1 < 3; ++layer1_1_conv1_LB_1) {
                layer1_1_conv1_LB_2: for (ap_int<32> layer1_1_conv1_LB_2 = 0; layer1_1_conv1_LB_2 < 16; ++layer1_1_conv1_LB_2) {
                  layer1_1_conv1_LB_0: for (ap_int<32> layer1_1_conv1_LB_0 = 0; layer1_1_conv1_LB_0 < 2; ++layer1_1_conv1_LB_0) {
                    layer1_1_conv1_WB[0][layer1_1_conv1_LB_2][layer1_1_conv1_LB_1][layer1_1_conv1_LB_0] = layer1_1_conv1_WB[0][layer1_1_conv1_LB_2][layer1_1_conv1_LB_1][(layer1_1_conv1_LB_0 + 1)];
                  }
                  layer1_1_conv1_WB[0][layer1_1_conv1_LB_2][layer1_1_conv1_LB_1][2] = layer1_1_conv1_LB[0][layer1_1_conv1_LB_2][layer1_1_conv1_LB_1][xx_reuse3];
                }
              }
              if (2 <= xx_reuse3) {
                ap_int<8> layer1_1_conv1_sum;
                layer1_1_conv1_sum = (ap_int<8>)0;
                layer1_1_conv1_rc3: for (ap_int<32> rc3 = 0; rc3 < 16; ++rc3) {
                  layer1_1_conv1_ry3: for (ap_int<32> ry3 = 0; ry3 < 3; ++ry3) {
                    layer1_1_conv1_rx3: for (ap_int<32> rx3 = 0; rx3 < 3; ++rx3) {
                      layer1_1_conv1_sum = ((ap_int<8>)(((ap_int<33>)(((((((ap_int<33>)1 - ((ap_int<33>)rx3)) <= ((ap_int<33>)(xx_reuse3 + -2))) && (((ap_int<33>)(xx_reuse3 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)rx3)))) && (((ap_int<33>)1 - ((ap_int<33>)ry3)) <= ((ap_int<33>)(yy_reuse3 + -2)))) && (((ap_int<33>)(yy_reuse3 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)ry3)))) ? ((ap_int<32>)((((1 - ((ap_int<32>)layer1_1_conv1_WB[0][rc3][ry3][rx3])) ^ w_layer1_1_conv1[ff3][rc3][ry3][rx3]) << 1) + -1)) : ((ap_int<32>)0))) + ((ap_int<33>)layer1_1_conv1_sum)));
                    }
                  }
                }
                ap_int<8> layer1_1_conv1_temp;
                layer1_1_conv1_temp = layer1_1_conv1_sum;
                layer1_1_conv1_pipe_18[0][ff3][(yy_reuse3 + -2)][(xx_reuse3 + -2)] = layer1_1_conv1_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer1_1_bn1_pipe_19[1][16][32][32];
      #pragma HLS stream variable=layer1_1_bn1_pipe_19 depth=19
      layer1_1_bn1_args03: for (ap_int<32> args03 = 0; args03 < 16; ++args03) {
        layer1_1_bn1_args13: for (ap_int<32> args13 = 0; args13 < 32; ++args13) {
          layer1_1_bn1_args23: for (ap_int<32> args23 = 0; args23 < 32; ++args23) {
          #pragma HLS pipeline
            ap_int<8> layer1_1_conv1_temp1;
            layer1_1_conv1_temp1 = layer1_1_conv1_pipe_18[0][args03][args13][args23];
            ap_fixed<32, 20> layer1_1_bn1_temp;
            layer1_1_bn1_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer1_1_conv1_temp1) - w_layer1_1_bn1_11[args03]))) / sqrt((((float)w_layer1_1_bn1_12[args03]) + 1.000000e-07f))) * ((float)w_layer1_1_bn1_9[args03])) + ((float)w_layer1_1_bn1_10[args03])));
            layer1_1_bn1_pipe_19[0][args03][args13][args23] = layer1_1_bn1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_1_residual1_pipe_20[1][16][32][32];
      #pragma HLS stream variable=layer1_1_residual1_pipe_20 depth=20
      layer1_1_residual1_cc7: for (ap_int<32> cc7 = 0; cc7 < 16; ++cc7) {
        layer1_1_residual1_ww7: for (ap_int<32> ww7 = 0; ww7 < 32; ++ww7) {
          layer1_1_residual1_hh7: for (ap_int<32> hh7 = 0; hh7 < 32; ++hh7) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_1_bn1_temp1;
            layer1_1_bn1_temp1 = layer1_1_bn1_pipe_19[0][cc7][ww7][hh7];
            ap_fixed<32, 20> layer1_1_residual1_temp;
            ap_fixed<32, 20> layer1_0_rprelu2_temp2;
            layer1_0_rprelu2_temp2 = layer1_0_rprelu2_pipe_117[0][cc7][ww7][hh7];
            layer1_1_residual1_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer1_1_bn1_temp1) + ((ap_fixed<33, 21>)layer1_0_rprelu2_temp2)));
            layer1_1_residual1_pipe_20[0][cc7][ww7][hh7] = layer1_1_residual1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_1_rprelu1_pipe_21[1][16][32][32];
      #pragma HLS stream variable=layer1_1_rprelu1_pipe_21 depth=21
      ap_fixed<32, 20> layer1_1_rprelu1_pipe_118[1][16][32][32];
      #pragma HLS stream variable=layer1_1_rprelu1_pipe_118 depth=118
      layer1_1_rprelu1_cc8: for (ap_int<32> cc8 = 0; cc8 < 16; ++cc8) {
        layer1_1_rprelu1_ww8: for (ap_int<32> ww8 = 0; ww8 < 32; ++ww8) {
          layer1_1_rprelu1_hh8: for (ap_int<32> hh8 = 0; hh8 < 32; ++hh8) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_1_residual1_temp1;
            layer1_1_residual1_temp1 = layer1_1_residual1_pipe_20[0][cc8][ww8][hh8];
            ap_fixed<32, 20> layer1_1_rprelu1_temp;
            layer1_1_rprelu1_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_1_residual1_temp1) + ((ap_fixed<33, 21>)w_layer1_1_rprelu1_0[cc8])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer1_1_residual1_temp1) + ((ap_fixed<33, 21>)w_layer1_1_rprelu1_0[cc8])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer1_1_rprelu1_2[cc8]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer1_1_residual1_temp1) + ((ap_fixed<33, 21>)w_layer1_1_rprelu1_0[cc8]))))))) + ((ap_fixed<66, 42>)w_layer1_1_rprelu1_1[cc8])));
            layer1_1_rprelu1_pipe_118[0][cc8][ww8][hh8] = layer1_1_rprelu1_temp;
            layer1_1_rprelu1_pipe_21[0][cc8][ww8][hh8] = layer1_1_rprelu1_temp;
          }
        }
      }
      ap_uint<1> layer1_1_rsign2_pipe_22[1][16][32][32];
      #pragma HLS stream variable=layer1_1_rsign2_pipe_22 depth=22
      layer1_1_rsign2_cc9: for (ap_int<32> cc9 = 0; cc9 < 16; ++cc9) {
        layer1_1_rsign2_ww9: for (ap_int<32> ww9 = 0; ww9 < 32; ++ww9) {
          layer1_1_rsign2_hh9: for (ap_int<32> hh9 = 0; hh9 < 32; ++hh9) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_1_rprelu1_temp1;
            layer1_1_rprelu1_temp1 = layer1_1_rprelu1_pipe_21[0][cc9][ww9][hh9];
            ap_uint<1> layer1_1_rsign2_temp;
            layer1_1_rsign2_temp = ((ap_uint<1>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_1_rprelu1_temp1) + ((ap_fixed<33, 21>)w_layer1_1_rsign2[cc9])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer1_1_rsign2_pipe_22[0][cc9][ww9][hh9] = layer1_1_rsign2_temp;
          }
        }
      }
      ap_uint<1> layer1_1_conv2_pad[1][16][34][34];
      ap_uint<1> layer1_1_conv2_pad_pipe_23[1][16][34][34];
      #pragma HLS stream variable=layer1_1_conv2_pad_pipe_23 depth=23
      layer1_1_conv2_pad_not_zero4: for (ap_int<32> not_zero4 = 0; not_zero4 < 16; ++not_zero4) {
        layer1_1_conv2_pad_index_tuple4: for (ap_int<32> index_tuple4 = 0; index_tuple4 < 34; ++index_tuple4) {
          layer1_1_conv2_pad_i4: for (ap_int<32> i4 = 0; i4 < 34; ++i4) {
        #pragma HLS pipeline
            ap_uint<1> layer1_1_rsign2_temp1;
            layer1_1_rsign2_temp1 = layer1_1_rsign2_pipe_22[0][not_zero4][(index_tuple4 + -1)][(i4 + -1)];
            ap_uint<1> layer1_1_conv2_pad_temp;
            layer1_1_conv2_pad_temp = (((((1 <= index_tuple4) && (index_tuple4 < 33)) && (1 <= i4)) && (i4 < 33)) ? ((ap_uint<1>)layer1_1_rsign2_temp1) : ((ap_uint<1>)0));
            layer1_1_conv2_pad_pipe_23[0][not_zero4][index_tuple4][i4] = layer1_1_conv2_pad_temp;
            layer1_1_conv2_pad[0][not_zero4][index_tuple4][i4] = layer1_1_conv2_pad_temp;
          }
        }
      }
      ap_uint<1> layer1_1_conv2_LB[1][16][3][34];
      #pragma HLS array_partition variable=layer1_1_conv2_LB dim=3 complete
      ap_uint<1> layer1_1_conv2_WB[1][16][3][3];
      #pragma HLS array_partition variable=layer1_1_conv2_WB dim=3 complete
      #pragma HLS array_partition variable=layer1_1_conv2_WB dim=4 complete
      ap_int<8> layer1_1_conv2_pipe_24[1][16][32][32];
      #pragma HLS stream variable=layer1_1_conv2_pipe_24 depth=24
      layer1_1_conv2_ff4: for (ap_int<32> ff4 = 0; ff4 < 16; ++ff4) {
        layer1_1_conv2_yy_reuse4: for (ap_int<32> yy_reuse4 = 0; yy_reuse4 < 34; ++yy_reuse4) {
          layer1_1_conv2_xx_reuse4: for (ap_int<32> xx_reuse4 = 0; xx_reuse4 < 34; ++xx_reuse4) {
            layer1_1_conv2_pad_2: for (ap_int<32> layer1_1_conv2_pad_2 = 0; layer1_1_conv2_pad_2 < 16; ++layer1_1_conv2_pad_2) {
          #pragma HLS pipeline
              layer1_1_conv2_pad_1: for (ap_int<32> layer1_1_conv2_pad_1 = 0; layer1_1_conv2_pad_1 < 2; ++layer1_1_conv2_pad_1) {
                layer1_1_conv2_LB[0][layer1_1_conv2_pad_2][layer1_1_conv2_pad_1][xx_reuse4] = layer1_1_conv2_LB[0][layer1_1_conv2_pad_2][(layer1_1_conv2_pad_1 + 1)][xx_reuse4];
              }
              ap_uint<1> layer1_1_conv2_pad_temp1;
              layer1_1_conv2_pad_temp1 = layer1_1_conv2_pad_pipe_23[0][layer1_1_conv2_pad_2][yy_reuse4][xx_reuse4];
              layer1_1_conv2_LB[0][layer1_1_conv2_pad_2][2][xx_reuse4] = layer1_1_conv2_pad_temp1;
            }
            if (2 <= yy_reuse4) {
              layer1_1_conv2_LB_1: for (ap_int<32> layer1_1_conv2_LB_1 = 0; layer1_1_conv2_LB_1 < 3; ++layer1_1_conv2_LB_1) {
                layer1_1_conv2_LB_2: for (ap_int<32> layer1_1_conv2_LB_2 = 0; layer1_1_conv2_LB_2 < 16; ++layer1_1_conv2_LB_2) {
                  layer1_1_conv2_LB_0: for (ap_int<32> layer1_1_conv2_LB_0 = 0; layer1_1_conv2_LB_0 < 2; ++layer1_1_conv2_LB_0) {
                    layer1_1_conv2_WB[0][layer1_1_conv2_LB_2][layer1_1_conv2_LB_1][layer1_1_conv2_LB_0] = layer1_1_conv2_WB[0][layer1_1_conv2_LB_2][layer1_1_conv2_LB_1][(layer1_1_conv2_LB_0 + 1)];
                  }
                  layer1_1_conv2_WB[0][layer1_1_conv2_LB_2][layer1_1_conv2_LB_1][2] = layer1_1_conv2_LB[0][layer1_1_conv2_LB_2][layer1_1_conv2_LB_1][xx_reuse4];
                }
              }
              if (2 <= xx_reuse4) {
                ap_int<8> layer1_1_conv2_sum;
                layer1_1_conv2_sum = (ap_int<8>)0;
                layer1_1_conv2_rc4: for (ap_int<32> rc4 = 0; rc4 < 16; ++rc4) {
                  layer1_1_conv2_ry4: for (ap_int<32> ry4 = 0; ry4 < 3; ++ry4) {
                    layer1_1_conv2_rx4: for (ap_int<32> rx4 = 0; rx4 < 3; ++rx4) {
                      layer1_1_conv2_sum = ((ap_int<8>)(((ap_int<34>)(((((((ap_int<33>)1 - ((ap_int<33>)rx4)) <= ((ap_int<33>)(xx_reuse4 + -2))) && (((ap_int<33>)(xx_reuse4 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)rx4)))) && (((ap_int<33>)1 - ((ap_int<33>)ry4)) <= ((ap_int<33>)(yy_reuse4 + -2)))) && (((ap_int<33>)(yy_reuse4 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)ry4)))) ? ((ap_uint<32>)((((1U - ((ap_uint<32>)layer1_1_conv2_WB[0][rc4][ry4][rx4])) ^ w_layer1_1_conv2[ff4][rc4][ry4][rx4]) << 1) - 1U)) : ((ap_uint<32>)0U))) + ((ap_int<34>)layer1_1_conv2_sum)));
                    }
                  }
                }
                ap_int<8> layer1_1_conv2_temp;
                layer1_1_conv2_temp = layer1_1_conv2_sum;
                layer1_1_conv2_pipe_24[0][ff4][(yy_reuse4 + -2)][(xx_reuse4 + -2)] = layer1_1_conv2_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer1_1_bn2_pipe_25[1][16][32][32];
      #pragma HLS stream variable=layer1_1_bn2_pipe_25 depth=25
      layer1_1_bn2_args04: for (ap_int<32> args04 = 0; args04 < 16; ++args04) {
        layer1_1_bn2_args14: for (ap_int<32> args14 = 0; args14 < 32; ++args14) {
          layer1_1_bn2_args24: for (ap_int<32> args24 = 0; args24 < 32; ++args24) {
          #pragma HLS pipeline
            ap_int<8> layer1_1_conv2_temp1;
            layer1_1_conv2_temp1 = layer1_1_conv2_pipe_24[0][args04][args14][args24];
            ap_fixed<32, 20> layer1_1_bn2_temp;
            layer1_1_bn2_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer1_1_conv2_temp1) - w_layer1_1_bn2_16[args04]))) / sqrt((((float)w_layer1_1_bn2_17[args04]) + 1.000000e-07f))) * ((float)w_layer1_1_bn2_14[args04])) + ((float)w_layer1_1_bn2_15[args04])));
            layer1_1_bn2_pipe_25[0][args04][args14][args24] = layer1_1_bn2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_1_residual2_pipe_26[1][16][32][32];
      #pragma HLS stream variable=layer1_1_residual2_pipe_26 depth=26
      layer1_1_residual2_cc10: for (ap_int<32> cc10 = 0; cc10 < 16; ++cc10) {
        layer1_1_residual2_ww10: for (ap_int<32> ww10 = 0; ww10 < 32; ++ww10) {
          layer1_1_residual2_hh10: for (ap_int<32> hh10 = 0; hh10 < 32; ++hh10) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_1_bn2_temp1;
            layer1_1_bn2_temp1 = layer1_1_bn2_pipe_25[0][cc10][ww10][hh10];
            ap_fixed<32, 20> layer1_1_residual2_temp;
            ap_fixed<32, 20> layer1_1_rprelu1_temp2;
            layer1_1_rprelu1_temp2 = layer1_1_rprelu1_pipe_118[0][cc10][ww10][hh10];
            layer1_1_residual2_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer1_1_bn2_temp1) + ((ap_fixed<33, 21>)layer1_1_rprelu1_temp2)));
            layer1_1_residual2_pipe_26[0][cc10][ww10][hh10] = layer1_1_residual2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_1_rprelu2_pipe_27[1][16][32][32];
      #pragma HLS stream variable=layer1_1_rprelu2_pipe_27 depth=27
      ap_fixed<32, 20> layer1_1_rprelu2_pipe_119[1][16][32][32];
      #pragma HLS stream variable=layer1_1_rprelu2_pipe_119 depth=119
      layer1_1_rprelu2_cc11: for (ap_int<32> cc11 = 0; cc11 < 16; ++cc11) {
        layer1_1_rprelu2_ww11: for (ap_int<32> ww11 = 0; ww11 < 32; ++ww11) {
          layer1_1_rprelu2_hh11: for (ap_int<32> hh11 = 0; hh11 < 32; ++hh11) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_1_residual2_temp1;
            layer1_1_residual2_temp1 = layer1_1_residual2_pipe_26[0][cc11][ww11][hh11];
            ap_fixed<32, 20> layer1_1_rprelu2_temp;
            layer1_1_rprelu2_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_1_residual2_temp1) + ((ap_fixed<33, 21>)w_layer1_1_rprelu2_3[cc11])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer1_1_residual2_temp1) + ((ap_fixed<33, 21>)w_layer1_1_rprelu2_3[cc11])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer1_1_rprelu2_5[cc11]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer1_1_residual2_temp1) + ((ap_fixed<33, 21>)w_layer1_1_rprelu2_3[cc11]))))))) + ((ap_fixed<66, 42>)w_layer1_1_rprelu2_4[cc11])));
            layer1_1_rprelu2_pipe_119[0][cc11][ww11][hh11] = layer1_1_rprelu2_temp;
            layer1_1_rprelu2_pipe_27[0][cc11][ww11][hh11] = layer1_1_rprelu2_temp;
          }
        }
      }
      ap_int<8> layer1_2_rsign1_pipe_28[1][16][32][32];
      #pragma HLS stream variable=layer1_2_rsign1_pipe_28 depth=28
      layer1_2_rsign1_cc12: for (ap_int<32> cc12 = 0; cc12 < 16; ++cc12) {
        layer1_2_rsign1_ww12: for (ap_int<32> ww12 = 0; ww12 < 32; ++ww12) {
          layer1_2_rsign1_hh12: for (ap_int<32> hh12 = 0; hh12 < 32; ++hh12) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_1_rprelu2_temp1;
            layer1_1_rprelu2_temp1 = layer1_1_rprelu2_pipe_27[0][cc12][ww12][hh12];
            ap_int<8> layer1_2_rsign1_temp;
            layer1_2_rsign1_temp = ((ap_int<8>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_1_rprelu2_temp1) + ((ap_fixed<33, 21>)w_layer1_2_rsign1[cc12])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer1_2_rsign1_pipe_28[0][cc12][ww12][hh12] = layer1_2_rsign1_temp;
          }
        }
      }
      ap_int<8> layer1_2_conv1_pad[1][16][34][34];
      ap_int<8> layer1_2_conv1_pad_pipe_29[1][16][34][34];
      #pragma HLS stream variable=layer1_2_conv1_pad_pipe_29 depth=29
      layer1_2_conv1_pad_not_zero5: for (ap_int<32> not_zero5 = 0; not_zero5 < 16; ++not_zero5) {
        layer1_2_conv1_pad_index_tuple5: for (ap_int<32> index_tuple5 = 0; index_tuple5 < 34; ++index_tuple5) {
          layer1_2_conv1_pad_i5: for (ap_int<32> i5 = 0; i5 < 34; ++i5) {
        #pragma HLS pipeline
            ap_int<8> layer1_2_rsign1_temp1;
            layer1_2_rsign1_temp1 = layer1_2_rsign1_pipe_28[0][not_zero5][(index_tuple5 + -1)][(i5 + -1)];
            ap_int<8> layer1_2_conv1_pad_temp;
            layer1_2_conv1_pad_temp = (((((1 <= index_tuple5) && (index_tuple5 < 33)) && (1 <= i5)) && (i5 < 33)) ? ((ap_int<8>)layer1_2_rsign1_temp1) : ((ap_int<8>)0));
            layer1_2_conv1_pad_pipe_29[0][not_zero5][index_tuple5][i5] = layer1_2_conv1_pad_temp;
            layer1_2_conv1_pad[0][not_zero5][index_tuple5][i5] = layer1_2_conv1_pad_temp;
          }
        }
      }
      ap_int<8> layer1_2_conv1_LB[1][16][3][34];
      #pragma HLS array_partition variable=layer1_2_conv1_LB dim=3 complete
      ap_int<8> layer1_2_conv1_WB[1][16][3][3];
      #pragma HLS array_partition variable=layer1_2_conv1_WB dim=3 complete
      #pragma HLS array_partition variable=layer1_2_conv1_WB dim=4 complete
      ap_int<8> layer1_2_conv1_pipe_30[1][16][32][32];
      #pragma HLS stream variable=layer1_2_conv1_pipe_30 depth=30
      layer1_2_conv1_ff5: for (ap_int<32> ff5 = 0; ff5 < 16; ++ff5) {
        layer1_2_conv1_yy_reuse5: for (ap_int<32> yy_reuse5 = 0; yy_reuse5 < 34; ++yy_reuse5) {
          layer1_2_conv1_xx_reuse5: for (ap_int<32> xx_reuse5 = 0; xx_reuse5 < 34; ++xx_reuse5) {
            layer1_2_conv1_pad_2: for (ap_int<32> layer1_2_conv1_pad_2 = 0; layer1_2_conv1_pad_2 < 16; ++layer1_2_conv1_pad_2) {
          #pragma HLS pipeline
              layer1_2_conv1_pad_1: for (ap_int<32> layer1_2_conv1_pad_1 = 0; layer1_2_conv1_pad_1 < 2; ++layer1_2_conv1_pad_1) {
                layer1_2_conv1_LB[0][layer1_2_conv1_pad_2][layer1_2_conv1_pad_1][xx_reuse5] = layer1_2_conv1_LB[0][layer1_2_conv1_pad_2][(layer1_2_conv1_pad_1 + 1)][xx_reuse5];
              }
              ap_int<8> layer1_2_conv1_pad_temp1;
              layer1_2_conv1_pad_temp1 = layer1_2_conv1_pad_pipe_29[0][layer1_2_conv1_pad_2][yy_reuse5][xx_reuse5];
              layer1_2_conv1_LB[0][layer1_2_conv1_pad_2][2][xx_reuse5] = layer1_2_conv1_pad_temp1;
            }
            if (2 <= yy_reuse5) {
              layer1_2_conv1_LB_1: for (ap_int<32> layer1_2_conv1_LB_1 = 0; layer1_2_conv1_LB_1 < 3; ++layer1_2_conv1_LB_1) {
                layer1_2_conv1_LB_2: for (ap_int<32> layer1_2_conv1_LB_2 = 0; layer1_2_conv1_LB_2 < 16; ++layer1_2_conv1_LB_2) {
                  layer1_2_conv1_LB_0: for (ap_int<32> layer1_2_conv1_LB_0 = 0; layer1_2_conv1_LB_0 < 2; ++layer1_2_conv1_LB_0) {
                    layer1_2_conv1_WB[0][layer1_2_conv1_LB_2][layer1_2_conv1_LB_1][layer1_2_conv1_LB_0] = layer1_2_conv1_WB[0][layer1_2_conv1_LB_2][layer1_2_conv1_LB_1][(layer1_2_conv1_LB_0 + 1)];
                  }
                  layer1_2_conv1_WB[0][layer1_2_conv1_LB_2][layer1_2_conv1_LB_1][2] = layer1_2_conv1_LB[0][layer1_2_conv1_LB_2][layer1_2_conv1_LB_1][xx_reuse5];
                }
              }
              if (2 <= xx_reuse5) {
                ap_int<8> layer1_2_conv1_sum;
                layer1_2_conv1_sum = (ap_int<8>)0;
                layer1_2_conv1_rc5: for (ap_int<32> rc5 = 0; rc5 < 16; ++rc5) {
                  layer1_2_conv1_ry5: for (ap_int<32> ry5 = 0; ry5 < 3; ++ry5) {
                    layer1_2_conv1_rx5: for (ap_int<32> rx5 = 0; rx5 < 3; ++rx5) {
                      layer1_2_conv1_sum = ((ap_int<8>)(((ap_int<33>)(((((((ap_int<33>)1 - ((ap_int<33>)rx5)) <= ((ap_int<33>)(xx_reuse5 + -2))) && (((ap_int<33>)(xx_reuse5 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)rx5)))) && (((ap_int<33>)1 - ((ap_int<33>)ry5)) <= ((ap_int<33>)(yy_reuse5 + -2)))) && (((ap_int<33>)(yy_reuse5 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)ry5)))) ? ((ap_int<32>)((((1 - ((ap_int<32>)layer1_2_conv1_WB[0][rc5][ry5][rx5])) ^ w_layer1_2_conv1[ff5][rc5][ry5][rx5]) << 1) + -1)) : ((ap_int<32>)0))) + ((ap_int<33>)layer1_2_conv1_sum)));
                    }
                  }
                }
                ap_int<8> layer1_2_conv1_temp;
                layer1_2_conv1_temp = layer1_2_conv1_sum;
                layer1_2_conv1_pipe_30[0][ff5][(yy_reuse5 + -2)][(xx_reuse5 + -2)] = layer1_2_conv1_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer1_2_bn1_pipe_31[1][16][32][32];
      #pragma HLS stream variable=layer1_2_bn1_pipe_31 depth=31
      layer1_2_bn1_args05: for (ap_int<32> args05 = 0; args05 < 16; ++args05) {
        layer1_2_bn1_args15: for (ap_int<32> args15 = 0; args15 < 32; ++args15) {
          layer1_2_bn1_args25: for (ap_int<32> args25 = 0; args25 < 32; ++args25) {
          #pragma HLS pipeline
            ap_int<8> layer1_2_conv1_temp1;
            layer1_2_conv1_temp1 = layer1_2_conv1_pipe_30[0][args05][args15][args25];
            ap_fixed<32, 20> layer1_2_bn1_temp;
            layer1_2_bn1_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer1_2_conv1_temp1) - w_layer1_2_bn1_11[args05]))) / sqrt((((float)w_layer1_2_bn1_12[args05]) + 1.000000e-07f))) * ((float)w_layer1_2_bn1_9[args05])) + ((float)w_layer1_2_bn1_10[args05])));
            layer1_2_bn1_pipe_31[0][args05][args15][args25] = layer1_2_bn1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_2_residual1_pipe_32[1][16][32][32];
      #pragma HLS stream variable=layer1_2_residual1_pipe_32 depth=32
      layer1_2_residual1_cc13: for (ap_int<32> cc13 = 0; cc13 < 16; ++cc13) {
        layer1_2_residual1_ww13: for (ap_int<32> ww13 = 0; ww13 < 32; ++ww13) {
          layer1_2_residual1_hh13: for (ap_int<32> hh13 = 0; hh13 < 32; ++hh13) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_2_bn1_temp1;
            layer1_2_bn1_temp1 = layer1_2_bn1_pipe_31[0][cc13][ww13][hh13];
            ap_fixed<32, 20> layer1_2_residual1_temp;
            ap_fixed<32, 20> layer1_1_rprelu2_temp2;
            layer1_1_rprelu2_temp2 = layer1_1_rprelu2_pipe_119[0][cc13][ww13][hh13];
            layer1_2_residual1_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer1_2_bn1_temp1) + ((ap_fixed<33, 21>)layer1_1_rprelu2_temp2)));
            layer1_2_residual1_pipe_32[0][cc13][ww13][hh13] = layer1_2_residual1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_2_rprelu1_pipe_33[1][16][32][32];
      #pragma HLS stream variable=layer1_2_rprelu1_pipe_33 depth=33
      ap_fixed<32, 20> layer1_2_rprelu1_pipe_120[1][16][32][32];
      #pragma HLS stream variable=layer1_2_rprelu1_pipe_120 depth=120
      layer1_2_rprelu1_cc14: for (ap_int<32> cc14 = 0; cc14 < 16; ++cc14) {
        layer1_2_rprelu1_ww14: for (ap_int<32> ww14 = 0; ww14 < 32; ++ww14) {
          layer1_2_rprelu1_hh14: for (ap_int<32> hh14 = 0; hh14 < 32; ++hh14) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_2_residual1_temp1;
            layer1_2_residual1_temp1 = layer1_2_residual1_pipe_32[0][cc14][ww14][hh14];
            ap_fixed<32, 20> layer1_2_rprelu1_temp;
            layer1_2_rprelu1_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_2_residual1_temp1) + ((ap_fixed<33, 21>)w_layer1_2_rprelu1_0[cc14])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer1_2_residual1_temp1) + ((ap_fixed<33, 21>)w_layer1_2_rprelu1_0[cc14])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer1_2_rprelu1_2[cc14]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer1_2_residual1_temp1) + ((ap_fixed<33, 21>)w_layer1_2_rprelu1_0[cc14]))))))) + ((ap_fixed<66, 42>)w_layer1_2_rprelu1_1[cc14])));
            layer1_2_rprelu1_pipe_120[0][cc14][ww14][hh14] = layer1_2_rprelu1_temp;
            layer1_2_rprelu1_pipe_33[0][cc14][ww14][hh14] = layer1_2_rprelu1_temp;
          }
        }
      }
      ap_uint<1> layer1_2_rsign2_pipe_34[1][16][32][32];
      #pragma HLS stream variable=layer1_2_rsign2_pipe_34 depth=34
      layer1_2_rsign2_cc15: for (ap_int<32> cc15 = 0; cc15 < 16; ++cc15) {
        layer1_2_rsign2_ww15: for (ap_int<32> ww15 = 0; ww15 < 32; ++ww15) {
          layer1_2_rsign2_hh15: for (ap_int<32> hh15 = 0; hh15 < 32; ++hh15) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_2_rprelu1_temp1;
            layer1_2_rprelu1_temp1 = layer1_2_rprelu1_pipe_33[0][cc15][ww15][hh15];
            ap_uint<1> layer1_2_rsign2_temp;
            layer1_2_rsign2_temp = ((ap_uint<1>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_2_rprelu1_temp1) + ((ap_fixed<33, 21>)w_layer1_2_rsign2[cc15])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer1_2_rsign2_pipe_34[0][cc15][ww15][hh15] = layer1_2_rsign2_temp;
          }
        }
      }
      ap_uint<1> layer1_2_conv2_pad[1][16][34][34];
      ap_uint<1> layer1_2_conv2_pad_pipe_35[1][16][34][34];
      #pragma HLS stream variable=layer1_2_conv2_pad_pipe_35 depth=35
      layer1_2_conv2_pad_not_zero6: for (ap_int<32> not_zero6 = 0; not_zero6 < 16; ++not_zero6) {
        layer1_2_conv2_pad_index_tuple6: for (ap_int<32> index_tuple6 = 0; index_tuple6 < 34; ++index_tuple6) {
          layer1_2_conv2_pad_i6: for (ap_int<32> i6 = 0; i6 < 34; ++i6) {
        #pragma HLS pipeline
            ap_uint<1> layer1_2_rsign2_temp1;
            layer1_2_rsign2_temp1 = layer1_2_rsign2_pipe_34[0][not_zero6][(index_tuple6 + -1)][(i6 + -1)];
            ap_uint<1> layer1_2_conv2_pad_temp;
            layer1_2_conv2_pad_temp = (((((1 <= index_tuple6) && (index_tuple6 < 33)) && (1 <= i6)) && (i6 < 33)) ? ((ap_uint<1>)layer1_2_rsign2_temp1) : ((ap_uint<1>)0));
            layer1_2_conv2_pad_pipe_35[0][not_zero6][index_tuple6][i6] = layer1_2_conv2_pad_temp;
            layer1_2_conv2_pad[0][not_zero6][index_tuple6][i6] = layer1_2_conv2_pad_temp;
          }
        }
      }
      ap_uint<1> layer1_2_conv2_LB[1][16][3][34];
      #pragma HLS array_partition variable=layer1_2_conv2_LB dim=3 complete
      ap_uint<1> layer1_2_conv2_WB[1][16][3][3];
      #pragma HLS array_partition variable=layer1_2_conv2_WB dim=3 complete
      #pragma HLS array_partition variable=layer1_2_conv2_WB dim=4 complete
      ap_int<8> layer1_2_conv2_pipe_36[1][16][32][32];
      #pragma HLS stream variable=layer1_2_conv2_pipe_36 depth=36
      layer1_2_conv2_ff6: for (ap_int<32> ff6 = 0; ff6 < 16; ++ff6) {
        layer1_2_conv2_yy_reuse6: for (ap_int<32> yy_reuse6 = 0; yy_reuse6 < 34; ++yy_reuse6) {
          layer1_2_conv2_xx_reuse6: for (ap_int<32> xx_reuse6 = 0; xx_reuse6 < 34; ++xx_reuse6) {
            layer1_2_conv2_pad_2: for (ap_int<32> layer1_2_conv2_pad_2 = 0; layer1_2_conv2_pad_2 < 16; ++layer1_2_conv2_pad_2) {
          #pragma HLS pipeline
              layer1_2_conv2_pad_1: for (ap_int<32> layer1_2_conv2_pad_1 = 0; layer1_2_conv2_pad_1 < 2; ++layer1_2_conv2_pad_1) {
                layer1_2_conv2_LB[0][layer1_2_conv2_pad_2][layer1_2_conv2_pad_1][xx_reuse6] = layer1_2_conv2_LB[0][layer1_2_conv2_pad_2][(layer1_2_conv2_pad_1 + 1)][xx_reuse6];
              }
              ap_uint<1> layer1_2_conv2_pad_temp1;
              layer1_2_conv2_pad_temp1 = layer1_2_conv2_pad_pipe_35[0][layer1_2_conv2_pad_2][yy_reuse6][xx_reuse6];
              layer1_2_conv2_LB[0][layer1_2_conv2_pad_2][2][xx_reuse6] = layer1_2_conv2_pad_temp1;
            }
            if (2 <= yy_reuse6) {
              layer1_2_conv2_LB_1: for (ap_int<32> layer1_2_conv2_LB_1 = 0; layer1_2_conv2_LB_1 < 3; ++layer1_2_conv2_LB_1) {
                layer1_2_conv2_LB_2: for (ap_int<32> layer1_2_conv2_LB_2 = 0; layer1_2_conv2_LB_2 < 16; ++layer1_2_conv2_LB_2) {
                  layer1_2_conv2_LB_0: for (ap_int<32> layer1_2_conv2_LB_0 = 0; layer1_2_conv2_LB_0 < 2; ++layer1_2_conv2_LB_0) {
                    layer1_2_conv2_WB[0][layer1_2_conv2_LB_2][layer1_2_conv2_LB_1][layer1_2_conv2_LB_0] = layer1_2_conv2_WB[0][layer1_2_conv2_LB_2][layer1_2_conv2_LB_1][(layer1_2_conv2_LB_0 + 1)];
                  }
                  layer1_2_conv2_WB[0][layer1_2_conv2_LB_2][layer1_2_conv2_LB_1][2] = layer1_2_conv2_LB[0][layer1_2_conv2_LB_2][layer1_2_conv2_LB_1][xx_reuse6];
                }
              }
              if (2 <= xx_reuse6) {
                ap_int<8> layer1_2_conv2_sum;
                layer1_2_conv2_sum = (ap_int<8>)0;
                layer1_2_conv2_rc6: for (ap_int<32> rc6 = 0; rc6 < 16; ++rc6) {
                  layer1_2_conv2_ry6: for (ap_int<32> ry6 = 0; ry6 < 3; ++ry6) {
                    layer1_2_conv2_rx6: for (ap_int<32> rx6 = 0; rx6 < 3; ++rx6) {
                      layer1_2_conv2_sum = ((ap_int<8>)(((ap_int<34>)(((((((ap_int<33>)1 - ((ap_int<33>)rx6)) <= ((ap_int<33>)(xx_reuse6 + -2))) && (((ap_int<33>)(xx_reuse6 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)rx6)))) && (((ap_int<33>)1 - ((ap_int<33>)ry6)) <= ((ap_int<33>)(yy_reuse6 + -2)))) && (((ap_int<33>)(yy_reuse6 + -2)) < ((ap_int<33>)33 - ((ap_int<33>)ry6)))) ? ((ap_uint<32>)((((1U - ((ap_uint<32>)layer1_2_conv2_WB[0][rc6][ry6][rx6])) ^ w_layer1_2_conv2[ff6][rc6][ry6][rx6]) << 1) - 1U)) : ((ap_uint<32>)0U))) + ((ap_int<34>)layer1_2_conv2_sum)));
                    }
                  }
                }
                ap_int<8> layer1_2_conv2_temp;
                layer1_2_conv2_temp = layer1_2_conv2_sum;
                layer1_2_conv2_pipe_36[0][ff6][(yy_reuse6 + -2)][(xx_reuse6 + -2)] = layer1_2_conv2_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer1_2_bn2_pipe_37[1][16][32][32];
      #pragma HLS stream variable=layer1_2_bn2_pipe_37 depth=37
      layer1_2_bn2_args06: for (ap_int<32> args06 = 0; args06 < 16; ++args06) {
        layer1_2_bn2_args16: for (ap_int<32> args16 = 0; args16 < 32; ++args16) {
          layer1_2_bn2_args26: for (ap_int<32> args26 = 0; args26 < 32; ++args26) {
          #pragma HLS pipeline
            ap_int<8> layer1_2_conv2_temp1;
            layer1_2_conv2_temp1 = layer1_2_conv2_pipe_36[0][args06][args16][args26];
            ap_fixed<32, 20> layer1_2_bn2_temp;
            layer1_2_bn2_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer1_2_conv2_temp1) - w_layer1_2_bn2_16[args06]))) / sqrt((((float)w_layer1_2_bn2_17[args06]) + 1.000000e-07f))) * ((float)w_layer1_2_bn2_14[args06])) + ((float)w_layer1_2_bn2_15[args06])));
            layer1_2_bn2_pipe_37[0][args06][args16][args26] = layer1_2_bn2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_2_residual2_pipe_38[1][16][32][32];
      #pragma HLS stream variable=layer1_2_residual2_pipe_38 depth=38
      layer1_2_residual2_cc16: for (ap_int<32> cc16 = 0; cc16 < 16; ++cc16) {
        layer1_2_residual2_ww16: for (ap_int<32> ww16 = 0; ww16 < 32; ++ww16) {
          layer1_2_residual2_hh16: for (ap_int<32> hh16 = 0; hh16 < 32; ++hh16) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_2_bn2_temp1;
            layer1_2_bn2_temp1 = layer1_2_bn2_pipe_37[0][cc16][ww16][hh16];
            ap_fixed<32, 20> layer1_2_residual2_temp;
            ap_fixed<32, 20> layer1_2_rprelu1_temp2;
            layer1_2_rprelu1_temp2 = layer1_2_rprelu1_pipe_120[0][cc16][ww16][hh16];
            layer1_2_residual2_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer1_2_bn2_temp1) + ((ap_fixed<33, 21>)layer1_2_rprelu1_temp2)));
            layer1_2_residual2_pipe_38[0][cc16][ww16][hh16] = layer1_2_residual2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer1_2_rprelu2_pipe_39[1][16][32][32];
      #pragma HLS stream variable=layer1_2_rprelu2_pipe_39 depth=39
      ap_fixed<32, 20> layer1_2_rprelu2_pipe_121[1][16][32][32];
      #pragma HLS stream variable=layer1_2_rprelu2_pipe_121 depth=121
      layer1_2_rprelu2_cc17: for (ap_int<32> cc17 = 0; cc17 < 16; ++cc17) {
        layer1_2_rprelu2_ww17: for (ap_int<32> ww17 = 0; ww17 < 32; ++ww17) {
          layer1_2_rprelu2_hh17: for (ap_int<32> hh17 = 0; hh17 < 32; ++hh17) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_2_residual2_temp1;
            layer1_2_residual2_temp1 = layer1_2_residual2_pipe_38[0][cc17][ww17][hh17];
            ap_fixed<32, 20> layer1_2_rprelu2_temp;
            layer1_2_rprelu2_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_2_residual2_temp1) + ((ap_fixed<33, 21>)w_layer1_2_rprelu2_3[cc17])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer1_2_residual2_temp1) + ((ap_fixed<33, 21>)w_layer1_2_rprelu2_3[cc17])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer1_2_rprelu2_5[cc17]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer1_2_residual2_temp1) + ((ap_fixed<33, 21>)w_layer1_2_rprelu2_3[cc17]))))))) + ((ap_fixed<66, 42>)w_layer1_2_rprelu2_4[cc17])));
            layer1_2_rprelu2_pipe_121[0][cc17][ww17][hh17] = layer1_2_rprelu2_temp;
            layer1_2_rprelu2_pipe_39[0][cc17][ww17][hh17] = layer1_2_rprelu2_temp;
          }
        }
      }
      ap_int<8> layer2_0_rsign1_pipe_40[1][16][32][32];
      #pragma HLS stream variable=layer2_0_rsign1_pipe_40 depth=40
      layer2_0_rsign1_cc18: for (ap_int<32> cc18 = 0; cc18 < 16; ++cc18) {
        layer2_0_rsign1_ww18: for (ap_int<32> ww18 = 0; ww18 < 32; ++ww18) {
          layer2_0_rsign1_hh18: for (ap_int<32> hh18 = 0; hh18 < 32; ++hh18) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer1_2_rprelu2_temp1;
            layer1_2_rprelu2_temp1 = layer1_2_rprelu2_pipe_39[0][cc18][ww18][hh18];
            ap_int<8> layer2_0_rsign1_temp;
            layer2_0_rsign1_temp = ((ap_int<8>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer1_2_rprelu2_temp1) + ((ap_fixed<33, 21>)w_layer2_0_rsign1[cc18])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer2_0_rsign1_pipe_40[0][cc18][ww18][hh18] = layer2_0_rsign1_temp;
          }
        }
      }
      ap_int<8> layer2_0_conv1_pad_pipe_41[1][16][34][34];
      #pragma HLS stream variable=layer2_0_conv1_pad_pipe_41 depth=41
      layer2_0_conv1_pad_not_zero7: for (ap_int<32> not_zero7 = 0; not_zero7 < 16; ++not_zero7) {
        layer2_0_conv1_pad_index_tuple7: for (ap_int<32> index_tuple7 = 0; index_tuple7 < 34; ++index_tuple7) {
          layer2_0_conv1_pad_i7: for (ap_int<32> i7 = 0; i7 < 34; ++i7) {
        #pragma HLS pipeline
            ap_int<8> layer2_0_rsign1_temp1;
            layer2_0_rsign1_temp1 = layer2_0_rsign1_pipe_40[0][not_zero7][(index_tuple7 + -1)][(i7 + -1)];
            ap_int<8> layer2_0_conv1_pad_temp;
            layer2_0_conv1_pad_temp = (((((1 <= index_tuple7) && (index_tuple7 < 33)) && (1 <= i7)) && (i7 < 33)) ? ((ap_int<8>)layer2_0_rsign1_temp1) : ((ap_int<8>)0));
            layer2_0_conv1_pad_pipe_41[0][not_zero7][index_tuple7][i7] = layer2_0_conv1_pad_temp;
          }
        }
      }
      ap_int<8> layer2_0_conv1_pipe_42[1][32][16][16];
      #pragma HLS stream variable=layer2_0_conv1_pipe_42 depth=42
      layer2_0_conv1_ff7: for (ap_int<32> ff7 = 0; ff7 < 32; ++ff7) {
        layer2_0_conv1_yy: for (ap_int<32> yy = 0; yy < 16; ++yy) {
          layer2_0_conv1_xx: for (ap_int<32> xx = 0; xx < 16; ++xx) {
            ap_int<8> layer2_0_conv1_sum;
            layer2_0_conv1_sum = (ap_int<8>)0;
            layer2_0_conv1_rc7: for (ap_int<32> rc7 = 0; rc7 < 16; ++rc7) {
              layer2_0_conv1_ry7: for (ap_int<32> ry7 = 0; ry7 < 3; ++ry7) {
                layer2_0_conv1_rx7: for (ap_int<32> rx7 = 0; rx7 < 3; ++rx7) {
                  ap_int<8> layer2_0_conv1_pad_temp1;
                  layer2_0_conv1_pad_temp1 = layer2_0_conv1_pad_pipe_41[0][rc7][((yy * 2) + ry7)][((xx * 2) + rx7)];
                  layer2_0_conv1_sum = ((ap_int<8>)(((ap_int<33>)(((((((ap_int<33>)1 - ((ap_int<33>)rx7)) <= ((ap_int<33>)xx)) && (((ap_int<33>)xx) < ((ap_int<33>)33 - ((ap_int<33>)rx7)))) && (((ap_int<33>)1 - ((ap_int<33>)ry7)) <= ((ap_int<33>)yy))) && (((ap_int<33>)yy) < ((ap_int<33>)33 - ((ap_int<33>)ry7)))) ? ((ap_int<32>)((((1 - ((ap_int<32>)layer2_0_conv1_pad_temp1)) ^ w_layer2_0_conv1[ff7][rc7][ry7][rx7]) << 1) + -1)) : ((ap_int<32>)0))) + ((ap_int<33>)layer2_0_conv1_sum)));
                }
              }
            }
            ap_int<8> layer2_0_conv1_temp;
            layer2_0_conv1_temp = layer2_0_conv1_sum;
            layer2_0_conv1_pipe_42[0][ff7][yy][xx] = layer2_0_conv1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_0_bn1_pipe_43[1][32][16][16];
      #pragma HLS stream variable=layer2_0_bn1_pipe_43 depth=43
      layer2_0_bn1_args07: for (ap_int<32> args07 = 0; args07 < 32; ++args07) {
        layer2_0_bn1_args17: for (ap_int<32> args17 = 0; args17 < 16; ++args17) {
          layer2_0_bn1_args27: for (ap_int<32> args27 = 0; args27 < 16; ++args27) {
          #pragma HLS pipeline
            ap_int<8> layer2_0_conv1_temp1;
            layer2_0_conv1_temp1 = layer2_0_conv1_pipe_42[0][args07][args17][args27];
            ap_fixed<32, 20> layer2_0_bn1_temp;
            layer2_0_bn1_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer2_0_conv1_temp1) - w_layer2_0_bn1_11[args07]))) / sqrt((((float)w_layer2_0_bn1_12[args07]) + 1.000000e-07f))) * ((float)w_layer2_0_bn1_9[args07])) + ((float)w_layer2_0_bn1_10[args07])));
            layer2_0_bn1_pipe_43[0][args07][args17][args27] = layer2_0_bn1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_0_avgpool_LB[2][32];
      ap_fixed<32, 20> layer2_0_avgpool_pipe_122[1][16][16][16];
      #pragma HLS stream variable=layer2_0_avgpool_pipe_122 depth=122
      layer2_0_avgpool_c: for (ap_int<32> c = 0; c < 16; ++c) {
        layer2_0_avgpool_h: for (ap_int<32> h = 0; h < 16; ++h) {
          layer2_0_avgpool_w: for (ap_int<32> w = 0; w < 16; ++w) {
            ap_fixed<32, 20> layer2_0_avgpool_val;
            layer2_0_avgpool_val = ((ap_fixed<32, 20>)0);
            layer2_0_avgpool_LB_i: for (ap_int<32> layer2_0_avgpool_LB_i = 0; layer2_0_avgpool_LB_i < 2; ++layer2_0_avgpool_LB_i) {
              layer2_0_avgpool_LB_j: for (ap_int<32> layer2_0_avgpool_LB_j = 0; layer2_0_avgpool_LB_j < 32; ++layer2_0_avgpool_LB_j) {
        #pragma HLS pipeline
                ap_fixed<32, 20> layer1_2_rprelu2_temp2;
                layer1_2_rprelu2_temp2 = layer1_2_rprelu2_pipe_121[0][c][((h * 2) + layer2_0_avgpool_LB_i)][layer2_0_avgpool_LB_j];
                layer2_0_avgpool_LB[layer2_0_avgpool_LB_i][layer2_0_avgpool_LB_j] = layer1_2_rprelu2_temp2;
              }
            }
            layer2_0_avgpool_rr: for (ap_int<32> layer2_0_avgpool_rr = 0; layer2_0_avgpool_rr < 2; ++layer2_0_avgpool_rr) {
              layer2_0_avgpool_cc: for (ap_int<32> layer2_0_avgpool_cc = 0; layer2_0_avgpool_cc < 2; ++layer2_0_avgpool_cc) {
                layer2_0_avgpool_val = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer2_0_avgpool_val) + ((ap_fixed<33, 21>)layer2_0_avgpool_LB[layer2_0_avgpool_rr][((w * 2) + layer2_0_avgpool_cc)])));
              }
            }
            ap_fixed<32, 20> layer2_0_avgpool_temp;
            layer2_0_avgpool_temp = ((ap_fixed<32, 20>)(((ap_fixed<64, 20>)layer2_0_avgpool_val) / (ap_fixed<64, 20>)4));
            layer2_0_avgpool_pipe_122[0][c][h][w] = layer2_0_avgpool_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_0_concat_pipe_123[1][32][16][16];
      #pragma HLS stream variable=layer2_0_concat_pipe_123 depth=123
      layer2_0_concat_cc19: for (ap_int<32> cc19 = 0; cc19 < 32; ++cc19) {
        layer2_0_concat_ww19: for (ap_int<32> ww19 = 0; ww19 < 16; ++ww19) {
          layer2_0_concat_hh19: for (ap_int<32> hh19 = 0; hh19 < 16; ++hh19) {
            ap_fixed<32, 20> layer2_0_avgpool_temp1;
            layer2_0_avgpool_temp1 = layer2_0_avgpool_pipe_122[(((cc19 % 16) - cc19) / 16)][cc19][ww19][hh19];
            ap_fixed<32, 20> layer2_0_concat_temp;
            layer2_0_concat_temp = layer2_0_avgpool_temp1;
            layer2_0_concat_pipe_123[0][cc19][ww19][hh19] = layer2_0_concat_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_0_residual1_pipe_44[1][32][16][16];
      #pragma HLS stream variable=layer2_0_residual1_pipe_44 depth=44
      layer2_0_residual1_cc20: for (ap_int<32> cc20 = 0; cc20 < 32; ++cc20) {
        layer2_0_residual1_ww20: for (ap_int<32> ww20 = 0; ww20 < 16; ++ww20) {
          layer2_0_residual1_hh20: for (ap_int<32> hh20 = 0; hh20 < 16; ++hh20) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_0_bn1_temp1;
            layer2_0_bn1_temp1 = layer2_0_bn1_pipe_43[0][cc20][ww20][hh20];
            ap_fixed<32, 20> layer2_0_residual1_temp;
            ap_fixed<32, 20> layer2_0_concat_temp1;
            layer2_0_concat_temp1 = layer2_0_concat_pipe_123[0][cc20][ww20][hh20];
            layer2_0_residual1_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer2_0_bn1_temp1) + ((ap_fixed<33, 21>)layer2_0_concat_temp1)));
            layer2_0_residual1_pipe_44[0][cc20][ww20][hh20] = layer2_0_residual1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_0_rprelu1_pipe_45[1][32][16][16];
      #pragma HLS stream variable=layer2_0_rprelu1_pipe_45 depth=45
      ap_fixed<32, 20> layer2_0_rprelu1_pipe_124[1][32][16][16];
      #pragma HLS stream variable=layer2_0_rprelu1_pipe_124 depth=124
      layer2_0_rprelu1_cc21: for (ap_int<32> cc21 = 0; cc21 < 32; ++cc21) {
        layer2_0_rprelu1_ww21: for (ap_int<32> ww21 = 0; ww21 < 16; ++ww21) {
          layer2_0_rprelu1_hh21: for (ap_int<32> hh21 = 0; hh21 < 16; ++hh21) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_0_residual1_temp1;
            layer2_0_residual1_temp1 = layer2_0_residual1_pipe_44[0][cc21][ww21][hh21];
            ap_fixed<32, 20> layer2_0_rprelu1_temp;
            layer2_0_rprelu1_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_0_residual1_temp1) + ((ap_fixed<33, 21>)w_layer2_0_rprelu1_0[cc21])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer2_0_residual1_temp1) + ((ap_fixed<33, 21>)w_layer2_0_rprelu1_0[cc21])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer2_0_rprelu1_2[cc21]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer2_0_residual1_temp1) + ((ap_fixed<33, 21>)w_layer2_0_rprelu1_0[cc21]))))))) + ((ap_fixed<66, 42>)w_layer2_0_rprelu1_1[cc21])));
            layer2_0_rprelu1_pipe_124[0][cc21][ww21][hh21] = layer2_0_rprelu1_temp;
            layer2_0_rprelu1_pipe_45[0][cc21][ww21][hh21] = layer2_0_rprelu1_temp;
          }
        }
      }
      ap_uint<1> layer2_0_rsign2_pipe_46[1][32][16][16];
      #pragma HLS stream variable=layer2_0_rsign2_pipe_46 depth=46
      layer2_0_rsign2_cc22: for (ap_int<32> cc22 = 0; cc22 < 32; ++cc22) {
        layer2_0_rsign2_ww22: for (ap_int<32> ww22 = 0; ww22 < 16; ++ww22) {
          layer2_0_rsign2_hh22: for (ap_int<32> hh22 = 0; hh22 < 16; ++hh22) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_0_rprelu1_temp1;
            layer2_0_rprelu1_temp1 = layer2_0_rprelu1_pipe_45[0][cc22][ww22][hh22];
            ap_uint<1> layer2_0_rsign2_temp;
            layer2_0_rsign2_temp = ((ap_uint<1>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_0_rprelu1_temp1) + ((ap_fixed<33, 21>)w_layer2_0_rsign2[cc22])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer2_0_rsign2_pipe_46[0][cc22][ww22][hh22] = layer2_0_rsign2_temp;
          }
        }
      }
      ap_uint<1> layer2_0_conv2_pad_pipe_47[1][32][18][18];
      #pragma HLS stream variable=layer2_0_conv2_pad_pipe_47 depth=47
      layer2_0_conv2_pad_not_zero8: for (ap_int<32> not_zero8 = 0; not_zero8 < 32; ++not_zero8) {
        layer2_0_conv2_pad_index_tuple8: for (ap_int<32> index_tuple8 = 0; index_tuple8 < 18; ++index_tuple8) {
          layer2_0_conv2_pad_i8: for (ap_int<32> i8 = 0; i8 < 18; ++i8) {
        #pragma HLS pipeline
            ap_uint<1> layer2_0_rsign2_temp1;
            layer2_0_rsign2_temp1 = layer2_0_rsign2_pipe_46[0][not_zero8][(index_tuple8 + -1)][(i8 + -1)];
            ap_uint<1> layer2_0_conv2_pad_temp;
            layer2_0_conv2_pad_temp = (((((1 <= index_tuple8) && (index_tuple8 < 17)) && (1 <= i8)) && (i8 < 17)) ? ((ap_uint<1>)layer2_0_rsign2_temp1) : ((ap_uint<1>)0));
            layer2_0_conv2_pad_pipe_47[0][not_zero8][index_tuple8][i8] = layer2_0_conv2_pad_temp;
          }
        }
      }
      ap_int<8> layer2_0_conv2_pipe_48[1][32][16][16];
      #pragma HLS stream variable=layer2_0_conv2_pipe_48 depth=48
      layer2_0_conv2_ff8: for (ap_int<32> ff8 = 0; ff8 < 32; ++ff8) {
        layer2_0_conv2_yy1: for (ap_int<32> yy1 = 0; yy1 < 16; ++yy1) {
          layer2_0_conv2_xx1: for (ap_int<32> xx1 = 0; xx1 < 16; ++xx1) {
            ap_int<8> layer2_0_conv2_sum;
            layer2_0_conv2_sum = (ap_int<8>)0;
            layer2_0_conv2_rc8: for (ap_int<32> rc8 = 0; rc8 < 32; ++rc8) {
              layer2_0_conv2_ry8: for (ap_int<32> ry8 = 0; ry8 < 3; ++ry8) {
                layer2_0_conv2_rx8: for (ap_int<32> rx8 = 0; rx8 < 3; ++rx8) {
                  ap_uint<1> layer2_0_conv2_pad_temp1;
                  layer2_0_conv2_pad_temp1 = layer2_0_conv2_pad_pipe_47[0][rc8][(yy1 + ry8)][(xx1 + rx8)];
                  layer2_0_conv2_sum = ((ap_int<8>)(((ap_int<34>)(((((((ap_int<33>)1 - ((ap_int<33>)rx8)) <= ((ap_int<33>)xx1)) && (((ap_int<33>)xx1) < ((ap_int<33>)17 - ((ap_int<33>)rx8)))) && (((ap_int<33>)1 - ((ap_int<33>)ry8)) <= ((ap_int<33>)yy1))) && (((ap_int<33>)yy1) < ((ap_int<33>)17 - ((ap_int<33>)ry8)))) ? ((ap_uint<32>)((((1U - ((ap_uint<32>)layer2_0_conv2_pad_temp1)) ^ w_layer2_0_conv2[ff8][rc8][ry8][rx8]) << 1) - 1U)) : ((ap_uint<32>)0U))) + ((ap_int<34>)layer2_0_conv2_sum)));
                }
              }
            }
            ap_int<8> layer2_0_conv2_temp;
            layer2_0_conv2_temp = layer2_0_conv2_sum;
            layer2_0_conv2_pipe_48[0][ff8][yy1][xx1] = layer2_0_conv2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_0_bn2_pipe_49[1][32][16][16];
      #pragma HLS stream variable=layer2_0_bn2_pipe_49 depth=49
      layer2_0_bn2_args08: for (ap_int<32> args08 = 0; args08 < 32; ++args08) {
        layer2_0_bn2_args18: for (ap_int<32> args18 = 0; args18 < 16; ++args18) {
          layer2_0_bn2_args28: for (ap_int<32> args28 = 0; args28 < 16; ++args28) {
          #pragma HLS pipeline
            ap_int<8> layer2_0_conv2_temp1;
            layer2_0_conv2_temp1 = layer2_0_conv2_pipe_48[0][args08][args18][args28];
            ap_fixed<32, 20> layer2_0_bn2_temp;
            layer2_0_bn2_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer2_0_conv2_temp1) - w_layer2_0_bn2_16[args08]))) / sqrt((((float)w_layer2_0_bn2_17[args08]) + 1.000000e-07f))) * ((float)w_layer2_0_bn2_14[args08])) + ((float)w_layer2_0_bn2_15[args08])));
            layer2_0_bn2_pipe_49[0][args08][args18][args28] = layer2_0_bn2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_0_residual2_pipe_50[1][32][16][16];
      #pragma HLS stream variable=layer2_0_residual2_pipe_50 depth=50
      layer2_0_residual2_cc23: for (ap_int<32> cc23 = 0; cc23 < 32; ++cc23) {
        layer2_0_residual2_ww23: for (ap_int<32> ww23 = 0; ww23 < 16; ++ww23) {
          layer2_0_residual2_hh23: for (ap_int<32> hh23 = 0; hh23 < 16; ++hh23) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_0_bn2_temp1;
            layer2_0_bn2_temp1 = layer2_0_bn2_pipe_49[0][cc23][ww23][hh23];
            ap_fixed<32, 20> layer2_0_residual2_temp;
            ap_fixed<32, 20> layer2_0_rprelu1_temp2;
            layer2_0_rprelu1_temp2 = layer2_0_rprelu1_pipe_124[0][cc23][ww23][hh23];
            layer2_0_residual2_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer2_0_bn2_temp1) + ((ap_fixed<33, 21>)layer2_0_rprelu1_temp2)));
            layer2_0_residual2_pipe_50[0][cc23][ww23][hh23] = layer2_0_residual2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_0_rprelu2_pipe_51[1][32][16][16];
      #pragma HLS stream variable=layer2_0_rprelu2_pipe_51 depth=51
      ap_fixed<32, 20> layer2_0_rprelu2_pipe_125[1][32][16][16];
      #pragma HLS stream variable=layer2_0_rprelu2_pipe_125 depth=125
      layer2_0_rprelu2_cc24: for (ap_int<32> cc24 = 0; cc24 < 32; ++cc24) {
        layer2_0_rprelu2_ww24: for (ap_int<32> ww24 = 0; ww24 < 16; ++ww24) {
          layer2_0_rprelu2_hh24: for (ap_int<32> hh24 = 0; hh24 < 16; ++hh24) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_0_residual2_temp1;
            layer2_0_residual2_temp1 = layer2_0_residual2_pipe_50[0][cc24][ww24][hh24];
            ap_fixed<32, 20> layer2_0_rprelu2_temp;
            layer2_0_rprelu2_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_0_residual2_temp1) + ((ap_fixed<33, 21>)w_layer2_0_rprelu2_3[cc24])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer2_0_residual2_temp1) + ((ap_fixed<33, 21>)w_layer2_0_rprelu2_3[cc24])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer2_0_rprelu2_5[cc24]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer2_0_residual2_temp1) + ((ap_fixed<33, 21>)w_layer2_0_rprelu2_3[cc24]))))))) + ((ap_fixed<66, 42>)w_layer2_0_rprelu2_4[cc24])));
            layer2_0_rprelu2_pipe_125[0][cc24][ww24][hh24] = layer2_0_rprelu2_temp;
            layer2_0_rprelu2_pipe_51[0][cc24][ww24][hh24] = layer2_0_rprelu2_temp;
          }
        }
      }
      ap_int<8> layer2_1_rsign1_pipe_52[1][32][16][16];
      #pragma HLS stream variable=layer2_1_rsign1_pipe_52 depth=52
      layer2_1_rsign1_cc25: for (ap_int<32> cc25 = 0; cc25 < 32; ++cc25) {
        layer2_1_rsign1_ww25: for (ap_int<32> ww25 = 0; ww25 < 16; ++ww25) {
          layer2_1_rsign1_hh25: for (ap_int<32> hh25 = 0; hh25 < 16; ++hh25) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_0_rprelu2_temp1;
            layer2_0_rprelu2_temp1 = layer2_0_rprelu2_pipe_51[0][cc25][ww25][hh25];
            ap_int<8> layer2_1_rsign1_temp;
            layer2_1_rsign1_temp = ((ap_int<8>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_0_rprelu2_temp1) + ((ap_fixed<33, 21>)w_layer2_1_rsign1[cc25])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer2_1_rsign1_pipe_52[0][cc25][ww25][hh25] = layer2_1_rsign1_temp;
          }
        }
      }
      ap_int<8> layer2_1_conv1_pad[1][32][18][18];
      ap_int<8> layer2_1_conv1_pad_pipe_53[1][32][18][18];
      #pragma HLS stream variable=layer2_1_conv1_pad_pipe_53 depth=53
      layer2_1_conv1_pad_not_zero9: for (ap_int<32> not_zero9 = 0; not_zero9 < 32; ++not_zero9) {
        layer2_1_conv1_pad_index_tuple9: for (ap_int<32> index_tuple9 = 0; index_tuple9 < 18; ++index_tuple9) {
          layer2_1_conv1_pad_i9: for (ap_int<32> i9 = 0; i9 < 18; ++i9) {
        #pragma HLS pipeline
            ap_int<8> layer2_1_rsign1_temp1;
            layer2_1_rsign1_temp1 = layer2_1_rsign1_pipe_52[0][not_zero9][(index_tuple9 + -1)][(i9 + -1)];
            ap_int<8> layer2_1_conv1_pad_temp;
            layer2_1_conv1_pad_temp = (((((1 <= index_tuple9) && (index_tuple9 < 17)) && (1 <= i9)) && (i9 < 17)) ? ((ap_int<8>)layer2_1_rsign1_temp1) : ((ap_int<8>)0));
            layer2_1_conv1_pad_pipe_53[0][not_zero9][index_tuple9][i9] = layer2_1_conv1_pad_temp;
            layer2_1_conv1_pad[0][not_zero9][index_tuple9][i9] = layer2_1_conv1_pad_temp;
          }
        }
      }
      ap_int<8> layer2_1_conv1_LB[1][32][3][18];
      #pragma HLS array_partition variable=layer2_1_conv1_LB dim=3 complete
      ap_int<8> layer2_1_conv1_WB[1][32][3][3];
      #pragma HLS array_partition variable=layer2_1_conv1_WB dim=3 complete
      #pragma HLS array_partition variable=layer2_1_conv1_WB dim=4 complete
      ap_int<8> layer2_1_conv1_pipe_54[1][32][16][16];
      #pragma HLS stream variable=layer2_1_conv1_pipe_54 depth=54
      layer2_1_conv1_ff9: for (ap_int<32> ff9 = 0; ff9 < 32; ++ff9) {
        layer2_1_conv1_yy_reuse7: for (ap_int<32> yy_reuse7 = 0; yy_reuse7 < 18; ++yy_reuse7) {
          layer2_1_conv1_xx_reuse7: for (ap_int<32> xx_reuse7 = 0; xx_reuse7 < 18; ++xx_reuse7) {
            layer2_1_conv1_pad_2: for (ap_int<32> layer2_1_conv1_pad_2 = 0; layer2_1_conv1_pad_2 < 32; ++layer2_1_conv1_pad_2) {
          #pragma HLS pipeline
              layer2_1_conv1_pad_1: for (ap_int<32> layer2_1_conv1_pad_1 = 0; layer2_1_conv1_pad_1 < 2; ++layer2_1_conv1_pad_1) {
                layer2_1_conv1_LB[0][layer2_1_conv1_pad_2][layer2_1_conv1_pad_1][xx_reuse7] = layer2_1_conv1_LB[0][layer2_1_conv1_pad_2][(layer2_1_conv1_pad_1 + 1)][xx_reuse7];
              }
              ap_int<8> layer2_1_conv1_pad_temp1;
              layer2_1_conv1_pad_temp1 = layer2_1_conv1_pad_pipe_53[0][layer2_1_conv1_pad_2][yy_reuse7][xx_reuse7];
              layer2_1_conv1_LB[0][layer2_1_conv1_pad_2][2][xx_reuse7] = layer2_1_conv1_pad_temp1;
            }
            if (2 <= yy_reuse7) {
              layer2_1_conv1_LB_1: for (ap_int<32> layer2_1_conv1_LB_1 = 0; layer2_1_conv1_LB_1 < 3; ++layer2_1_conv1_LB_1) {
                layer2_1_conv1_LB_2: for (ap_int<32> layer2_1_conv1_LB_2 = 0; layer2_1_conv1_LB_2 < 32; ++layer2_1_conv1_LB_2) {
                  layer2_1_conv1_LB_0: for (ap_int<32> layer2_1_conv1_LB_0 = 0; layer2_1_conv1_LB_0 < 2; ++layer2_1_conv1_LB_0) {
                    layer2_1_conv1_WB[0][layer2_1_conv1_LB_2][layer2_1_conv1_LB_1][layer2_1_conv1_LB_0] = layer2_1_conv1_WB[0][layer2_1_conv1_LB_2][layer2_1_conv1_LB_1][(layer2_1_conv1_LB_0 + 1)];
                  }
                  layer2_1_conv1_WB[0][layer2_1_conv1_LB_2][layer2_1_conv1_LB_1][2] = layer2_1_conv1_LB[0][layer2_1_conv1_LB_2][layer2_1_conv1_LB_1][xx_reuse7];
                }
              }
              if (2 <= xx_reuse7) {
                ap_int<8> layer2_1_conv1_sum;
                layer2_1_conv1_sum = (ap_int<8>)0;
                layer2_1_conv1_rc9: for (ap_int<32> rc9 = 0; rc9 < 32; ++rc9) {
                  layer2_1_conv1_ry9: for (ap_int<32> ry9 = 0; ry9 < 3; ++ry9) {
                    layer2_1_conv1_rx9: for (ap_int<32> rx9 = 0; rx9 < 3; ++rx9) {
                      layer2_1_conv1_sum = ((ap_int<8>)(((ap_int<33>)(((((((ap_int<33>)1 - ((ap_int<33>)rx9)) <= ((ap_int<33>)(xx_reuse7 + -2))) && (((ap_int<33>)(xx_reuse7 + -2)) < ((ap_int<33>)17 - ((ap_int<33>)rx9)))) && (((ap_int<33>)1 - ((ap_int<33>)ry9)) <= ((ap_int<33>)(yy_reuse7 + -2)))) && (((ap_int<33>)(yy_reuse7 + -2)) < ((ap_int<33>)17 - ((ap_int<33>)ry9)))) ? ((ap_int<32>)((((1 - ((ap_int<32>)layer2_1_conv1_WB[0][rc9][ry9][rx9])) ^ w_layer2_1_conv1[ff9][rc9][ry9][rx9]) << 1) + -1)) : ((ap_int<32>)0))) + ((ap_int<33>)layer2_1_conv1_sum)));
                    }
                  }
                }
                ap_int<8> layer2_1_conv1_temp;
                layer2_1_conv1_temp = layer2_1_conv1_sum;
                layer2_1_conv1_pipe_54[0][ff9][(yy_reuse7 + -2)][(xx_reuse7 + -2)] = layer2_1_conv1_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer2_1_bn1_pipe_55[1][32][16][16];
      #pragma HLS stream variable=layer2_1_bn1_pipe_55 depth=55
      layer2_1_bn1_args09: for (ap_int<32> args09 = 0; args09 < 32; ++args09) {
        layer2_1_bn1_args19: for (ap_int<32> args19 = 0; args19 < 16; ++args19) {
          layer2_1_bn1_args29: for (ap_int<32> args29 = 0; args29 < 16; ++args29) {
          #pragma HLS pipeline
            ap_int<8> layer2_1_conv1_temp1;
            layer2_1_conv1_temp1 = layer2_1_conv1_pipe_54[0][args09][args19][args29];
            ap_fixed<32, 20> layer2_1_bn1_temp;
            layer2_1_bn1_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer2_1_conv1_temp1) - w_layer2_1_bn1_11[args09]))) / sqrt((((float)w_layer2_1_bn1_12[args09]) + 1.000000e-07f))) * ((float)w_layer2_1_bn1_9[args09])) + ((float)w_layer2_1_bn1_10[args09])));
            layer2_1_bn1_pipe_55[0][args09][args19][args29] = layer2_1_bn1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_1_residual1_pipe_56[1][32][16][16];
      #pragma HLS stream variable=layer2_1_residual1_pipe_56 depth=56
      layer2_1_residual1_cc26: for (ap_int<32> cc26 = 0; cc26 < 32; ++cc26) {
        layer2_1_residual1_ww26: for (ap_int<32> ww26 = 0; ww26 < 16; ++ww26) {
          layer2_1_residual1_hh26: for (ap_int<32> hh26 = 0; hh26 < 16; ++hh26) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_1_bn1_temp1;
            layer2_1_bn1_temp1 = layer2_1_bn1_pipe_55[0][cc26][ww26][hh26];
            ap_fixed<32, 20> layer2_1_residual1_temp;
            ap_fixed<32, 20> layer2_0_rprelu2_temp2;
            layer2_0_rprelu2_temp2 = layer2_0_rprelu2_pipe_125[0][cc26][ww26][hh26];
            layer2_1_residual1_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer2_1_bn1_temp1) + ((ap_fixed<33, 21>)layer2_0_rprelu2_temp2)));
            layer2_1_residual1_pipe_56[0][cc26][ww26][hh26] = layer2_1_residual1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_1_rprelu1_pipe_57[1][32][16][16];
      #pragma HLS stream variable=layer2_1_rprelu1_pipe_57 depth=57
      ap_fixed<32, 20> layer2_1_rprelu1_pipe_126[1][32][16][16];
      #pragma HLS stream variable=layer2_1_rprelu1_pipe_126 depth=126
      layer2_1_rprelu1_cc27: for (ap_int<32> cc27 = 0; cc27 < 32; ++cc27) {
        layer2_1_rprelu1_ww27: for (ap_int<32> ww27 = 0; ww27 < 16; ++ww27) {
          layer2_1_rprelu1_hh27: for (ap_int<32> hh27 = 0; hh27 < 16; ++hh27) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_1_residual1_temp1;
            layer2_1_residual1_temp1 = layer2_1_residual1_pipe_56[0][cc27][ww27][hh27];
            ap_fixed<32, 20> layer2_1_rprelu1_temp;
            layer2_1_rprelu1_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_1_residual1_temp1) + ((ap_fixed<33, 21>)w_layer2_1_rprelu1_0[cc27])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer2_1_residual1_temp1) + ((ap_fixed<33, 21>)w_layer2_1_rprelu1_0[cc27])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer2_1_rprelu1_2[cc27]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer2_1_residual1_temp1) + ((ap_fixed<33, 21>)w_layer2_1_rprelu1_0[cc27]))))))) + ((ap_fixed<66, 42>)w_layer2_1_rprelu1_1[cc27])));
            layer2_1_rprelu1_pipe_126[0][cc27][ww27][hh27] = layer2_1_rprelu1_temp;
            layer2_1_rprelu1_pipe_57[0][cc27][ww27][hh27] = layer2_1_rprelu1_temp;
          }
        }
      }
      ap_uint<1> layer2_1_rsign2_pipe_58[1][32][16][16];
      #pragma HLS stream variable=layer2_1_rsign2_pipe_58 depth=58
      layer2_1_rsign2_cc28: for (ap_int<32> cc28 = 0; cc28 < 32; ++cc28) {
        layer2_1_rsign2_ww28: for (ap_int<32> ww28 = 0; ww28 < 16; ++ww28) {
          layer2_1_rsign2_hh28: for (ap_int<32> hh28 = 0; hh28 < 16; ++hh28) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_1_rprelu1_temp1;
            layer2_1_rprelu1_temp1 = layer2_1_rprelu1_pipe_57[0][cc28][ww28][hh28];
            ap_uint<1> layer2_1_rsign2_temp;
            layer2_1_rsign2_temp = ((ap_uint<1>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_1_rprelu1_temp1) + ((ap_fixed<33, 21>)w_layer2_1_rsign2[cc28])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer2_1_rsign2_pipe_58[0][cc28][ww28][hh28] = layer2_1_rsign2_temp;
          }
        }
      }
      ap_uint<1> layer2_1_conv2_pad[1][32][18][18];
      ap_uint<1> layer2_1_conv2_pad_pipe_59[1][32][18][18];
      #pragma HLS stream variable=layer2_1_conv2_pad_pipe_59 depth=59
      layer2_1_conv2_pad_not_zero10: for (ap_int<32> not_zero10 = 0; not_zero10 < 32; ++not_zero10) {
        layer2_1_conv2_pad_index_tuple10: for (ap_int<32> index_tuple10 = 0; index_tuple10 < 18; ++index_tuple10) {
          layer2_1_conv2_pad_i10: for (ap_int<32> i10 = 0; i10 < 18; ++i10) {
        #pragma HLS pipeline
            ap_uint<1> layer2_1_rsign2_temp1;
            layer2_1_rsign2_temp1 = layer2_1_rsign2_pipe_58[0][not_zero10][(index_tuple10 + -1)][(i10 + -1)];
            ap_uint<1> layer2_1_conv2_pad_temp;
            layer2_1_conv2_pad_temp = (((((1 <= index_tuple10) && (index_tuple10 < 17)) && (1 <= i10)) && (i10 < 17)) ? ((ap_uint<1>)layer2_1_rsign2_temp1) : ((ap_uint<1>)0));
            layer2_1_conv2_pad_pipe_59[0][not_zero10][index_tuple10][i10] = layer2_1_conv2_pad_temp;
            layer2_1_conv2_pad[0][not_zero10][index_tuple10][i10] = layer2_1_conv2_pad_temp;
          }
        }
      }
      ap_uint<1> layer2_1_conv2_LB[1][32][3][18];
      #pragma HLS array_partition variable=layer2_1_conv2_LB dim=3 complete
      ap_uint<1> layer2_1_conv2_WB[1][32][3][3];
      #pragma HLS array_partition variable=layer2_1_conv2_WB dim=3 complete
      #pragma HLS array_partition variable=layer2_1_conv2_WB dim=4 complete
      ap_int<8> layer2_1_conv2_pipe_60[1][32][16][16];
      #pragma HLS stream variable=layer2_1_conv2_pipe_60 depth=60
      layer2_1_conv2_ff10: for (ap_int<32> ff10 = 0; ff10 < 32; ++ff10) {
        layer2_1_conv2_yy_reuse8: for (ap_int<32> yy_reuse8 = 0; yy_reuse8 < 18; ++yy_reuse8) {
          layer2_1_conv2_xx_reuse8: for (ap_int<32> xx_reuse8 = 0; xx_reuse8 < 18; ++xx_reuse8) {
            layer2_1_conv2_pad_2: for (ap_int<32> layer2_1_conv2_pad_2 = 0; layer2_1_conv2_pad_2 < 32; ++layer2_1_conv2_pad_2) {
          #pragma HLS pipeline
              layer2_1_conv2_pad_1: for (ap_int<32> layer2_1_conv2_pad_1 = 0; layer2_1_conv2_pad_1 < 2; ++layer2_1_conv2_pad_1) {
                layer2_1_conv2_LB[0][layer2_1_conv2_pad_2][layer2_1_conv2_pad_1][xx_reuse8] = layer2_1_conv2_LB[0][layer2_1_conv2_pad_2][(layer2_1_conv2_pad_1 + 1)][xx_reuse8];
              }
              ap_uint<1> layer2_1_conv2_pad_temp1;
              layer2_1_conv2_pad_temp1 = layer2_1_conv2_pad_pipe_59[0][layer2_1_conv2_pad_2][yy_reuse8][xx_reuse8];
              layer2_1_conv2_LB[0][layer2_1_conv2_pad_2][2][xx_reuse8] = layer2_1_conv2_pad_temp1;
            }
            if (2 <= yy_reuse8) {
              layer2_1_conv2_LB_1: for (ap_int<32> layer2_1_conv2_LB_1 = 0; layer2_1_conv2_LB_1 < 3; ++layer2_1_conv2_LB_1) {
                layer2_1_conv2_LB_2: for (ap_int<32> layer2_1_conv2_LB_2 = 0; layer2_1_conv2_LB_2 < 32; ++layer2_1_conv2_LB_2) {
                  layer2_1_conv2_LB_0: for (ap_int<32> layer2_1_conv2_LB_0 = 0; layer2_1_conv2_LB_0 < 2; ++layer2_1_conv2_LB_0) {
                    layer2_1_conv2_WB[0][layer2_1_conv2_LB_2][layer2_1_conv2_LB_1][layer2_1_conv2_LB_0] = layer2_1_conv2_WB[0][layer2_1_conv2_LB_2][layer2_1_conv2_LB_1][(layer2_1_conv2_LB_0 + 1)];
                  }
                  layer2_1_conv2_WB[0][layer2_1_conv2_LB_2][layer2_1_conv2_LB_1][2] = layer2_1_conv2_LB[0][layer2_1_conv2_LB_2][layer2_1_conv2_LB_1][xx_reuse8];
                }
              }
              if (2 <= xx_reuse8) {
                ap_int<8> layer2_1_conv2_sum;
                layer2_1_conv2_sum = (ap_int<8>)0;
                layer2_1_conv2_rc10: for (ap_int<32> rc10 = 0; rc10 < 32; ++rc10) {
                  layer2_1_conv2_ry10: for (ap_int<32> ry10 = 0; ry10 < 3; ++ry10) {
                    layer2_1_conv2_rx10: for (ap_int<32> rx10 = 0; rx10 < 3; ++rx10) {
                      layer2_1_conv2_sum = ((ap_int<8>)(((ap_int<34>)(((((((ap_int<33>)1 - ((ap_int<33>)rx10)) <= ((ap_int<33>)(xx_reuse8 + -2))) && (((ap_int<33>)(xx_reuse8 + -2)) < ((ap_int<33>)17 - ((ap_int<33>)rx10)))) && (((ap_int<33>)1 - ((ap_int<33>)ry10)) <= ((ap_int<33>)(yy_reuse8 + -2)))) && (((ap_int<33>)(yy_reuse8 + -2)) < ((ap_int<33>)17 - ((ap_int<33>)ry10)))) ? ((ap_uint<32>)((((1U - ((ap_uint<32>)layer2_1_conv2_WB[0][rc10][ry10][rx10])) ^ w_layer2_1_conv2[ff10][rc10][ry10][rx10]) << 1) - 1U)) : ((ap_uint<32>)0U))) + ((ap_int<34>)layer2_1_conv2_sum)));
                    }
                  }
                }
                ap_int<8> layer2_1_conv2_temp;
                layer2_1_conv2_temp = layer2_1_conv2_sum;
                layer2_1_conv2_pipe_60[0][ff10][(yy_reuse8 + -2)][(xx_reuse8 + -2)] = layer2_1_conv2_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer2_1_bn2_pipe_61[1][32][16][16];
      #pragma HLS stream variable=layer2_1_bn2_pipe_61 depth=61
      layer2_1_bn2_args010: for (ap_int<32> args010 = 0; args010 < 32; ++args010) {
        layer2_1_bn2_args110: for (ap_int<32> args110 = 0; args110 < 16; ++args110) {
          layer2_1_bn2_args210: for (ap_int<32> args210 = 0; args210 < 16; ++args210) {
          #pragma HLS pipeline
            ap_int<8> layer2_1_conv2_temp1;
            layer2_1_conv2_temp1 = layer2_1_conv2_pipe_60[0][args010][args110][args210];
            ap_fixed<32, 20> layer2_1_bn2_temp;
            layer2_1_bn2_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer2_1_conv2_temp1) - w_layer2_1_bn2_16[args010]))) / sqrt((((float)w_layer2_1_bn2_17[args010]) + 1.000000e-07f))) * ((float)w_layer2_1_bn2_14[args010])) + ((float)w_layer2_1_bn2_15[args010])));
            layer2_1_bn2_pipe_61[0][args010][args110][args210] = layer2_1_bn2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_1_residual2_pipe_62[1][32][16][16];
      #pragma HLS stream variable=layer2_1_residual2_pipe_62 depth=62
      layer2_1_residual2_cc29: for (ap_int<32> cc29 = 0; cc29 < 32; ++cc29) {
        layer2_1_residual2_ww29: for (ap_int<32> ww29 = 0; ww29 < 16; ++ww29) {
          layer2_1_residual2_hh29: for (ap_int<32> hh29 = 0; hh29 < 16; ++hh29) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_1_bn2_temp1;
            layer2_1_bn2_temp1 = layer2_1_bn2_pipe_61[0][cc29][ww29][hh29];
            ap_fixed<32, 20> layer2_1_residual2_temp;
            ap_fixed<32, 20> layer2_1_rprelu1_temp2;
            layer2_1_rprelu1_temp2 = layer2_1_rprelu1_pipe_126[0][cc29][ww29][hh29];
            layer2_1_residual2_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer2_1_bn2_temp1) + ((ap_fixed<33, 21>)layer2_1_rprelu1_temp2)));
            layer2_1_residual2_pipe_62[0][cc29][ww29][hh29] = layer2_1_residual2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_1_rprelu2_pipe_63[1][32][16][16];
      #pragma HLS stream variable=layer2_1_rprelu2_pipe_63 depth=63
      ap_fixed<32, 20> layer2_1_rprelu2_pipe_127[1][32][16][16];
      #pragma HLS stream variable=layer2_1_rprelu2_pipe_127 depth=127
      layer2_1_rprelu2_cc30: for (ap_int<32> cc30 = 0; cc30 < 32; ++cc30) {
        layer2_1_rprelu2_ww30: for (ap_int<32> ww30 = 0; ww30 < 16; ++ww30) {
          layer2_1_rprelu2_hh30: for (ap_int<32> hh30 = 0; hh30 < 16; ++hh30) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_1_residual2_temp1;
            layer2_1_residual2_temp1 = layer2_1_residual2_pipe_62[0][cc30][ww30][hh30];
            ap_fixed<32, 20> layer2_1_rprelu2_temp;
            layer2_1_rprelu2_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_1_residual2_temp1) + ((ap_fixed<33, 21>)w_layer2_1_rprelu2_3[cc30])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer2_1_residual2_temp1) + ((ap_fixed<33, 21>)w_layer2_1_rprelu2_3[cc30])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer2_1_rprelu2_5[cc30]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer2_1_residual2_temp1) + ((ap_fixed<33, 21>)w_layer2_1_rprelu2_3[cc30]))))))) + ((ap_fixed<66, 42>)w_layer2_1_rprelu2_4[cc30])));
            layer2_1_rprelu2_pipe_127[0][cc30][ww30][hh30] = layer2_1_rprelu2_temp;
            layer2_1_rprelu2_pipe_63[0][cc30][ww30][hh30] = layer2_1_rprelu2_temp;
          }
        }
      }
      ap_int<8> layer2_2_rsign1_pipe_64[1][32][16][16];
      #pragma HLS stream variable=layer2_2_rsign1_pipe_64 depth=64
      layer2_2_rsign1_cc31: for (ap_int<32> cc31 = 0; cc31 < 32; ++cc31) {
        layer2_2_rsign1_ww31: for (ap_int<32> ww31 = 0; ww31 < 16; ++ww31) {
          layer2_2_rsign1_hh31: for (ap_int<32> hh31 = 0; hh31 < 16; ++hh31) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_1_rprelu2_temp1;
            layer2_1_rprelu2_temp1 = layer2_1_rprelu2_pipe_63[0][cc31][ww31][hh31];
            ap_int<8> layer2_2_rsign1_temp;
            layer2_2_rsign1_temp = ((ap_int<8>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_1_rprelu2_temp1) + ((ap_fixed<33, 21>)w_layer2_2_rsign1[cc31])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer2_2_rsign1_pipe_64[0][cc31][ww31][hh31] = layer2_2_rsign1_temp;
          }
        }
      }
      ap_int<8> layer2_2_conv1_pad[1][32][18][18];
      ap_int<8> layer2_2_conv1_pad_pipe_65[1][32][18][18];
      #pragma HLS stream variable=layer2_2_conv1_pad_pipe_65 depth=65
      layer2_2_conv1_pad_not_zero11: for (ap_int<32> not_zero11 = 0; not_zero11 < 32; ++not_zero11) {
        layer2_2_conv1_pad_index_tuple11: for (ap_int<32> index_tuple11 = 0; index_tuple11 < 18; ++index_tuple11) {
          layer2_2_conv1_pad_i11: for (ap_int<32> i11 = 0; i11 < 18; ++i11) {
        #pragma HLS pipeline
            ap_int<8> layer2_2_rsign1_temp1;
            layer2_2_rsign1_temp1 = layer2_2_rsign1_pipe_64[0][not_zero11][(index_tuple11 + -1)][(i11 + -1)];
            ap_int<8> layer2_2_conv1_pad_temp;
            layer2_2_conv1_pad_temp = (((((1 <= index_tuple11) && (index_tuple11 < 17)) && (1 <= i11)) && (i11 < 17)) ? ((ap_int<8>)layer2_2_rsign1_temp1) : ((ap_int<8>)0));
            layer2_2_conv1_pad_pipe_65[0][not_zero11][index_tuple11][i11] = layer2_2_conv1_pad_temp;
            layer2_2_conv1_pad[0][not_zero11][index_tuple11][i11] = layer2_2_conv1_pad_temp;
          }
        }
      }
      ap_int<8> layer2_2_conv1_LB[1][32][3][18];
      #pragma HLS array_partition variable=layer2_2_conv1_LB dim=3 complete
      ap_int<8> layer2_2_conv1_WB[1][32][3][3];
      #pragma HLS array_partition variable=layer2_2_conv1_WB dim=3 complete
      #pragma HLS array_partition variable=layer2_2_conv1_WB dim=4 complete
      ap_int<8> layer2_2_conv1_pipe_66[1][32][16][16];
      #pragma HLS stream variable=layer2_2_conv1_pipe_66 depth=66
      layer2_2_conv1_ff11: for (ap_int<32> ff11 = 0; ff11 < 32; ++ff11) {
        layer2_2_conv1_yy_reuse9: for (ap_int<32> yy_reuse9 = 0; yy_reuse9 < 18; ++yy_reuse9) {
          layer2_2_conv1_xx_reuse9: for (ap_int<32> xx_reuse9 = 0; xx_reuse9 < 18; ++xx_reuse9) {
            layer2_2_conv1_pad_2: for (ap_int<32> layer2_2_conv1_pad_2 = 0; layer2_2_conv1_pad_2 < 32; ++layer2_2_conv1_pad_2) {
          #pragma HLS pipeline
              layer2_2_conv1_pad_1: for (ap_int<32> layer2_2_conv1_pad_1 = 0; layer2_2_conv1_pad_1 < 2; ++layer2_2_conv1_pad_1) {
                layer2_2_conv1_LB[0][layer2_2_conv1_pad_2][layer2_2_conv1_pad_1][xx_reuse9] = layer2_2_conv1_LB[0][layer2_2_conv1_pad_2][(layer2_2_conv1_pad_1 + 1)][xx_reuse9];
              }
              ap_int<8> layer2_2_conv1_pad_temp1;
              layer2_2_conv1_pad_temp1 = layer2_2_conv1_pad_pipe_65[0][layer2_2_conv1_pad_2][yy_reuse9][xx_reuse9];
              layer2_2_conv1_LB[0][layer2_2_conv1_pad_2][2][xx_reuse9] = layer2_2_conv1_pad_temp1;
            }
            if (2 <= yy_reuse9) {
              layer2_2_conv1_LB_1: for (ap_int<32> layer2_2_conv1_LB_1 = 0; layer2_2_conv1_LB_1 < 3; ++layer2_2_conv1_LB_1) {
                layer2_2_conv1_LB_2: for (ap_int<32> layer2_2_conv1_LB_2 = 0; layer2_2_conv1_LB_2 < 32; ++layer2_2_conv1_LB_2) {
                  layer2_2_conv1_LB_0: for (ap_int<32> layer2_2_conv1_LB_0 = 0; layer2_2_conv1_LB_0 < 2; ++layer2_2_conv1_LB_0) {
                    layer2_2_conv1_WB[0][layer2_2_conv1_LB_2][layer2_2_conv1_LB_1][layer2_2_conv1_LB_0] = layer2_2_conv1_WB[0][layer2_2_conv1_LB_2][layer2_2_conv1_LB_1][(layer2_2_conv1_LB_0 + 1)];
                  }
                  layer2_2_conv1_WB[0][layer2_2_conv1_LB_2][layer2_2_conv1_LB_1][2] = layer2_2_conv1_LB[0][layer2_2_conv1_LB_2][layer2_2_conv1_LB_1][xx_reuse9];
                }
              }
              if (2 <= xx_reuse9) {
                ap_int<8> layer2_2_conv1_sum;
                layer2_2_conv1_sum = (ap_int<8>)0;
                layer2_2_conv1_rc11: for (ap_int<32> rc11 = 0; rc11 < 32; ++rc11) {
                  layer2_2_conv1_ry11: for (ap_int<32> ry11 = 0; ry11 < 3; ++ry11) {
                    layer2_2_conv1_rx11: for (ap_int<32> rx11 = 0; rx11 < 3; ++rx11) {
                      layer2_2_conv1_sum = ((ap_int<8>)(((ap_int<33>)(((((((ap_int<33>)1 - ((ap_int<33>)rx11)) <= ((ap_int<33>)(xx_reuse9 + -2))) && (((ap_int<33>)(xx_reuse9 + -2)) < ((ap_int<33>)17 - ((ap_int<33>)rx11)))) && (((ap_int<33>)1 - ((ap_int<33>)ry11)) <= ((ap_int<33>)(yy_reuse9 + -2)))) && (((ap_int<33>)(yy_reuse9 + -2)) < ((ap_int<33>)17 - ((ap_int<33>)ry11)))) ? ((ap_int<32>)((((1 - ((ap_int<32>)layer2_2_conv1_WB[0][rc11][ry11][rx11])) ^ w_layer2_2_conv1[ff11][rc11][ry11][rx11]) << 1) + -1)) : ((ap_int<32>)0))) + ((ap_int<33>)layer2_2_conv1_sum)));
                    }
                  }
                }
                ap_int<8> layer2_2_conv1_temp;
                layer2_2_conv1_temp = layer2_2_conv1_sum;
                layer2_2_conv1_pipe_66[0][ff11][(yy_reuse9 + -2)][(xx_reuse9 + -2)] = layer2_2_conv1_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer2_2_bn1_pipe_67[1][32][16][16];
      #pragma HLS stream variable=layer2_2_bn1_pipe_67 depth=67
      layer2_2_bn1_args011: for (ap_int<32> args011 = 0; args011 < 32; ++args011) {
        layer2_2_bn1_args111: for (ap_int<32> args111 = 0; args111 < 16; ++args111) {
          layer2_2_bn1_args211: for (ap_int<32> args211 = 0; args211 < 16; ++args211) {
          #pragma HLS pipeline
            ap_int<8> layer2_2_conv1_temp1;
            layer2_2_conv1_temp1 = layer2_2_conv1_pipe_66[0][args011][args111][args211];
            ap_fixed<32, 20> layer2_2_bn1_temp;
            layer2_2_bn1_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer2_2_conv1_temp1) - w_layer2_2_bn1_11[args011]))) / sqrt((((float)w_layer2_2_bn1_12[args011]) + 1.000000e-07f))) * ((float)w_layer2_2_bn1_9[args011])) + ((float)w_layer2_2_bn1_10[args011])));
            layer2_2_bn1_pipe_67[0][args011][args111][args211] = layer2_2_bn1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_2_residual1_pipe_68[1][32][16][16];
      #pragma HLS stream variable=layer2_2_residual1_pipe_68 depth=68
      layer2_2_residual1_cc32: for (ap_int<32> cc32 = 0; cc32 < 32; ++cc32) {
        layer2_2_residual1_ww32: for (ap_int<32> ww32 = 0; ww32 < 16; ++ww32) {
          layer2_2_residual1_hh32: for (ap_int<32> hh32 = 0; hh32 < 16; ++hh32) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_2_bn1_temp1;
            layer2_2_bn1_temp1 = layer2_2_bn1_pipe_67[0][cc32][ww32][hh32];
            ap_fixed<32, 20> layer2_2_residual1_temp;
            ap_fixed<32, 20> layer2_1_rprelu2_temp2;
            layer2_1_rprelu2_temp2 = layer2_1_rprelu2_pipe_127[0][cc32][ww32][hh32];
            layer2_2_residual1_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer2_2_bn1_temp1) + ((ap_fixed<33, 21>)layer2_1_rprelu2_temp2)));
            layer2_2_residual1_pipe_68[0][cc32][ww32][hh32] = layer2_2_residual1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_2_rprelu1_pipe_69[1][32][16][16];
      #pragma HLS stream variable=layer2_2_rprelu1_pipe_69 depth=69
      ap_fixed<32, 20> layer2_2_rprelu1_pipe_128[1][32][16][16];
      #pragma HLS stream variable=layer2_2_rprelu1_pipe_128 depth=128
      layer2_2_rprelu1_cc33: for (ap_int<32> cc33 = 0; cc33 < 32; ++cc33) {
        layer2_2_rprelu1_ww33: for (ap_int<32> ww33 = 0; ww33 < 16; ++ww33) {
          layer2_2_rprelu1_hh33: for (ap_int<32> hh33 = 0; hh33 < 16; ++hh33) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_2_residual1_temp1;
            layer2_2_residual1_temp1 = layer2_2_residual1_pipe_68[0][cc33][ww33][hh33];
            ap_fixed<32, 20> layer2_2_rprelu1_temp;
            layer2_2_rprelu1_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_2_residual1_temp1) + ((ap_fixed<33, 21>)w_layer2_2_rprelu1_0[cc33])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer2_2_residual1_temp1) + ((ap_fixed<33, 21>)w_layer2_2_rprelu1_0[cc33])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer2_2_rprelu1_2[cc33]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer2_2_residual1_temp1) + ((ap_fixed<33, 21>)w_layer2_2_rprelu1_0[cc33]))))))) + ((ap_fixed<66, 42>)w_layer2_2_rprelu1_1[cc33])));
            layer2_2_rprelu1_pipe_128[0][cc33][ww33][hh33] = layer2_2_rprelu1_temp;
            layer2_2_rprelu1_pipe_69[0][cc33][ww33][hh33] = layer2_2_rprelu1_temp;
          }
        }
      }
      ap_uint<1> layer2_2_rsign2_pipe_70[1][32][16][16];
      #pragma HLS stream variable=layer2_2_rsign2_pipe_70 depth=70
      layer2_2_rsign2_cc34: for (ap_int<32> cc34 = 0; cc34 < 32; ++cc34) {
        layer2_2_rsign2_ww34: for (ap_int<32> ww34 = 0; ww34 < 16; ++ww34) {
          layer2_2_rsign2_hh34: for (ap_int<32> hh34 = 0; hh34 < 16; ++hh34) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_2_rprelu1_temp1;
            layer2_2_rprelu1_temp1 = layer2_2_rprelu1_pipe_69[0][cc34][ww34][hh34];
            ap_uint<1> layer2_2_rsign2_temp;
            layer2_2_rsign2_temp = ((ap_uint<1>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_2_rprelu1_temp1) + ((ap_fixed<33, 21>)w_layer2_2_rsign2[cc34])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer2_2_rsign2_pipe_70[0][cc34][ww34][hh34] = layer2_2_rsign2_temp;
          }
        }
      }
      ap_uint<1> layer2_2_conv2_pad[1][32][18][18];
      ap_uint<1> layer2_2_conv2_pad_pipe_71[1][32][18][18];
      #pragma HLS stream variable=layer2_2_conv2_pad_pipe_71 depth=71
      layer2_2_conv2_pad_not_zero12: for (ap_int<32> not_zero12 = 0; not_zero12 < 32; ++not_zero12) {
        layer2_2_conv2_pad_index_tuple12: for (ap_int<32> index_tuple12 = 0; index_tuple12 < 18; ++index_tuple12) {
          layer2_2_conv2_pad_i12: for (ap_int<32> i12 = 0; i12 < 18; ++i12) {
        #pragma HLS pipeline
            ap_uint<1> layer2_2_rsign2_temp1;
            layer2_2_rsign2_temp1 = layer2_2_rsign2_pipe_70[0][not_zero12][(index_tuple12 + -1)][(i12 + -1)];
            ap_uint<1> layer2_2_conv2_pad_temp;
            layer2_2_conv2_pad_temp = (((((1 <= index_tuple12) && (index_tuple12 < 17)) && (1 <= i12)) && (i12 < 17)) ? ((ap_uint<1>)layer2_2_rsign2_temp1) : ((ap_uint<1>)0));
            layer2_2_conv2_pad_pipe_71[0][not_zero12][index_tuple12][i12] = layer2_2_conv2_pad_temp;
            layer2_2_conv2_pad[0][not_zero12][index_tuple12][i12] = layer2_2_conv2_pad_temp;
          }
        }
      }
      ap_uint<1> layer2_2_conv2_LB[1][32][3][18];
      #pragma HLS array_partition variable=layer2_2_conv2_LB dim=3 complete
      ap_uint<1> layer2_2_conv2_WB[1][32][3][3];
      #pragma HLS array_partition variable=layer2_2_conv2_WB dim=3 complete
      #pragma HLS array_partition variable=layer2_2_conv2_WB dim=4 complete
      ap_int<8> layer2_2_conv2_pipe_72[1][32][16][16];
      #pragma HLS stream variable=layer2_2_conv2_pipe_72 depth=72
      layer2_2_conv2_ff12: for (ap_int<32> ff12 = 0; ff12 < 32; ++ff12) {
        layer2_2_conv2_yy_reuse10: for (ap_int<32> yy_reuse10 = 0; yy_reuse10 < 18; ++yy_reuse10) {
          layer2_2_conv2_xx_reuse10: for (ap_int<32> xx_reuse10 = 0; xx_reuse10 < 18; ++xx_reuse10) {
            layer2_2_conv2_pad_2: for (ap_int<32> layer2_2_conv2_pad_2 = 0; layer2_2_conv2_pad_2 < 32; ++layer2_2_conv2_pad_2) {
          #pragma HLS pipeline
              layer2_2_conv2_pad_1: for (ap_int<32> layer2_2_conv2_pad_1 = 0; layer2_2_conv2_pad_1 < 2; ++layer2_2_conv2_pad_1) {
                layer2_2_conv2_LB[0][layer2_2_conv2_pad_2][layer2_2_conv2_pad_1][xx_reuse10] = layer2_2_conv2_LB[0][layer2_2_conv2_pad_2][(layer2_2_conv2_pad_1 + 1)][xx_reuse10];
              }
              ap_uint<1> layer2_2_conv2_pad_temp1;
              layer2_2_conv2_pad_temp1 = layer2_2_conv2_pad_pipe_71[0][layer2_2_conv2_pad_2][yy_reuse10][xx_reuse10];
              layer2_2_conv2_LB[0][layer2_2_conv2_pad_2][2][xx_reuse10] = layer2_2_conv2_pad_temp1;
            }
            if (2 <= yy_reuse10) {
              layer2_2_conv2_LB_1: for (ap_int<32> layer2_2_conv2_LB_1 = 0; layer2_2_conv2_LB_1 < 3; ++layer2_2_conv2_LB_1) {
                layer2_2_conv2_LB_2: for (ap_int<32> layer2_2_conv2_LB_2 = 0; layer2_2_conv2_LB_2 < 32; ++layer2_2_conv2_LB_2) {
                  layer2_2_conv2_LB_0: for (ap_int<32> layer2_2_conv2_LB_0 = 0; layer2_2_conv2_LB_0 < 2; ++layer2_2_conv2_LB_0) {
                    layer2_2_conv2_WB[0][layer2_2_conv2_LB_2][layer2_2_conv2_LB_1][layer2_2_conv2_LB_0] = layer2_2_conv2_WB[0][layer2_2_conv2_LB_2][layer2_2_conv2_LB_1][(layer2_2_conv2_LB_0 + 1)];
                  }
                  layer2_2_conv2_WB[0][layer2_2_conv2_LB_2][layer2_2_conv2_LB_1][2] = layer2_2_conv2_LB[0][layer2_2_conv2_LB_2][layer2_2_conv2_LB_1][xx_reuse10];
                }
              }
              if (2 <= xx_reuse10) {
                ap_int<8> layer2_2_conv2_sum;
                layer2_2_conv2_sum = (ap_int<8>)0;
                layer2_2_conv2_rc12: for (ap_int<32> rc12 = 0; rc12 < 32; ++rc12) {
                  layer2_2_conv2_ry12: for (ap_int<32> ry12 = 0; ry12 < 3; ++ry12) {
                    layer2_2_conv2_rx12: for (ap_int<32> rx12 = 0; rx12 < 3; ++rx12) {
                      layer2_2_conv2_sum = ((ap_int<8>)(((ap_int<34>)(((((((ap_int<33>)1 - ((ap_int<33>)rx12)) <= ((ap_int<33>)(xx_reuse10 + -2))) && (((ap_int<33>)(xx_reuse10 + -2)) < ((ap_int<33>)17 - ((ap_int<33>)rx12)))) && (((ap_int<33>)1 - ((ap_int<33>)ry12)) <= ((ap_int<33>)(yy_reuse10 + -2)))) && (((ap_int<33>)(yy_reuse10 + -2)) < ((ap_int<33>)17 - ((ap_int<33>)ry12)))) ? ((ap_uint<32>)((((1U - ((ap_uint<32>)layer2_2_conv2_WB[0][rc12][ry12][rx12])) ^ w_layer2_2_conv2[ff12][rc12][ry12][rx12]) << 1) - 1U)) : ((ap_uint<32>)0U))) + ((ap_int<34>)layer2_2_conv2_sum)));
                    }
                  }
                }
                ap_int<8> layer2_2_conv2_temp;
                layer2_2_conv2_temp = layer2_2_conv2_sum;
                layer2_2_conv2_pipe_72[0][ff12][(yy_reuse10 + -2)][(xx_reuse10 + -2)] = layer2_2_conv2_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer2_2_bn2_pipe_73[1][32][16][16];
      #pragma HLS stream variable=layer2_2_bn2_pipe_73 depth=73
      layer2_2_bn2_args012: for (ap_int<32> args012 = 0; args012 < 32; ++args012) {
        layer2_2_bn2_args112: for (ap_int<32> args112 = 0; args112 < 16; ++args112) {
          layer2_2_bn2_args212: for (ap_int<32> args212 = 0; args212 < 16; ++args212) {
          #pragma HLS pipeline
            ap_int<8> layer2_2_conv2_temp1;
            layer2_2_conv2_temp1 = layer2_2_conv2_pipe_72[0][args012][args112][args212];
            ap_fixed<32, 20> layer2_2_bn2_temp;
            layer2_2_bn2_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer2_2_conv2_temp1) - w_layer2_2_bn2_16[args012]))) / sqrt((((float)w_layer2_2_bn2_17[args012]) + 1.000000e-07f))) * ((float)w_layer2_2_bn2_14[args012])) + ((float)w_layer2_2_bn2_15[args012])));
            layer2_2_bn2_pipe_73[0][args012][args112][args212] = layer2_2_bn2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_2_residual2_pipe_74[1][32][16][16];
      #pragma HLS stream variable=layer2_2_residual2_pipe_74 depth=74
      layer2_2_residual2_cc35: for (ap_int<32> cc35 = 0; cc35 < 32; ++cc35) {
        layer2_2_residual2_ww35: for (ap_int<32> ww35 = 0; ww35 < 16; ++ww35) {
          layer2_2_residual2_hh35: for (ap_int<32> hh35 = 0; hh35 < 16; ++hh35) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_2_bn2_temp1;
            layer2_2_bn2_temp1 = layer2_2_bn2_pipe_73[0][cc35][ww35][hh35];
            ap_fixed<32, 20> layer2_2_residual2_temp;
            ap_fixed<32, 20> layer2_2_rprelu1_temp2;
            layer2_2_rprelu1_temp2 = layer2_2_rprelu1_pipe_128[0][cc35][ww35][hh35];
            layer2_2_residual2_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer2_2_bn2_temp1) + ((ap_fixed<33, 21>)layer2_2_rprelu1_temp2)));
            layer2_2_residual2_pipe_74[0][cc35][ww35][hh35] = layer2_2_residual2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer2_2_rprelu2_pipe_75[1][32][16][16];
      #pragma HLS stream variable=layer2_2_rprelu2_pipe_75 depth=75
      ap_fixed<32, 20> layer2_2_rprelu2_pipe_129[1][32][16][16];
      #pragma HLS stream variable=layer2_2_rprelu2_pipe_129 depth=129
      layer2_2_rprelu2_cc36: for (ap_int<32> cc36 = 0; cc36 < 32; ++cc36) {
        layer2_2_rprelu2_ww36: for (ap_int<32> ww36 = 0; ww36 < 16; ++ww36) {
          layer2_2_rprelu2_hh36: for (ap_int<32> hh36 = 0; hh36 < 16; ++hh36) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_2_residual2_temp1;
            layer2_2_residual2_temp1 = layer2_2_residual2_pipe_74[0][cc36][ww36][hh36];
            ap_fixed<32, 20> layer2_2_rprelu2_temp;
            layer2_2_rprelu2_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_2_residual2_temp1) + ((ap_fixed<33, 21>)w_layer2_2_rprelu2_3[cc36])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer2_2_residual2_temp1) + ((ap_fixed<33, 21>)w_layer2_2_rprelu2_3[cc36])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer2_2_rprelu2_5[cc36]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer2_2_residual2_temp1) + ((ap_fixed<33, 21>)w_layer2_2_rprelu2_3[cc36]))))))) + ((ap_fixed<66, 42>)w_layer2_2_rprelu2_4[cc36])));
            layer2_2_rprelu2_pipe_129[0][cc36][ww36][hh36] = layer2_2_rprelu2_temp;
            layer2_2_rprelu2_pipe_75[0][cc36][ww36][hh36] = layer2_2_rprelu2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_0_avgpool_LB[2][16];
      ap_fixed<32, 20> layer3_0_avgpool_pipe_130[1][32][8][8];
      #pragma HLS stream variable=layer3_0_avgpool_pipe_130 depth=130
      layer3_0_avgpool_c1: for (ap_int<32> c1 = 0; c1 < 32; ++c1) {
        layer3_0_avgpool_h1: for (ap_int<32> h1 = 0; h1 < 8; ++h1) {
          layer3_0_avgpool_w1: for (ap_int<32> w1 = 0; w1 < 8; ++w1) {
            ap_fixed<32, 20> layer3_0_avgpool_val;
            layer3_0_avgpool_val = ((ap_fixed<32, 20>)0);
            layer3_0_avgpool_LB_i: for (ap_int<32> layer3_0_avgpool_LB_i = 0; layer3_0_avgpool_LB_i < 2; ++layer3_0_avgpool_LB_i) {
              layer3_0_avgpool_LB_j: for (ap_int<32> layer3_0_avgpool_LB_j = 0; layer3_0_avgpool_LB_j < 16; ++layer3_0_avgpool_LB_j) {
        #pragma HLS pipeline
                ap_fixed<32, 20> layer2_2_rprelu2_temp1;
                layer2_2_rprelu2_temp1 = layer2_2_rprelu2_pipe_129[0][c1][((h1 * 2) + layer3_0_avgpool_LB_i)][layer3_0_avgpool_LB_j];
                layer3_0_avgpool_LB[layer3_0_avgpool_LB_i][layer3_0_avgpool_LB_j] = layer2_2_rprelu2_temp1;
              }
            }
            layer3_0_avgpool_rr: for (ap_int<32> layer3_0_avgpool_rr = 0; layer3_0_avgpool_rr < 2; ++layer3_0_avgpool_rr) {
              layer3_0_avgpool_cc: for (ap_int<32> layer3_0_avgpool_cc = 0; layer3_0_avgpool_cc < 2; ++layer3_0_avgpool_cc) {
                layer3_0_avgpool_val = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer3_0_avgpool_val) + ((ap_fixed<33, 21>)layer3_0_avgpool_LB[layer3_0_avgpool_rr][((w1 * 2) + layer3_0_avgpool_cc)])));
              }
            }
            ap_fixed<32, 20> layer3_0_avgpool_temp;
            layer3_0_avgpool_temp = ((ap_fixed<32, 20>)(((ap_fixed<64, 20>)layer3_0_avgpool_val) / (ap_fixed<64, 20>)4));
            layer3_0_avgpool_pipe_130[0][c1][h1][w1] = layer3_0_avgpool_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_0_concat_pipe_131[1][64][8][8];
      #pragma HLS stream variable=layer3_0_concat_pipe_131 depth=131
      layer3_0_concat_cc37: for (ap_int<32> cc37 = 0; cc37 < 64; ++cc37) {
        layer3_0_concat_ww37: for (ap_int<32> ww37 = 0; ww37 < 8; ++ww37) {
          layer3_0_concat_hh37: for (ap_int<32> hh37 = 0; hh37 < 8; ++hh37) {
            ap_fixed<32, 20> layer3_0_avgpool_temp1;
            layer3_0_avgpool_temp1 = layer3_0_avgpool_pipe_130[(((cc37 % 32) - cc37) / 32)][cc37][ww37][hh37];
            ap_fixed<32, 20> layer3_0_concat_temp;
            layer3_0_concat_temp = layer3_0_avgpool_temp1;
            layer3_0_concat_pipe_131[0][cc37][ww37][hh37] = layer3_0_concat_temp;
          }
        }
      }
      ap_int<8> layer3_0_rsign1_pipe_76[1][32][16][16];
      #pragma HLS stream variable=layer3_0_rsign1_pipe_76 depth=76
      layer3_0_rsign1_cc38: for (ap_int<32> cc38 = 0; cc38 < 32; ++cc38) {
        layer3_0_rsign1_ww38: for (ap_int<32> ww38 = 0; ww38 < 16; ++ww38) {
          layer3_0_rsign1_hh38: for (ap_int<32> hh38 = 0; hh38 < 16; ++hh38) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer2_2_rprelu2_temp2;
            layer2_2_rprelu2_temp2 = layer2_2_rprelu2_pipe_75[0][cc38][ww38][hh38];
            ap_int<8> layer3_0_rsign1_temp;
            layer3_0_rsign1_temp = ((ap_int<8>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer2_2_rprelu2_temp2) + ((ap_fixed<33, 21>)w_layer3_0_rsign1[cc38])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer3_0_rsign1_pipe_76[0][cc38][ww38][hh38] = layer3_0_rsign1_temp;
          }
        }
      }
      ap_int<8> layer3_0_conv1_pad_pipe_77[1][32][18][18];
      #pragma HLS stream variable=layer3_0_conv1_pad_pipe_77 depth=77
      layer3_0_conv1_pad_not_zero13: for (ap_int<32> not_zero13 = 0; not_zero13 < 32; ++not_zero13) {
        layer3_0_conv1_pad_index_tuple13: for (ap_int<32> index_tuple13 = 0; index_tuple13 < 18; ++index_tuple13) {
          layer3_0_conv1_pad_i13: for (ap_int<32> i13 = 0; i13 < 18; ++i13) {
        #pragma HLS pipeline
            ap_int<8> layer3_0_rsign1_temp1;
            layer3_0_rsign1_temp1 = layer3_0_rsign1_pipe_76[0][not_zero13][(index_tuple13 + -1)][(i13 + -1)];
            ap_int<8> layer3_0_conv1_pad_temp;
            layer3_0_conv1_pad_temp = (((((1 <= index_tuple13) && (index_tuple13 < 17)) && (1 <= i13)) && (i13 < 17)) ? ((ap_int<8>)layer3_0_rsign1_temp1) : ((ap_int<8>)0));
            layer3_0_conv1_pad_pipe_77[0][not_zero13][index_tuple13][i13] = layer3_0_conv1_pad_temp;
          }
        }
      }
      ap_int<8> layer3_0_conv1_pipe_78[1][64][8][8];
      #pragma HLS stream variable=layer3_0_conv1_pipe_78 depth=78
      layer3_0_conv1_ff13: for (ap_int<32> ff13 = 0; ff13 < 64; ++ff13) {
        layer3_0_conv1_yy2: for (ap_int<32> yy2 = 0; yy2 < 8; ++yy2) {
          layer3_0_conv1_xx2: for (ap_int<32> xx2 = 0; xx2 < 8; ++xx2) {
            ap_int<8> layer3_0_conv1_sum;
            layer3_0_conv1_sum = (ap_int<8>)0;
            layer3_0_conv1_rc13: for (ap_int<32> rc13 = 0; rc13 < 32; ++rc13) {
              layer3_0_conv1_ry13: for (ap_int<32> ry13 = 0; ry13 < 3; ++ry13) {
                layer3_0_conv1_rx13: for (ap_int<32> rx13 = 0; rx13 < 3; ++rx13) {
                  ap_int<8> layer3_0_conv1_pad_temp1;
                  layer3_0_conv1_pad_temp1 = layer3_0_conv1_pad_pipe_77[0][rc13][((yy2 * 2) + ry13)][((xx2 * 2) + rx13)];
                  layer3_0_conv1_sum = ((ap_int<8>)(((ap_int<33>)(((((((ap_int<33>)1 - ((ap_int<33>)rx13)) <= ((ap_int<33>)xx2)) && (((ap_int<33>)xx2) < ((ap_int<33>)17 - ((ap_int<33>)rx13)))) && (((ap_int<33>)1 - ((ap_int<33>)ry13)) <= ((ap_int<33>)yy2))) && (((ap_int<33>)yy2) < ((ap_int<33>)17 - ((ap_int<33>)ry13)))) ? ((ap_int<32>)((((1 - ((ap_int<32>)layer3_0_conv1_pad_temp1)) ^ w_layer3_0_conv1[ff13][rc13][ry13][rx13]) << 1) + -1)) : ((ap_int<32>)0))) + ((ap_int<33>)layer3_0_conv1_sum)));
                }
              }
            }
            ap_int<8> layer3_0_conv1_temp;
            layer3_0_conv1_temp = layer3_0_conv1_sum;
            layer3_0_conv1_pipe_78[0][ff13][yy2][xx2] = layer3_0_conv1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_0_bn1_pipe_79[1][64][8][8];
      #pragma HLS stream variable=layer3_0_bn1_pipe_79 depth=79
      layer3_0_bn1_args013: for (ap_int<32> args013 = 0; args013 < 64; ++args013) {
        layer3_0_bn1_args113: for (ap_int<32> args113 = 0; args113 < 8; ++args113) {
          layer3_0_bn1_args213: for (ap_int<32> args213 = 0; args213 < 8; ++args213) {
          #pragma HLS pipeline
            ap_int<8> layer3_0_conv1_temp1;
            layer3_0_conv1_temp1 = layer3_0_conv1_pipe_78[0][args013][args113][args213];
            ap_fixed<32, 20> layer3_0_bn1_temp;
            layer3_0_bn1_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer3_0_conv1_temp1) - w_layer3_0_bn1_11[args013]))) / sqrt((((float)w_layer3_0_bn1_12[args013]) + 1.000000e-07f))) * ((float)w_layer3_0_bn1_9[args013])) + ((float)w_layer3_0_bn1_10[args013])));
            layer3_0_bn1_pipe_79[0][args013][args113][args213] = layer3_0_bn1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_0_residual1_pipe_80[1][64][8][8];
      #pragma HLS stream variable=layer3_0_residual1_pipe_80 depth=80
      layer3_0_residual1_cc39: for (ap_int<32> cc39 = 0; cc39 < 64; ++cc39) {
        layer3_0_residual1_ww39: for (ap_int<32> ww39 = 0; ww39 < 8; ++ww39) {
          layer3_0_residual1_hh39: for (ap_int<32> hh39 = 0; hh39 < 8; ++hh39) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_0_bn1_temp1;
            layer3_0_bn1_temp1 = layer3_0_bn1_pipe_79[0][cc39][ww39][hh39];
            ap_fixed<32, 20> layer3_0_residual1_temp;
            ap_fixed<32, 20> layer3_0_concat_temp1;
            layer3_0_concat_temp1 = layer3_0_concat_pipe_131[0][cc39][ww39][hh39];
            layer3_0_residual1_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer3_0_bn1_temp1) + ((ap_fixed<33, 21>)layer3_0_concat_temp1)));
            layer3_0_residual1_pipe_80[0][cc39][ww39][hh39] = layer3_0_residual1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_0_rprelu1_pipe_81[1][64][8][8];
      #pragma HLS stream variable=layer3_0_rprelu1_pipe_81 depth=81
      ap_fixed<32, 20> layer3_0_rprelu1_pipe_132[1][64][8][8];
      #pragma HLS stream variable=layer3_0_rprelu1_pipe_132 depth=132
      layer3_0_rprelu1_cc40: for (ap_int<32> cc40 = 0; cc40 < 64; ++cc40) {
        layer3_0_rprelu1_ww40: for (ap_int<32> ww40 = 0; ww40 < 8; ++ww40) {
          layer3_0_rprelu1_hh40: for (ap_int<32> hh40 = 0; hh40 < 8; ++hh40) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_0_residual1_temp1;
            layer3_0_residual1_temp1 = layer3_0_residual1_pipe_80[0][cc40][ww40][hh40];
            ap_fixed<32, 20> layer3_0_rprelu1_temp;
            layer3_0_rprelu1_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer3_0_residual1_temp1) + ((ap_fixed<33, 21>)w_layer3_0_rprelu1_0[cc40])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer3_0_residual1_temp1) + ((ap_fixed<33, 21>)w_layer3_0_rprelu1_0[cc40])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer3_0_rprelu1_2[cc40]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer3_0_residual1_temp1) + ((ap_fixed<33, 21>)w_layer3_0_rprelu1_0[cc40]))))))) + ((ap_fixed<66, 42>)w_layer3_0_rprelu1_1[cc40])));
            layer3_0_rprelu1_pipe_132[0][cc40][ww40][hh40] = layer3_0_rprelu1_temp;
            layer3_0_rprelu1_pipe_81[0][cc40][ww40][hh40] = layer3_0_rprelu1_temp;
          }
        }
      }
      ap_uint<1> layer3_0_rsign2_pipe_82[1][64][8][8];
      #pragma HLS stream variable=layer3_0_rsign2_pipe_82 depth=82
      layer3_0_rsign2_cc41: for (ap_int<32> cc41 = 0; cc41 < 64; ++cc41) {
        layer3_0_rsign2_ww41: for (ap_int<32> ww41 = 0; ww41 < 8; ++ww41) {
          layer3_0_rsign2_hh41: for (ap_int<32> hh41 = 0; hh41 < 8; ++hh41) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_0_rprelu1_temp1;
            layer3_0_rprelu1_temp1 = layer3_0_rprelu1_pipe_81[0][cc41][ww41][hh41];
            ap_uint<1> layer3_0_rsign2_temp;
            layer3_0_rsign2_temp = ((ap_uint<1>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer3_0_rprelu1_temp1) + ((ap_fixed<33, 21>)w_layer3_0_rsign2[cc41])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer3_0_rsign2_pipe_82[0][cc41][ww41][hh41] = layer3_0_rsign2_temp;
          }
        }
      }
      ap_uint<1> layer3_0_conv2_pad_pipe_83[1][64][10][10];
      #pragma HLS stream variable=layer3_0_conv2_pad_pipe_83 depth=83
      layer3_0_conv2_pad_not_zero14: for (ap_int<32> not_zero14 = 0; not_zero14 < 64; ++not_zero14) {
        layer3_0_conv2_pad_index_tuple14: for (ap_int<32> index_tuple14 = 0; index_tuple14 < 10; ++index_tuple14) {
          layer3_0_conv2_pad_i14: for (ap_int<32> i14 = 0; i14 < 10; ++i14) {
        #pragma HLS pipeline
            ap_uint<1> layer3_0_rsign2_temp1;
            layer3_0_rsign2_temp1 = layer3_0_rsign2_pipe_82[0][not_zero14][(index_tuple14 + -1)][(i14 + -1)];
            ap_uint<1> layer3_0_conv2_pad_temp;
            layer3_0_conv2_pad_temp = (((((1 <= index_tuple14) && (index_tuple14 < 9)) && (1 <= i14)) && (i14 < 9)) ? ((ap_uint<1>)layer3_0_rsign2_temp1) : ((ap_uint<1>)0));
            layer3_0_conv2_pad_pipe_83[0][not_zero14][index_tuple14][i14] = layer3_0_conv2_pad_temp;
          }
        }
      }
      ap_int<8> layer3_0_conv2_pipe_84[1][64][8][8];
      #pragma HLS stream variable=layer3_0_conv2_pipe_84 depth=84
      layer3_0_conv2_ff14: for (ap_int<32> ff14 = 0; ff14 < 64; ++ff14) {
        layer3_0_conv2_yy3: for (ap_int<32> yy3 = 0; yy3 < 8; ++yy3) {
          layer3_0_conv2_xx3: for (ap_int<32> xx3 = 0; xx3 < 8; ++xx3) {
            ap_int<8> layer3_0_conv2_sum;
            layer3_0_conv2_sum = (ap_int<8>)0;
            layer3_0_conv2_rc14: for (ap_int<32> rc14 = 0; rc14 < 64; ++rc14) {
              layer3_0_conv2_ry14: for (ap_int<32> ry14 = 0; ry14 < 3; ++ry14) {
                layer3_0_conv2_rx14: for (ap_int<32> rx14 = 0; rx14 < 3; ++rx14) {
        #pragma HLS pipeline
                  ap_uint<1> layer3_0_conv2_pad_temp1;
                  layer3_0_conv2_pad_temp1 = layer3_0_conv2_pad_pipe_83[0][rc14][(yy3 + ry14)][(xx3 + rx14)];
                  layer3_0_conv2_sum = ((ap_int<8>)(((ap_int<34>)(((((((ap_int<33>)1 - ((ap_int<33>)rx14)) <= ((ap_int<33>)xx3)) && (((ap_int<33>)xx3) < ((ap_int<33>)9 - ((ap_int<33>)rx14)))) && (((ap_int<33>)1 - ((ap_int<33>)ry14)) <= ((ap_int<33>)yy3))) && (((ap_int<33>)yy3) < ((ap_int<33>)9 - ((ap_int<33>)ry14)))) ? ((ap_uint<32>)((((1U - ((ap_uint<32>)layer3_0_conv2_pad_temp1)) ^ w_layer3_0_conv2[ff14][rc14][ry14][rx14]) << 1) - 1U)) : ((ap_uint<32>)0U))) + ((ap_int<34>)layer3_0_conv2_sum)));
                }
              }
            }
            ap_int<8> layer3_0_conv2_temp;
            layer3_0_conv2_temp = layer3_0_conv2_sum;
            layer3_0_conv2_pipe_84[0][ff14][yy3][xx3] = layer3_0_conv2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_0_bn2_pipe_85[1][64][8][8];
      #pragma HLS stream variable=layer3_0_bn2_pipe_85 depth=85
      layer3_0_bn2_args014: for (ap_int<32> args014 = 0; args014 < 64; ++args014) {
        layer3_0_bn2_args114: for (ap_int<32> args114 = 0; args114 < 8; ++args114) {
          layer3_0_bn2_args214: for (ap_int<32> args214 = 0; args214 < 8; ++args214) {
          #pragma HLS pipeline
            ap_int<8> layer3_0_conv2_temp1;
            layer3_0_conv2_temp1 = layer3_0_conv2_pipe_84[0][args014][args114][args214];
            ap_fixed<32, 20> layer3_0_bn2_temp;
            layer3_0_bn2_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer3_0_conv2_temp1) - w_layer3_0_bn2_16[args014]))) / sqrt((((float)w_layer3_0_bn2_17[args014]) + 1.000000e-07f))) * ((float)w_layer3_0_bn2_14[args014])) + ((float)w_layer3_0_bn2_15[args014])));
            layer3_0_bn2_pipe_85[0][args014][args114][args214] = layer3_0_bn2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_0_residual2_pipe_86[1][64][8][8];
      #pragma HLS stream variable=layer3_0_residual2_pipe_86 depth=86
      layer3_0_residual2_cc42: for (ap_int<32> cc42 = 0; cc42 < 64; ++cc42) {
        layer3_0_residual2_ww42: for (ap_int<32> ww42 = 0; ww42 < 8; ++ww42) {
          layer3_0_residual2_hh42: for (ap_int<32> hh42 = 0; hh42 < 8; ++hh42) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_0_bn2_temp1;
            layer3_0_bn2_temp1 = layer3_0_bn2_pipe_85[0][cc42][ww42][hh42];
            ap_fixed<32, 20> layer3_0_residual2_temp;
            ap_fixed<32, 20> layer3_0_rprelu1_temp2;
            layer3_0_rprelu1_temp2 = layer3_0_rprelu1_pipe_132[0][cc42][ww42][hh42];
            layer3_0_residual2_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer3_0_bn2_temp1) + ((ap_fixed<33, 21>)layer3_0_rprelu1_temp2)));
            layer3_0_residual2_pipe_86[0][cc42][ww42][hh42] = layer3_0_residual2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_0_rprelu2_pipe_87[1][64][8][8];
      #pragma HLS stream variable=layer3_0_rprelu2_pipe_87 depth=87
      ap_fixed<32, 20> layer3_0_rprelu2_pipe_133[1][64][8][8];
      #pragma HLS stream variable=layer3_0_rprelu2_pipe_133 depth=133
      layer3_0_rprelu2_cc43: for (ap_int<32> cc43 = 0; cc43 < 64; ++cc43) {
        layer3_0_rprelu2_ww43: for (ap_int<32> ww43 = 0; ww43 < 8; ++ww43) {
          layer3_0_rprelu2_hh43: for (ap_int<32> hh43 = 0; hh43 < 8; ++hh43) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_0_residual2_temp1;
            layer3_0_residual2_temp1 = layer3_0_residual2_pipe_86[0][cc43][ww43][hh43];
            ap_fixed<32, 20> layer3_0_rprelu2_temp;
            layer3_0_rprelu2_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer3_0_residual2_temp1) + ((ap_fixed<33, 21>)w_layer3_0_rprelu2_3[cc43])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer3_0_residual2_temp1) + ((ap_fixed<33, 21>)w_layer3_0_rprelu2_3[cc43])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer3_0_rprelu2_5[cc43]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer3_0_residual2_temp1) + ((ap_fixed<33, 21>)w_layer3_0_rprelu2_3[cc43]))))))) + ((ap_fixed<66, 42>)w_layer3_0_rprelu2_4[cc43])));
            layer3_0_rprelu2_pipe_133[0][cc43][ww43][hh43] = layer3_0_rprelu2_temp;
            layer3_0_rprelu2_pipe_87[0][cc43][ww43][hh43] = layer3_0_rprelu2_temp;
          }
        }
      }
      ap_int<8> layer3_1_rsign1_pipe_88[1][64][8][8];
      #pragma HLS stream variable=layer3_1_rsign1_pipe_88 depth=88
      layer3_1_rsign1_cc44: for (ap_int<32> cc44 = 0; cc44 < 64; ++cc44) {
        layer3_1_rsign1_ww44: for (ap_int<32> ww44 = 0; ww44 < 8; ++ww44) {
          layer3_1_rsign1_hh44: for (ap_int<32> hh44 = 0; hh44 < 8; ++hh44) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_0_rprelu2_temp1;
            layer3_0_rprelu2_temp1 = layer3_0_rprelu2_pipe_87[0][cc44][ww44][hh44];
            ap_int<8> layer3_1_rsign1_temp;
            layer3_1_rsign1_temp = ((ap_int<8>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer3_0_rprelu2_temp1) + ((ap_fixed<33, 21>)w_layer3_1_rsign1[cc44])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer3_1_rsign1_pipe_88[0][cc44][ww44][hh44] = layer3_1_rsign1_temp;
          }
        }
      }
      ap_int<8> layer3_1_conv1_pad[1][64][10][10];
      ap_int<8> layer3_1_conv1_pad_pipe_89[1][64][10][10];
      #pragma HLS stream variable=layer3_1_conv1_pad_pipe_89 depth=89
      layer3_1_conv1_pad_not_zero15: for (ap_int<32> not_zero15 = 0; not_zero15 < 64; ++not_zero15) {
        layer3_1_conv1_pad_index_tuple15: for (ap_int<32> index_tuple15 = 0; index_tuple15 < 10; ++index_tuple15) {
          layer3_1_conv1_pad_i15: for (ap_int<32> i15 = 0; i15 < 10; ++i15) {
        #pragma HLS pipeline
            ap_int<8> layer3_1_rsign1_temp1;
            layer3_1_rsign1_temp1 = layer3_1_rsign1_pipe_88[0][not_zero15][(index_tuple15 + -1)][(i15 + -1)];
            ap_int<8> layer3_1_conv1_pad_temp;
            layer3_1_conv1_pad_temp = (((((1 <= index_tuple15) && (index_tuple15 < 9)) && (1 <= i15)) && (i15 < 9)) ? ((ap_int<8>)layer3_1_rsign1_temp1) : ((ap_int<8>)0));
            layer3_1_conv1_pad_pipe_89[0][not_zero15][index_tuple15][i15] = layer3_1_conv1_pad_temp;
            layer3_1_conv1_pad[0][not_zero15][index_tuple15][i15] = layer3_1_conv1_pad_temp;
          }
        }
      }
      ap_int<8> layer3_1_conv1_LB[1][64][3][10];
      #pragma HLS array_partition variable=layer3_1_conv1_LB dim=3 complete
      ap_int<8> layer3_1_conv1_WB[1][64][3][3];
      #pragma HLS array_partition variable=layer3_1_conv1_WB dim=3 complete
      #pragma HLS array_partition variable=layer3_1_conv1_WB dim=4 complete
      ap_int<8> layer3_1_conv1_pipe_90[1][64][8][8];
      #pragma HLS stream variable=layer3_1_conv1_pipe_90 depth=90
      layer3_1_conv1_ff15: for (ap_int<32> ff15 = 0; ff15 < 64; ++ff15) {
        layer3_1_conv1_yy_reuse11: for (ap_int<32> yy_reuse11 = 0; yy_reuse11 < 10; ++yy_reuse11) {
          layer3_1_conv1_xx_reuse11: for (ap_int<32> xx_reuse11 = 0; xx_reuse11 < 10; ++xx_reuse11) {
            layer3_1_conv1_pad_2: for (ap_int<32> layer3_1_conv1_pad_2 = 0; layer3_1_conv1_pad_2 < 64; ++layer3_1_conv1_pad_2) {
          #pragma HLS pipeline
              layer3_1_conv1_pad_1: for (ap_int<32> layer3_1_conv1_pad_1 = 0; layer3_1_conv1_pad_1 < 2; ++layer3_1_conv1_pad_1) {
                layer3_1_conv1_LB[0][layer3_1_conv1_pad_2][layer3_1_conv1_pad_1][xx_reuse11] = layer3_1_conv1_LB[0][layer3_1_conv1_pad_2][(layer3_1_conv1_pad_1 + 1)][xx_reuse11];
              }
              ap_int<8> layer3_1_conv1_pad_temp1;
              layer3_1_conv1_pad_temp1 = layer3_1_conv1_pad_pipe_89[0][layer3_1_conv1_pad_2][yy_reuse11][xx_reuse11];
              layer3_1_conv1_LB[0][layer3_1_conv1_pad_2][2][xx_reuse11] = layer3_1_conv1_pad_temp1;
            }
            if (2 <= yy_reuse11) {
              layer3_1_conv1_LB_1: for (ap_int<32> layer3_1_conv1_LB_1 = 0; layer3_1_conv1_LB_1 < 3; ++layer3_1_conv1_LB_1) {
                layer3_1_conv1_LB_2: for (ap_int<32> layer3_1_conv1_LB_2 = 0; layer3_1_conv1_LB_2 < 64; ++layer3_1_conv1_LB_2) {
                  layer3_1_conv1_LB_0: for (ap_int<32> layer3_1_conv1_LB_0 = 0; layer3_1_conv1_LB_0 < 2; ++layer3_1_conv1_LB_0) {
                    layer3_1_conv1_WB[0][layer3_1_conv1_LB_2][layer3_1_conv1_LB_1][layer3_1_conv1_LB_0] = layer3_1_conv1_WB[0][layer3_1_conv1_LB_2][layer3_1_conv1_LB_1][(layer3_1_conv1_LB_0 + 1)];
                  }
                  layer3_1_conv1_WB[0][layer3_1_conv1_LB_2][layer3_1_conv1_LB_1][2] = layer3_1_conv1_LB[0][layer3_1_conv1_LB_2][layer3_1_conv1_LB_1][xx_reuse11];
                }
              }
              if (2 <= xx_reuse11) {
                ap_int<8> layer3_1_conv1_sum;
                layer3_1_conv1_sum = (ap_int<8>)0;
                layer3_1_conv1_rc15: for (ap_int<32> rc15 = 0; rc15 < 64; ++rc15) {
                  layer3_1_conv1_ry15: for (ap_int<32> ry15 = 0; ry15 < 3; ++ry15) {
                    layer3_1_conv1_rx15: for (ap_int<32> rx15 = 0; rx15 < 3; ++rx15) {
                      layer3_1_conv1_sum = ((ap_int<8>)(((ap_int<33>)(((((((ap_int<33>)1 - ((ap_int<33>)rx15)) <= ((ap_int<33>)(xx_reuse11 + -2))) && (((ap_int<33>)(xx_reuse11 + -2)) < ((ap_int<33>)9 - ((ap_int<33>)rx15)))) && (((ap_int<33>)1 - ((ap_int<33>)ry15)) <= ((ap_int<33>)(yy_reuse11 + -2)))) && (((ap_int<33>)(yy_reuse11 + -2)) < ((ap_int<33>)9 - ((ap_int<33>)ry15)))) ? ((ap_int<32>)((((1 - ((ap_int<32>)layer3_1_conv1_WB[0][rc15][ry15][rx15])) ^ w_layer3_1_conv1[ff15][rc15][ry15][rx15]) << 1) + -1)) : ((ap_int<32>)0))) + ((ap_int<33>)layer3_1_conv1_sum)));
                    }
                  }
                }
                ap_int<8> layer3_1_conv1_temp;
                layer3_1_conv1_temp = layer3_1_conv1_sum;
                layer3_1_conv1_pipe_90[0][ff15][(yy_reuse11 + -2)][(xx_reuse11 + -2)] = layer3_1_conv1_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer3_1_bn1_pipe_91[1][64][8][8];
      #pragma HLS stream variable=layer3_1_bn1_pipe_91 depth=91
      layer3_1_bn1_args015: for (ap_int<32> args015 = 0; args015 < 64; ++args015) {
        layer3_1_bn1_args115: for (ap_int<32> args115 = 0; args115 < 8; ++args115) {
          layer3_1_bn1_args215: for (ap_int<32> args215 = 0; args215 < 8; ++args215) {
          #pragma HLS pipeline
            ap_int<8> layer3_1_conv1_temp1;
            layer3_1_conv1_temp1 = layer3_1_conv1_pipe_90[0][args015][args115][args215];
            ap_fixed<32, 20> layer3_1_bn1_temp;
            layer3_1_bn1_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer3_1_conv1_temp1) - w_layer3_1_bn1_11[args015]))) / sqrt((((float)w_layer3_1_bn1_12[args015]) + 1.000000e-07f))) * ((float)w_layer3_1_bn1_9[args015])) + ((float)w_layer3_1_bn1_10[args015])));
            layer3_1_bn1_pipe_91[0][args015][args115][args215] = layer3_1_bn1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_1_residual1_pipe_92[1][64][8][8];
      #pragma HLS stream variable=layer3_1_residual1_pipe_92 depth=92
      layer3_1_residual1_cc45: for (ap_int<32> cc45 = 0; cc45 < 64; ++cc45) {
        layer3_1_residual1_ww45: for (ap_int<32> ww45 = 0; ww45 < 8; ++ww45) {
          layer3_1_residual1_hh45: for (ap_int<32> hh45 = 0; hh45 < 8; ++hh45) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_1_bn1_temp1;
            layer3_1_bn1_temp1 = layer3_1_bn1_pipe_91[0][cc45][ww45][hh45];
            ap_fixed<32, 20> layer3_1_residual1_temp;
            ap_fixed<32, 20> layer3_0_rprelu2_temp2;
            layer3_0_rprelu2_temp2 = layer3_0_rprelu2_pipe_133[0][cc45][ww45][hh45];
            layer3_1_residual1_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer3_1_bn1_temp1) + ((ap_fixed<33, 21>)layer3_0_rprelu2_temp2)));
            layer3_1_residual1_pipe_92[0][cc45][ww45][hh45] = layer3_1_residual1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_1_rprelu1_pipe_93[1][64][8][8];
      #pragma HLS stream variable=layer3_1_rprelu1_pipe_93 depth=93
      ap_fixed<32, 20> layer3_1_rprelu1_pipe_134[1][64][8][8];
      #pragma HLS stream variable=layer3_1_rprelu1_pipe_134 depth=134
      layer3_1_rprelu1_cc46: for (ap_int<32> cc46 = 0; cc46 < 64; ++cc46) {
        layer3_1_rprelu1_ww46: for (ap_int<32> ww46 = 0; ww46 < 8; ++ww46) {
          layer3_1_rprelu1_hh46: for (ap_int<32> hh46 = 0; hh46 < 8; ++hh46) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_1_residual1_temp1;
            layer3_1_residual1_temp1 = layer3_1_residual1_pipe_92[0][cc46][ww46][hh46];
            ap_fixed<32, 20> layer3_1_rprelu1_temp;
            layer3_1_rprelu1_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer3_1_residual1_temp1) + ((ap_fixed<33, 21>)w_layer3_1_rprelu1_0[cc46])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer3_1_residual1_temp1) + ((ap_fixed<33, 21>)w_layer3_1_rprelu1_0[cc46])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer3_1_rprelu1_2[cc46]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer3_1_residual1_temp1) + ((ap_fixed<33, 21>)w_layer3_1_rprelu1_0[cc46]))))))) + ((ap_fixed<66, 42>)w_layer3_1_rprelu1_1[cc46])));
            layer3_1_rprelu1_pipe_134[0][cc46][ww46][hh46] = layer3_1_rprelu1_temp;
            layer3_1_rprelu1_pipe_93[0][cc46][ww46][hh46] = layer3_1_rprelu1_temp;
          }
        }
      }
      ap_uint<1> layer3_1_rsign2_pipe_94[1][64][8][8];
      #pragma HLS stream variable=layer3_1_rsign2_pipe_94 depth=94
      layer3_1_rsign2_cc47: for (ap_int<32> cc47 = 0; cc47 < 64; ++cc47) {
        layer3_1_rsign2_ww47: for (ap_int<32> ww47 = 0; ww47 < 8; ++ww47) {
          layer3_1_rsign2_hh47: for (ap_int<32> hh47 = 0; hh47 < 8; ++hh47) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_1_rprelu1_temp1;
            layer3_1_rprelu1_temp1 = layer3_1_rprelu1_pipe_93[0][cc47][ww47][hh47];
            ap_uint<1> layer3_1_rsign2_temp;
            layer3_1_rsign2_temp = ((ap_uint<1>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer3_1_rprelu1_temp1) + ((ap_fixed<33, 21>)w_layer3_1_rsign2[cc47])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer3_1_rsign2_pipe_94[0][cc47][ww47][hh47] = layer3_1_rsign2_temp;
          }
        }
      }
      ap_uint<1> layer3_1_conv2_pad[1][64][10][10];
      ap_uint<1> layer3_1_conv2_pad_pipe_95[1][64][10][10];
      #pragma HLS stream variable=layer3_1_conv2_pad_pipe_95 depth=95
      layer3_1_conv2_pad_not_zero16: for (ap_int<32> not_zero16 = 0; not_zero16 < 64; ++not_zero16) {
        layer3_1_conv2_pad_index_tuple16: for (ap_int<32> index_tuple16 = 0; index_tuple16 < 10; ++index_tuple16) {
          layer3_1_conv2_pad_i16: for (ap_int<32> i16 = 0; i16 < 10; ++i16) {
        #pragma HLS pipeline
            ap_uint<1> layer3_1_rsign2_temp1;
            layer3_1_rsign2_temp1 = layer3_1_rsign2_pipe_94[0][not_zero16][(index_tuple16 + -1)][(i16 + -1)];
            ap_uint<1> layer3_1_conv2_pad_temp;
            layer3_1_conv2_pad_temp = (((((1 <= index_tuple16) && (index_tuple16 < 9)) && (1 <= i16)) && (i16 < 9)) ? ((ap_uint<1>)layer3_1_rsign2_temp1) : ((ap_uint<1>)0));
            layer3_1_conv2_pad_pipe_95[0][not_zero16][index_tuple16][i16] = layer3_1_conv2_pad_temp;
            layer3_1_conv2_pad[0][not_zero16][index_tuple16][i16] = layer3_1_conv2_pad_temp;
          }
        }
      }
      ap_uint<1> layer3_1_conv2_LB[1][64][3][10];
      #pragma HLS array_partition variable=layer3_1_conv2_LB dim=3 complete
      ap_uint<1> layer3_1_conv2_WB[1][64][3][3];
      #pragma HLS array_partition variable=layer3_1_conv2_WB dim=3 complete
      #pragma HLS array_partition variable=layer3_1_conv2_WB dim=4 complete
      ap_int<8> layer3_1_conv2_pipe_96[1][64][8][8];
      #pragma HLS stream variable=layer3_1_conv2_pipe_96 depth=96
      layer3_1_conv2_ff16: for (ap_int<32> ff16 = 0; ff16 < 64; ++ff16) {
        layer3_1_conv2_yy_reuse12: for (ap_int<32> yy_reuse12 = 0; yy_reuse12 < 10; ++yy_reuse12) {
          layer3_1_conv2_xx_reuse12: for (ap_int<32> xx_reuse12 = 0; xx_reuse12 < 10; ++xx_reuse12) {
            layer3_1_conv2_pad_2: for (ap_int<32> layer3_1_conv2_pad_2 = 0; layer3_1_conv2_pad_2 < 64; ++layer3_1_conv2_pad_2) {
          #pragma HLS pipeline
              layer3_1_conv2_pad_1: for (ap_int<32> layer3_1_conv2_pad_1 = 0; layer3_1_conv2_pad_1 < 2; ++layer3_1_conv2_pad_1) {
                layer3_1_conv2_LB[0][layer3_1_conv2_pad_2][layer3_1_conv2_pad_1][xx_reuse12] = layer3_1_conv2_LB[0][layer3_1_conv2_pad_2][(layer3_1_conv2_pad_1 + 1)][xx_reuse12];
              }
              ap_uint<1> layer3_1_conv2_pad_temp1;
              layer3_1_conv2_pad_temp1 = layer3_1_conv2_pad_pipe_95[0][layer3_1_conv2_pad_2][yy_reuse12][xx_reuse12];
              layer3_1_conv2_LB[0][layer3_1_conv2_pad_2][2][xx_reuse12] = layer3_1_conv2_pad_temp1;
            }
            if (2 <= yy_reuse12) {
              layer3_1_conv2_LB_1: for (ap_int<32> layer3_1_conv2_LB_1 = 0; layer3_1_conv2_LB_1 < 3; ++layer3_1_conv2_LB_1) {
                layer3_1_conv2_LB_2: for (ap_int<32> layer3_1_conv2_LB_2 = 0; layer3_1_conv2_LB_2 < 64; ++layer3_1_conv2_LB_2) {
                  layer3_1_conv2_LB_0: for (ap_int<32> layer3_1_conv2_LB_0 = 0; layer3_1_conv2_LB_0 < 2; ++layer3_1_conv2_LB_0) {
                    layer3_1_conv2_WB[0][layer3_1_conv2_LB_2][layer3_1_conv2_LB_1][layer3_1_conv2_LB_0] = layer3_1_conv2_WB[0][layer3_1_conv2_LB_2][layer3_1_conv2_LB_1][(layer3_1_conv2_LB_0 + 1)];
                  }
                  layer3_1_conv2_WB[0][layer3_1_conv2_LB_2][layer3_1_conv2_LB_1][2] = layer3_1_conv2_LB[0][layer3_1_conv2_LB_2][layer3_1_conv2_LB_1][xx_reuse12];
                }
              }
              if (2 <= xx_reuse12) {
                ap_int<8> layer3_1_conv2_sum;
                layer3_1_conv2_sum = (ap_int<8>)0;
                layer3_1_conv2_rc16: for (ap_int<32> rc16 = 0; rc16 < 64; ++rc16) {
                  layer3_1_conv2_ry16: for (ap_int<32> ry16 = 0; ry16 < 3; ++ry16) {
                    layer3_1_conv2_rx16: for (ap_int<32> rx16 = 0; rx16 < 3; ++rx16) {
                      layer3_1_conv2_sum = ((ap_int<8>)(((ap_int<34>)(((((((ap_int<33>)1 - ((ap_int<33>)rx16)) <= ((ap_int<33>)(xx_reuse12 + -2))) && (((ap_int<33>)(xx_reuse12 + -2)) < ((ap_int<33>)9 - ((ap_int<33>)rx16)))) && (((ap_int<33>)1 - ((ap_int<33>)ry16)) <= ((ap_int<33>)(yy_reuse12 + -2)))) && (((ap_int<33>)(yy_reuse12 + -2)) < ((ap_int<33>)9 - ((ap_int<33>)ry16)))) ? ((ap_uint<32>)((((1U - ((ap_uint<32>)layer3_1_conv2_WB[0][rc16][ry16][rx16])) ^ w_layer3_1_conv2[ff16][rc16][ry16][rx16]) << 1) - 1U)) : ((ap_uint<32>)0U))) + ((ap_int<34>)layer3_1_conv2_sum)));
                    }
                  }
                }
                ap_int<8> layer3_1_conv2_temp;
                layer3_1_conv2_temp = layer3_1_conv2_sum;
                layer3_1_conv2_pipe_96[0][ff16][(yy_reuse12 + -2)][(xx_reuse12 + -2)] = layer3_1_conv2_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer3_1_bn2_pipe_97[1][64][8][8];
      #pragma HLS stream variable=layer3_1_bn2_pipe_97 depth=97
      layer3_1_bn2_args016: for (ap_int<32> args016 = 0; args016 < 64; ++args016) {
        layer3_1_bn2_args116: for (ap_int<32> args116 = 0; args116 < 8; ++args116) {
          layer3_1_bn2_args216: for (ap_int<32> args216 = 0; args216 < 8; ++args216) {
          #pragma HLS pipeline
            ap_int<8> layer3_1_conv2_temp1;
            layer3_1_conv2_temp1 = layer3_1_conv2_pipe_96[0][args016][args116][args216];
            ap_fixed<32, 20> layer3_1_bn2_temp;
            layer3_1_bn2_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer3_1_conv2_temp1) - w_layer3_1_bn2_16[args016]))) / sqrt((((float)w_layer3_1_bn2_17[args016]) + 1.000000e-07f))) * ((float)w_layer3_1_bn2_14[args016])) + ((float)w_layer3_1_bn2_15[args016])));
            layer3_1_bn2_pipe_97[0][args016][args116][args216] = layer3_1_bn2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_1_residual2_pipe_98[1][64][8][8];
      #pragma HLS stream variable=layer3_1_residual2_pipe_98 depth=98
      layer3_1_residual2_cc48: for (ap_int<32> cc48 = 0; cc48 < 64; ++cc48) {
        layer3_1_residual2_ww48: for (ap_int<32> ww48 = 0; ww48 < 8; ++ww48) {
          layer3_1_residual2_hh48: for (ap_int<32> hh48 = 0; hh48 < 8; ++hh48) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_1_bn2_temp1;
            layer3_1_bn2_temp1 = layer3_1_bn2_pipe_97[0][cc48][ww48][hh48];
            ap_fixed<32, 20> layer3_1_residual2_temp;
            ap_fixed<32, 20> layer3_1_rprelu1_temp2;
            layer3_1_rprelu1_temp2 = layer3_1_rprelu1_pipe_134[0][cc48][ww48][hh48];
            layer3_1_residual2_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer3_1_bn2_temp1) + ((ap_fixed<33, 21>)layer3_1_rprelu1_temp2)));
            layer3_1_residual2_pipe_98[0][cc48][ww48][hh48] = layer3_1_residual2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_1_rprelu2_pipe_99[1][64][8][8];
      #pragma HLS stream variable=layer3_1_rprelu2_pipe_99 depth=99
      ap_fixed<32, 20> layer3_1_rprelu2_pipe_135[1][64][8][8];
      #pragma HLS stream variable=layer3_1_rprelu2_pipe_135 depth=135
      layer3_1_rprelu2_cc49: for (ap_int<32> cc49 = 0; cc49 < 64; ++cc49) {
        layer3_1_rprelu2_ww49: for (ap_int<32> ww49 = 0; ww49 < 8; ++ww49) {
          layer3_1_rprelu2_hh49: for (ap_int<32> hh49 = 0; hh49 < 8; ++hh49) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_1_residual2_temp1;
            layer3_1_residual2_temp1 = layer3_1_residual2_pipe_98[0][cc49][ww49][hh49];
            ap_fixed<32, 20> layer3_1_rprelu2_temp;
            layer3_1_rprelu2_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer3_1_residual2_temp1) + ((ap_fixed<33, 21>)w_layer3_1_rprelu2_3[cc49])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer3_1_residual2_temp1) + ((ap_fixed<33, 21>)w_layer3_1_rprelu2_3[cc49])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer3_1_rprelu2_5[cc49]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer3_1_residual2_temp1) + ((ap_fixed<33, 21>)w_layer3_1_rprelu2_3[cc49]))))))) + ((ap_fixed<66, 42>)w_layer3_1_rprelu2_4[cc49])));
            layer3_1_rprelu2_pipe_135[0][cc49][ww49][hh49] = layer3_1_rprelu2_temp;
            layer3_1_rprelu2_pipe_99[0][cc49][ww49][hh49] = layer3_1_rprelu2_temp;
          }
        }
      }
      ap_int<8> layer3_2_rsign1_pipe_100[1][64][8][8];
      #pragma HLS stream variable=layer3_2_rsign1_pipe_100 depth=100
      layer3_2_rsign1_cc50: for (ap_int<32> cc50 = 0; cc50 < 64; ++cc50) {
        layer3_2_rsign1_ww50: for (ap_int<32> ww50 = 0; ww50 < 8; ++ww50) {
          layer3_2_rsign1_hh50: for (ap_int<32> hh50 = 0; hh50 < 8; ++hh50) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_1_rprelu2_temp1;
            layer3_1_rprelu2_temp1 = layer3_1_rprelu2_pipe_99[0][cc50][ww50][hh50];
            ap_int<8> layer3_2_rsign1_temp;
            layer3_2_rsign1_temp = ((ap_int<8>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer3_1_rprelu2_temp1) + ((ap_fixed<33, 21>)w_layer3_2_rsign1[cc50])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer3_2_rsign1_pipe_100[0][cc50][ww50][hh50] = layer3_2_rsign1_temp;
          }
        }
      }
      ap_int<8> layer3_2_conv1_pad[1][64][10][10];
      ap_int<8> layer3_2_conv1_pad_pipe_101[1][64][10][10];
      #pragma HLS stream variable=layer3_2_conv1_pad_pipe_101 depth=101
      layer3_2_conv1_pad_not_zero17: for (ap_int<32> not_zero17 = 0; not_zero17 < 64; ++not_zero17) {
        layer3_2_conv1_pad_index_tuple17: for (ap_int<32> index_tuple17 = 0; index_tuple17 < 10; ++index_tuple17) {
          layer3_2_conv1_pad_i17: for (ap_int<32> i17 = 0; i17 < 10; ++i17) {
        #pragma HLS pipeline
            ap_int<8> layer3_2_rsign1_temp1;
            layer3_2_rsign1_temp1 = layer3_2_rsign1_pipe_100[0][not_zero17][(index_tuple17 + -1)][(i17 + -1)];
            ap_int<8> layer3_2_conv1_pad_temp;
            layer3_2_conv1_pad_temp = (((((1 <= index_tuple17) && (index_tuple17 < 9)) && (1 <= i17)) && (i17 < 9)) ? ((ap_int<8>)layer3_2_rsign1_temp1) : ((ap_int<8>)0));
            layer3_2_conv1_pad_pipe_101[0][not_zero17][index_tuple17][i17] = layer3_2_conv1_pad_temp;
            layer3_2_conv1_pad[0][not_zero17][index_tuple17][i17] = layer3_2_conv1_pad_temp;
          }
        }
      }
      ap_int<8> layer3_2_conv1_LB[1][64][3][10];
      #pragma HLS array_partition variable=layer3_2_conv1_LB dim=3 complete
      ap_int<8> layer3_2_conv1_WB[1][64][3][3];
      #pragma HLS array_partition variable=layer3_2_conv1_WB dim=3 complete
      #pragma HLS array_partition variable=layer3_2_conv1_WB dim=4 complete
      ap_int<8> layer3_2_conv1_pipe_102[1][64][8][8];
      #pragma HLS stream variable=layer3_2_conv1_pipe_102 depth=102
      layer3_2_conv1_ff17: for (ap_int<32> ff17 = 0; ff17 < 64; ++ff17) {
        layer3_2_conv1_yy_reuse13: for (ap_int<32> yy_reuse13 = 0; yy_reuse13 < 10; ++yy_reuse13) {
          layer3_2_conv1_xx_reuse13: for (ap_int<32> xx_reuse13 = 0; xx_reuse13 < 10; ++xx_reuse13) {
            layer3_2_conv1_pad_2: for (ap_int<32> layer3_2_conv1_pad_2 = 0; layer3_2_conv1_pad_2 < 64; ++layer3_2_conv1_pad_2) {
          #pragma HLS pipeline
              layer3_2_conv1_pad_1: for (ap_int<32> layer3_2_conv1_pad_1 = 0; layer3_2_conv1_pad_1 < 2; ++layer3_2_conv1_pad_1) {
                layer3_2_conv1_LB[0][layer3_2_conv1_pad_2][layer3_2_conv1_pad_1][xx_reuse13] = layer3_2_conv1_LB[0][layer3_2_conv1_pad_2][(layer3_2_conv1_pad_1 + 1)][xx_reuse13];
              }
              ap_int<8> layer3_2_conv1_pad_temp1;
              layer3_2_conv1_pad_temp1 = layer3_2_conv1_pad_pipe_101[0][layer3_2_conv1_pad_2][yy_reuse13][xx_reuse13];
              layer3_2_conv1_LB[0][layer3_2_conv1_pad_2][2][xx_reuse13] = layer3_2_conv1_pad_temp1;
            }
            if (2 <= yy_reuse13) {
              layer3_2_conv1_LB_1: for (ap_int<32> layer3_2_conv1_LB_1 = 0; layer3_2_conv1_LB_1 < 3; ++layer3_2_conv1_LB_1) {
                layer3_2_conv1_LB_2: for (ap_int<32> layer3_2_conv1_LB_2 = 0; layer3_2_conv1_LB_2 < 64; ++layer3_2_conv1_LB_2) {
                  layer3_2_conv1_LB_0: for (ap_int<32> layer3_2_conv1_LB_0 = 0; layer3_2_conv1_LB_0 < 2; ++layer3_2_conv1_LB_0) {
                    layer3_2_conv1_WB[0][layer3_2_conv1_LB_2][layer3_2_conv1_LB_1][layer3_2_conv1_LB_0] = layer3_2_conv1_WB[0][layer3_2_conv1_LB_2][layer3_2_conv1_LB_1][(layer3_2_conv1_LB_0 + 1)];
                  }
                  layer3_2_conv1_WB[0][layer3_2_conv1_LB_2][layer3_2_conv1_LB_1][2] = layer3_2_conv1_LB[0][layer3_2_conv1_LB_2][layer3_2_conv1_LB_1][xx_reuse13];
                }
              }
              if (2 <= xx_reuse13) {
                ap_int<8> layer3_2_conv1_sum;
                layer3_2_conv1_sum = (ap_int<8>)0;
                layer3_2_conv1_rc17: for (ap_int<32> rc17 = 0; rc17 < 64; ++rc17) {
                  layer3_2_conv1_ry17: for (ap_int<32> ry17 = 0; ry17 < 3; ++ry17) {
                    layer3_2_conv1_rx17: for (ap_int<32> rx17 = 0; rx17 < 3; ++rx17) {
                      layer3_2_conv1_sum = ((ap_int<8>)(((ap_int<33>)(((((((ap_int<33>)1 - ((ap_int<33>)rx17)) <= ((ap_int<33>)(xx_reuse13 + -2))) && (((ap_int<33>)(xx_reuse13 + -2)) < ((ap_int<33>)9 - ((ap_int<33>)rx17)))) && (((ap_int<33>)1 - ((ap_int<33>)ry17)) <= ((ap_int<33>)(yy_reuse13 + -2)))) && (((ap_int<33>)(yy_reuse13 + -2)) < ((ap_int<33>)9 - ((ap_int<33>)ry17)))) ? ((ap_int<32>)((((1 - ((ap_int<32>)layer3_2_conv1_WB[0][rc17][ry17][rx17])) ^ w_layer3_2_conv1[ff17][rc17][ry17][rx17]) << 1) + -1)) : ((ap_int<32>)0))) + ((ap_int<33>)layer3_2_conv1_sum)));
                    }
                  }
                }
                ap_int<8> layer3_2_conv1_temp;
                layer3_2_conv1_temp = layer3_2_conv1_sum;
                layer3_2_conv1_pipe_102[0][ff17][(yy_reuse13 + -2)][(xx_reuse13 + -2)] = layer3_2_conv1_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer3_2_bn1_pipe_103[1][64][8][8];
      #pragma HLS stream variable=layer3_2_bn1_pipe_103 depth=103
      layer3_2_bn1_args017: for (ap_int<32> args017 = 0; args017 < 64; ++args017) {
        layer3_2_bn1_args117: for (ap_int<32> args117 = 0; args117 < 8; ++args117) {
          layer3_2_bn1_args217: for (ap_int<32> args217 = 0; args217 < 8; ++args217) {
          #pragma HLS pipeline
            ap_int<8> layer3_2_conv1_temp1;
            layer3_2_conv1_temp1 = layer3_2_conv1_pipe_102[0][args017][args117][args217];
            ap_fixed<32, 20> layer3_2_bn1_temp;
            layer3_2_bn1_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer3_2_conv1_temp1) - w_layer3_2_bn1_11[args017]))) / sqrt((((float)w_layer3_2_bn1_12[args017]) + 1.000000e-07f))) * ((float)w_layer3_2_bn1_9[args017])) + ((float)w_layer3_2_bn1_10[args017])));
            layer3_2_bn1_pipe_103[0][args017][args117][args217] = layer3_2_bn1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_2_residual1_pipe_104[1][64][8][8];
      #pragma HLS stream variable=layer3_2_residual1_pipe_104 depth=104
      layer3_2_residual1_cc51: for (ap_int<32> cc51 = 0; cc51 < 64; ++cc51) {
        layer3_2_residual1_ww51: for (ap_int<32> ww51 = 0; ww51 < 8; ++ww51) {
          layer3_2_residual1_hh51: for (ap_int<32> hh51 = 0; hh51 < 8; ++hh51) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_2_bn1_temp1;
            layer3_2_bn1_temp1 = layer3_2_bn1_pipe_103[0][cc51][ww51][hh51];
            ap_fixed<32, 20> layer3_2_residual1_temp;
            ap_fixed<32, 20> layer3_1_rprelu2_temp2;
            layer3_1_rprelu2_temp2 = layer3_1_rprelu2_pipe_135[0][cc51][ww51][hh51];
            layer3_2_residual1_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer3_2_bn1_temp1) + ((ap_fixed<33, 21>)layer3_1_rprelu2_temp2)));
            layer3_2_residual1_pipe_104[0][cc51][ww51][hh51] = layer3_2_residual1_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_2_rprelu1_pipe_105[1][64][8][8];
      #pragma HLS stream variable=layer3_2_rprelu1_pipe_105 depth=105
      ap_fixed<32, 20> layer3_2_rprelu1_pipe_136[1][64][8][8];
      #pragma HLS stream variable=layer3_2_rprelu1_pipe_136 depth=136
      layer3_2_rprelu1_cc52: for (ap_int<32> cc52 = 0; cc52 < 64; ++cc52) {
        layer3_2_rprelu1_ww52: for (ap_int<32> ww52 = 0; ww52 < 8; ++ww52) {
          layer3_2_rprelu1_hh52: for (ap_int<32> hh52 = 0; hh52 < 8; ++hh52) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_2_residual1_temp1;
            layer3_2_residual1_temp1 = layer3_2_residual1_pipe_104[0][cc52][ww52][hh52];
            ap_fixed<32, 20> layer3_2_rprelu1_temp;
            layer3_2_rprelu1_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer3_2_residual1_temp1) + ((ap_fixed<33, 21>)w_layer3_2_rprelu1_0[cc52])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer3_2_residual1_temp1) + ((ap_fixed<33, 21>)w_layer3_2_rprelu1_0[cc52])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer3_2_rprelu1_2[cc52]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer3_2_residual1_temp1) + ((ap_fixed<33, 21>)w_layer3_2_rprelu1_0[cc52]))))))) + ((ap_fixed<66, 42>)w_layer3_2_rprelu1_1[cc52])));
            layer3_2_rprelu1_pipe_136[0][cc52][ww52][hh52] = layer3_2_rprelu1_temp;
            layer3_2_rprelu1_pipe_105[0][cc52][ww52][hh52] = layer3_2_rprelu1_temp;
          }
        }
      }
      ap_fixed<32, 20> avgpool_LB[8][8];
      ap_uint<1> layer3_2_rsign2_pipe_106[1][64][8][8];
      #pragma HLS stream variable=layer3_2_rsign2_pipe_106 depth=106
      layer3_2_rsign2_cc53: for (ap_int<32> cc53 = 0; cc53 < 64; ++cc53) {
        layer3_2_rsign2_ww53: for (ap_int<32> ww53 = 0; ww53 < 8; ++ww53) {
          layer3_2_rsign2_hh53: for (ap_int<32> hh53 = 0; hh53 < 8; ++hh53) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_2_rprelu1_temp1;
            layer3_2_rprelu1_temp1 = layer3_2_rprelu1_pipe_105[0][cc53][ww53][hh53];
            ap_uint<1> layer3_2_rsign2_temp;
            layer3_2_rsign2_temp = ((ap_uint<1>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer3_2_rprelu1_temp1) + ((ap_fixed<33, 21>)w_layer3_2_rsign2[cc53])))) ? ((ap_int<32>)1) : ((ap_int<32>)0)));
            layer3_2_rsign2_pipe_106[0][cc53][ww53][hh53] = layer3_2_rsign2_temp;
          }
        }
      }
      ap_uint<1> layer3_2_conv2_pad[1][64][10][10];
      ap_uint<1> layer3_2_conv2_pad_pipe_107[1][64][10][10];
      #pragma HLS stream variable=layer3_2_conv2_pad_pipe_107 depth=107
      layer3_2_conv2_pad_not_zero18: for (ap_int<32> not_zero18 = 0; not_zero18 < 64; ++not_zero18) {
        layer3_2_conv2_pad_index_tuple18: for (ap_int<32> index_tuple18 = 0; index_tuple18 < 10; ++index_tuple18) {
          layer3_2_conv2_pad_i18: for (ap_int<32> i18 = 0; i18 < 10; ++i18) {
        #pragma HLS pipeline
            ap_uint<1> layer3_2_rsign2_temp1;
            layer3_2_rsign2_temp1 = layer3_2_rsign2_pipe_106[0][not_zero18][(index_tuple18 + -1)][(i18 + -1)];
            ap_uint<1> layer3_2_conv2_pad_temp;
            layer3_2_conv2_pad_temp = (((((1 <= index_tuple18) && (index_tuple18 < 9)) && (1 <= i18)) && (i18 < 9)) ? ((ap_uint<1>)layer3_2_rsign2_temp1) : ((ap_uint<1>)0));
            layer3_2_conv2_pad_pipe_107[0][not_zero18][index_tuple18][i18] = layer3_2_conv2_pad_temp;
            layer3_2_conv2_pad[0][not_zero18][index_tuple18][i18] = layer3_2_conv2_pad_temp;
          }
        }
      }
      ap_uint<1> layer3_2_conv2_LB[1][64][3][10];
      #pragma HLS array_partition variable=layer3_2_conv2_LB dim=3 complete
      ap_uint<1> layer3_2_conv2_WB[1][64][3][3];
      #pragma HLS array_partition variable=layer3_2_conv2_WB dim=3 complete
      #pragma HLS array_partition variable=layer3_2_conv2_WB dim=4 complete
      ap_int<8> layer3_2_conv2_pipe_108[1][64][8][8];
      #pragma HLS stream variable=layer3_2_conv2_pipe_108 depth=108
      layer3_2_conv2_ff18: for (ap_int<32> ff18 = 0; ff18 < 64; ++ff18) {
        layer3_2_conv2_yy_reuse14: for (ap_int<32> yy_reuse14 = 0; yy_reuse14 < 10; ++yy_reuse14) {
          layer3_2_conv2_xx_reuse14: for (ap_int<32> xx_reuse14 = 0; xx_reuse14 < 10; ++xx_reuse14) {
            layer3_2_conv2_pad_2: for (ap_int<32> layer3_2_conv2_pad_2 = 0; layer3_2_conv2_pad_2 < 64; ++layer3_2_conv2_pad_2) {
          #pragma HLS pipeline
              layer3_2_conv2_pad_1: for (ap_int<32> layer3_2_conv2_pad_1 = 0; layer3_2_conv2_pad_1 < 2; ++layer3_2_conv2_pad_1) {
                layer3_2_conv2_LB[0][layer3_2_conv2_pad_2][layer3_2_conv2_pad_1][xx_reuse14] = layer3_2_conv2_LB[0][layer3_2_conv2_pad_2][(layer3_2_conv2_pad_1 + 1)][xx_reuse14];
              }
              ap_uint<1> layer3_2_conv2_pad_temp1;
              layer3_2_conv2_pad_temp1 = layer3_2_conv2_pad_pipe_107[0][layer3_2_conv2_pad_2][yy_reuse14][xx_reuse14];
              layer3_2_conv2_LB[0][layer3_2_conv2_pad_2][2][xx_reuse14] = layer3_2_conv2_pad_temp1;
            }
            if (2 <= yy_reuse14) {
              layer3_2_conv2_LB_1: for (ap_int<32> layer3_2_conv2_LB_1 = 0; layer3_2_conv2_LB_1 < 3; ++layer3_2_conv2_LB_1) {
                layer3_2_conv2_LB_2: for (ap_int<32> layer3_2_conv2_LB_2 = 0; layer3_2_conv2_LB_2 < 64; ++layer3_2_conv2_LB_2) {
                  layer3_2_conv2_LB_0: for (ap_int<32> layer3_2_conv2_LB_0 = 0; layer3_2_conv2_LB_0 < 2; ++layer3_2_conv2_LB_0) {
                    layer3_2_conv2_WB[0][layer3_2_conv2_LB_2][layer3_2_conv2_LB_1][layer3_2_conv2_LB_0] = layer3_2_conv2_WB[0][layer3_2_conv2_LB_2][layer3_2_conv2_LB_1][(layer3_2_conv2_LB_0 + 1)];
                  }
                  layer3_2_conv2_WB[0][layer3_2_conv2_LB_2][layer3_2_conv2_LB_1][2] = layer3_2_conv2_LB[0][layer3_2_conv2_LB_2][layer3_2_conv2_LB_1][xx_reuse14];
                }
              }
              if (2 <= xx_reuse14) {
                ap_int<8> layer3_2_conv2_sum;
                layer3_2_conv2_sum = (ap_int<8>)0;
                layer3_2_conv2_rc18: for (ap_int<32> rc18 = 0; rc18 < 64; ++rc18) {
                  layer3_2_conv2_ry18: for (ap_int<32> ry18 = 0; ry18 < 3; ++ry18) {
                    layer3_2_conv2_rx18: for (ap_int<32> rx18 = 0; rx18 < 3; ++rx18) {
                      layer3_2_conv2_sum = ((ap_int<8>)(((ap_int<34>)(((((((ap_int<33>)1 - ((ap_int<33>)rx18)) <= ((ap_int<33>)(xx_reuse14 + -2))) && (((ap_int<33>)(xx_reuse14 + -2)) < ((ap_int<33>)9 - ((ap_int<33>)rx18)))) && (((ap_int<33>)1 - ((ap_int<33>)ry18)) <= ((ap_int<33>)(yy_reuse14 + -2)))) && (((ap_int<33>)(yy_reuse14 + -2)) < ((ap_int<33>)9 - ((ap_int<33>)ry18)))) ? ((ap_uint<32>)((((1U - ((ap_uint<32>)layer3_2_conv2_WB[0][rc18][ry18][rx18])) ^ w_layer3_2_conv2[ff18][rc18][ry18][rx18]) << 1) - 1U)) : ((ap_uint<32>)0U))) + ((ap_int<34>)layer3_2_conv2_sum)));
                    }
                  }
                }
                ap_int<8> layer3_2_conv2_temp;
                layer3_2_conv2_temp = layer3_2_conv2_sum;
                layer3_2_conv2_pipe_108[0][ff18][(yy_reuse14 + -2)][(xx_reuse14 + -2)] = layer3_2_conv2_temp;
              }
            }
          }
        }
      }
      ap_fixed<32, 20> layer3_2_bn2_pipe_109[1][64][8][8];
      #pragma HLS stream variable=layer3_2_bn2_pipe_109 depth=109
      layer3_2_bn2_args018: for (ap_int<32> args018 = 0; args018 < 64; ++args018) {
        layer3_2_bn2_args118: for (ap_int<32> args118 = 0; args118 < 8; ++args118) {
          layer3_2_bn2_args218: for (ap_int<32> args218 = 0; args218 < 8; ++args218) {
          #pragma HLS pipeline
            ap_int<8> layer3_2_conv2_temp1;
            layer3_2_conv2_temp1 = layer3_2_conv2_pipe_108[0][args018][args118][args218];
            ap_fixed<32, 20> layer3_2_bn2_temp;
            layer3_2_bn2_temp = ((ap_fixed<32, 20>)(((((float)((ap_fixed<33, 21>)(((ap_fixed<32, 20>)layer3_2_conv2_temp1) - w_layer3_2_bn2_16[args018]))) / sqrt((((float)w_layer3_2_bn2_17[args018]) + 1.000000e-07f))) * ((float)w_layer3_2_bn2_14[args018])) + ((float)w_layer3_2_bn2_15[args018])));
            layer3_2_bn2_pipe_109[0][args018][args118][args218] = layer3_2_bn2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_2_residual2_pipe_110[1][64][8][8];
      #pragma HLS stream variable=layer3_2_residual2_pipe_110 depth=110
      layer3_2_residual2_cc54: for (ap_int<32> cc54 = 0; cc54 < 64; ++cc54) {
        layer3_2_residual2_ww54: for (ap_int<32> ww54 = 0; ww54 < 8; ++ww54) {
          layer3_2_residual2_hh54: for (ap_int<32> hh54 = 0; hh54 < 8; ++hh54) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_2_bn2_temp1;
            layer3_2_bn2_temp1 = layer3_2_bn2_pipe_109[0][cc54][ww54][hh54];
            ap_fixed<32, 20> layer3_2_residual2_temp;
            ap_fixed<32, 20> layer3_2_rprelu1_temp2;
            layer3_2_rprelu1_temp2 = layer3_2_rprelu1_pipe_136[0][cc54][ww54][hh54];
            layer3_2_residual2_temp = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)layer3_2_bn2_temp1) + ((ap_fixed<33, 21>)layer3_2_rprelu1_temp2)));
            layer3_2_residual2_pipe_110[0][cc54][ww54][hh54] = layer3_2_residual2_temp;
          }
        }
      }
      ap_fixed<32, 20> layer3_2_rprelu2_pipe_111[1][64][8][8];
      #pragma HLS stream variable=layer3_2_rprelu2_pipe_111 depth=111
      layer3_2_rprelu2_cc55: for (ap_int<32> cc55 = 0; cc55 < 64; ++cc55) {
        layer3_2_rprelu2_ww55: for (ap_int<32> ww55 = 0; ww55 < 8; ++ww55) {
          layer3_2_rprelu2_hh55: for (ap_int<32> hh55 = 0; hh55 < 8; ++hh55) {
          #pragma HLS pipeline
            ap_fixed<32, 20> layer3_2_residual2_temp1;
            layer3_2_residual2_temp1 = layer3_2_residual2_pipe_110[0][cc55][ww55][hh55];
            ap_fixed<32, 20> layer3_2_rprelu2_temp;
            layer3_2_rprelu2_temp = ((ap_fixed<32, 20>)(((ap_fixed<66, 42>)(((ap_fixed<44, 32>)0 < ((ap_fixed<44, 32>)(((ap_fixed<33, 21>)layer3_2_residual2_temp1) + ((ap_fixed<33, 21>)w_layer3_2_rprelu2_3[cc55])))) ? (((ap_fixed<65, 41>)(((ap_fixed<33, 21>)layer3_2_residual2_temp1) + ((ap_fixed<33, 21>)w_layer3_2_rprelu2_3[cc55])))) : ((ap_fixed<65, 41>)(((ap_fixed<65, 53>)w_layer3_2_rprelu2_5[cc55]) * ((ap_fixed<65, 53>)(((ap_fixed<33, 21>)layer3_2_residual2_temp1) + ((ap_fixed<33, 21>)w_layer3_2_rprelu2_3[cc55]))))))) + ((ap_fixed<66, 42>)w_layer3_2_rprelu2_4[cc55])));
            layer3_2_rprelu2_pipe_111[0][cc55][ww55][hh55] = layer3_2_rprelu2_temp;
          }
        }
      }
      ap_fixed<32, 20> avgpool_pipe_112[1][64][1][1];
      #pragma HLS stream variable=avgpool_pipe_112 depth=112
      avgpool_c2: for (ap_int<32> c2 = 0; c2 < 64; ++c2) {
        avgpool_h2: for (ap_int<32> h2 = 0; h2 < 1; ++h2) {
          ap_fixed<32, 20> avgpool_val;
          avgpool_val = ((ap_fixed<32, 20>)0);
          avgpool_LB_i: for (ap_int<32> avgpool_LB_i = 0; avgpool_LB_i < 8; ++avgpool_LB_i) {
            avgpool_LB_j: for (ap_int<32> avgpool_LB_j = 0; avgpool_LB_j < 8; ++avgpool_LB_j) {
        #pragma HLS pipeline
              ap_fixed<32, 20> layer3_2_rprelu2_temp1;
              layer3_2_rprelu2_temp1 = layer3_2_rprelu2_pipe_111[0][(h2 + c2)][avgpool_LB_i][avgpool_LB_j];
              avgpool_LB[avgpool_LB_i][avgpool_LB_j] = layer3_2_rprelu2_temp1;
            }
          }
          avgpool_rr: for (ap_int<32> avgpool_rr = 0; avgpool_rr < 8; ++avgpool_rr) {
            avgpool_cc: for (ap_int<32> avgpool_cc = 0; avgpool_cc < 8; ++avgpool_cc) {
              avgpool_val = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)avgpool_val) + ((ap_fixed<33, 21>)avgpool_LB[avgpool_rr][avgpool_cc])));
            }
          }
          ap_fixed<32, 20> avgpool_temp;
          avgpool_temp = ((ap_fixed<32, 20>)(((ap_fixed<64, 20>)avgpool_val) / (ap_fixed<64, 20>)64));
          avgpool_pipe_112[0][(h2 + c2)][0][0] = avgpool_temp;
        }
      }
      ap_fixed<32, 20> flatten_pipe_113[1][64];
      #pragma HLS stream variable=flatten_pipe_113 depth=113
      flatten_j: for (ap_int<32> j = 0; j < 64; ++j) {
      #pragma HLS pipeline
        ap_fixed<32, 20> avgpool_temp1;
        avgpool_temp1 = avgpool_pipe_112[0][j][0][0];
        ap_fixed<32, 20> flatten_temp;
        flatten_temp = avgpool_temp1;
        flatten_pipe_113[0][j] = flatten_temp;
      }
      ap_fixed<32, 20> fc_matmul_pipe_114[1][10];
      #pragma HLS stream variable=fc_matmul_pipe_114 depth=114
      fc_matmul_j1: for (ap_int<32> j1 = 0; j1 < 10; ++j1) {
        ap_fixed<32,20> reducer0 = 0;
        fc_matmul_ra6: for (ap_int<32> ra6 = 0; ra6 < 64; ++ra6) {
        #pragma HLS pipeline
          ap_fixed<32, 20> flatten_temp1;
          flatten_temp1 = flatten_pipe_113[0][ra6];
          reducer0 = (flatten_temp1) * (w_fc_167[j1][ra6]) + reducer0;
        }
        ap_fixed<32, 20> fc_matmul_temp;
        fc_matmul_temp = ((ap_fixed<32, 20>)reducer0);
        fc_matmul_pipe_114[0][j1] = fc_matmul_temp;
      }
      fc_j2: for (ap_int<32> j2 = 0; j2 < 10; ++j2) {
      #pragma HLS pipeline
        ap_fixed<32, 20> fc_matmul_temp1;
        fc_matmul_temp1 = fc_matmul_pipe_114[0][j2];
        fc[0][j2] = ((ap_fixed<32, 20>)(((ap_fixed<33, 21>)fc_matmul_temp1) + ((ap_fixed<33, 21>)w_fc_168[j2])));
      }
    }
}

