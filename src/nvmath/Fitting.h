// This code is in the public domain -- Ignacio Castaño <castano@gmail.com>
#pragma once

#include "nvmath.h" // NV_EPSILON
#include <simd/simd.h>
#include "Plane.h"

namespace nv
{
    namespace Fit
    {
        simd::float3 computeCentroid(int n, const simd::float3 * points);
        simd::float3 computeCentroid(int n, const simd::float3 * points, const float * weights, const simd::float3 & metric);

        simd::float4 computeCentroid(int n, const simd::float4 * points);
        simd::float4 computeCentroid(int n, const simd::float4 * points, const float * weights, const simd::float4 & metric);

        simd::float3 computeCovariance(int n, const simd::float3 * points, float * covariance);
        simd::float3 computeCovariance(int n, const simd::float3 * points, const float * weights, const simd::float3 & metric, float * covariance);

        simd::float4 computeCovariance(int n, const simd::float4 * points, float * covariance);
        simd::float4 computeCovariance(int n, const simd::float4 * points, const float * weights, const simd::float4 & metric, float * covariance);

        simd::float3 computePrincipalComponent_PowerMethod(int n, const simd::float3 * points);
        simd::float3 computePrincipalComponent_PowerMethod(int n, const simd::float3 * points, const float * weights, const simd::float3 & metric);

        simd::float3 computePrincipalComponent_EigenSolver(int n, const simd::float3 * points);
        simd::float3 computePrincipalComponent_EigenSolver(int n, const simd::float3 * points, const float * weights, const simd::float3 & metric);

		simd::float4 computePrincipalComponent_EigenSolver(int n, const simd::float4 * points);
        simd::float4 computePrincipalComponent_EigenSolver(int n, const simd::float4 * points, const float * weights, const simd::float4 & metric);

        simd::float3 computePrincipalComponent_SVD(int n, const simd::float3 * points);
        simd::float4 computePrincipalComponent_SVD(int n, const simd::float4 * points);

        Plane bestPlane(int n, const simd::float3 * points);
        bool isPlanar(int n, const simd::float3 * points, float epsilon = NV_EPSILON);

        bool eigenSolveSymmetric3(const float matrix[6], float eigenValues[3], simd::float3 eigenVectors[3]);
        bool eigenSolveSymmetric4(const float matrix[10], float eigenValues[4], simd::float4 eigenVectors[4]);

        // Returns number of clusters [1-4].
        int compute4Means(int n, const simd::float3 * points, const float * weights, const simd::float3 & metric, simd::float3 * cluster);
    }

} // nv namespace
