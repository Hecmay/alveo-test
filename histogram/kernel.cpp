#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <hls_math.h>
#include <math.h>
#include <stdint.h>

#define SIZE 1024 * 1024 / 8

extern "C" {
    void test(ap_uint<32>* input, ap_uint<32>* output) {
    #pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem1

    #pragma HLS INTERFACE s_axilite port=input bundle=control
    #pragma HLS INTERFACE s_axilite port=output bundle=control
    #pragma HLS INTERFACE s_axilite port=return bundle=control

    #pragma HLS dataflow

    ap_int<32> data_batch_0[SIZE];
    ap_int<32> data_batch_1[SIZE];
    ap_int<32> data_batch_2[SIZE];
    ap_int<32> data_batch_3[SIZE];
    ap_int<32> data_batch_4[SIZE];
    ap_int<32> data_batch_5[SIZE];
    ap_int<32> data_batch_6[SIZE];
    ap_int<32> data_batch_7[SIZE];

    ap_uint<32> split;
    for (ap_int<32> x4 = 0; x4 < SIZE; ++x4) {
      data_batch_0[x4] = input[(x4)];
      data_batch_1[x4] = input[((x4) + SIZE)];
      data_batch_2[x4] = input[((x4) + SIZE*2)];
      data_batch_3[x4] = input[((x4) + SIZE*3)];
      data_batch_4[x4] = input[((x4) + SIZE*4)];
      data_batch_5[x4] = input[((x4) + SIZE*5)];
      data_batch_6[x4] = input[((x4) + SIZE*6)];
      data_batch_7[x4] = input[((x4) + SIZE*7)];
    }

    ap_uint<32> map_batch_0[10];
    for (ap_int<32> args = 0; args < 10; ++args) {
      map_batch_0[args] = 0U;
    }
    ap_uint<32> pe_0;
    for (ap_int<32> x5 = 0; x5 < SIZE; ++x5) {
      map_batch_0[data_batch_0[x5]] = (map_batch_0[data_batch_0[x5]] + 1U);
    }
    ap_uint<32> map_batch_1[10];
    for (ap_int<32> args1 = 0; args1 < 10; ++args1) {
      map_batch_1[args1] = 0U;
    }
    ap_uint<32> pe_1;
    for (ap_int<32> x6 = 0; x6 < SIZE; ++x6) {
      map_batch_1[data_batch_1[x6]] = (map_batch_1[data_batch_1[x6]] + 1U);
    }
    ap_uint<32> map_batch_2[10];
    for (ap_int<32> args2 = 0; args2 < 10; ++args2) {
      map_batch_2[args2] = 0U;
    }
    ap_uint<32> pe_2;
    for (ap_int<32> x7 = 0; x7 < SIZE; ++x7) {
      map_batch_2[data_batch_2[x7]] = (map_batch_2[data_batch_2[x7]] + 1U);
    }
    ap_uint<32> map_batch_3[10];
    for (ap_int<32> args3 = 0; args3 < 10; ++args3) {
      map_batch_3[args3] = 0U;
    }
    ap_uint<32> pe_3;
    for (ap_int<32> x8 = 0; x8 < SIZE; ++x8) {
      map_batch_3[data_batch_3[x8]] = (map_batch_3[data_batch_3[x8]] + 1U);
    }
    ap_uint<32> map_batch_4[10];
    for (ap_int<32> args4 = 0; args4 < 10; ++args4) {
      map_batch_4[args4] = 0U;
    }
    ap_uint<32> pe_4;
    for (ap_int<32> x9 = 0; x9 < SIZE; ++x9) {
      map_batch_4[data_batch_4[x9]] = (map_batch_4[data_batch_4[x9]] + 1U);
    }

    ap_uint<32> map_batch_5[10];
    for (ap_int<32> args5 = 0; args5 < 10; ++args5) {
      map_batch_5[args5] = 0U;
    }
    ap_uint<32> pe_5;
    for (ap_int<32> x8 = 0; x8 < SIZE; ++x8) {
      map_batch_5[data_batch_5[x8]] = (map_batch_5[data_batch_5[x8]] + 1U);
    }

    ap_uint<32> map_batch_6[10];
    for (ap_int<32> args3 = 0; args3 < 10; ++args3) {
      map_batch_6[args3] = 0U;
    }
    ap_uint<32> pe_6;
    for (ap_int<32> x8 = 0; x8 < SIZE; ++x8) {
      map_batch_6[data_batch_6[x8]] = (map_batch_6[data_batch_6[x8]] + 1U);
    }
    ap_uint<32> map_batch_7[10];
    for (ap_int<32> args3 = 0; args3 < 10; ++args3) {
      map_batch_7[args3] = 0U;
    }
    ap_uint<32> pe_7;
    for (ap_int<32> x8 = 0; x8 < SIZE; ++x8) {
      map_batch_7[data_batch_7[x8]] = (map_batch_7[data_batch_7[x8]] + 1U);
    }

    for (ap_int<32> x9 = 0; x9 < 10; ++x9) {
      output[x9] = 0U;
    }
    ap_uint<32> reducer;
    for (ap_int<32> x10 = 0; x10 < 10; ++x10) {
      output[x10] = ((ap_uint<32>)(((ap_uint<33>)output[x10]) + ((ap_uint<33>)map_batch_0[x10])));
      output[x10] = ((ap_uint<32>)(((ap_uint<33>)output[x10]) + ((ap_uint<33>)map_batch_1[x10])));
      output[x10] = ((ap_uint<32>)(((ap_uint<33>)output[x10]) + ((ap_uint<33>)map_batch_2[x10])));
      output[x10] = ((ap_uint<32>)(((ap_uint<33>)output[x10]) + ((ap_uint<33>)map_batch_3[x10])));
      output[x10] = ((ap_uint<32>)(((ap_uint<33>)output[x10]) + ((ap_uint<33>)map_batch_4[x10])));
      output[x10] = ((ap_uint<32>)(((ap_uint<33>)output[x10]) + ((ap_uint<33>)map_batch_5[x10])));
      output[x10] = ((ap_uint<32>)(((ap_uint<33>)output[x10]) + ((ap_uint<33>)map_batch_6[x10])));
      output[x10] = ((ap_uint<32>)(((ap_uint<33>)output[x10]) + ((ap_uint<33>)map_batch_7[x10])));
    }
  }
}


