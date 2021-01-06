extern "C" __global__ void default_function_kernel0(float* __restrict__ X, float* __restrict__ W, float* __restrict__ T_dense) {
  float T_dense_local[96];
  __shared__ float X_shared[768];
  __shared__ float W_shared[576];
  for (int i_c_inner_init = 0; i_c_inner_init < 4; ++i_c_inner_init) {
    for (int j_c_inner_init = 0; j_c_inner_init < 3; ++j_c_inner_init) {
      T_dense_local[(((i_c_inner_init * 3) + j_c_inner_init))] = 0.000000e+00f;
      T_dense_local[((((i_c_inner_init * 3) + j_c_inner_init) + 12))] = 0.000000e+00f;
      T_dense_local[((((i_c_inner_init * 3) + j_c_inner_init) + 24))] = 0.000000e+00f;
      T_dense_local[((((i_c_inner_init * 3) + j_c_inner_init) + 36))] = 0.000000e+00f;
      T_dense_local[((((i_c_inner_init * 3) + j_c_inner_init) + 48))] = 0.000000e+00f;
      T_dense_local[((((i_c_inner_init * 3) + j_c_inner_init) + 60))] = 0.000000e+00f;
      T_dense_local[((((i_c_inner_init * 3) + j_c_inner_init) + 72))] = 0.000000e+00f;
      T_dense_local[((((i_c_inner_init * 3) + j_c_inner_init) + 84))] = 0.000000e+00f;
    }
  }
  for (int k_outer_outer = 0; k_outer_outer < 128; ++k_outer_outer) {
    __syncthreads();
    for (int ax0_ax1_fused_outer_outer = 0; ax0_ax1_fused_outer_outer < 6; ++ax0_ax1_fused_outer_outer) {
      X_shared[(((ax0_ax1_fused_outer_outer * 128) + ((int)threadIdx.x)))] = X[((((((((int)blockIdx.x) / 24) * 98304) + ((((ax0_ax1_fused_outer_outer * 128) + ((int)threadIdx.x)) / 6) * 768)) + (k_outer_outer * 6)) + (((ax0_ax1_fused_outer_outer * 128) + ((int)threadIdx.x)) % 6)))];
    }
    for (int ax0_ax1_fused_outer_outer1 = 0; ax0_ax1_fused_outer_outer1 < 5; ++ax0_ax1_fused_outer_outer1) {
      if (((ax0_ax1_fused_outer_outer1 * 128) + ((int)threadIdx.x)) < 576) {
        W_shared[(((ax0_ax1_fused_outer_outer1 * 128) + ((int)threadIdx.x)))] = W[((((((((int)blockIdx.x) % 24) * 73728) + ((((ax0_ax1_fused_outer_outer1 * 128) + ((int)threadIdx.x)) / 6) * 768)) + (k_outer_outer * 6)) + (((ax0_ax1_fused_outer_outer1 * 128) + ((int)threadIdx.x)) % 6)))];
      }
    }
    __syncthreads();
    for (int k_inner = 0; k_inner < 6; ++k_inner) {
      for (int i_c_inner = 0; i_c_inner < 4; ++i_c_inner) {
        for (int j_c_inner = 0; j_c_inner < 3; ++j_c_inner) {
          T_dense_local[(((i_c_inner * 3) + j_c_inner))] = (T_dense_local[(((i_c_inner * 3) + j_c_inner))] + (X_shared[(((((((int)threadIdx.x) >> 3) * 24) + (i_c_inner * 6)) + k_inner))] * W_shared[(((((((int)threadIdx.x) & 7) * 18) + (j_c_inner * 6)) + k_inner))]));
          T_dense_local[((((i_c_inner * 3) + j_c_inner) + 12))] = (T_dense_local[((((i_c_inner * 3) + j_c_inner) + 12))] + (X_shared[(((((((int)threadIdx.x) >> 3) * 24) + (i_c_inner * 6)) + k_inner))] * W_shared[((((((((int)threadIdx.x) & 7) * 18) + (j_c_inner * 6)) + k_inner) + 144))]));
          T_dense_local[((((i_c_inner * 3) + j_c_inner) + 24))] = (T_dense_local[((((i_c_inner * 3) + j_c_inner) + 24))] + (X_shared[(((((((int)threadIdx.x) >> 3) * 24) + (i_c_inner * 6)) + k_inner))] * W_shared[((((((((int)threadIdx.x) & 7) * 18) + (j_c_inner * 6)) + k_inner) + 288))]));
          T_dense_local[((((i_c_inner * 3) + j_c_inner) + 36))] = (T_dense_local[((((i_c_inner * 3) + j_c_inner) + 36))] + (X_shared[(((((((int)threadIdx.x) >> 3) * 24) + (i_c_inner * 6)) + k_inner))] * W_shared[((((((((int)threadIdx.x) & 7) * 18) + (j_c_inner * 6)) + k_inner) + 432))]));
          T_dense_local[((((i_c_inner * 3) + j_c_inner) + 48))] = (T_dense_local[((((i_c_inner * 3) + j_c_inner) + 48))] + (X_shared[((((((((int)threadIdx.x) >> 3) * 24) + (i_c_inner * 6)) + k_inner) + 384))] * W_shared[(((((((int)threadIdx.x) & 7) * 18) + (j_c_inner * 6)) + k_inner))]));
          T_dense_local[((((i_c_inner * 3) + j_c_inner) + 60))] = (T_dense_local[((((i_c_inner * 3) + j_c_inner) + 60))] + (X_shared[((((((((int)threadIdx.x) >> 3) * 24) + (i_c_inner * 6)) + k_inner) + 384))] * W_shared[((((((((int)threadIdx.x) & 7) * 18) + (j_c_inner * 6)) + k_inner) + 144))]));
          T_dense_local[((((i_c_inner * 3) + j_c_inner) + 72))] = (T_dense_local[((((i_c_inner * 3) + j_c_inner) + 72))] + (X_shared[((((((((int)threadIdx.x) >> 3) * 24) + (i_c_inner * 6)) + k_inner) + 384))] * W_shared[((((((((int)threadIdx.x) & 7) * 18) + (j_c_inner * 6)) + k_inner) + 288))]));
          T_dense_local[((((i_c_inner * 3) + j_c_inner) + 84))] = (T_dense_local[((((i_c_inner * 3) + j_c_inner) + 84))] + (X_shared[((((((((int)threadIdx.x) >> 3) * 24) + (i_c_inner * 6)) + k_inner) + 384))] * W_shared[((((((((int)threadIdx.x) & 7) * 18) + (j_c_inner * 6)) + k_inner) + 432))]));
        }
      }
    }
  }
  for (int i_inner = 0; i_inner < 4; ++i_inner) {
    for (int j_inner = 0; j_inner < 3; ++j_inner) {
      T_dense[((((((((((int)blockIdx.x) / 24) * 294912) + ((((int)threadIdx.x) >> 3) * 9216)) + (i_inner * 2304)) + ((((int)blockIdx.x) % 24) * 96)) + ((((int)threadIdx.x) & 7) * 3)) + j_inner))] = T_dense_local[(((i_inner * 3) + j_inner))];
      T_dense[(((((((((((int)blockIdx.x) / 24) * 294912) + ((((int)threadIdx.x) >> 3) * 9216)) + (i_inner * 2304)) + ((((int)blockIdx.x) % 24) * 96)) + ((((int)threadIdx.x) & 7) * 3)) + j_inner) + 24))] = T_dense_local[((((i_inner * 3) + j_inner) + 12))];
      T_dense[(((((((((((int)blockIdx.x) / 24) * 294912) + ((((int)threadIdx.x) >> 3) * 9216)) + (i_inner * 2304)) + ((((int)blockIdx.x) % 24) * 96)) + ((((int)threadIdx.x) & 7) * 3)) + j_inner) + 48))] = T_dense_local[((((i_inner * 3) + j_inner) + 24))];
      T_dense[(((((((((((int)blockIdx.x) / 24) * 294912) + ((((int)threadIdx.x) >> 3) * 9216)) + (i_inner * 2304)) + ((((int)blockIdx.x) % 24) * 96)) + ((((int)threadIdx.x) & 7) * 3)) + j_inner) + 72))] = T_dense_local[((((i_inner * 3) + j_inner) + 36))];
      T_dense[(((((((((((int)blockIdx.x) / 24) * 294912) + ((((int)threadIdx.x) >> 3) * 9216)) + (i_inner * 2304)) + ((((int)blockIdx.x) % 24) * 96)) + ((((int)threadIdx.x) & 7) * 3)) + j_inner) + 147456))] = T_dense_local[((((i_inner * 3) + j_inner) + 48))];
      T_dense[(((((((((((int)blockIdx.x) / 24) * 294912) + ((((int)threadIdx.x) >> 3) * 9216)) + (i_inner * 2304)) + ((((int)blockIdx.x) % 24) * 96)) + ((((int)threadIdx.x) & 7) * 3)) + j_inner) + 147480))] = T_dense_local[((((i_inner * 3) + j_inner) + 60))];
      T_dense[(((((((((((int)blockIdx.x) / 24) * 294912) + ((((int)threadIdx.x) >> 3) * 9216)) + (i_inner * 2304)) + ((((int)blockIdx.x) % 24) * 96)) + ((((int)threadIdx.x) & 7) * 3)) + j_inner) + 147504))] = T_dense_local[((((i_inner * 3) + j_inner) + 72))];
      T_dense[(((((((((((int)blockIdx.x) / 24) * 294912) + ((((int)threadIdx.x) >> 3) * 9216)) + (i_inner * 2304)) + ((((int)blockIdx.x) % 24) * 96)) + ((((int)threadIdx.x) & 7) * 3)) + j_inner) + 147528))] = T_dense_local[((((i_inner * 3) + j_inner) + 84))];
    }
  }
}
