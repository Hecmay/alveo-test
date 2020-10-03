#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <hls_math.h>
#include <stdint.h>

typedef ap_uint<32> bit32;
typedef ap_uint<16> bit16;
typedef ap_uint<8> bit8;

extern "C" {
  void test(bit32* triangle_3ds, bit32* output, const unsigned int angle) {
    #pragma HLS INTERFACE m_axi port=triangle_3ds offset=slave bundle=gmem
    #pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem

    #pragma HLS INTERFACE s_axilite port=triangle_3ds bundle=control 
    #pragma HLS INTERFACE s_axilite port=output bundle=control
    #pragma HLS INTERFACE s_axilite port = angle bundle=control
    #pragma HLS INTERFACE s_axilite port=return bundle=control

    bit8 frame_buffer[256][256];
    #pragma HLS array_partition variable=frame_buffer cyclic factor=4 dim=2
    bit32 z_buffer[256*256];
    for (bit16 x = 0; x < 256; ++x) {
      for (bit16 y = 0; y < 256; ++y) {
        z_buffer[(x *256) + y] = 255;
      }
    }

    for (bit16 m = 0; m < 3192; ++m) {
    #pragma HLS pipeline
      bit32 input_lo  = triangle_3ds[3*m];
      bit32 input_mi  = triangle_3ds[3*m+1];
      bit32 input_hi  = triangle_3ds[3*m+2];
      bit8 triangle_3d[9];

      triangle_3d[0] = input_lo( 7,  0);
      triangle_3d[1] = input_lo(15,  8);
      triangle_3d[2] = input_lo(23, 16);
      triangle_3d[3] = input_lo(31, 24);
      triangle_3d[4] = input_mi( 7,  0);
      triangle_3d[5] = input_mi(15,  8);
      triangle_3d[6] = input_mi(23, 16);
      triangle_3d[7] = input_mi(31, 24);
      triangle_3d[8] = input_hi( 7,  0);

      bit8 fragment[500][4];
      bit8 pixels[500][3];

      bit8 triangle_2d[7];
      bit32 frag_cntr;
      frag_cntr = 0;
      bit32 size_pixels;
      size_pixels = 0;
      for (bit8 x6 = 0; x6 < 7; ++x6) {
        if (x6 == 0) {
          if (angle == 2) {
            triangle_2d[0] = triangle_3d[2];
          } else {
            triangle_2d[0] = triangle_3d[0];
          }
        }
        if (x6 == 1) {
          if (angle == 1) {
            triangle_2d[1] = triangle_3d[2];
          } else {
            triangle_2d[1] = triangle_3d[1];
          }
        }
        if (x6 == 2) {
          if (angle == 2) {
            triangle_2d[2] = triangle_3d[5];
          } else {
            triangle_2d[2] = triangle_3d[3];
          }
        }
        if (x6 == 3) {
          if (angle == 1) {
            triangle_2d[3] = triangle_3d[5];
          } else {
            triangle_2d[3] = triangle_3d[4];
          }
        }
        if (x6 == 4) {
          if (angle == 2) {
            triangle_2d[4] = triangle_3d[8];
          } else {
            triangle_2d[4] = triangle_3d[6];
          }
        }
        if (x6 == 5) {
          if (angle == 1) {
            triangle_2d[5] = triangle_3d[8];
          } else {
            triangle_2d[5] = triangle_3d[7];
          }
        }
        if (x6 == 6) {
          if (angle == 0) {
            triangle_2d[6] = ((triangle_3d[2]) + (triangle_3d[5]) + (triangle_3d[8])) /3;
          } else {
            if (angle == 1) {
              triangle_2d[6] = (((triangle_3d[1])) + (triangle_3d[4]) + (triangle_3d[7])) / 3;
            } else {
              if (angle == 2) {
                triangle_2d[6] = ((triangle_3d[0]) + (triangle_3d[3]) + (triangle_3d[6])) / 3;
              }
            }
          }
        }
      }
      bit8 x0;
      x0 = triangle_2d[0];
      bit8 y0;
      y0 = triangle_2d[1];
      bit8 x11;
      x11 = triangle_2d[2];
      bit8 y11;
      y11 = triangle_2d[3];
      bit8 x21;
      x21 = triangle_2d[4];
      bit8 y21;
      y21 = triangle_2d[5];
      bit8 z;
      z = triangle_2d[6];
      int cw;
      cw = ((int)((x21 - x0) * (y11 - y0) - (y21 - y0) * (x11 - x0)));
      if (cw == 0) {
        frag_cntr = 0;
      } else {
        if (cw < 0) {
          bit8 scalar0;
          scalar0 = x0;
          bit8 scalar1;
          scalar1 = y0;
          x0 = x11;
          y0 = y11;
          x11 = scalar0;
          y11 = scalar1;
        }
      }
      bit8 scalar2;
      scalar2 = 0;
      bit8 scalar3;
      scalar3 = 0;
      bit8 scalar4;
      scalar4 = 0;
      bit8 scalar5;
      scalar5 = 0;
      if (x0 < x11) {
        if (x21 < x0) {
          scalar2 = x21;
        } else {
          scalar2 = x0;
        }
      } else {
        if (x21 < x11) {
          scalar2 = x21;
        } else {
          scalar2 = x11;
        }
      }
      if (x11 < x0) {
        if (x0 < x21) {
          scalar3 = x21;
        } else {
          scalar3 = x0;
        }
      } else {
        if (x11 < x21) {
          scalar5 = y21;
        } else {
          scalar5 = y11;
        }
      }


      bit8 color;
      color = 100;
      bit8 scalar6 = 0;
      bit8 max_min_x = scalar3 - scalar2;
      bit8 max_index = max_min_x * (scalar5 - scalar4);
FIRST: for (int k = 0; k < max_index; k++)
      {
        #pragma HLS pipeline
        bit8 x7 = scalar2 + k%max_min_x;
        bit8 i = scalar4 + k/max_min_x;
        bit32 compute0;
        // #pragma HLS BIND_OP variable=compute0 op=mul  impl=DSP
        compute0 = ((x7 - x0) + scalar2) * (y11 - y0) - ((i - y0) + scalar4) * (x11 - x0);
        bit32 compute1;
        // #pragma HLS BIND_OP variable=compute1 op=mul  impl=DSP
        compute1 = ((x7 - x11) + scalar2) * (y21 - y11) - ((i - y11) + scalar4) * (x21 - x11);
        bit32 compute2;
        // #pragma HLS BIND_OP variable=compute2 op=mul  impl=DSP
        compute2 = ((x7 - x21) + scalar2) * (y0 - y21) - ((i - y21) + scalar4) * (x0 - x21);
        if (0 <= hls::min(hls::min(compute0, compute1), compute2)) {
          fragment[scalar6][0] = x7 + scalar2;
          fragment[scalar6][1] = i + scalar4;
          fragment[scalar6][2] = z;
          fragment[scalar6][3] = color;
          scalar6 = (scalar6 + 1);
        }
      }

      frag_cntr = scalar6;
      bit8 scalar7;
      scalar7 = 0;
ZCU: for (bit16 n = 0; n < frag_cntr; ++n) {
      #pragma HLS loop_tripcount min=0 max=446 avg=223
      #pragma HLS pipeline
        bit8 scalar8;
        scalar8 = fragment[n][0];
        bit8 scalar9;
        scalar9 = fragment[n][1];
        bit8 scalar10;
        scalar10 = fragment[n][2];
        bit8 scalar11;
        scalar11 = fragment[n][3];
        bit8 temp = z_buffer[(scalar9 * 256) + scalar8];
        if (scalar10 < temp) {
          pixels[scalar7][0] = scalar8;
          pixels[scalar7][1] = scalar9;
          pixels[scalar7][2] = scalar11;
          scalar7 = (scalar7 + 1);
          z_buffer[(scalar9 *256) + scalar8] = scalar10;
        }
      }
      size_pixels = scalar7;
OUTPUT: for (bit16 x8 = 0; x8 < size_pixels; ++x8) {
      #pragma HLS loop_tripcount min=0 max=446 avg=223
      #pragma HLS pipeline
        bit8 scalar12;
        scalar12 = pixels[x8][0];
        bit8 scalar13;
        scalar13 = pixels[x8][1];
        frame_buffer[(scalar12)][scalar13] = pixels[x8][2];
      }
    }

    // Output loop
    bit32 out_FB = 0;
    OUTPUT_FB_ROW: for ( ap_uint<16> i = 0; i < 256; i++) {
      #pragma HLS PIPELINE II=1
      for (ap_uint<16> j = 0; j < 256; j = j + 4) {
        out_FB( 7,  0) = frame_buffer[i][j + 0];
        out_FB(15,  8) = frame_buffer[i][j + 1];
        out_FB(23, 16) = frame_buffer[i][j + 2];
        out_FB(31, 24) = frame_buffer[i][j + 3];
        output[(i * 64) + (j /4)] = out_FB;
      }
    }
  }
}
