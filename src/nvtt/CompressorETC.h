#include "nvcore/nvcore.h"
#include <simd/simd.h>

namespace nv {
    
    void decompress_etc(const void * input_block, simd::float4 output_colors[16]);
    void decompress_eac(const void * input_block, simd::float4 output_colors[16], int output_channel);
    void decompress_etc_eac(const void * input_block, simd::float4 output_colors[16]);

    float compress_etc1(simd::float4 input_colors[16], float input_weights[16], const simd::float3 & color_weights, void * output);
    float compress_etc2(simd::float4 input_colors[16], float input_weights[16], const simd::float3 & color_weights, void * output);
    float compress_etc2_a1(simd::float4 input_colors[16], float input_weights[16], const simd::float3 & color_weights, void * output);
    float compress_eac(simd::float4 input_colors[16], float input_weights[16], int input_channel, int search_radius, bool use_11bit_mode, void * output);
    float compress_etc2_eac(simd::float4 input_colors[16], float input_weights[16], const simd::float3 & color_weights, void * output);

}


