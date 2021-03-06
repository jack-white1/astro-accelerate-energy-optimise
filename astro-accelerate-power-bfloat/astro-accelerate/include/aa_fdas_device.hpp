#ifndef ASTRO_ACCELERATE_AA_FDAS_DEVICE_HPP
#define ASTRO_ACCELERATE_AA_FDAS_DEVICE_HPP

#include <cufft.h>
#include <stdio.h>
#include <cuda_runtime.h>
#include "aa_fdas_device.hpp"
#include "aa_params.hpp"
#include "cuda_bf16.h"

namespace astroaccelerate {

  /** \brief CUDA kernels. */

  __global__ void cuda_overlap_copy(__nv_bfloat162* d_ext_data, __nv_bfloat162* d_cpx_signal, int sigblock,  int sig_rfftlen, int sig_tot_convlen, int kern_offset, int total_blocks);

  /** \brief Kernel wrapper function for overlap_copy kernel function. */
  void call_kernel_cuda_overlap_copy(__nv_bfloat162 *const d_ext_data, __nv_bfloat162 *const d_cpx_signal, const int &sigblock, const int &sig_rfftlen, const int &sig_tot_convlen, const int &kern_offset, const int &total_blocks);
  
  __global__ void cuda_overlap_copy_smallblk(__nv_bfloat162* d_ext_data, __nv_bfloat162* d_cpx_signal, int sigblock,  int sig_rfftlen, int sig_tot_convlen, int kern_offset, int total_blocks);

  /** \brief Kernel wrapper function for cuda_overlap_copy_smallbl kernel function. */
  void call_kernel_cuda_overlap_copy_smallblk(const int &blocks, __nv_bfloat162 *const d_ext_data, __nv_bfloat162 *const d_cpx_signal, const int &sigblock, const int &sig_rfftlen, const int &sig_tot_convlen, const int &kern_offset, const int &total_blocks);

  __global__ void cuda_convolve_reg_1d_halftemps(__nv_bfloat162* d_kernel, __nv_bfloat162* d_signal, __nv_bfloat162* d_ffdot_plane, int sig_tot_convlen, float scale);

  /** \brief Kernel wrapper function for cuda_convolve_reg_1d_halftemps kernel function. */
  void call_kernel_cuda_convolve_reg_1d_halftemps(const int &blocks, const int &threads, __nv_bfloat162 *const d_kernel, __nv_bfloat162 *const d_signal, __nv_bfloat162 *const d_ffdot_plane, const int &sig_tot_convlen, const float &scale);

  __global__ void cuda_ffdotpow_concat_2d(__nv_bfloat162* d_ffdot_plane_cpx, __nv_bfloat16* d_ffdot_plane, int sigblock, int kern_offset, int total_blocks,  int sig_tot_convlen, int sig_totlen);

  /** \brief Kernel wrapper function for cuda_ffdotpow_concat_2d kernel function. */
  void call_kernel_cuda_ffdotpow_concat_2d(const dim3 &blocks, const dim3 &threads, __nv_bfloat162 *const d_ffdot_plane_cpx, __nv_bfloat16 *const d_ffdot_plane, const int &sigblock, const int &kern_offset, const int &total_blocks, const int &sig_tot_convlen, const int &sig_totlen);

  __global__ void cuda_ffdotpow_concat_2d_temp(__nv_bfloat162* d_ffdot_plane_cpx, __nv_bfloat162* d_ffdot_plane, int sigblock, int kern_offset, int total_blocks,  int sig_tot_convlen, int sig_totlen);

  /** \brief Kernel wrapper function for cuda_ffdotpow_concat_2d kernel function. */
  void call_kernel_cuda_ffdotpow_concat_2d_temp(const dim3 &blocks, const dim3 &threads, __nv_bfloat162 *const d_ffdot_plane_cpx, __nv_bfloat162 *const d_ffdot_plane, const int &sigblock, const int &kern_offset, const int &total_blocks, const int &sig_tot_convlen, const int &sig_totlen);

  __global__ void cuda_ffdotpow_concat_2d_inbin(__nv_bfloat162* d_ffdot_plane_cpx, __nv_bfloat16* d_ffdot_plane, int sigblock, int kern_offset, int total_blocks, int  sig_tot_convlen, int sig_totlen);

  /** \brief Kernel wrapper function for cuda_ffdotpow_concat_2d_inbin kernel function. */
  void call_kernel_cuda_ffdotpow_concat_2d_inbin(const dim3 &blocks, const dim3 &threads, __nv_bfloat162 *const d_ffdot_plane_cpx, __nv_bfloat16 *const d_ffdot_plane, const int &sigblock, const int &kern_offset, const int &total_blocks, const int &sig_tot_convlen, const int &sig_totlen);

  __global__ void cuda_ffdotpow_concat_2d_ndm_inbin(__nv_bfloat162* d_ffdot_plane_cpx, __nv_bfloat16* d_ffdot_plane, int kernlen, int siglen, int nkern, int kern_offset, int total_blocks, int sig_tot_convlen, int sig_totlen, int ndm);

