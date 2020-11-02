#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <hls_math.h>
#include <math.h>
#include <stdint.h>

extern "C" {
void test(ap_uint<64> test_image, ap_uint<64> train_images[10][1800], ap_uint<8> gknn_mat[10][3]) {
    #pragma HLS INTERFACE m_axi port=train_images offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=gknn_mat offset=slave bundle=gmem1

    #pragma HLS INTERFACE s_axilite port=test_image bundle=control
    #pragma HLS INTERFACE s_axilite port=train_images bundle=control
    #pragma HLS INTERFACE s_axilite port=gknn_mat bundle=control
    #pragma HLS INTERFACE s_axilite port=return bundle=control

  ap_uint<6> knn_mat[10][3];
  #pragma HLS array_partition variable=knn_mat dim=2 complete
  for (ap_int<32> x = 0; x < 10; ++x) {
    for (ap_int<32> y = 0; y < 3; ++y) {
      knn_mat[x][y] = (ap_uint<6>)50;
    }
  }
  ap_uint<64> knn_update;
  for (ap_int<32> y1 = 0; y1 < 1800; ++y1) {
    for (ap_int<32> x1 = 0; x1 < 10; ++x1) {
    #pragma HLS pipeline
      ap_uint<6> dist;
      ap_uint<64> diff;
      diff = (train_images[x1][y1] ^ test_image);
      ap_uint<6> out;
      out = (ap_uint<6>)0;
      for (ap_int<32> i = 0; i < 49; ++i) {
        out = ((ap_uint<6>)(((ap_uint<50>)out) + ((ap_uint<50>)diff[i])));
      }
      dist = out;
      ap_uint<64> max_id;
      max_id = (ap_uint<64>)0;
      for (ap_int<32> i1 = 0; i1 < 3; ++i1) {
        if (knn_mat[x1][max_id] < knn_mat[x1][i1]) {
          max_id = ((ap_uint<64>)i1);
        }
      }
      if (dist < knn_mat[x1][max_id]) {
        knn_mat[x1][max_id] = dist;
      }
    }
  }
  for (ap_int<32> x = 0; x < 10; ++x) {
    for (ap_int<32> y = 0; y < 3; ++y) {
      gknn_mat[x][y] = knn_mat[x][y];
    }
  }

}
}


