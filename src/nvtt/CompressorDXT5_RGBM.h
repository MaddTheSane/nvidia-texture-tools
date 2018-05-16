#include <simd/simd.h>

namespace nv {

    struct BlockDXT5;

    float compress_dxt5_rgbm(const simd::float4 input_colors[16], const float input_weights[16], float min_m, BlockDXT5 * output);
    float compress_etc2_rgbm(simd::float4 input_colors[16], float input_weights[16], float min_m, void * output);
}
