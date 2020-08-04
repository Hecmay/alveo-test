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

    ap_int<8> data_batch_0[SIZE];
    #pragma HLS stream variable=data_batch_0 depth=10
    ap_int<8> data_batch_1[SIZE];
    #pragma HLS stream variable=data_batch_1 depth=10
    ap_int<8> data_batch_2[SIZE];
    #pragma HLS stream variable=data_batch_2 depth=10
    ap_int<8> data_batch_3[SIZE];
    #pragma HLS stream variable=data_batch_3 depth=10
    ap_int<8> data_batch_4[SIZE];
    #pragma HLS stream variable=data_batch_4 depth=10
    ap_int<8> data_batch_5[SIZE];
    #pragma HLS stream variable=data_batch_5 depth=10
    ap_int<8> data_batch_6[SIZE];
    #pragma HLS stream variable=data_batch_6 depth=10
    ap_int<8> data_batch_7[SIZE];
    #pragma HLS stream variable=data_batch_7 depth=10

    for (ap_int<32> x4 = 0; x4 < SIZE; ++x4) {
      ap_int<32> data = input[(x4)];
      data_batch_0[x4] = data(3,0);
      data_batch_1[x4] = data(7,4);
      data_batch_2[x4] = data(11,8);
      data_batch_3[x4] = data(15,12);
      data_batch_4[x4] = data(19,16);
      data_batch_5[x4] = data(23,20);
      data_batch_6[x4] = data(27,24);
      data_batch_7[x4] = data(31,28);
    }

    ap_uint<32> map_batch_0[10];
    pe_0: for (ap_int<32> x5 = 0; x5 < SIZE; ++x5) {
      int index = data_batch_0[x5];
      map_batch_0[index] = (map_batch_0[index] + 1U);
    }

    ap_uint<32> map_batch_1[10];
    pe_1: for (ap_int<32> x6 = 0; x6 < SIZE; ++x6) {
      int index = data_batch_1[x6];
      map_batch_1[index] = (map_batch_1[index] + 1U);
    }

    ap_uint<32> map_batch_2[10];
    pe_2: for (ap_int<32> x7 = 0; x7 < SIZE; ++x7) {
      int index = data_batch_2[x7];
      map_batch_2[index] = (map_batch_2[index] + 1U);
    }

    ap_uint<32> map_batch_3[10];
    pe_3: for (ap_int<32> x8 = 0; x8 < SIZE; ++x8) {
      int index = data_batch_3[x8];
      map_batch_3[index] = (map_batch_3[index] + 1U);
    }

    ap_uint<32> map_batch_4[10];
    pe_4: for (ap_int<32> x8 = 0; x8 < SIZE; ++x8) {
      int index = data_batch_4[x8];
      map_batch_4[index] = (map_batch_4[index] + 1U);
    }

    ap_uint<32> map_batch_5[10];
    pe_5: for (ap_int<32> x8 = 0; x8 < SIZE; ++x8) {
      int index = data_batch_5[x8];
      map_batch_5[index] = (map_batch_5[index] + 1U);
    }

    ap_uint<32> map_batch_6[10];
    pe_6: for (ap_int<32> x8 = 0; x8 < SIZE; ++x8) {
      int index = data_batch_6[x8];
      map_batch_6[index] = (map_batch_6[index] + 1U);
    }

    ap_uint<32> map_batch_7[10];
    pe_7: for (ap_int<32> x8 = 0; x8 < SIZE; ++x8) {
      int index = data_batch_7[x8];
      map_batch_7[index] = (map_batch_7[index] + 1U);
    }

    reducer: for (ap_int<32> x10 = 0; x10 < 10; ++x10) {
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


