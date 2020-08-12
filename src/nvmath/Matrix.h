// This code is in the public domain -- castanyo@yahoo.es

#pragma once

#include "Vector.h"
#include <simd/simd.h>

// - Matrices are stored in memory in *column major* order.
// - Points are to be though of as column vectors.
// - Transformation of a point p by a matrix M is: p' = M * p

namespace nv
{
    enum identity_t { identity };

    // 2x2 matrix.
    class Matrix2
    {
    public:
        Matrix2();
        explicit Matrix2(float f);
        explicit Matrix2(identity_t);
        Matrix2(const Matrix2 & m);
        Matrix2(const simd::float2 & v0, const simd::float2 & v1);
        Matrix2(float a, float b, float c, float d);
        
        float data(uint idx) const;
        float & data(uint idx);
        float get(uint row, uint col) const;
        float operator()(uint row, uint col) const;
        float & operator()(uint row, uint col);
        
        simd::float2 row(uint i) const;
        simd::float2 column(uint i) const;
        
        void operator*=(float s);
        void operator/=(float s);
        void operator+=(const Matrix2 & m);
        void operator-=(const Matrix2 & m);
        
        void scale(float s);
        void scale(const simd::float2 & s);
        float determinant() const;
        
    private:
        float m_data[4];
    };
    
    // Solve equation system using LU decomposition and back-substitution.
	extern bool solveLU(const Matrix2 & m, const simd::float2 & b, simd::float2 * x);
    
    // Solve equation system using Cramer's inverse.
    extern bool solveCramer(const Matrix2 & A, const simd::float2 & b, simd::float2 * x);
    
    
    // 3x3 matrix.
    class Matrix3
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

    extern Matrix3 inverse(const simd::float3 & m);
    

    // 4x4 matrix.
    class Matrix
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
