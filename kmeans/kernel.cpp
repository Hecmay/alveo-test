// HASH:4094949207
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

extern "C" {
void test(ap_int<32> labels[320], ap_int<32> points[320][32], ap_int<32> means[16][32]) {
    // #pragma HLS INTERFACE m_axi port=labels offset=slave bundle=gmem0
    // #pragma HLS INTERFACE m_axi port=points offset=slave bundle=gmem0
    // #pragma HLS INTERFACE m_axi port=means offset=slave bundle=gmem0
    // #pragma HLS INTERFACE s_axilite port=labels bundle=control
    // #pragma HLS INTERFACE s_axilite port=points bundle=control
    // #pragma HLS INTERFACE s_axilite port=means bundle=control
    // #pragma HLS INTERFACE s_axilite port=return bundle=control

      #pragma HLS array_partition variable=means complete dim=0
      #pragma HLS array_partition variable=points complete dim=2

      main_loop__1: for (ap_int<32> _1 = 0; _1 < 200; ++_1) {
        n: for (ap_int<32> n = 0; n < 320; ++n) {
        #pragma HLS pipeline
          ap_int<32> scalar0 = 100000;
          ap_int<32> scalar1;
          i: for (ap_int<32> i = 0; i < 16; ++i) {
            ap_int<32> scalar2;
            i1: for (ap_int<32> i1 = 0; i1 < 32; ++i1) {
              int temp1 = points[n][i1];
              int temp2 = means[i][i1];					
              scalar2 = (scalar2) + ((temp1) - (temp2)) * ((temp1) - (temp2));
            }
            if (scalar2 < scalar0) {
              scalar0 = scalar2;
              scalar1 = i;
            }
          }
          labels[n] = scalar1;
        }
        ap_int<32> num_k[16];
        #pragma HLS array_partition variable=num_k complete dim=0
        ap_int<32> num_k_partitioned;
        ap_int<32> sum_k[16][32];
        #pragma HLS array_partition variable=sum_k complete dim=0
        ap_int<32> sum_k_partitioned;
        ap_int<32> calc_sum;
        calc_sum_n1: for (ap_int<32> n1 = 0; n1 < 320; ++n1) {
        #pragma HLS pipeline
          int index = labels[n1];
          num_k[index] = (num_k[index] + 1);
          i2: for (ap_int<32> i2 = 0; i2 < 32; ++i2) {
            sum_k[index][i2] = ((ap_int<32>)(((ap_int<33>)sum_k[index][i2]) + ((ap_int<33>)points[n1][i2])));
          }
        }
        update_mean_k: for (ap_int<32> k = 0; k < 16; ++k) {
          #pragma HLS unroll
          update_mean_d: for (ap_int<32> d = 0; d < 32; ++d) {
          #pragma HLS unroll
            means[k][d] = (sum_k[k][d] / num_k[k]);
          }
        }
      }
    }
}

