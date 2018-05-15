// This code is in the public domain -- castanyo@yahoo.es

#pragma once
#ifndef NV_MATH_MATRIX_H
#define NV_MATH_MATRIX_H

#include <simd/simd.h>

// - Matrices are stored in memory in *column major* order.
// - Points are to be though of as column vectors.
// - Transformation of a point p by a matrix M is: p' = M * p

namespace nv
{
    enum identity_t { identity };

    // 3x3 matrix.
    class NVMATH_CLASS Matrix3
    {
    public:
        Matrix3();
        explicit Matrix3(float f);
        explicit Matrix3(identity_t);
        Matrix3(const Matrix3 & m);
        Matrix3(const simd::float3 & v0, const simd::float3 & v1, const simd::float3 & v2);

        float data(uint idx) const;
        float & data(uint idx);
        float get(uint row, uint col) const;
        float operator()(uint row, uint col) const;
        float & operator()(uint row, uint col);

        simd::float3 row(uint i) const;
        simd::float3 column(uint i) const;

        void operator*=(float s);
        void operator/=(float s);
        void operator+=(const Matrix3 & m);
        void operator-=(const Matrix3 & m);

        void scale(float s);
        void scale(const simd::float3 & s);
        float determinant() const;

    private:
        float m_data[9];
    };

    // Solve equation system using LU decomposition and back-substitution.
    extern bool solveLU(const Matrix3 & m, const simd::float3 & b, simd::float3 * x);

    // Solve equation system using Cramer's inverse.
    extern bool solveCramer(const Matrix3 & A, const simd::float3 & b, simd::float3 * x);


    // 4x4 matrix.
    class NVMATH_CLASS Matrix
    {
    public:
        typedef Matrix const & Arg;

        Matrix();
        explicit Matrix(float f);
        explicit Matrix(identity_t);
        Matrix(const Matrix3 & m);
        Matrix(const Matrix & m);
        Matrix(const simd::float4 & v0, const simd::float4 & v1, const simd::float4 & v2, const simd::float4 & v3);
        //explicit Matrix(const float m[]);	// m is assumed to contain 16 elements

        float data(uint idx) const;
        float & data(uint idx);
        float get(uint row, uint col) const;
        float operator()(uint row, uint col) const;
        float & operator()(uint row, uint col);
        const float * ptr() const;

        simd::float4 row(uint i) const;
        simd::float4 column(uint i) const;

        void zero();
        void identity();

        void scale(float s);
        void scale(const simd::float3 & s);
        void translate(const simd::float3 & t);
        void rotate(float theta, float v0, float v1, float v2);
        float determinant() const;

        void operator+=(const Matrix & m);
        void operator-=(const Matrix & m);

        void apply(Matrix::Arg m);

    private:
        float m_data[16];
    };

    // Solve equation system using LU decomposition and back-substitution.
    extern bool solveLU(const Matrix & A, const simd::float4 & b, simd::float4 * x);

    // Solve equation system using Cramer's inverse.
    extern bool solveCramer(const Matrix & A, const simd::float4 & b, simd::float4 * x);

    // Compute inverse using LU decomposition.
    extern Matrix inverseLU(const Matrix & m);

    // Compute inverse using Gaussian elimination and partial pivoting.
    extern Matrix inverse(const Matrix & m);
    extern Matrix3 inverse(const Matrix3 & m);

} // nv namespace

#endif // NV_MATH_MATRIX_H
