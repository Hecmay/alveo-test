// HASH:2610458785
#include "ihc_apint.h"
__kernel void test(__global int32_t* restrict input_image, __global int32_t* restrict fc) {
    int32_t _top;
    int32_t conv1_pad[3468];
    for (int32_t indices = 0; indices < 1; ++indices) {
      for (int32_t not_zero = 0; not_zero < 3; ++not_zero) {
        for (int32_t index_tuple = 0; index_tuple < 34; ++index_tuple) {
          for (int32_t i = 0; i < 34; ++i) {
            conv1_pad[(((i + (index_tuple * 34)) + (not_zero * 1156)) + (indices * 3468))] = (int32_t)(((((1 <= index_tuple) && (index_tuple < 33)) && (1 <= i)) && (i < 33)) ? ((int32_t)input_image[((((i + (index_tuple * 32)) + (not_zero * 1024)) + (indices * 3072)) + -33)]) : ((int32_t)0));
          }
        }
      }
    }
    int32_t conv1[16384];
    for (int32_t nn = 0; nn < 1; ++nn) {
      for (int32_t ff = 0; ff < 16; ++ff) {
        for (int32_t yy = 0; yy < 32; ++yy) {
          for (int32_t xx = 0; xx < 32; ++xx) {
            int32_t sum;
            for (int32_t rc = 0; rc < 3; ++rc) {
              for (int32_t ry = 0; ry < 3; ++ry) {
                for (int32_t rx = 0; rx < 3; ++rx) {
                  sum = ((int32_t)(((int64_t)(((int64_t)conv1_pad[((((xx + rx) + ((yy + ry) * 34)) + (rc * 1156)) + (nn * 3468))]) * ((int64_t)xx))) + ((int64_t)sum)));
                }
              }
            }
            conv1[(((xx + (yy * 32)) + (ff * 1024)) + (nn * 16384))] = sum;
          }
        }
      }
    }
    int32_t bn1[16384];
    for (int32_t x = 0; x < 1; ++x) {
      for (int32_t args0 = 0; args0 < 16; ++args0) {
        for (int32_t args1 = 0; args1 < 32; ++args1) {
          for (int32_t args2 = 0; args2 < 32; ++args2) {
            bn1[(((args2 + (args1 * 32)) + (args0 * 1024)) + (x * 16384))] = ((int32_t)(((int64_t)(((int64_t)conv1[(((args2 + (args1 * 32)) + (args0 * 1024)) + (x * 16384))]) * ((int64_t)args1))) + ((int64_t)args2)));
          }
        }
      }
    }
    bool layer1_0_rsign1[16384];
    for (int32_t nn1 = 0; nn1 < 1; ++nn1) {
      for (int32_t cc = 0; cc < 16; ++cc) {
        for (int32_t ww = 0; ww < 32; ++ww) {
          for (int32_t hh = 0; hh < 32; ++hh) {
            layer1_0_rsign1[(((hh + (ww * 32)) + (cc * 1024)) + (nn1 * 16384))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)bn1[(((hh + (ww * 32)) + (cc * 1024)) + (nn1 * 16384))]) + ((int33_t)ww)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer1_0_conv1_pad[18496];
    for (int32_t indices1 = 0; indices1 < 1; ++indices1) {
      for (int32_t not_zero1 = 0; not_zero1 < 16; ++not_zero1) {
        for (int32_t index_tuple1 = 0; index_tuple1 < 34; ++index_tuple1) {
          for (int32_t i1 = 0; i1 < 34; ++i1) {
            layer1_0_conv1_pad[(((i1 + (index_tuple1 * 34)) + (not_zero1 * 1156)) + (indices1 * 18496))] = (bool)(((((1 <= index_tuple1) && (index_tuple1 < 33)) && (1 <= i1)) && (i1 < 33)) ? ((bool)layer1_0_rsign1[((((i1 + (index_tuple1 * 32)) + (not_zero1 * 1024)) + (indices1 * 16384)) + -33)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer1_0_conv1[16384];
    for (int32_t nn2 = 0; nn2 < 1; ++nn2) {
      for (int32_t ff1 = 0; ff1 < 16; ++ff1) {
        for (int32_t yy1 = 0; yy1 < 32; ++yy1) {
          for (int32_t xx1 = 0; xx1 < 32; ++xx1) {
            int8_t layer1_0_conv1_sum;
            for (int32_t rc1 = 0; rc1 < 16; ++rc1) {
              for (int32_t ry1 = 0; ry1 < 3; ++ry1) {
                for (int32_t rx1 = 0; rx1 < 3; ++rx1) {
                  layer1_0_conv1_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx1)) <= ((int64_t)xx1)) && (((int64_t)xx1) < ((int64_t)33 - ((int64_t)rx1)))) && (((int64_t)1 - ((int64_t)ry1)) <= ((int64_t)yy1))) && (((int64_t)yy1) < ((int64_t)33 - ((int64_t)ry1)))) ? ((uint32_t)((((1U - ((uint32_t)layer1_0_conv1_pad[((((xx1 + rx1) + ((yy1 + ry1) * 34)) + (rc1 * 1156)) + (nn2 * 18496))])) ^ 0) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer1_0_conv1_sum)));
                }
              }
            }
            layer1_0_conv1[(((xx1 + (yy1 * 32)) + (ff1 * 1024)) + (nn2 * 16384))] = layer1_0_conv1_sum;
          }
        }
      }
    }
    int32_t layer1_0_bn1[16384];
    for (int32_t x1 = 0; x1 < 1; ++x1) {
      for (int32_t args01 = 0; args01 < 16; ++args01) {
        for (int32_t args11 = 0; args11 < 32; ++args11) {
          for (int32_t args21 = 0; args21 < 32; ++args21) {
            layer1_0_bn1[(((args21 + (args11 * 32)) + (args01 * 1024)) + (x1 * 16384))] = ((int32_t)(((int41_t)(((int64_t)layer1_0_conv1[(((args21 + (args11 * 32)) + (args01 * 1024)) + (x1 * 16384))]) * ((int40_t)args11))) + ((int41_t)args21)));
          }
        }
      }
    }
    int32_t layer1_0_residual1[16384];
    for (int32_t nn3 = 0; nn3 < 1; ++nn3) {
      for (int32_t cc1 = 0; cc1 < 16; ++cc1) {
        for (int32_t ww1 = 0; ww1 < 32; ++ww1) {
          for (int32_t hh1 = 0; hh1 < 32; ++hh1) {
            layer1_0_residual1[(((hh1 + (ww1 * 32)) + (cc1 * 1024)) + (nn3 * 16384))] = ((int32_t)(((int33_t)layer1_0_bn1[(((hh1 + (ww1 * 32)) + (cc1 * 1024)) + (nn3 * 16384))]) + ((int33_t)bn1[(((hh1 + (ww1 * 32)) + (cc1 * 1024)) + (nn3 * 16384))])));
          }
        }
      }
    }
    int32_t layer1_0_rprelu1[16384];
    for (int32_t nn4 = 0; nn4 < 1; ++nn4) {
      for (int32_t cc2 = 0; cc2 < 16; ++cc2) {
        for (int32_t ww2 = 0; ww2 < 32; ++ww2) {
          for (int32_t hh2 = 0; hh2 < 32; ++hh2) {
            layer1_0_rprelu1[(((hh2 + (ww2 * 32)) + (cc2 * 1024)) + (nn4 * 16384))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_0_residual1[(((hh2 + (ww2 * 32)) + (cc2 * 1024)) + (nn4 * 16384))]) + ((int33_t)hh2)))) ? (((int64_t)(((int33_t)layer1_0_residual1[(((hh2 + (ww2 * 32)) + (cc2 * 1024)) + (nn4 * 16384))]) + ((int33_t)ww2)))) : ((int64_t)(((int64_t)hh2) * ((int64_t)(((int33_t)layer1_0_residual1[(((hh2 + (ww2 * 32)) + (cc2 * 1024)) + (nn4 * 16384))]) + ((int33_t)ww2))))))) + ((int64_t)hh2)));
          }
        }
      }
    }
    bool layer1_0_rsign2[16384];
    for (int32_t nn5 = 0; nn5 < 1; ++nn5) {
      for (int32_t cc3 = 0; cc3 < 16; ++cc3) {
        for (int32_t ww3 = 0; ww3 < 32; ++ww3) {
          for (int32_t hh3 = 0; hh3 < 32; ++hh3) {
            layer1_0_rsign2[(((hh3 + (ww3 * 32)) + (cc3 * 1024)) + (nn5 * 16384))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_0_rprelu1[(((hh3 + (ww3 * 32)) + (cc3 * 1024)) + (nn5 * 16384))]) + ((int33_t)hh3)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer1_0_conv2_pad[18496];
    for (int32_t indices2 = 0; indices2 < 1; ++indices2) {
      for (int32_t not_zero2 = 0; not_zero2 < 16; ++not_zero2) {
        for (int32_t index_tuple2 = 0; index_tuple2 < 34; ++index_tuple2) {
          for (int32_t i2 = 0; i2 < 34; ++i2) {
            layer1_0_conv2_pad[(((i2 + (index_tuple2 * 34)) + (not_zero2 * 1156)) + (indices2 * 18496))] = (bool)(((((1 <= index_tuple2) && (index_tuple2 < 33)) && (1 <= i2)) && (i2 < 33)) ? ((bool)layer1_0_rsign2[((((i2 + (index_tuple2 * 32)) + (not_zero2 * 1024)) + (indices2 * 16384)) + -33)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer1_0_conv2[16384];
    for (int32_t nn6 = 0; nn6 < 1; ++nn6) {
      for (int32_t ff2 = 0; ff2 < 16; ++ff2) {
        for (int32_t yy2 = 0; yy2 < 32; ++yy2) {
          for (int32_t xx2 = 0; xx2 < 32; ++xx2) {
            int8_t layer1_0_conv2_sum;
            for (int32_t rc2 = 0; rc2 < 16; ++rc2) {
              for (int32_t ry2 = 0; ry2 < 3; ++ry2) {
                for (int32_t rx2 = 0; rx2 < 3; ++rx2) {
                  layer1_0_conv2_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx2)) <= ((int64_t)xx2)) && (((int64_t)xx2) < ((int64_t)33 - ((int64_t)rx2)))) && (((int64_t)1 - ((int64_t)ry2)) <= ((int64_t)yy2))) && (((int64_t)yy2) < ((int64_t)33 - ((int64_t)ry2)))) ? ((uint32_t)((((1U - ((uint32_t)layer1_0_conv2_pad[((((xx2 + rx2) + ((yy2 + ry2) * 34)) + (rc2 * 1156)) + (nn6 * 18496))])) ^ 0) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer1_0_conv2_sum)));
                }
              }
            }
            layer1_0_conv2[(((xx2 + (yy2 * 32)) + (ff2 * 1024)) + (nn6 * 16384))] = layer1_0_conv2_sum;
          }
        }
      }
    }
    int32_t layer1_0_bn2[16384];
    for (int32_t x2 = 0; x2 < 1; ++x2) {
      for (int32_t args02 = 0; args02 < 16; ++args02) {
        for (int32_t args12 = 0; args12 < 32; ++args12) {
          for (int32_t args22 = 0; args22 < 32; ++args22) {
            layer1_0_bn2[(((args22 + (args12 * 32)) + (args02 * 1024)) + (x2 * 16384))] = ((int32_t)(((int41_t)(((int64_t)layer1_0_conv2[(((args22 + (args12 * 32)) + (args02 * 1024)) + (x2 * 16384))]) * ((int40_t)args22))) + ((int41_t)args12)));
          }
        }
      }
    }
    int32_t layer1_0_residual2[16384];
    for (int32_t nn7 = 0; nn7 < 1; ++nn7) {
      for (int32_t cc4 = 0; cc4 < 16; ++cc4) {
        for (int32_t ww4 = 0; ww4 < 32; ++ww4) {
          for (int32_t hh4 = 0; hh4 < 32; ++hh4) {
            layer1_0_residual2[(((hh4 + (ww4 * 32)) + (cc4 * 1024)) + (nn7 * 16384))] = ((int32_t)(((int33_t)layer1_0_bn2[(((hh4 + (ww4 * 32)) + (cc4 * 1024)) + (nn7 * 16384))]) + ((int33_t)layer1_0_rprelu1[(((hh4 + (ww4 * 32)) + (cc4 * 1024)) + (nn7 * 16384))])));
          }
        }
      }
    }
    int32_t layer1_0_rprelu2[16384];
    for (int32_t nn8 = 0; nn8 < 1; ++nn8) {
      for (int32_t cc5 = 0; cc5 < 16; ++cc5) {
        for (int32_t ww5 = 0; ww5 < 32; ++ww5) {
          for (int32_t hh5 = 0; hh5 < 32; ++hh5) {
            layer1_0_rprelu2[(((hh5 + (ww5 * 32)) + (cc5 * 1024)) + (nn8 * 16384))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_0_residual2[(((hh5 + (ww5 * 32)) + (cc5 * 1024)) + (nn8 * 16384))]) + ((int33_t)hh5)))) ? (((int64_t)(((int33_t)layer1_0_residual2[(((hh5 + (ww5 * 32)) + (cc5 * 1024)) + (nn8 * 16384))]) + ((int33_t)ww5)))) : ((int64_t)(((int64_t)hh5) * ((int64_t)(((int33_t)layer1_0_residual2[(((hh5 + (ww5 * 32)) + (cc5 * 1024)) + (nn8 * 16384))]) + ((int33_t)ww5))))))) + ((int64_t)hh5)));
          }
        }
      }
    }
    bool layer1_1_rsign1[16384];
    for (int32_t nn9 = 0; nn9 < 1; ++nn9) {
      for (int32_t cc6 = 0; cc6 < 16; ++cc6) {
        for (int32_t ww6 = 0; ww6 < 32; ++ww6) {
          for (int32_t hh6 = 0; hh6 < 32; ++hh6) {
            layer1_1_rsign1[(((hh6 + (ww6 * 32)) + (cc6 * 1024)) + (nn9 * 16384))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_0_rprelu2[(((hh6 + (ww6 * 32)) + (cc6 * 1024)) + (nn9 * 16384))]) + ((int33_t)hh6)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer1_1_conv1_pad[18496];
    for (int32_t indices3 = 0; indices3 < 1; ++indices3) {
      for (int32_t not_zero3 = 0; not_zero3 < 16; ++not_zero3) {
        for (int32_t index_tuple3 = 0; index_tuple3 < 34; ++index_tuple3) {
          for (int32_t i3 = 0; i3 < 34; ++i3) {
            layer1_1_conv1_pad[(((i3 + (index_tuple3 * 34)) + (not_zero3 * 1156)) + (indices3 * 18496))] = (bool)(((((1 <= index_tuple3) && (index_tuple3 < 33)) && (1 <= i3)) && (i3 < 33)) ? ((bool)layer1_1_rsign1[((((i3 + (index_tuple3 * 32)) + (not_zero3 * 1024)) + (indices3 * 16384)) + -33)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer1_1_conv1[16384];
    for (int32_t nn10 = 0; nn10 < 1; ++nn10) {
      for (int32_t ff3 = 0; ff3 < 16; ++ff3) {
        for (int32_t yy3 = 0; yy3 < 32; ++yy3) {
          for (int32_t xx3 = 0; xx3 < 32; ++xx3) {
            int8_t layer1_1_conv1_sum;
            for (int32_t rc3 = 0; rc3 < 16; ++rc3) {
              for (int32_t ry3 = 0; ry3 < 3; ++ry3) {
                for (int32_t rx3 = 0; rx3 < 3; ++rx3) {
                  layer1_1_conv1_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx3)) <= ((int64_t)xx3)) && (((int64_t)xx3) < ((int64_t)33 - ((int64_t)rx3)))) && (((int64_t)1 - ((int64_t)ry3)) <= ((int64_t)yy3))) && (((int64_t)yy3) < ((int64_t)33 - ((int64_t)ry3)))) ? ((uint32_t)((((1U - ((uint32_t)layer1_1_conv1_pad[((((xx3 + rx3) + ((yy3 + ry3) * 34)) + (rc3 * 1156)) + (nn10 * 18496))])) ^ 0) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer1_1_conv1_sum)));
                }
              }
            }
            layer1_1_conv1[(((xx3 + (yy3 * 32)) + (ff3 * 1024)) + (nn10 * 16384))] = layer1_1_conv1_sum;
          }
        }
      }
    }
    int32_t layer1_1_bn1[16384];
    for (int32_t x3 = 0; x3 < 1; ++x3) {
      for (int32_t args03 = 0; args03 < 16; ++args03) {
        for (int32_t args13 = 0; args13 < 32; ++args13) {
          for (int32_t args23 = 0; args23 < 32; ++args23) {
            layer1_1_bn1[(((args23 + (args13 * 32)) + (args03 * 1024)) + (x3 * 16384))] = ((int32_t)(((int41_t)(((int64_t)layer1_1_conv1[(((args23 + (args13 * 32)) + (args03 * 1024)) + (x3 * 16384))]) * ((int40_t)args23))) + ((int41_t)args13)));
          }
        }
      }
    }
    int32_t layer1_1_residual1[16384];
    for (int32_t nn11 = 0; nn11 < 1; ++nn11) {
      for (int32_t cc7 = 0; cc7 < 16; ++cc7) {
        for (int32_t ww7 = 0; ww7 < 32; ++ww7) {
          for (int32_t hh7 = 0; hh7 < 32; ++hh7) {
            layer1_1_residual1[(((hh7 + (ww7 * 32)) + (cc7 * 1024)) + (nn11 * 16384))] = ((int32_t)(((int33_t)layer1_1_bn1[(((hh7 + (ww7 * 32)) + (cc7 * 1024)) + (nn11 * 16384))]) + ((int33_t)layer1_0_rprelu2[(((hh7 + (ww7 * 32)) + (cc7 * 1024)) + (nn11 * 16384))])));
          }
        }
      }
    }
    int32_t layer1_1_rprelu1[16384];
    for (int32_t nn12 = 0; nn12 < 1; ++nn12) {
      for (int32_t cc8 = 0; cc8 < 16; ++cc8) {
        for (int32_t ww8 = 0; ww8 < 32; ++ww8) {
          for (int32_t hh8 = 0; hh8 < 32; ++hh8) {
            layer1_1_rprelu1[(((hh8 + (ww8 * 32)) + (cc8 * 1024)) + (nn12 * 16384))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_1_residual1[(((hh8 + (ww8 * 32)) + (cc8 * 1024)) + (nn12 * 16384))]) + ((int33_t)ww8)))) ? (((int64_t)(((int33_t)layer1_1_residual1[(((hh8 + (ww8 * 32)) + (cc8 * 1024)) + (nn12 * 16384))]) + ((int33_t)hh8)))) : ((int64_t)(((int64_t)ww8) * ((int64_t)(((int33_t)layer1_1_residual1[(((hh8 + (ww8 * 32)) + (cc8 * 1024)) + (nn12 * 16384))]) + ((int33_t)hh8))))))) + ((int64_t)ww8)));
          }
        }
      }
    }
    bool layer1_1_rsign2[16384];
    for (int32_t nn13 = 0; nn13 < 1; ++nn13) {
      for (int32_t cc9 = 0; cc9 < 16; ++cc9) {
        for (int32_t ww9 = 0; ww9 < 32; ++ww9) {
          for (int32_t hh9 = 0; hh9 < 32; ++hh9) {
            layer1_1_rsign2[(((hh9 + (ww9 * 32)) + (cc9 * 1024)) + (nn13 * 16384))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_1_rprelu1[(((hh9 + (ww9 * 32)) + (cc9 * 1024)) + (nn13 * 16384))]) + ((int33_t)ww9)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer1_1_conv2_pad[18496];
    for (int32_t indices4 = 0; indices4 < 1; ++indices4) {
      for (int32_t not_zero4 = 0; not_zero4 < 16; ++not_zero4) {
        for (int32_t index_tuple4 = 0; index_tuple4 < 34; ++index_tuple4) {
          for (int32_t i4 = 0; i4 < 34; ++i4) {
            layer1_1_conv2_pad[(((i4 + (index_tuple4 * 34)) + (not_zero4 * 1156)) + (indices4 * 18496))] = (bool)(((((1 <= index_tuple4) && (index_tuple4 < 33)) && (1 <= i4)) && (i4 < 33)) ? ((bool)layer1_1_rsign2[((((i4 + (index_tuple4 * 32)) + (not_zero4 * 1024)) + (indices4 * 16384)) + -33)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer1_1_conv2[16384];
    for (int32_t nn14 = 0; nn14 < 1; ++nn14) {
      for (int32_t ff4 = 0; ff4 < 16; ++ff4) {
        for (int32_t yy4 = 0; yy4 < 32; ++yy4) {
          for (int32_t xx4 = 0; xx4 < 32; ++xx4) {
            int8_t layer1_1_conv2_sum;
            for (int32_t rc4 = 0; rc4 < 16; ++rc4) {
              for (int32_t ry4 = 0; ry4 < 3; ++ry4) {
                for (int32_t rx4 = 0; rx4 < 3; ++rx4) {
                  layer1_1_conv2_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx4)) <= ((int64_t)xx4)) && (((int64_t)xx4) < ((int64_t)33 - ((int64_t)rx4)))) && (((int64_t)1 - ((int64_t)ry4)) <= ((int64_t)yy4))) && (((int64_t)yy4) < ((int64_t)33 - ((int64_t)ry4)))) ? ((uint32_t)((((1U - ((uint32_t)layer1_1_conv2_pad[((((xx4 + rx4) + ((yy4 + ry4) * 34)) + (rc4 * 1156)) + (nn14 * 18496))])) ^ 0) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer1_1_conv2_sum)));
                }
              }
            }
            layer1_1_conv2[(((xx4 + (yy4 * 32)) + (ff4 * 1024)) + (nn14 * 16384))] = layer1_1_conv2_sum;
          }
        }
      }
    }
    int32_t layer1_1_bn2[16384];
    for (int32_t x4 = 0; x4 < 1; ++x4) {
      for (int32_t args04 = 0; args04 < 16; ++args04) {
        for (int32_t args14 = 0; args14 < 32; ++args14) {
          for (int32_t args24 = 0; args24 < 32; ++args24) {
            layer1_1_bn2[(((args24 + (args14 * 32)) + (args04 * 1024)) + (x4 * 16384))] = ((int32_t)(((int41_t)(((int64_t)layer1_1_conv2[(((args24 + (args14 * 32)) + (args04 * 1024)) + (x4 * 16384))]) * ((int40_t)args14))) + ((int41_t)args24)));
          }
        }
      }
    }
    int32_t layer1_1_residual2[16384];
    for (int32_t nn15 = 0; nn15 < 1; ++nn15) {
      for (int32_t cc10 = 0; cc10 < 16; ++cc10) {
        for (int32_t ww10 = 0; ww10 < 32; ++ww10) {
          for (int32_t hh10 = 0; hh10 < 32; ++hh10) {
            layer1_1_residual2[(((hh10 + (ww10 * 32)) + (cc10 * 1024)) + (nn15 * 16384))] = ((int32_t)(((int33_t)layer1_1_bn2[(((hh10 + (ww10 * 32)) + (cc10 * 1024)) + (nn15 * 16384))]) + ((int33_t)layer1_1_rprelu1[(((hh10 + (ww10 * 32)) + (cc10 * 1024)) + (nn15 * 16384))])));
          }
        }
      }
    }
    int32_t layer1_1_rprelu2[16384];
    for (int32_t nn16 = 0; nn16 < 1; ++nn16) {
      for (int32_t cc11 = 0; cc11 < 16; ++cc11) {
        for (int32_t ww11 = 0; ww11 < 32; ++ww11) {
          for (int32_t hh11 = 0; hh11 < 32; ++hh11) {
            layer1_1_rprelu2[(((hh11 + (ww11 * 32)) + (cc11 * 1024)) + (nn16 * 16384))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_1_residual2[(((hh11 + (ww11 * 32)) + (cc11 * 1024)) + (nn16 * 16384))]) + ((int33_t)ww11)))) ? (((int64_t)(((int33_t)layer1_1_residual2[(((hh11 + (ww11 * 32)) + (cc11 * 1024)) + (nn16 * 16384))]) + ((int33_t)hh11)))) : ((int64_t)(((int64_t)ww11) * ((int64_t)(((int33_t)layer1_1_residual2[(((hh11 + (ww11 * 32)) + (cc11 * 1024)) + (nn16 * 16384))]) + ((int33_t)hh11))))))) + ((int64_t)ww11)));
          }
        }
      }
    }
    bool layer1_2_rsign1[16384];
    for (int32_t nn17 = 0; nn17 < 1; ++nn17) {
      for (int32_t cc12 = 0; cc12 < 16; ++cc12) {
        for (int32_t ww12 = 0; ww12 < 32; ++ww12) {
          for (int32_t hh12 = 0; hh12 < 32; ++hh12) {
            layer1_2_rsign1[(((hh12 + (ww12 * 32)) + (cc12 * 1024)) + (nn17 * 16384))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_1_rprelu2[(((hh12 + (ww12 * 32)) + (cc12 * 1024)) + (nn17 * 16384))]) + ((int33_t)ww12)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer1_2_conv1_pad[18496];
    for (int32_t indices5 = 0; indices5 < 1; ++indices5) {
      for (int32_t not_zero5 = 0; not_zero5 < 16; ++not_zero5) {
        for (int32_t index_tuple5 = 0; index_tuple5 < 34; ++index_tuple5) {
          for (int32_t i5 = 0; i5 < 34; ++i5) {
            layer1_2_conv1_pad[(((i5 + (index_tuple5 * 34)) + (not_zero5 * 1156)) + (indices5 * 18496))] = (bool)(((((1 <= index_tuple5) && (index_tuple5 < 33)) && (1 <= i5)) && (i5 < 33)) ? ((bool)layer1_2_rsign1[((((i5 + (index_tuple5 * 32)) + (not_zero5 * 1024)) + (indices5 * 16384)) + -33)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer1_2_conv1[16384];
    for (int32_t nn18 = 0; nn18 < 1; ++nn18) {
      for (int32_t ff5 = 0; ff5 < 16; ++ff5) {
        for (int32_t yy5 = 0; yy5 < 32; ++yy5) {
          for (int32_t xx5 = 0; xx5 < 32; ++xx5) {
            int8_t layer1_2_conv1_sum;
            for (int32_t rc5 = 0; rc5 < 16; ++rc5) {
              for (int32_t ry5 = 0; ry5 < 3; ++ry5) {
                for (int32_t rx5 = 0; rx5 < 3; ++rx5) {
                  layer1_2_conv1_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx5)) <= ((int64_t)xx5)) && (((int64_t)xx5) < ((int64_t)33 - ((int64_t)rx5)))) && (((int64_t)1 - ((int64_t)ry5)) <= ((int64_t)yy5))) && (((int64_t)yy5) < ((int64_t)33 - ((int64_t)ry5)))) ? ((uint32_t)((((1U - ((uint32_t)layer1_2_conv1_pad[((((xx5 + rx5) + ((yy5 + ry5) * 34)) + (rc5 * 1156)) + (nn18 * 18496))])) ^ 1) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer1_2_conv1_sum)));
                }
              }
            }
            layer1_2_conv1[(((xx5 + (yy5 * 32)) + (ff5 * 1024)) + (nn18 * 16384))] = layer1_2_conv1_sum;
          }
        }
      }
    }
    int32_t layer1_2_bn1[16384];
    for (int32_t x5 = 0; x5 < 1; ++x5) {
      for (int32_t args05 = 0; args05 < 16; ++args05) {
        for (int32_t args15 = 0; args15 < 32; ++args15) {
          for (int32_t args25 = 0; args25 < 32; ++args25) {
            layer1_2_bn1[(((args25 + (args15 * 32)) + (args05 * 1024)) + (x5 * 16384))] = ((int32_t)(((int41_t)(((int64_t)layer1_2_conv1[(((args25 + (args15 * 32)) + (args05 * 1024)) + (x5 * 16384))]) * ((int40_t)args15))) + ((int41_t)args25)));
          }
        }
      }
    }
    int32_t layer1_2_residual1[16384];
    for (int32_t nn19 = 0; nn19 < 1; ++nn19) {
      for (int32_t cc13 = 0; cc13 < 16; ++cc13) {
        for (int32_t ww13 = 0; ww13 < 32; ++ww13) {
          for (int32_t hh13 = 0; hh13 < 32; ++hh13) {
            layer1_2_residual1[(((hh13 + (ww13 * 32)) + (cc13 * 1024)) + (nn19 * 16384))] = ((int32_t)(((int33_t)layer1_2_bn1[(((hh13 + (ww13 * 32)) + (cc13 * 1024)) + (nn19 * 16384))]) + ((int33_t)layer1_1_rprelu2[(((hh13 + (ww13 * 32)) + (cc13 * 1024)) + (nn19 * 16384))])));
          }
        }
      }
    }
    int32_t layer1_2_rprelu1[16384];
    for (int32_t nn20 = 0; nn20 < 1; ++nn20) {
      for (int32_t cc14 = 0; cc14 < 16; ++cc14) {
        for (int32_t ww14 = 0; ww14 < 32; ++ww14) {
          for (int32_t hh14 = 0; hh14 < 32; ++hh14) {
            layer1_2_rprelu1[(((hh14 + (ww14 * 32)) + (cc14 * 1024)) + (nn20 * 16384))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_2_residual1[(((hh14 + (ww14 * 32)) + (cc14 * 1024)) + (nn20 * 16384))]) + ((int33_t)ww14)))) ? (((int64_t)(((int33_t)layer1_2_residual1[(((hh14 + (ww14 * 32)) + (cc14 * 1024)) + (nn20 * 16384))]) + ((int33_t)hh14)))) : ((int64_t)(((int64_t)ww14) * ((int64_t)(((int33_t)layer1_2_residual1[(((hh14 + (ww14 * 32)) + (cc14 * 1024)) + (nn20 * 16384))]) + ((int33_t)hh14))))))) + ((int64_t)ww14)));
          }
        }
      }
    }
    bool layer1_2_rsign2[16384];
    for (int32_t nn21 = 0; nn21 < 1; ++nn21) {
      for (int32_t cc15 = 0; cc15 < 16; ++cc15) {
        for (int32_t ww15 = 0; ww15 < 32; ++ww15) {
          for (int32_t hh15 = 0; hh15 < 32; ++hh15) {
            layer1_2_rsign2[(((hh15 + (ww15 * 32)) + (cc15 * 1024)) + (nn21 * 16384))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_2_rprelu1[(((hh15 + (ww15 * 32)) + (cc15 * 1024)) + (nn21 * 16384))]) + ((int33_t)ww15)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer1_2_conv2_pad[18496];
    for (int32_t indices6 = 0; indices6 < 1; ++indices6) {
      for (int32_t not_zero6 = 0; not_zero6 < 16; ++not_zero6) {
        for (int32_t index_tuple6 = 0; index_tuple6 < 34; ++index_tuple6) {
          for (int32_t i6 = 0; i6 < 34; ++i6) {
            layer1_2_conv2_pad[(((i6 + (index_tuple6 * 34)) + (not_zero6 * 1156)) + (indices6 * 18496))] = (bool)(((((1 <= index_tuple6) && (index_tuple6 < 33)) && (1 <= i6)) && (i6 < 33)) ? ((bool)layer1_2_rsign2[((((i6 + (index_tuple6 * 32)) + (not_zero6 * 1024)) + (indices6 * 16384)) + -33)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer1_2_conv2[16384];
    for (int32_t nn22 = 0; nn22 < 1; ++nn22) {
      for (int32_t ff6 = 0; ff6 < 16; ++ff6) {
        for (int32_t yy6 = 0; yy6 < 32; ++yy6) {
          for (int32_t xx6 = 0; xx6 < 32; ++xx6) {
            int8_t layer1_2_conv2_sum;
            for (int32_t rc6 = 0; rc6 < 16; ++rc6) {
              for (int32_t ry6 = 0; ry6 < 3; ++ry6) {
                for (int32_t rx6 = 0; rx6 < 3; ++rx6) {
                  layer1_2_conv2_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx6)) <= ((int64_t)xx6)) && (((int64_t)xx6) < ((int64_t)33 - ((int64_t)rx6)))) && (((int64_t)1 - ((int64_t)ry6)) <= ((int64_t)yy6))) && (((int64_t)yy6) < ((int64_t)33 - ((int64_t)ry6)))) ? ((uint32_t)((((1U - ((uint32_t)layer1_2_conv2_pad[((((xx6 + rx6) + ((yy6 + ry6) * 34)) + (rc6 * 1156)) + (nn22 * 18496))])) ^ 1) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer1_2_conv2_sum)));
                }
              }
            }
            layer1_2_conv2[(((xx6 + (yy6 * 32)) + (ff6 * 1024)) + (nn22 * 16384))] = layer1_2_conv2_sum;
          }
        }
      }
    }
    int32_t layer1_2_bn2[16384];
    for (int32_t x6 = 0; x6 < 1; ++x6) {
      for (int32_t args06 = 0; args06 < 16; ++args06) {
        for (int32_t args16 = 0; args16 < 32; ++args16) {
          for (int32_t args26 = 0; args26 < 32; ++args26) {
            layer1_2_bn2[(((args26 + (args16 * 32)) + (args06 * 1024)) + (x6 * 16384))] = ((int32_t)(((int41_t)(((int64_t)layer1_2_conv2[(((args26 + (args16 * 32)) + (args06 * 1024)) + (x6 * 16384))]) * ((int40_t)args16))) + ((int41_t)args26)));
          }
        }
      }
    }
    int32_t layer1_2_residual2[16384];
    for (int32_t nn23 = 0; nn23 < 1; ++nn23) {
      for (int32_t cc16 = 0; cc16 < 16; ++cc16) {
        for (int32_t ww16 = 0; ww16 < 32; ++ww16) {
          for (int32_t hh16 = 0; hh16 < 32; ++hh16) {
            layer1_2_residual2[(((hh16 + (ww16 * 32)) + (cc16 * 1024)) + (nn23 * 16384))] = ((int32_t)(((int33_t)layer1_2_bn2[(((hh16 + (ww16 * 32)) + (cc16 * 1024)) + (nn23 * 16384))]) + ((int33_t)layer1_2_rprelu1[(((hh16 + (ww16 * 32)) + (cc16 * 1024)) + (nn23 * 16384))])));
          }
        }
      }
    }
    int32_t layer1_2_rprelu2[16384];
    for (int32_t nn24 = 0; nn24 < 1; ++nn24) {
      for (int32_t cc17 = 0; cc17 < 16; ++cc17) {
        for (int32_t ww17 = 0; ww17 < 32; ++ww17) {
          for (int32_t hh17 = 0; hh17 < 32; ++hh17) {
            layer1_2_rprelu2[(((hh17 + (ww17 * 32)) + (cc17 * 1024)) + (nn24 * 16384))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_2_residual2[(((hh17 + (ww17 * 32)) + (cc17 * 1024)) + (nn24 * 16384))]) + ((int33_t)ww17)))) ? (((int64_t)(((int33_t)layer1_2_residual2[(((hh17 + (ww17 * 32)) + (cc17 * 1024)) + (nn24 * 16384))]) + ((int33_t)hh17)))) : ((int64_t)(((int64_t)ww17) * ((int64_t)(((int33_t)layer1_2_residual2[(((hh17 + (ww17 * 32)) + (cc17 * 1024)) + (nn24 * 16384))]) + ((int33_t)hh17))))))) + ((int64_t)ww17)));
          }
        }
      }
    }
    bool layer2_0_rsign1[16384];
    for (int32_t nn25 = 0; nn25 < 1; ++nn25) {
      for (int32_t cc18 = 0; cc18 < 16; ++cc18) {
        for (int32_t ww18 = 0; ww18 < 32; ++ww18) {
          for (int32_t hh18 = 0; hh18 < 32; ++hh18) {
            layer2_0_rsign1[(((hh18 + (ww18 * 32)) + (cc18 * 1024)) + (nn25 * 16384))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer1_2_rprelu2[(((hh18 + (ww18 * 32)) + (cc18 * 1024)) + (nn25 * 16384))]) + ((int33_t)hh18)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer2_0_conv1_pad[18496];
    for (int32_t indices7 = 0; indices7 < 1; ++indices7) {
      for (int32_t not_zero7 = 0; not_zero7 < 16; ++not_zero7) {
        for (int32_t index_tuple7 = 0; index_tuple7 < 34; ++index_tuple7) {
          for (int32_t i7 = 0; i7 < 34; ++i7) {
            layer2_0_conv1_pad[(((i7 + (index_tuple7 * 34)) + (not_zero7 * 1156)) + (indices7 * 18496))] = (bool)(((((1 <= index_tuple7) && (index_tuple7 < 33)) && (1 <= i7)) && (i7 < 33)) ? ((bool)layer2_0_rsign1[((((i7 + (index_tuple7 * 32)) + (not_zero7 * 1024)) + (indices7 * 16384)) + -33)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer2_0_conv1[8192];
    for (int32_t nn26 = 0; nn26 < 1; ++nn26) {
      for (int32_t ff7 = 0; ff7 < 32; ++ff7) {
        for (int32_t yy7 = 0; yy7 < 16; ++yy7) {
          for (int32_t xx7 = 0; xx7 < 16; ++xx7) {
            int8_t layer2_0_conv1_sum;
            for (int32_t rc7 = 0; rc7 < 16; ++rc7) {
              for (int32_t ry7 = 0; ry7 < 3; ++ry7) {
                for (int32_t rx7 = 0; rx7 < 3; ++rx7) {
                  layer2_0_conv1_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx7)) <= ((int64_t)(xx7 * 2))) && (((int64_t)(xx7 * 2)) < ((int64_t)33 - ((int64_t)rx7)))) && (((int64_t)1 - ((int64_t)ry7)) <= ((int64_t)(yy7 * 2)))) && (((int64_t)(yy7 * 2)) < ((int64_t)33 - ((int64_t)ry7)))) ? ((uint32_t)((((1U - ((uint32_t)layer2_0_conv1_pad[(((((xx7 * 2) + rx7) + (((yy7 * 2) + ry7) * 34)) + (rc7 * 1156)) + (nn26 * 18496))])) ^ 0) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer2_0_conv1_sum)));
                }
              }
            }
            layer2_0_conv1[(((xx7 + (yy7 * 16)) + (ff7 * 256)) + (nn26 * 8192))] = layer2_0_conv1_sum;
          }
        }
      }
    }
    int32_t layer2_0_bn1[8192];
    for (int32_t x7 = 0; x7 < 1; ++x7) {
      for (int32_t args07 = 0; args07 < 32; ++args07) {
        for (int32_t args17 = 0; args17 < 16; ++args17) {
          for (int32_t args27 = 0; args27 < 16; ++args27) {
            layer2_0_bn1[(((args27 + (args17 * 16)) + (args07 * 256)) + (x7 * 8192))] = ((int32_t)(((int41_t)(((int64_t)layer2_0_conv1[(((args27 + (args17 * 16)) + (args07 * 256)) + (x7 * 8192))]) * ((int40_t)args27))) + ((int41_t)args17)));
          }
        }
      }
    }
    int32_t layer2_0_avgpool_res[4096];
    int32_t layer2_0_avgpool_LB[64];
    int32_t layer2_0_avgpool;
    for (int32_t ii = 0; ii < 1; ++ii) {
      for (int32_t cc19 = 0; cc19 < 16; ++cc19) {
        for (int32_t hh19 = 0; hh19 < 16; ++hh19) {
          for (int32_t layer2_0_avgpool_LB_i = 0; layer2_0_avgpool_LB_i < 2; ++layer2_0_avgpool_LB_i) {
            for (int32_t layer2_0_avgpool_LB_j = 0; layer2_0_avgpool_LB_j < 32; ++layer2_0_avgpool_LB_j) {
              layer2_0_avgpool_LB[(layer2_0_avgpool_LB_j + (layer2_0_avgpool_LB_i * 32))] = layer1_2_rprelu2[(((layer2_0_avgpool_LB_j + (((hh19 * 2) + layer2_0_avgpool_LB_i) * 32)) + (cc19 * 1024)) + (ii * 16384))];
            }
          }
          for (int32_t layer2_0_avgpool_ww = 0; layer2_0_avgpool_ww < 16; ++layer2_0_avgpool_ww) {
            int32_t layer2_0_avgpool_val;
            for (int32_t layer2_0_avgpool_ry = 0; layer2_0_avgpool_ry < 2; ++layer2_0_avgpool_ry) {
              for (int32_t layer2_0_avgpool_rx = 0; layer2_0_avgpool_rx < 2; ++layer2_0_avgpool_rx) {
                layer2_0_avgpool_val = ((int32_t)(((int33_t)layer2_0_avgpool_val) + ((int33_t)layer2_0_avgpool_LB[(((layer2_0_avgpool_ww * 2) + layer2_0_avgpool_rx) + (layer2_0_avgpool_ry * 32))])));
              }
            }
            layer2_0_avgpool_res[(((layer2_0_avgpool_ww + (hh19 * 16)) + (cc19 * 256)) + (ii * 4096))] = ((int32_t)(((int64_t)layer2_0_avgpool_val) / (int64_t)4));
          }
        }
      }
    }
    int32_t layer2_0_concat[8192];
    for (int32_t nn27 = 0; nn27 < 1; ++nn27) {
      for (int32_t cc20 = 0; cc20 < 32; ++cc20) {
        for (int32_t ww19 = 0; ww19 < 16; ++ww19) {
          for (int32_t hh20 = 0; hh20 < 16; ++hh20) {
            layer2_0_concat[(((hh20 + (ww19 * 16)) + (cc20 * 256)) + (nn27 * 8192))] = layer2_0_avgpool_res[(((hh20 + (ww19 * 16)) + ((cc20 % 16) * 256)) + (nn27 * 4096))];
          }
        }
      }
    }
    int32_t layer2_0_residual1[8192];
    for (int32_t nn28 = 0; nn28 < 1; ++nn28) {
      for (int32_t cc21 = 0; cc21 < 32; ++cc21) {
        for (int32_t ww20 = 0; ww20 < 16; ++ww20) {
          for (int32_t hh21 = 0; hh21 < 16; ++hh21) {
            layer2_0_residual1[(((hh21 + (ww20 * 16)) + (cc21 * 256)) + (nn28 * 8192))] = ((int32_t)(((int33_t)layer2_0_bn1[(((hh21 + (ww20 * 16)) + (cc21 * 256)) + (nn28 * 8192))]) + ((int33_t)layer2_0_concat[(((hh21 + (ww20 * 16)) + (cc21 * 256)) + (nn28 * 8192))])));
          }
        }
      }
    }
    int32_t layer2_0_rprelu1[8192];
    for (int32_t nn29 = 0; nn29 < 1; ++nn29) {
      for (int32_t cc22 = 0; cc22 < 32; ++cc22) {
        for (int32_t ww21 = 0; ww21 < 16; ++ww21) {
          for (int32_t hh22 = 0; hh22 < 16; ++hh22) {
            layer2_0_rprelu1[(((hh22 + (ww21 * 16)) + (cc22 * 256)) + (nn29 * 8192))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_0_residual1[(((hh22 + (ww21 * 16)) + (cc22 * 256)) + (nn29 * 8192))]) + ((int33_t)ww21)))) ? (((int64_t)(((int33_t)layer2_0_residual1[(((hh22 + (ww21 * 16)) + (cc22 * 256)) + (nn29 * 8192))]) + ((int33_t)hh22)))) : ((int64_t)(((int64_t)cc22) * ((int64_t)(((int33_t)layer2_0_residual1[(((hh22 + (ww21 * 16)) + (cc22 * 256)) + (nn29 * 8192))]) + ((int33_t)hh22))))))) + ((int64_t)ww21)));
          }
        }
      }
    }
    bool layer2_0_rsign2[8192];
    for (int32_t nn30 = 0; nn30 < 1; ++nn30) {
      for (int32_t cc23 = 0; cc23 < 32; ++cc23) {
        for (int32_t ww22 = 0; ww22 < 16; ++ww22) {
          for (int32_t hh23 = 0; hh23 < 16; ++hh23) {
            layer2_0_rsign2[(((hh23 + (ww22 * 16)) + (cc23 * 256)) + (nn30 * 8192))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_0_rprelu1[(((hh23 + (ww22 * 16)) + (cc23 * 256)) + (nn30 * 8192))]) + ((int33_t)256)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer2_0_conv2_pad[10368];
    for (int32_t indices8 = 0; indices8 < 1; ++indices8) {
      for (int32_t not_zero8 = 0; not_zero8 < 32; ++not_zero8) {
        for (int32_t index_tuple8 = 0; index_tuple8 < 18; ++index_tuple8) {
          for (int32_t i8 = 0; i8 < 18; ++i8) {
            layer2_0_conv2_pad[(((i8 + (index_tuple8 * 18)) + (not_zero8 * 324)) + (indices8 * 10368))] = (bool)(((((1 <= index_tuple8) && (index_tuple8 < 17)) && (1 <= i8)) && (i8 < 17)) ? ((bool)layer2_0_rsign2[((((i8 + (index_tuple8 * 16)) + (not_zero8 * 256)) + (indices8 * 8192)) + -17)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer2_0_conv2[8192];
    for (int32_t nn31 = 0; nn31 < 1; ++nn31) {
      for (int32_t ff8 = 0; ff8 < 32; ++ff8) {
        for (int32_t yy8 = 0; yy8 < 16; ++yy8) {
          for (int32_t xx8 = 0; xx8 < 16; ++xx8) {
            int8_t layer2_0_conv2_sum;
            for (int32_t rc8 = 0; rc8 < 32; ++rc8) {
              for (int32_t ry8 = 0; ry8 < 3; ++ry8) {
                for (int32_t rx8 = 0; rx8 < 3; ++rx8) {
                  layer2_0_conv2_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx8)) <= ((int64_t)xx8)) && (((int64_t)xx8) < ((int64_t)17 - ((int64_t)rx8)))) && (((int64_t)1 - ((int64_t)ry8)) <= ((int64_t)yy8))) && (((int64_t)yy8) < ((int64_t)17 - ((int64_t)ry8)))) ? ((uint32_t)((((1U - ((uint32_t)layer2_0_conv2_pad[((((xx8 + rx8) + ((yy8 + ry8) * 18)) + (rc8 * 324)) + (nn31 * 10368))])) ^ 0) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer2_0_conv2_sum)));
                }
              }
            }
            layer2_0_conv2[(((xx8 + (yy8 * 16)) + (ff8 * 256)) + (nn31 * 8192))] = layer2_0_conv2_sum;
          }
        }
      }
    }
    int32_t layer2_0_bn2[8192];
    for (int32_t x8 = 0; x8 < 1; ++x8) {
      for (int32_t args08 = 0; args08 < 32; ++args08) {
        for (int32_t args18 = 0; args18 < 16; ++args18) {
          for (int32_t args28 = 0; args28 < 16; ++args28) {
            layer2_0_bn2[(((args28 + (args18 * 16)) + (args08 * 256)) + (x8 * 8192))] = ((int32_t)(((int41_t)(((int64_t)layer2_0_conv2[(((args28 + (args18 * 16)) + (args08 * 256)) + (x8 * 8192))]) * ((int40_t)args18))) + ((int41_t)args28)));
          }
        }
      }
    }
    int32_t layer2_0_residual2[8192];
    for (int32_t nn32 = 0; nn32 < 1; ++nn32) {
      for (int32_t cc24 = 0; cc24 < 32; ++cc24) {
        for (int32_t ww23 = 0; ww23 < 16; ++ww23) {
          for (int32_t hh24 = 0; hh24 < 16; ++hh24) {
            layer2_0_residual2[(((hh24 + (ww23 * 16)) + (cc24 * 256)) + (nn32 * 8192))] = ((int32_t)(((int33_t)layer2_0_bn2[(((hh24 + (ww23 * 16)) + (cc24 * 256)) + (nn32 * 8192))]) + ((int33_t)layer2_0_rprelu1[(((hh24 + (ww23 * 16)) + (cc24 * 256)) + (nn32 * 8192))])));
          }
        }
      }
    }
    int32_t layer2_0_rprelu2[8192];
    for (int32_t nn33 = 0; nn33 < 1; ++nn33) {
      for (int32_t cc25 = 0; cc25 < 32; ++cc25) {
        for (int32_t ww24 = 0; ww24 < 16; ++ww24) {
          for (int32_t hh25 = 0; hh25 < 16; ++hh25) {
            layer2_0_rprelu2[(((hh25 + (ww24 * 16)) + (cc25 * 256)) + (nn33 * 8192))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_0_residual2[(((hh25 + (ww24 * 16)) + (cc25 * 256)) + (nn33 * 8192))]) + ((int33_t)ww24)))) ? (((int64_t)(((int33_t)layer2_0_residual2[(((hh25 + (ww24 * 16)) + (cc25 * 256)) + (nn33 * 8192))]) + ((int33_t)h25)))) : ((int64_t)(((int64_t)hh25) * ((int64_t)(((int33_t)layer2_0_residual2[(((hh25 + (ww24 * 16)) + (cc25 * 256)) + (nn33 * 8192))]) + ((int33_t)ww24))))))) + ((int64_t)hh25)));
          }
        }
      }
    }
    bool layer2_1_rsign1[8192];
    for (int32_t nn34 = 0; nn34 < 1; ++nn34) {
      for (int32_t cc26 = 0; cc26 < 32; ++cc26) {
        for (int32_t ww25 = 0; ww25 < 16; ++ww25) {
          for (int32_t hh26 = 0; hh26 < 16; ++hh26) {
            layer2_1_rsign1[(((hh26 + (ww25 * 16)) + (cc26 * 256)) + (nn34 * 8192))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_0_rprelu2[(((hh26 + (ww25 * 16)) + (cc26 * 256)) + (nn34 * 8192))]) + ((int33_t)256)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer2_1_conv1_pad[10368];
    for (int32_t indices9 = 0; indices9 < 1; ++indices9) {
      for (int32_t not_zero9 = 0; not_zero9 < 32; ++not_zero9) {
        for (int32_t index_tuple9 = 0; index_tuple9 < 18; ++index_tuple9) {
          for (int32_t i9 = 0; i9 < 18; ++i9) {
            layer2_1_conv1_pad[(((i9 + (index_tuple9 * 18)) + (not_zero9 * 324)) + (indices9 * 10368))] = (bool)(((((1 <= index_tuple9) && (index_tuple9 < 17)) && (1 <= i9)) && (i9 < 17)) ? ((bool)layer2_1_rsign1[((((i9 + (index_tuple9 * 16)) + (not_zero9 * 256)) + (indices9 * 8192)) + -17)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer2_1_conv1[8192];
    for (int32_t nn35 = 0; nn35 < 1; ++nn35) {
      for (int32_t ff9 = 0; ff9 < 32; ++ff9) {
        for (int32_t yy9 = 0; yy9 < 16; ++yy9) {
          for (int32_t xx9 = 0; xx9 < 16; ++xx9) {
            int8_t layer2_1_conv1_sum;
            for (int32_t rc9 = 0; rc9 < 32; ++rc9) {
              for (int32_t ry9 = 0; ry9 < 3; ++ry9) {
                for (int32_t rx9 = 0; rx9 < 3; ++rx9) {
                  layer2_1_conv1_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx9)) <= ((int64_t)xx9)) && (((int64_t)xx9) < ((int64_t)17 - ((int64_t)rx9)))) && (((int64_t)1 - ((int64_t)ry9)) <= ((int64_t)yy9))) && (((int64_t)yy9) < ((int64_t)17 - ((int64_t)ry9)))) ? ((uint32_t)((((1U - ((uint32_t)layer2_1_conv1_pad[((((xx9 + rx9) + ((yy9 + ry9) * 18)) + (rc9 * 324)) + (nn35 * 10368))])) ^ 1) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer2_1_conv1_sum)));
                }
              }
            }
            layer2_1_conv1[(((xx9 + (yy9 * 16)) + (ff9 * 256)) + (nn35 * 8192))] = layer2_1_conv1_sum;
          }
        }
      }
    }
    int32_t layer2_1_bn1[8192];
    for (int32_t x9 = 0; x9 < 1; ++x9) {
      for (int32_t args09 = 0; args09 < 32; ++args09) {
        for (int32_t args19 = 0; args19 < 16; ++args19) {
          for (int32_t args29 = 0; args29 < 16; ++args29) {
            layer2_1_bn1[(((args29 + (args19 * 16)) + (args09 * 256)) + (x9 * 8192))] = ((int32_t)(((int41_t)(((int64_t)layer2_1_conv1[(((args29 + (args19 * 16)) + (args09 * 256)) + (x9 * 8192))]) * ((int40_t)args19))) + ((int41_t)args29)));
          }
        }
      }
    }
    int32_t layer2_1_residual1[8192];
    for (int32_t nn36 = 0; nn36 < 1; ++nn36) {
      for (int32_t cc27 = 0; cc27 < 32; ++cc27) {
        for (int32_t ww26 = 0; ww26 < 16; ++ww26) {
          for (int32_t hh27 = 0; hh27 < 16; ++hh27) {
            layer2_1_residual1[(((hh27 + (ww26 * 16)) + (cc27 * 256)) + (nn36 * 8192))] = ((int32_t)(((int33_t)layer2_1_bn1[(((hh27 + (ww26 * 16)) + (cc27 * 256)) + (nn36 * 8192))]) + ((int33_t)layer2_0_rprelu2[(((hh27 + (ww26 * 16)) + (cc27 * 256)) + (nn36 * 8192))])));
          }
        }
      }
    }
    int32_t layer2_1_rprelu1[8192];
    for (int32_t nn37 = 0; nn37 < 1; ++nn37) {
      for (int32_t cc28 = 0; cc28 < 32; ++cc28) {
        for (int32_t ww27 = 0; ww27 < 16; ++ww27) {
          for (int32_t hh28 = 0; hh28 < 16; ++hh28) {
            layer2_1_rprelu1[(((hh28 + (ww27 * 16)) + (cc28 * 256)) + (nn37 * 8192))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_1_residual1[(((hh28 + (ww27 * 16)) + (cc28 * 256)) + (nn37 * 8192))]) + ((int33_t)hh28)))) ? (((int64_t)(((int33_t)layer2_1_residual1[(((hh28 + (ww27 * 16)) + (cc28 * 256)) + (nn37 * 8192))]) + ((int33_t)hh28)))) : ((int64_t)(((int64_t)ww27) * ((int64_t)(((int33_t)layer2_1_residual1[(((hh28 + (ww27 * 16)) + (cc28 * 256)) + (nn37 * 8192))]) + ((int33_t)hh28))))))) + ((int64_t)ww27)));
          }
        }
      }
    }
    bool layer2_1_rsign2[8192];
    for (int32_t nn38 = 0; nn38 < 1; ++nn38) {
      for (int32_t cc29 = 0; cc29 < 32; ++cc29) {
        for (int32_t ww28 = 0; ww28 < 16; ++ww28) {
          for (int32_t hh29 = 0; hh29 < 16; ++hh29) {
            layer2_1_rsign2[(((hh29 + (ww28 * 16)) + (cc29 * 256)) + (nn38 * 8192))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_1_rprelu1[(((hh29 + (ww28 * 16)) + (cc29 * 256)) + (nn38 * 8192))]) + ((int33_t)hh29)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer2_1_conv2_pad[10368];
    for (int32_t indices10 = 0; indices10 < 1; ++indices10) {
      for (int32_t not_zero10 = 0; not_zero10 < 32; ++not_zero10) {
        for (int32_t index_tuple10 = 0; index_tuple10 < 18; ++index_tuple10) {
          for (int32_t i10 = 0; i10 < 18; ++i10) {
            layer2_1_conv2_pad[(((i10 + (index_tuple10 * 18)) + (not_zero10 * 324)) + (indices10 * 10368))] = (bool)(((((1 <= index_tuple10) && (index_tuple10 < 17)) && (1 <= i10)) && (i10 < 17)) ? ((bool)layer2_1_rsign2[((((i10 + (index_tuple10 * 16)) + (not_zero10 * 256)) + (indices10 * 8192)) + -17)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer2_1_conv2[8192];
    for (int32_t nn39 = 0; nn39 < 1; ++nn39) {
      for (int32_t ff10 = 0; ff10 < 32; ++ff10) {
        for (int32_t yy10 = 0; yy10 < 16; ++yy10) {
          for (int32_t xx10 = 0; xx10 < 16; ++xx10) {
            int8_t layer2_1_conv2_sum;
            for (int32_t rc10 = 0; rc10 < 32; ++rc10) {
              for (int32_t ry10 = 0; ry10 < 3; ++ry10) {
                for (int32_t rx10 = 0; rx10 < 3; ++rx10) {
                  layer2_1_conv2_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx10)) <= ((int64_t)xx10)) && (((int64_t)xx10) < ((int64_t)17 - ((int64_t)rx10)))) && (((int64_t)1 - ((int64_t)ry10)) <= ((int64_t)yy10))) && (((int64_t)yy10) < ((int64_t)17 - ((int64_t)ry10)))) ? ((uint32_t)((((1U - ((uint32_t)layer2_1_conv2_pad[((((xx10 + rx10) + ((yy10 + ry10) * 18)) + (rc10 * 324)) + (nn39 * 10368))])) ^ 1) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer2_1_conv2_sum)));
                }
              }
            }
            layer2_1_conv2[(((xx10 + (yy10 * 16)) + (ff10 * 256)) + (nn39 * 8192))] = layer2_1_conv2_sum;
          }
        }
      }
    }
    int32_t layer2_1_bn2[8192];
    for (int32_t x10 = 0; x10 < 1; ++x10) {
      for (int32_t args010 = 0; args010 < 32; ++args010) {
        for (int32_t args110 = 0; args110 < 16; ++args110) {
          for (int32_t args210 = 0; args210 < 16; ++args210) {
            layer2_1_bn2[(((args210 + (args110 * 16)) + (args010 * 256)) + (x10 * 8192))] = ((int32_t)(((int41_t)(((int64_t)layer2_1_conv2[(((args210 + (args110 * 16)) + (args010 * 256)) + (x10 * 8192))]) * ((int40_t)256))) + ((int41_t)256)));
          }
        }
      }
    }
    int32_t layer2_1_residual2[8192];
    for (int32_t nn40 = 0; nn40 < 1; ++nn40) {
      for (int32_t cc30 = 0; cc30 < 32; ++cc30) {
        for (int32_t ww29 = 0; ww29 < 16; ++ww29) {
          for (int32_t hh30 = 0; hh30 < 16; ++hh30) {
            layer2_1_residual2[(((hh30 + (ww29 * 16)) + (cc30 * 256)) + (nn40 * 8192))] = ((int32_t)(((int33_t)layer2_1_bn2[(((hh30 + (ww29 * 16)) + (cc30 * 256)) + (nn40 * 8192))]) + ((int33_t)layer2_1_rprelu1[(((hh30 + (ww29 * 16)) + (cc30 * 256)) + (nn40 * 8192))])));
          }
        }
      }
    }
    int32_t layer2_1_rprelu2[8192];
    for (int32_t nn41 = 0; nn41 < 1; ++nn41) {
      for (int32_t cc31 = 0; cc31 < 32; ++cc31) {
        for (int32_t ww30 = 0; ww30 < 16; ++ww30) {
          for (int32_t hh31 = 0; hh31 < 16; ++hh31) {
            layer2_1_rprelu2[(((hh31 + (ww30 * 16)) + (cc31 * 256)) + (nn41 * 8192))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_1_residual2[(((hh31 + (ww30 * 16)) + (cc31 * 256)) + (nn41 * 8192))]) + ((int33_t)hh31)))) ? (((int64_t)(((int33_t)layer2_1_residual2[(((hh31 + (ww30 * 16)) + (cc31 * 256)) + (nn41 * 8192))]) + ((int33_t)hh31)))) : ((int64_t)(((int64_t)ww30) * ((int64_t)(((int33_t)layer2_1_residual2[(((hh31 + (ww30 * 16)) + (cc31 * 256)) + (nn41 * 8192))]) + ((int33_t)cc31))))))) + ((int64_t)hh31)));
          }
        }
      }
    }
    bool layer2_2_rsign1[8192];
    for (int32_t nn42 = 0; nn42 < 1; ++nn42) {
      for (int32_t cc32 = 0; cc32 < 32; ++cc32) {
        for (int32_t ww31 = 0; ww31 < 16; ++ww31) {
          for (int32_t hh32 = 0; hh32 < 16; ++hh32) {
            layer2_2_rsign1[(((hh32 + (ww31 * 16)) + (cc32 * 256)) + (nn42 * 8192))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_1_rprelu2[(((hh32 + (ww31 * 16)) + (cc32 * 256)) + (nn42 * 8192))]) + ((int33_t)hh32)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer2_2_conv1_pad[10368];
    for (int32_t indices11 = 0; indices11 < 1; ++indices11) {
      for (int32_t not_zero11 = 0; not_zero11 < 32; ++not_zero11) {
        for (int32_t index_tuple11 = 0; index_tuple11 < 18; ++index_tuple11) {
          for (int32_t i11 = 0; i11 < 18; ++i11) {
            layer2_2_conv1_pad[(((i11 + (index_tuple11 * 18)) + (not_zero11 * 324)) + (indices11 * 10368))] = (bool)(((((1 <= index_tuple11) && (index_tuple11 < 17)) && (1 <= i11)) && (i11 < 17)) ? ((bool)layer2_2_rsign1[((((i11 + (index_tuple11 * 16)) + (not_zero11 * 256)) + (indices11 * 8192)) + -17)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer2_2_conv1[8192];
    for (int32_t nn43 = 0; nn43 < 1; ++nn43) {
      for (int32_t ff11 = 0; ff11 < 32; ++ff11) {
        for (int32_t yy11 = 0; yy11 < 16; ++yy11) {
          for (int32_t xx11 = 0; xx11 < 16; ++xx11) {
            int8_t layer2_2_conv1_sum;
            for (int32_t rc11 = 0; rc11 < 32; ++rc11) {
              for (int32_t ry11 = 0; ry11 < 3; ++ry11) {
                for (int32_t rx11 = 0; rx11 < 3; ++rx11) {
                  layer2_2_conv1_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx11)) <= ((int64_t)xx11)) && (((int64_t)xx11) < ((int64_t)17 - ((int64_t)rx11)))) && (((int64_t)1 - ((int64_t)ry11)) <= ((int64_t)yy11))) && (((int64_t)yy11) < ((int64_t)17 - ((int64_t)ry11)))) ? ((uint32_t)((((1U - ((uint32_t)layer2_2_conv1_pad[((((xx11 + rx11) + ((yy11 + ry11) * 18)) + (rc11 * 324)) + (nn43 * 10368))])) ^ 0) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer2_2_conv1_sum)));
                }
              }
            }
            layer2_2_conv1[(((xx11 + (yy11 * 16)) + (ff11 * 256)) + (nn43 * 8192))] = layer2_2_conv1_sum;
          }
        }
      }
    }
    int32_t layer2_2_bn1[8192];
    for (int32_t x11 = 0; x11 < 1; ++x11) {
      for (int32_t args011 = 0; args011 < 32; ++args011) {
        for (int32_t args111 = 0; args111 < 16; ++args111) {
          for (int32_t args211 = 0; args211 < 16; ++args211) {
            layer2_2_bn1[(((args211 + (args111 * 16)) + (args011 * 256)) + (x11 * 8192))] = ((int32_t)(((int41_t)(((int64_t)layer2_2_conv1[(((args211 + (args111 * 16)) + (args011 * 256)) + (x11 * 8192))]) * ((int40_t)args111))) + ((int41_t)args211)));
          }
        }
      }
    }
    int32_t layer2_2_residual1[8192];
    for (int32_t nn44 = 0; nn44 < 1; ++nn44) {
      for (int32_t cc33 = 0; cc33 < 32; ++cc33) {
        for (int32_t ww32 = 0; ww32 < 16; ++ww32) {
          for (int32_t hh33 = 0; hh33 < 16; ++hh33) {
            layer2_2_residual1[(((hh33 + (ww32 * 16)) + (cc33 * 256)) + (nn44 * 8192))] = ((int32_t)(((int33_t)layer2_2_bn1[(((hh33 + (ww32 * 16)) + (cc33 * 256)) + (nn44 * 8192))]) + ((int33_t)layer2_1_rprelu2[(((hh33 + (ww32 * 16)) + (cc33 * 256)) + (nn44 * 8192))])));
          }
        }
      }
    }
    int32_t layer2_2_rprelu1[8192];
    for (int32_t nn45 = 0; nn45 < 1; ++nn45) {
      for (int32_t cc34 = 0; cc34 < 32; ++cc34) {
        for (int32_t ww33 = 0; ww33 < 16; ++ww33) {
          for (int32_t hh34 = 0; hh34 < 16; ++hh34) {
            layer2_2_rprelu1[(((hh34 + (ww33 * 16)) + (cc34 * 256)) + (nn45 * 8192))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_2_residual1[(((hh34 + (ww33 * 16)) + (cc34 * 256)) + (nn45 * 8192))]) + ((int33_t)hh34)))) ? (((int64_t)(((int33_t)layer2_2_residual1[(((hh34 + (ww33 * 16)) + (cc34 * 256)) + (nn45 * 8192))]) + ((int33_t)hh34)))) : ((int64_t)(((int64_t)ww33) * ((int64_t)(((int33_t)layer2_2_residual1[(((hh34 + (ww33 * 16)) + (cc34 * 256)) + (nn45 * 8192))]) + ((int33_t)ww33))))))) + ((int64_t)hh34)));
          }
        }
      }
    }
    bool layer2_2_rsign2[8192];
    for (int32_t nn46 = 0; nn46 < 1; ++nn46) {
      for (int32_t cc35 = 0; cc35 < 32; ++cc35) {
        for (int32_t ww34 = 0; ww34 < 16; ++ww34) {
          for (int32_t hh35 = 0; hh35 < 16; ++hh35) {
            layer2_2_rsign2[(((hh35 + (ww34 * 16)) + (cc35 * 256)) + (nn46 * 8192))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_2_rprelu1[(((hh35 + (ww34 * 16)) + (cc35 * 256)) + (nn46 * 8192))]) + ((int33_t)hh35)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer2_2_conv2_pad[10368];
    for (int32_t indices12 = 0; indices12 < 1; ++indices12) {
      for (int32_t not_zero12 = 0; not_zero12 < 32; ++not_zero12) {
        for (int32_t index_tuple12 = 0; index_tuple12 < 18; ++index_tuple12) {
          for (int32_t i12 = 0; i12 < 18; ++i12) {
            layer2_2_conv2_pad[(((i12 + (index_tuple12 * 18)) + (not_zero12 * 324)) + (indices12 * 10368))] = (bool)(((((1 <= index_tuple12) && (index_tuple12 < 17)) && (1 <= i12)) && (i12 < 17)) ? ((bool)layer2_2_rsign2[((((i12 + (index_tuple12 * 16)) + (not_zero12 * 256)) + (indices12 * 8192)) + -17)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer2_2_conv2[8192];
    for (int32_t nn47 = 0; nn47 < 1; ++nn47) {
      for (int32_t ff12 = 0; ff12 < 32; ++ff12) {
        for (int32_t yy12 = 0; yy12 < 16; ++yy12) {
          for (int32_t xx12 = 0; xx12 < 16; ++xx12) {
            int8_t layer2_2_conv2_sum;
            for (int32_t rc12 = 0; rc12 < 32; ++rc12) {
              for (int32_t ry12 = 0; ry12 < 3; ++ry12) {
                for (int32_t rx12 = 0; rx12 < 3; ++rx12) {
                  layer2_2_conv2_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx12)) <= ((int64_t)xx12)) && (((int64_t)xx12) < ((int64_t)17 - ((int64_t)rx12)))) && (((int64_t)1 - ((int64_t)ry12)) <= ((int64_t)yy12))) && (((int64_t)yy12) < ((int64_t)17 - ((int64_t)ry12)))) ? ((uint32_t)((((1U - ((uint32_t)layer2_2_conv2_pad[((((xx12 + rx12) + ((yy12 + ry12) * 18)) + (rc12 * 324)) + (nn47 * 10368))])) ^ 1) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer2_2_conv2_sum)));
                }
              }
            }
            layer2_2_conv2[(((xx12 + (yy12 * 16)) + (ff12 * 256)) + (nn47 * 8192))] = layer2_2_conv2_sum;
          }
        }
      }
    }
    int32_t layer2_2_bn2[8192];
    for (int32_t x12 = 0; x12 < 1; ++x12) {
      for (int32_t args012 = 0; args012 < 32; ++args012) {
        for (int32_t args112 = 0; args112 < 16; ++args112) {
          for (int32_t args212 = 0; args212 < 16; ++args212) {
            layer2_2_bn2[(((args212 + (args112 * 16)) + (args012 * 256)) + (x12 * 8192))] = ((int32_t)(((int41_t)(((int64_t)layer2_2_conv2[(((args212 + (args112 * 16)) + (args012 * 256)) + (x12 * 8192))]) * ((int40_t)args112))) + ((int41_t)args212)));
          }
        }
      }
    }
    int32_t layer2_2_residual2[8192];
    for (int32_t nn48 = 0; nn48 < 1; ++nn48) {
      for (int32_t cc36 = 0; cc36 < 32; ++cc36) {
        for (int32_t ww35 = 0; ww35 < 16; ++ww35) {
          for (int32_t hh36 = 0; hh36 < 16; ++hh36) {
            layer2_2_residual2[(((hh36 + (ww35 * 16)) + (cc36 * 256)) + (nn48 * 8192))] = ((int32_t)(((int33_t)layer2_2_bn2[(((hh36 + (ww35 * 16)) + (cc36 * 256)) + (nn48 * 8192))]) + ((int33_t)layer2_2_rprelu1[(((hh36 + (ww35 * 16)) + (cc36 * 256)) + (nn48 * 8192))])));
          }
        }
      }
    }
    int32_t layer2_2_rprelu2[8192];
    for (int32_t nn49 = 0; nn49 < 1; ++nn49) {
      for (int32_t cc37 = 0; cc37 < 32; ++cc37) {
        for (int32_t ww36 = 0; ww36 < 16; ++ww36) {
          for (int32_t hh37 = 0; hh37 < 16; ++hh37) {
            layer2_2_rprelu2[(((hh37 + (ww36 * 16)) + (cc37 * 256)) + (nn49 * 8192))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_2_residual2[(((hh37 + (ww36 * 16)) + (cc37 * 256)) + (nn49 * 8192))]) + ((int33_t)hh37)))) ? (((int64_t)(((int33_t)layer2_2_residual2[(((hh37 + (ww36 * 16)) + (cc37 * 256)) + (nn49 * 8192))]) + ((int33_t)ww36)))) : ((int64_t)(((int64_t)hh37) * ((int64_t)(((int33_t)layer2_2_residual2[(((hh37 + (ww36 * 16)) + (cc37 * 256)) + (nn49 * 8192))]) + ((int33_t)ww36))))))) + ((int64_t)hh37)));
          }
        }
      }
    }
    bool layer3_0_rsign1[8192];
    for (int32_t nn50 = 0; nn50 < 1; ++nn50) {
      for (int32_t cc38 = 0; cc38 < 32; ++cc38) {
        for (int32_t ww37 = 0; ww37 < 16; ++ww37) {
          for (int32_t hh38 = 0; hh38 < 16; ++hh38) {
            layer3_0_rsign1[(((hh38 + (ww37 * 16)) + (cc38 * 256)) + (nn50 * 8192))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer2_2_rprelu2[(((hh38 + (ww37 * 16)) + (cc38 * 256)) + (nn50 * 8192))]) + ((int33_t)hh38)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer3_0_conv1_pad[10368];
    for (int32_t indices13 = 0; indices13 < 1; ++indices13) {
      for (int32_t not_zero13 = 0; not_zero13 < 32; ++not_zero13) {
        for (int32_t index_tuple13 = 0; index_tuple13 < 18; ++index_tuple13) {
          for (int32_t i13 = 0; i13 < 18; ++i13) {
            layer3_0_conv1_pad[(((i13 + (index_tuple13 * 18)) + (not_zero13 * 324)) + (indices13 * 10368))] = (bool)(((((1 <= index_tuple13) && (index_tuple13 < 17)) && (1 <= i13)) && (i13 < 17)) ? ((bool)layer3_0_rsign1[((((i13 + (index_tuple13 * 16)) + (not_zero13 * 256)) + (indices13 * 8192)) + -17)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer3_0_conv1[4096];
    for (int32_t nn51 = 0; nn51 < 1; ++nn51) {
      for (int32_t ff13 = 0; ff13 < 64; ++ff13) {
        for (int32_t yy13 = 0; yy13 < 8; ++yy13) {
          for (int32_t xx13 = 0; xx13 < 8; ++xx13) {
            int8_t layer3_0_conv1_sum;
            for (int32_t rc13 = 0; rc13 < 32; ++rc13) {
              for (int32_t ry13 = 0; ry13 < 3; ++ry13) {
                for (int32_t rx13 = 0; rx13 < 3; ++rx13) {
                  layer3_0_conv1_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx13)) <= ((int64_t)(xx13 * 2))) && (((int64_t)(xx13 * 2)) < ((int64_t)17 - ((int64_t)rx13)))) && (((int64_t)1 - ((int64_t)ry13)) <= ((int64_t)(yy13 * 2)))) && (((int64_t)(yy13 * 2)) < ((int64_t)17 - ((int64_t)ry13)))) ? ((uint32_t)((((1U - ((uint32_t)layer3_0_conv1_pad[(((((xx13 * 2) + rx13) + (((yy13 * 2) + ry13) * 18)) + (rc13 * 324)) + (nn51 * 10368))])) ^ 1) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer3_0_conv1_sum)));
                }
              }
            }
            layer3_0_conv1[(((xx13 + (yy13 * 8)) + (ff13 * 64)) + (nn51 * 4096))] = layer3_0_conv1_sum;
          }
        }
      }
    }
    int32_t layer3_0_bn1[4096];
    for (int32_t x13 = 0; x13 < 1; ++x13) {
      for (int32_t args013 = 0; args013 < 64; ++args013) {
        for (int32_t args113 = 0; args113 < 8; ++args113) {
          for (int32_t args213 = 0; args213 < 8; ++args213) {
            layer3_0_bn1[(((args213 + (args113 * 8)) + (args013 * 64)) + (x13 * 4096))] = ((int32_t)(((int41_t)(((int64_t)layer3_0_conv1[(((args213 + (args113 * 8)) + (args013 * 64)) + (x13 * 4096))]) * ((int40_t)args213))) + ((int41_t)args113)));
          }
        }
      }
    }
    int32_t layer3_0_avgpool_res[2048];
    int32_t layer3_0_avgpool_LB[32];
    int32_t layer3_0_avgpool;
    for (int32_t ii1 = 0; ii1 < 1; ++ii1) {
      for (int32_t cc39 = 0; cc39 < 32; ++cc39) {
        for (int32_t hh39 = 0; hh39 < 8; ++hh39) {
          for (int32_t layer3_0_avgpool_LB_i = 0; layer3_0_avgpool_LB_i < 2; ++layer3_0_avgpool_LB_i) {
            for (int32_t layer3_0_avgpool_LB_j = 0; layer3_0_avgpool_LB_j < 16; ++layer3_0_avgpool_LB_j) {
              layer3_0_avgpool_LB[(layer3_0_avgpool_LB_j + (layer3_0_avgpool_LB_i * 16))] = layer2_2_rprelu2[(((layer3_0_avgpool_LB_j + (((hh39 * 2) + layer3_0_avgpool_LB_i) * 16)) + (cc39 * 256)) + (ii1 * 8192))];
            }
          }
          for (int32_t layer3_0_avgpool_ww = 0; layer3_0_avgpool_ww < 8; ++layer3_0_avgpool_ww) {
            int32_t layer3_0_avgpool_val;
            for (int32_t layer3_0_avgpool_ry = 0; layer3_0_avgpool_ry < 2; ++layer3_0_avgpool_ry) {
              for (int32_t layer3_0_avgpool_rx = 0; layer3_0_avgpool_rx < 2; ++layer3_0_avgpool_rx) {
                layer3_0_avgpool_val = ((int32_t)(((int33_t)layer3_0_avgpool_val) + ((int33_t)layer3_0_avgpool_LB[(((layer3_0_avgpool_ww * 2) + layer3_0_avgpool_rx) + (layer3_0_avgpool_ry * 16))])));
              }
            }
            layer3_0_avgpool_res[(((layer3_0_avgpool_ww + (hh39 * 8)) + (cc39 * 64)) + (ii1 * 2048))] = ((int32_t)(((int64_t)layer3_0_avgpool_val) / (int64_t)4));
          }
        }
      }
    }
    int32_t layer3_0_concat[4096];
    for (int32_t nn52 = 0; nn52 < 1; ++nn52) {
      for (int32_t cc40 = 0; cc40 < 64; ++cc40) {
        for (int32_t ww38 = 0; ww38 < 8; ++ww38) {
          for (int32_t hh40 = 0; hh40 < 8; ++hh40) {
            layer3_0_concat[(((hh40 + (ww38 * 8)) + (cc40 * 64)) + (nn52 * 4096))] = layer3_0_avgpool_res[(((hh40 + (ww38 * 8)) + ((cc40 % 32) * 64)) + (nn52 * 2048))];
          }
        }
      }
    }
    int32_t layer3_0_residual1[4096];
    for (int32_t nn53 = 0; nn53 < 1; ++nn53) {
      for (int32_t cc41 = 0; cc41 < 64; ++cc41) {
        for (int32_t ww39 = 0; ww39 < 8; ++ww39) {
          for (int32_t hh41 = 0; hh41 < 8; ++hh41) {
            layer3_0_residual1[(((hh41 + (ww39 * 8)) + (cc41 * 64)) + (nn53 * 4096))] = ((int32_t)(((int33_t)layer3_0_bn1[(((hh41 + (ww39 * 8)) + (cc41 * 64)) + (nn53 * 4096))]) + ((int33_t)layer3_0_concat[(((hh41 + (ww39 * 8)) + (cc41 * 64)) + (nn53 * 4096))])));
          }
        }
      }
    }
    int32_t layer3_0_rprelu1[4096];
    for (int32_t nn54 = 0; nn54 < 1; ++nn54) {
      for (int32_t cc42 = 0; cc42 < 64; ++cc42) {
        for (int32_t ww40 = 0; ww40 < 8; ++ww40) {
          for (int32_t hh42 = 0; hh42 < 8; ++hh42) {
            layer3_0_rprelu1[(((hh42 + (ww40 * 8)) + (cc42 * 64)) + (nn54 * 4096))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer3_0_residual1[(((hh42 + (ww40 * 8)) + (cc42 * 64)) + (nn54 * 4096))]) + ((int33_t)hh42)))) ? (((int64_t)(((int33_t)layer3_0_residual1[(((hh42 + (ww40 * 8)) + (cc42 * 64)) + (nn54 * 4096))]) + ((int33_t)hh42)))) : ((int64_t)(((int64_t)hh42) * ((int64_t)(((int33_t)layer3_0_residual1[(((hh42 + (ww40 * 8)) + (cc42 * 64)) + (nn54 * 4096))]) + ((int33_t)hh42))))))) + ((int64_t)hh42)));
          }
        }
      }
    }
    bool layer3_0_rsign2[4096];
    for (int32_t nn55 = 0; nn55 < 1; ++nn55) {
      for (int32_t cc43 = 0; cc43 < 64; ++cc43) {
        for (int32_t ww41 = 0; ww41 < 8; ++ww41) {
          for (int32_t hh43 = 0; hh43 < 8; ++hh43) {
            layer3_0_rsign2[(((hh43 + (ww41 * 8)) + (cc43 * 64)) + (nn55 * 4096))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer3_0_rprelu1[(((hh43 + (ww41 * 8)) + (cc43 * 64)) + (nn55 * 4096))]) + ((int33_t)hh43)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer3_0_conv2_pad[6400];
    for (int32_t indices14 = 0; indices14 < 1; ++indices14) {
      for (int32_t not_zero14 = 0; not_zero14 < 64; ++not_zero14) {
        for (int32_t index_tuple14 = 0; index_tuple14 < 10; ++index_tuple14) {
          for (int32_t i14 = 0; i14 < 10; ++i14) {
            layer3_0_conv2_pad[(((i14 + (index_tuple14 * 10)) + (not_zero14 * 100)) + (indices14 * 6400))] = (bool)(((((1 <= index_tuple14) && (index_tuple14 < 9)) && (1 <= i14)) && (i14 < 9)) ? ((bool)layer3_0_rsign2[((((i14 + (index_tuple14 * 8)) + (not_zero14 * 64)) + (indices14 * 4096)) + -9)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer3_0_conv2[4096];
    for (int32_t nn56 = 0; nn56 < 1; ++nn56) {
      for (int32_t ff14 = 0; ff14 < 64; ++ff14) {
        for (int32_t yy14 = 0; yy14 < 8; ++yy14) {
          for (int32_t xx14 = 0; xx14 < 8; ++xx14) {
            int8_t layer3_0_conv2_sum;
            for (int32_t rc14 = 0; rc14 < 64; ++rc14) {
              for (int32_t ry14 = 0; ry14 < 3; ++ry14) {
                for (int32_t rx14 = 0; rx14 < 3; ++rx14) {
                  layer3_0_conv2_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx14)) <= ((int64_t)xx14)) && (((int64_t)xx14) < ((int64_t)9 - ((int64_t)rx14)))) && (((int64_t)1 - ((int64_t)ry14)) <= ((int64_t)yy14))) && (((int64_t)yy14) < ((int64_t)9 - ((int64_t)ry14)))) ? ((uint32_t)((((1U - ((uint32_t)layer3_0_conv2_pad[((((xx14 + rx14) + ((yy14 + ry14) * 10)) + (rc14 * 100)) + (nn56 * 6400))])) ^ 1) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer3_0_conv2_sum)));
                }
              }
            }
            layer3_0_conv2[(((xx14 + (yy14 * 8)) + (ff14 * 64)) + (nn56 * 4096))] = layer3_0_conv2_sum;
          }
        }
      }
    }
    int32_t layer3_0_bn2[4096];
    for (int32_t x14 = 0; x14 < 1; ++x14) {
      for (int32_t args014 = 0; args014 < 64; ++args014) {
        for (int32_t args114 = 0; args114 < 8; ++args114) {
          for (int32_t args214 = 0; args214 < 8; ++args214) {
            layer3_0_bn2[(((args214 + (args114 * 8)) + (args014 * 64)) + (x14 * 4096))] = ((int32_t)(((int41_t)(((int64_t)layer3_0_conv2[(((args214 + (args114 * 8)) + (args014 * 64)) + (x14 * 4096))]) * ((int40_t)hh45))) + ((int41_t)hh45)));
          }
        }
      }
    }
    int32_t layer3_0_residual2[4096];
    for (int32_t nn57 = 0; nn57 < 1; ++nn57) {
      for (int32_t cc44 = 0; cc44 < 64; ++cc44) {
        for (int32_t ww42 = 0; ww42 < 8; ++ww42) {
          for (int32_t hh44 = 0; hh44 < 8; ++hh44) {
            layer3_0_residual2[(((hh44 + (ww42 * 8)) + (cc44 * 64)) + (nn57 * 4096))] = ((int32_t)(((int33_t)layer3_0_bn2[(((hh44 + (ww42 * 8)) + (cc44 * 64)) + (nn57 * 4096))]) + ((int33_t)layer3_0_rprelu1[(((hh44 + (ww42 * 8)) + (cc44 * 64)) + (nn57 * 4096))])));
          }
        }
      }
    }
    int32_t layer3_0_rprelu2[4096];
    for (int32_t nn58 = 0; nn58 < 1; ++nn58) {
      for (int32_t cc45 = 0; cc45 < 64; ++cc45) {
        for (int32_t ww43 = 0; ww43 < 8; ++ww43) {
          for (int32_t hh45 = 0; hh45 < 8; ++hh45) {
            layer3_0_rprelu2[(((hh45 + (ww43 * 8)) + (cc45 * 64)) + (nn58 * 4096))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer3_0_residual2[(((hh45 + (ww43 * 8)) + (cc45 * 64)) + (nn58 * 4096))]) + ((int33_t)hh45)))) ? (((int64_t)(((int33_t)layer3_0_residual2[(((hh45 + (ww43 * 8)) + (cc45 * 64)) + (nn58 * 4096))]) + ((int33_t)hh45)))) : ((int64_t)(((int64_t)hh45) * ((int64_t)(((int33_t)layer3_0_residual2[(((hh45 + (ww43 * 8)) + (cc45 * 64)) + (nn58 * 4096))]) + ((int33_t)hh45))))))) + ((int64_t)hh45)));
          }
        }
      }
    }
    bool layer3_1_rsign1[4096];
    for (int32_t nn59 = 0; nn59 < 1; ++nn59) {
      for (int32_t cc46 = 0; cc46 < 64; ++cc46) {
        for (int32_t ww44 = 0; ww44 < 8; ++ww44) {
          for (int32_t hh46 = 0; hh46 < 8; ++hh46) {
            layer3_1_rsign1[(((hh46 + (ww44 * 8)) + (cc46 * 64)) + (nn59 * 4096))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer3_0_rprelu2[(((hh46 + (ww44 * 8)) + (cc46 * 64)) + (nn59 * 4096))]) + ((int33_t)hh46)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer3_1_conv1_pad[6400];
    for (int32_t indices15 = 0; indices15 < 1; ++indices15) {
      for (int32_t not_zero15 = 0; not_zero15 < 64; ++not_zero15) {
        for (int32_t index_tuple15 = 0; index_tuple15 < 10; ++index_tuple15) {
          for (int32_t i15 = 0; i15 < 10; ++i15) {
            layer3_1_conv1_pad[(((i15 + (index_tuple15 * 10)) + (not_zero15 * 100)) + (indices15 * 6400))] = (bool)(((((1 <= index_tuple15) && (index_tuple15 < 9)) && (1 <= i15)) && (i15 < 9)) ? ((bool)layer3_1_rsign1[((((i15 + (index_tuple15 * 8)) + (not_zero15 * 64)) + (indices15 * 4096)) + -9)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer3_1_conv1[4096];
    for (int32_t nn60 = 0; nn60 < 1; ++nn60) {
      for (int32_t ff15 = 0; ff15 < 64; ++ff15) {
        for (int32_t yy15 = 0; yy15 < 8; ++yy15) {
          for (int32_t xx15 = 0; xx15 < 8; ++xx15) {
            int8_t layer3_1_conv1_sum;
            for (int32_t rc15 = 0; rc15 < 64; ++rc15) {
              for (int32_t ry15 = 0; ry15 < 3; ++ry15) {
                for (int32_t rx15 = 0; rx15 < 3; ++rx15) {
                  layer3_1_conv1_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx15)) <= ((int64_t)xx15)) && (((int64_t)xx15) < ((int64_t)9 - ((int64_t)rx15)))) && (((int64_t)1 - ((int64_t)ry15)) <= ((int64_t)yy15))) && (((int64_t)yy15) < ((int64_t)9 - ((int64_t)ry15)))) ? ((uint32_t)((((1U - ((uint32_t)layer3_1_conv1_pad[((((xx15 + rx15) + ((yy15 + ry15) * 10)) + (rc15 * 100)) + (nn60 * 6400))])) ^ 0) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer3_1_conv1_sum)));
                }
              }
            }
            layer3_1_conv1[(((xx15 + (yy15 * 8)) + (ff15 * 64)) + (nn60 * 4096))] = layer3_1_conv1_sum;
          }
        }
      }
    }
    int32_t layer3_1_bn1[4096];
    for (int32_t x15 = 0; x15 < 1; ++x15) {
      for (int32_t args015 = 0; args015 < 64; ++args015) {
        for (int32_t args115 = 0; args115 < 8; ++args115) {
          for (int32_t args215 = 0; args215 < 8; ++args215) {
            layer3_1_bn1[(((args215 + (args115 * 8)) + (args015 * 64)) + (x15 * 4096))] = ((int32_t)(((int41_t)(((int64_t)layer3_1_conv1[(((args215 + (args115 * 8)) + (args015 * 64)) + (x15 * 4096))]) * ((int40_t)args215))) + ((int41_t)args115)));
          }
        }
      }
    }
    int32_t layer3_1_residual1[4096];
    for (int32_t nn61 = 0; nn61 < 1; ++nn61) {
      for (int32_t cc47 = 0; cc47 < 64; ++cc47) {
        for (int32_t ww45 = 0; ww45 < 8; ++ww45) {
          for (int32_t hh47 = 0; hh47 < 8; ++hh47) {
            layer3_1_residual1[(((hh47 + (ww45 * 8)) + (cc47 * 64)) + (nn61 * 4096))] = ((int32_t)(((int33_t)layer3_1_bn1[(((hh47 + (ww45 * 8)) + (cc47 * 64)) + (nn61 * 4096))]) + ((int33_t)layer3_0_rprelu2[(((hh47 + (ww45 * 8)) + (cc47 * 64)) + (nn61 * 4096))])));
          }
        }
      }
    }
    int32_t layer3_1_rprelu1[4096];
    for (int32_t nn62 = 0; nn62 < 1; ++nn62) {
      for (int32_t cc48 = 0; cc48 < 64; ++cc48) {
        for (int32_t ww46 = 0; ww46 < 8; ++ww46) {
          for (int32_t hh48 = 0; hh48 < 8; ++hh48) {
            layer3_1_rprelu1[(((hh48 + (ww46 * 8)) + (cc48 * 64)) + (nn62 * 4096))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer3_1_residual1[(((hh48 + (ww46 * 8)) + (cc48 * 64)) + (nn62 * 4096))]) + ((int33_t)hh48)))) ? (((int64_t)(((int33_t)layer3_1_residual1[(((hh48 + (ww46 * 8)) + (cc48 * 64)) + (nn62 * 4096))]) + ((int33_t)hh48)))) : ((int64_t)(((int64_t)hh48) * ((int64_t)(((int33_t)layer3_1_residual1[(((hh48 + (ww46 * 8)) + (cc48 * 64)) + (nn62 * 4096))]) + ((int33_t)hh48))))))) + ((int64_t)hh48)));
          }
        }
      }
    }
    bool layer3_1_rsign2[4096];
    for (int32_t nn63 = 0; nn63 < 1; ++nn63) {
      for (int32_t cc49 = 0; cc49 < 64; ++cc49) {
        for (int32_t ww47 = 0; ww47 < 8; ++ww47) {
          for (int32_t hh49 = 0; hh49 < 8; ++hh49) {
            layer3_1_rsign2[(((hh49 + (ww47 * 8)) + (cc49 * 64)) + (nn63 * 4096))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer3_1_rprelu1[(((hh49 + (ww47 * 8)) + (cc49 * 64)) + (nn63 * 4096))]) + ((int33_t)hh49)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer3_1_conv2_pad[6400];
    for (int32_t indices16 = 0; indices16 < 1; ++indices16) {
      for (int32_t not_zero16 = 0; not_zero16 < 64; ++not_zero16) {
        for (int32_t index_tuple16 = 0; index_tuple16 < 10; ++index_tuple16) {
          for (int32_t i16 = 0; i16 < 10; ++i16) {
            layer3_1_conv2_pad[(((i16 + (index_tuple16 * 10)) + (not_zero16 * 100)) + (indices16 * 6400))] = (bool)(((((1 <= index_tuple16) && (index_tuple16 < 9)) && (1 <= i16)) && (i16 < 9)) ? ((bool)layer3_1_rsign2[((((i16 + (index_tuple16 * 8)) + (not_zero16 * 64)) + (indices16 * 4096)) + -9)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer3_1_conv2[4096];
    for (int32_t nn64 = 0; nn64 < 1; ++nn64) {
      for (int32_t ff16 = 0; ff16 < 64; ++ff16) {
        for (int32_t yy16 = 0; yy16 < 8; ++yy16) {
          for (int32_t xx16 = 0; xx16 < 8; ++xx16) {
            int8_t layer3_1_conv2_sum;
            for (int32_t rc16 = 0; rc16 < 64; ++rc16) {
              for (int32_t ry16 = 0; ry16 < 3; ++ry16) {
                for (int32_t rx16 = 0; rx16 < 3; ++rx16) {
                  layer3_1_conv2_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx16)) <= ((int64_t)xx16)) && (((int64_t)xx16) < ((int64_t)9 - ((int64_t)rx16)))) && (((int64_t)1 - ((int64_t)ry16)) <= ((int64_t)yy16))) && (((int64_t)yy16) < ((int64_t)9 - ((int64_t)ry16)))) ? ((uint32_t)((((1U - ((uint32_t)layer3_1_conv2_pad[((((xx16 + rx16) + ((yy16 + ry16) * 10)) + (rc16 * 100)) + (nn64 * 6400))])) ^ 1) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer3_1_conv2_sum)));
                }
              }
            }
            layer3_1_conv2[(((xx16 + (yy16 * 8)) + (ff16 * 64)) + (nn64 * 4096))] = layer3_1_conv2_sum;
          }
        }
      }
    }
    int32_t layer3_1_bn2[4096];
    for (int32_t x16 = 0; x16 < 1; ++x16) {
      for (int32_t args016 = 0; args016 < 64; ++args016) {
        for (int32_t args116 = 0; args116 < 8; ++args116) {
          for (int32_t args216 = 0; args216 < 8; ++args216) {
            layer3_1_bn2[(((args216 + (args116 * 8)) + (args016 * 64)) + (x16 * 4096))] = ((int32_t)(((int41_t)(((int64_t)layer3_1_conv2[(((args216 + (args116 * 8)) + (args016 * 64)) + (x16 * 4096))]) * ((int40_t)args016))) + ((int41_t)args216)));
          }
        }
      }
    }
    int32_t layer3_1_residual2[4096];
    for (int32_t nn65 = 0; nn65 < 1; ++nn65) {
      for (int32_t cc50 = 0; cc50 < 64; ++cc50) {
        for (int32_t ww48 = 0; ww48 < 8; ++ww48) {
          for (int32_t hh50 = 0; hh50 < 8; ++hh50) {
            layer3_1_residual2[(((hh50 + (ww48 * 8)) + (cc50 * 64)) + (nn65 * 4096))] = ((int32_t)(((int33_t)layer3_1_bn2[(((hh50 + (ww48 * 8)) + (cc50 * 64)) + (nn65 * 4096))]) + ((int33_t)layer3_1_rprelu1[(((hh50 + (ww48 * 8)) + (cc50 * 64)) + (nn65 * 4096))])));
          }
        }
      }
    }
    int32_t layer3_1_rprelu2[4096];
    for (int32_t nn66 = 0; nn66 < 1; ++nn66) {
      for (int32_t cc51 = 0; cc51 < 64; ++cc51) {
        for (int32_t ww49 = 0; ww49 < 8; ++ww49) {
          for (int32_t hh51 = 0; hh51 < 8; ++hh51) {
            layer3_1_rprelu2[(((hh51 + (ww49 * 8)) + (cc51 * 64)) + (nn66 * 4096))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer3_1_residual2[(((hh51 + (ww49 * 8)) + (cc51 * 64)) + (nn66 * 4096))]) + ((int33_t)hh51)))) ? (((int64_t)(((int33_t)layer3_1_residual2[(((hh51 + (ww49 * 8)) + (cc51 * 64)) + (nn66 * 4096))]) + ((int33_t)hh51)))) : ((int64_t)(((int64_t)hh51) * ((int64_t)(((int33_t)layer3_1_residual2[(((hh51 + (ww49 * 8)) + (cc51 * 64)) + (nn66 * 4096))]) + ((int33_t)hh51))))))) + ((int64_t)hh51)));
          }
        }
      }
    }
    bool layer3_2_rsign1[4096];
    for (int32_t nn67 = 0; nn67 < 1; ++nn67) {
      for (int32_t cc52 = 0; cc52 < 64; ++cc52) {
        for (int32_t ww50 = 0; ww50 < 8; ++ww50) {
          for (int32_t hh52 = 0; hh52 < 8; ++hh52) {
            layer3_2_rsign1[(((hh52 + (ww50 * 8)) + (cc52 * 64)) + (nn67 * 4096))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer3_1_rprelu2[(((hh52 + (ww50 * 8)) + (cc52 * 64)) + (nn67 * 4096))]) + ((int33_t)hh52)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer3_2_conv1_pad[6400];
    for (int32_t indices17 = 0; indices17 < 1; ++indices17) {
      for (int32_t not_zero17 = 0; not_zero17 < 64; ++not_zero17) {
        for (int32_t index_tuple17 = 0; index_tuple17 < 10; ++index_tuple17) {
          for (int32_t i17 = 0; i17 < 10; ++i17) {
            layer3_2_conv1_pad[(((i17 + (index_tuple17 * 10)) + (not_zero17 * 100)) + (indices17 * 6400))] = (bool)(((((1 <= index_tuple17) && (index_tuple17 < 9)) && (1 <= i17)) && (i17 < 9)) ? ((bool)layer3_2_rsign1[((((i17 + (index_tuple17 * 8)) + (not_zero17 * 64)) + (indices17 * 4096)) + -9)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer3_2_conv1[4096];
    for (int32_t nn68 = 0; nn68 < 1; ++nn68) {
      for (int32_t ff17 = 0; ff17 < 64; ++ff17) {
        for (int32_t yy17 = 0; yy17 < 8; ++yy17) {
          for (int32_t xx17 = 0; xx17 < 8; ++xx17) {
            int8_t layer3_2_conv1_sum;
            for (int32_t rc17 = 0; rc17 < 64; ++rc17) {
              for (int32_t ry17 = 0; ry17 < 3; ++ry17) {
                for (int32_t rx17 = 0; rx17 < 3; ++rx17) {
                  layer3_2_conv1_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx17)) <= ((int64_t)xx17)) && (((int64_t)xx17) < ((int64_t)9 - ((int64_t)rx17)))) && (((int64_t)1 - ((int64_t)ry17)) <= ((int64_t)yy17))) && (((int64_t)yy17) < ((int64_t)9 - ((int64_t)ry17)))) ? ((uint32_t)((((1U - ((uint32_t)layer3_2_conv1_pad[((((xx17 + rx17) + ((yy17 + ry17) * 10)) + (rc17 * 100)) + (nn68 * 6400))])) ^ 1) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer3_2_conv1_sum)));
                }
              }
            }
            layer3_2_conv1[(((xx17 + (yy17 * 8)) + (ff17 * 64)) + (nn68 * 4096))] = layer3_2_conv1_sum;
          }
        }
      }
    }
    int32_t layer3_2_bn1[4096];
    for (int32_t x17 = 0; x17 < 1; ++x17) {
      for (int32_t args017 = 0; args017 < 64; ++args017) {
        for (int32_t args117 = 0; args117 < 8; ++args117) {
          for (int32_t args217 = 0; args217 < 8; ++args217) {
            layer3_2_bn1[(((args217 + (args117 * 8)) + (args017 * 64)) + (x17 * 4096))] = ((int32_t)(((int41_t)(((int64_t)layer3_2_conv1[(((args217 + (args117 * 8)) + (args017 * 64)) + (x17 * 4096))]) * ((int40_t)args017))) + ((int41_t)args217)));
          }
        }
      }
    }
    int32_t layer3_2_residual1[4096];
    for (int32_t nn69 = 0; nn69 < 1; ++nn69) {
      for (int32_t cc53 = 0; cc53 < 64; ++cc53) {
        for (int32_t ww51 = 0; ww51 < 8; ++ww51) {
          for (int32_t hh53 = 0; hh53 < 8; ++hh53) {
            layer3_2_residual1[(((hh53 + (ww51 * 8)) + (cc53 * 64)) + (nn69 * 4096))] = ((int32_t)(((int33_t)layer3_2_bn1[(((hh53 + (ww51 * 8)) + (cc53 * 64)) + (nn69 * 4096))]) + ((int33_t)layer3_1_rprelu2[(((hh53 + (ww51 * 8)) + (cc53 * 64)) + (nn69 * 4096))])));
          }
        }
      }
    }
    int32_t layer3_2_rprelu1[4096];
    for (int32_t nn70 = 0; nn70 < 1; ++nn70) {
      for (int32_t cc54 = 0; cc54 < 64; ++cc54) {
        for (int32_t ww52 = 0; ww52 < 8; ++ww52) {
          for (int32_t hh54 = 0; hh54 < 8; ++hh54) {
            layer3_2_rprelu1[(((hh54 + (ww52 * 8)) + (cc54 * 64)) + (nn70 * 4096))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer3_2_residual1[(((hh54 + (ww52 * 8)) + (cc54 * 64)) + (nn70 * 4096))]) + ((int33_t)hh54)))) ? (((int64_t)(((int33_t)layer3_2_residual1[(((hh54 + (ww52 * 8)) + (cc54 * 64)) + (nn70 * 4096))]) + ((int33_t)hh54)))) : ((int64_t)(((int64_t)hh54) * ((int64_t)(((int33_t)layer3_2_residual1[(((hh54 + (ww52 * 8)) + (cc54 * 64)) + (nn70 * 4096))]) + ((int33_t)hh54))))))) + ((int64_t)hh54)));
          }
        }
      }
    }
    bool layer3_2_rsign2[4096];
    for (int32_t nn71 = 0; nn71 < 1; ++nn71) {
      for (int32_t cc55 = 0; cc55 < 64; ++cc55) {
        for (int32_t ww53 = 0; ww53 < 8; ++ww53) {
          for (int32_t hh55 = 0; hh55 < 8; ++hh55) {
            layer3_2_rsign2[(((hh55 + (ww53 * 8)) + (cc55 * 64)) + (nn71 * 4096))] = ((bool)(int32_t)(((int44_t)0 < ((int44_t)(((int33_t)layer3_2_rprelu1[(((hh55 + (ww53 * 8)) + (cc55 * 64)) + (nn71 * 4096))]) + ((int33_t)hh55)))) ? ((int32_t)1) : ((int32_t)0)));
          }
        }
      }
    }
    bool layer3_2_conv2_pad[6400];
    for (int32_t indices18 = 0; indices18 < 1; ++indices18) {
      for (int32_t not_zero18 = 0; not_zero18 < 64; ++not_zero18) {
        for (int32_t index_tuple18 = 0; index_tuple18 < 10; ++index_tuple18) {
          for (int32_t i18 = 0; i18 < 10; ++i18) {
            layer3_2_conv2_pad[(((i18 + (index_tuple18 * 10)) + (not_zero18 * 100)) + (indices18 * 6400))] = (bool)(((((1 <= index_tuple18) && (index_tuple18 < 9)) && (1 <= i18)) && (i18 < 9)) ? ((bool)layer3_2_rsign2[((((i18 + (index_tuple18 * 8)) + (not_zero18 * 64)) + (indices18 * 4096)) + -9)]) : ((bool)0));
          }
        }
      }
    }
    int8_t layer3_2_conv2[4096];
    for (int32_t nn72 = 0; nn72 < 1; ++nn72) {
      for (int32_t ff18 = 0; ff18 < 64; ++ff18) {
        for (int32_t yy18 = 0; yy18 < 8; ++yy18) {
          for (int32_t xx18 = 0; xx18 < 8; ++xx18) {
            int8_t layer3_2_conv2_sum;
            for (int32_t rc18 = 0; rc18 < 64; ++rc18) {
              for (int32_t ry18 = 0; ry18 < 3; ++ry18) {
                for (int32_t rx18 = 0; rx18 < 3; ++rx18) {
                  layer3_2_conv2_sum = ((int8_t)(((int64_t)(uint32_t)(((((((int64_t)1 - ((int64_t)rx18)) <= ((int64_t)xx18)) && (((int64_t)xx18) < ((int64_t)9 - ((int64_t)rx18)))) && (((int64_t)1 - ((int64_t)ry18)) <= ((int64_t)yy18))) && (((int64_t)yy18) < ((int64_t)9 - ((int64_t)ry18)))) ? ((uint32_t)((((1U - ((uint32_t)layer3_2_conv2_pad[((((xx18 + rx18) + ((yy18 + ry18) * 10)) + (rc18 * 100)) + (nn72 * 6400))])) ^ 1) << 1) - 1U)) : ((uint32_t)0U))) + ((int64_t)layer3_2_conv2_sum)));
                }
              }
            }
            layer3_2_conv2[(((xx18 + (yy18 * 8)) + (ff18 * 64)) + (nn72 * 4096))] = layer3_2_conv2_sum;
          }
        }
      }
    }
    int32_t layer3_2_bn2[4096];
    for (int32_t x18 = 0; x18 < 1; ++x18) {
      for (int32_t args018 = 0; args018 < 64; ++args018) {
        for (int32_t args118 = 0; args118 < 8; ++args118) {
          for (int32_t args218 = 0; args218 < 8; ++args218) {
            layer3_2_bn2[(((args218 + (args118 * 8)) + (args018 * 64)) + (x18 * 4096))] = ((int32_t)(((int41_t)(((int64_t)layer3_2_conv2[(((args218 + (args118 * 8)) + (args018 * 64)) + (x18 * 4096))]) * ((int40_t)args218))) + ((int41_t)args218)));
          }
        }
      }
    }
    int32_t layer3_2_residual2[4096];
    for (int32_t nn73 = 0; nn73 < 1; ++nn73) {
      for (int32_t cc56 = 0; cc56 < 64; ++cc56) {
        for (int32_t ww54 = 0; ww54 < 8; ++ww54) {
          for (int32_t hh56 = 0; hh56 < 8; ++hh56) {
            layer3_2_residual2[(((hh56 + (ww54 * 8)) + (cc56 * 64)) + (nn73 * 4096))] = ((int32_t)(((int33_t)layer3_2_bn2[(((hh56 + (ww54 * 8)) + (cc56 * 64)) + (nn73 * 4096))]) + ((int33_t)layer3_2_rprelu1[(((hh56 + (ww54 * 8)) + (cc56 * 64)) + (nn73 * 4096))])));
          }
        }
      }
    }
    int32_t layer3_2_rprelu2[4096];
    for (int32_t nn74 = 0; nn74 < 1; ++nn74) {
      for (int32_t cc57 = 0; cc57 < 64; ++cc57) {
        for (int32_t ww55 = 0; ww55 < 8; ++ww55) {
          for (int32_t hh57 = 0; hh57 < 8; ++hh57) {
            layer3_2_rprelu2[(((hh57 + (ww55 * 8)) + (cc57 * 64)) + (nn74 * 4096))] = ((int32_t)(((int64_t)(int64_t)(((int44_t)0 < ((int44_t)(((int33_t)layer3_2_residual2[(((hh57 + (ww55 * 8)) + (cc57 * 64)) + (nn74 * 4096))]) + ((int33_t)hh57)))) ? (((int64_t)(((int33_t)layer3_2_residual2[(((hh57 + (ww55 * 8)) + (cc57 * 64)) + (nn74 * 4096))]) + ((int33_t)hh57)))) : ((int64_t)(((int64_t)hh57) * ((int64_t)(((int33_t)layer3_2_residual2[(((hh57 + (ww55 * 8)) + (cc57 * 64)) + (nn74 * 4096))]) + ((int33_t)hh57))))))) + ((int64_t)hh57)));
          }
        }
      }
    }
    int32_t avgpool_res[64];
    int32_t avgpool_LB[64];
    int32_t avgpool;
    for (int32_t ii2 = 0; ii2 < 1; ++ii2) {
      for (int32_t cc58 = 0; cc58 < 64; ++cc58) {
        for (int32_t hh58 = 0; hh58 < 1; ++hh58) {
          for (int32_t avgpool_LB_i = 0; avgpool_LB_i < 8; ++avgpool_LB_i) {
            for (int32_t avgpool_LB_j = 0; avgpool_LB_j < 8; ++avgpool_LB_j) {
              avgpool_LB[(avgpool_LB_j + (avgpool_LB_i * 8))] = layer3_2_rprelu2[(((avgpool_LB_j + (((hh58 * 8) + avgpool_LB_i) * 8)) + (cc58 * 64)) + (ii2 * 4096))];
            }
          }
          int32_t avgpool_val;
          for (int32_t avgpool_ry = 0; avgpool_ry < 8; ++avgpool_ry) {
            for (int32_t avgpool_rx = 0; avgpool_rx < 8; ++avgpool_rx) {
              avgpool_val = ((int32_t)(((int33_t)avgpool_val) + ((int33_t)avgpool_LB[(avgpool_rx + (avgpool_ry * 8))])));
            }
          }
          avgpool_res[((hh58 + cc58) + (ii2 * 64))] = ((int32_t)(((int64_t)avgpool_val) / (int64_t)64));
        }
      }
    }
    int32_t flatten[64];
    for (int32_t i19 = 0; i19 < 1; ++i19) {
      for (int32_t j = 0; j < 64; ++j) {
        flatten[(j + (i19 * 64))] = avgpool_res[(j + (i19 * 64))];
      }
    }
    int32_t fc_matmul[10];
    for (int32_t i20 = 0; i20 < 1; ++i20) {
      for (int32_t j1 = 0; j1 < 10; ++j1) {
        float reducer0;
        for (int32_t ra6 = 0; ra6 < 64; ++ra6) {
          reducer0 = (((float)(((int64_t)flatten[(ra6 + (i20 * 64))]) * ((int64_t)ra6))) + reducer0);
        }
        fc_matmul[(j1 + (i20 * 10))] = ((int32_t)reducer0 * 1000000000000);
      }
    }
    for (int32_t i21 = 0; i21 < 1; ++i21) {
      for (int32_t j2 = 0; j2 < 10; ++j2) {
        fc[(j2 + (i21 * 10))] = ((int32_t)(((int33_t)fc_matmul[(j2 + (i21 * 10))]) + ((int33_t)j2)));
      }
    }
}