  __global__ void cuda_convolve_customfft_wes_no_reorder02(__nv_bfloat162* d_kernel, __nv_bfloat162* d_signal, __nv_bfloat16 *d_ffdot_pw, int sigblock, int sig_tot_convlen, int sig_totlen, int offset, float scale);

  /** \brief Kernel wrapper function for cuda_convolve_customfft_wes_no_reorder02 kernel function. */
  void call_kernel_cuda_convolve_customfft_wes_no_reorder02(const int &blocks, __nv_bfloat162 *const d_kernel, __nv_bfloat162 *const d_signal, __nv_bfloat16 *const d_ffdot_pw, const int &sigblock, const int &sig_tot_convlen, const int &sig_totlen, const int &offset, const float &scale);

  __global__ void cuda_convolve_customfft_wes_no_reorder02_inbin(__nv_bfloat162* d_kernel, __nv_bfloat162* d_signal, __nv_bfloat16 *d_ffdot_pw, int sigblock, int sig_tot_convlen, int sig_totlen, int offset, float scale, float2 *ip_edge_points);

  /** \brief Kernel wrapper function for cuda_convolve_customfft_wes_no_reorder02_inbin kernel function. */
  void call_kernel_cuda_convolve_customfft_wes_no_reorder02_inbin(const int &blocks, __nv_bfloat162 *const d_kernel, __nv_bfloat162 *const d_signal, __nv_bfloat16 *const d_ffdot_pw, const int &sigblock, const int &sig_tot_convlen, const int &sig_totlen, const int &offset, const float &scale, float2 *const ip_edge_points);

  __global__ void GPU_CONV_kFFT_mk11_2elem_2v(__nv_bfloat162 const* __restrict__ d_input_signal, __nv_bfloat16 *d_output_plane_reduced, __nv_bfloat162 const* __restrict__ d_templates, int useful_part_size, int offset, int nConvolutions, float scale);

  __global__ void GPU_CONV_kFFT_mk11_4elem_2v(__nv_bfloat162 const* __restrict__ d_input_signal, __nv_bfloat16 *d_output_plane_reduced, __nv_bfloat162 const* __restrict__ d_templates, int useful_part_size, int offset, int nConvolutions, float scale);

  /** \brief Kernel wrapper function for GPU_CONV_kFFT_mk11_4elem_2v kernel function. */
  void call_kernel_GPU_CONV_kFFT_mk11_4elem_2v(const dim3 &grid_size, const dim3 &block_size, __nv_bfloat162 const*const d_input_signal, __nv_bfloat16 *const d_output_plane_reduced, __nv_bfloat162 const*const d_templates, const int &useful_part_size, const int &offset, const int &nConvolutions, const float &scale);

  __global__ void customfft_fwd_temps_no_reorder(__nv_bfloat162* d_signal);

  /** \brief Kernel wrapper function for customfft_fwd_temps_no_reorder kernel function. */
  void call_kernel_customfft_fwd_temps_no_reorder(__nv_bfloat162 *const d_signal);

  void call_kernel_cast_bfloat16_to_float(float *d_output, __nv_bfloat16 *d_input, size_t data_length_bytes);

  __global__ void cast_bfloat16_to_float(float *d_output, __nv_bfloat16 *d_input, unsigned long long N_floats);

  void call_kernel_cast_bfloat162_to_float2(float2 *d_output, __nv_bfloat162 *d_input, size_t data_length_bytes);

  __global__ void cast_bfloat162_to_float2(float2 *d_output, __nv_bfloat162 *d_input, unsigned long long N_floats);

  void call_kernel_cast_float_to_bfloat16(__nv_bfloat16 *d_output, float *d_input, size_t data_length_bytes);

  __global__ void cast_float_to_bfloat16(__nv_bfloat16 *d_output, float *d_input, unsigned long long N_floats);

  void call_kernel_cast_float2_to_bfloat162(__nv_bfloat162 *d_output, float2 *d_input, size_t data_length_bytes);

  __global__ void cast_float2_to_bfloat162(__nv_bfloat162 *d_output, float2 *d_input, unsigned long long N_floats);

  void call_kernel_cast_float_to_bfloat16_down(__nv_bfloat16 *d_output, float *d_input, size_t data_length_bytes);

__global__ void cast_float_to_bfloat16_down(__nv_bfloat16 *d_output, float *d_input, unsigned long long N_floats);

void call_kernel_cast_float_to_bfloat16_up(__nv_bfloat16 *d_output, float *d_input, size_t data_length_bytes);

__global__ void cast_float_to_bfloat16_up(__nv_bfloat16 *d_output, float *d_input, unsigned long long N_floats);

void call_kernel_cast_float2_to_bfloat162_down(__nv_bfloat162 *d_output, float2 *d_input, size_t data_length_bytes);

__global__ void cast_float2_to_bfloat162_down(__nv_bfloat162 *d_output, float2 *d_input, unsigned long long N_floats);

void call_kernel_cast_float2_to_bfloat162_up(__nv_bfloat162 *d_output, float2 *d_input, size_t data_length_bytes);

__global__ void cast_float2_to_bfloat162_up(__nv_bfloat162 *d_output, float2 *d_input, unsigned long long N_floats);

} // namespace astroaccelerate

#endif // ASTRO_ACCELERATE_AA_FDAS_DEVICE_HPP
