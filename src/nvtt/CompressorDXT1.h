
#include <simd/simd.h>

namespace nv {

    class Color32;
    struct ColorBlock;
    struct BlockDXT1;

    // All these functions return MSE.

    float compress_dxt1_single_color_optimal(Color32 c, BlockDXT1 * output);
    float compress_dxt1_single_color_optimal(const simd::float3 & color, BlockDXT1 * output);

    float compress_dxt1_single_color(const simd::float3 * colors, const float * weights, int count, const simd::float3 & color_weights, BlockDXT1 * output);
    float compress_dxt1_least_squares_fit(const simd::float4 input_colors[16], const simd::float3 * colors, const float * weights, int count, const simd::float3 & color_weights, BlockDXT1 * output);
    float compress_dxt1_bounding_box_exhaustive(const simd::float4 input_colors[16], const simd::float3 * colors, const float * weights, int count, const simd::float3 & color_weights, bool three_color_mode, int search_limit, BlockDXT1 * output);
    void compress_dxt1_cluster_fit(const simd::float4 input_colors[16], const simd::float3 * colors, const float * weights, int count, const simd::float3 & color_weights, bool three_color_mode, BlockDXT1 * output);


    float compress_dxt1(const simd::float4 input_colors[16], const float input_weights[16], const simd::float3 & color_weights, bool three_color_mode, BlockDXT1 * output);

}
