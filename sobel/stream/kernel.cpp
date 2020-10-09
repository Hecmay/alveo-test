#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <hls_math.h>
#include <math.h>
#include <stdint.h>

void generate(ap_int<32> A[1500*1500], ap_int<8> B1[1500][1500], ap_int<8> B2[1500][1500]) {
  #pragma HLS INLINE off
  for (ap_int<32> x = 0; x < 1500; ++x) {
    for (ap_int<32> y = 0; y < 1500; ++y) {
    #pragma HLS pipeline II=1
      ap_int<32> data = A[x*1500+y];
      ap_int<8> a = data(7,0) + data(15,8) + data(23,16);
      B1[x][y] = (a);
      B2[x][y] = (a);
    }
  }
}

void get_xx(ap_int<8> B1[1500][1500], ap_int<8> xx[1498][1498]) {
  #pragma HLS INLINE off
  const int Gx[3][3] =
  {
      {1,0,-1},
      {2,0,-2},
      {1,0,-1}
  };
  #pragma HLS array_partition variable=Gx complete dim=0

  ap_int<8> LBX[3][1500];
  #pragma HLS array_partition variable=LBX complete dim=1
  ap_int<8> WBX[3][3];
  #pragma HLS array_partition variable=WBX complete dim=0
  for (ap_int<32> x_reuse = 0; x_reuse < 1500; ++x_reuse) {
    for (ap_int<32> y_reuse = 0; y_reuse < 1500; ++y_reuse) {
    #pragma HLS pipeline II=1
      for (ap_int<32> B_1 = 0; B_1 < 2; ++B_1) {
        LBX[B_1][y_reuse] = LBX[(B_1 + 1)][y_reuse];
      }
      LBX[2][y_reuse] = B1[x_reuse][y_reuse];
      if (2 <= x_reuse) {
        for (ap_int<32> LBX_1 = 0; LBX_1 < 3; ++LBX_1) {
          for (ap_int<32> LBX_0 = 0; LBX_0 < 2; ++LBX_0) {
            WBX[LBX_1][LBX_0] = WBX[LBX_1][(LBX_0 + 1)];
          }
          WBX[LBX_1][2] = LBX[LBX_1][y_reuse];
        }
        if (2 <= y_reuse) {
          ap_int<32> sum1;
          sum1 = 0;
          for (ap_int<32> ra0 = 0; ra0 < 3; ++ra0) {
            for (ap_int<32> ra1 = 0; ra1 < 3; ++ra1) {
              sum1 = ((ap_int<32>)((WBX[ra0][ra1] * Gx[ra0][ra1]) + ((ap_int<8>)sum1)));
            }
          }
          xx[(x_reuse + -2)][(y_reuse + -2)] = ((ap_int<8>)sum1);
        }
      }
    }
  }
}

void get_yy(ap_int<8> B2[1500][1500], ap_int<8> yy[1498][1498]) {
  #pragma HLS INLINE off
  const int Gy[3][3] =
  {
      {1,2,1},
      {0,0,0},
      {-1,-2,-1}
  };
  #pragma HLS array_partition variable=Gy complete dim=0
  ap_int<8> LBY[3][1500];
  #pragma HLS array_partition variable=LBY complete dim=1
  ap_int<8> WBY[3][3];
  #pragma HLS array_partition variable=WBY complete dim=0
  for (ap_int<32> x_reuse1 = 0; x_reuse1 < 1500; ++x_reuse1) {
    for (ap_int<32> y_reuse1 = 0; y_reuse1 < 1500; ++y_reuse1) {
    #pragma HLS pipeline II=1
      for (ap_int<32> B_11 = 0; B_11 < 2; ++B_11) {
        LBY[B_11][y_reuse1] = LBY[(B_11 + 1)][y_reuse1];
      }
      LBY[2][y_reuse1] = B2[x_reuse1][y_reuse1];
      if (2 <= x_reuse1) {
        for (ap_int<32> LBY_1 = 0; LBY_1 < 3; ++LBY_1) {
          for (ap_int<32> LBY_0 = 0; LBY_0 < 2; ++LBY_0) {
            WBY[LBY_1][LBY_0] = WBY[LBY_1][(LBY_0 + 1)];
          }
          WBY[LBY_1][2] = LBY[LBY_1][y_reuse1];
        }
        if (2 <= y_reuse1) {
          ap_int<32> sum;
          sum = 0;
          for (ap_int<32> ra2 = 0; ra2 < 3; ++ra2) {
            for (ap_int<32> ra3 = 0; ra3 < 3; ++ra3) {
              sum = ((ap_int<32>)((WBY[ra2][ra3] * Gy[ra2][ra3]) + ((ap_int<8>)sum)));
            }
          }
          yy[(x_reuse1 + -2)][(y_reuse1 + -2)] = ((ap_int<8>)sum);
        }
      }
    }
  }
}

void get_res(ap_int<8> xx[1498][1498], ap_int<8> yy[1498][1498], ap_int<8> Fimg[1498*1498]) {
  #pragma HLS INLINE off
  for (ap_int<32> x1 = 0; x1 < 1498; ++x1) {
    for (ap_int<32> y1 = 0; y1 < 1498; ++y1) {
    #pragma HLS pipeline II=1
      ap_int<8> tx = xx[x1][y1];
      ap_int<8> ty = yy[x1][y1];
      Fimg[x1*1498+y1] = (sqrt(((tx*tx) + (ty*ty))) * 5.891867e-02f);
    }
  }
}

extern "C" 
{
void top(ap_int<32> A[1500*1500], ap_int<8> Fimg[1498*1498]) {
    #pragma HLS INTERFACE m_axi port=A offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=Fimg offset=slave bundle=gmem1
    #pragma HLS INTERFACE s_axilite port=A bundle=control
    #pragma HLS INTERFACE s_axilite port=Fimg bundle=control
    #pragma HLS INTERFACE s_axilite port=return bundle=control

  #pragma HLS DATAFLOW

  ap_int<8> B1[1500][1500];
  #pragma HLS STREAM variable=B1 depth=1
  ap_int<8> B2[1500][1500];
  #pragma HLS STREAM variable=B2 depth=1
  ap_int<8> xx[1498][1498];
  #pragma HLS STREAM variable=xx depth=1
  ap_int<8> yy[1498][1498];
  #pragma HLS STREAM variable=yy depth=1

  generate(A, B1, B2);
  get_xx(B1, xx);
  get_yy(B2, yy);
  get_res(xx, yy, Fimg);

}

}
