#pragma once
#include "std.h"

namespace kXNA
{
    namespace Ogre
    {
        class Vector3;
    }

    class Matrix
    {
    public:
        Matrix(void);
        Matrix(const XMMATRIX& matrix);
        ~Matrix(void);

        inline FLOAT GetM11() const { return m_Matrix._11; }
        inline void SetM11(FLOAT fM11) { m_Matrix._11 = fM11; }
        inline FLOAT GetM12() const { return m_Matrix._12; }
        inline void SetM12(FLOAT fM12) { m_Matrix._12 = fM12; }
        inline FLOAT GetM13() const { return m_Matrix._13; }
        inline void SetM13(FLOAT fM13) { m_Matrix._13 = fM13; }
        inline FLOAT GetM14() const { return m_Matrix._14; }
        inline void SetM14(FLOAT fM14) { m_Matrix._14 = fM14; }
        inline FLOAT GetM21() const { return m_Matrix._21; }
        inline void SetM21(FLOAT fM21) { m_Matrix._21 = fM21; }
        inline FLOAT GetM22() const { return m_Matrix._22; }
        inline void SetM22(FLOAT fM22) { m_Matrix._22 = fM22; }
        inline FLOAT GetM23() const { return m_Matrix._23; }
        inline void SetM23(FLOAT fM23) { m_Matrix._23 = fM23; }
        inline FLOAT GetM24() const { return m_Matrix._24; }
        inline void SetM24(FLOAT fM24) { m_Matrix._24 = fM24; }
        inline FLOAT GetM31() const { return m_Matrix._31; }
        inline void SetM31(FLOAT fM31) { m_Matrix._31 = fM31; }
        inline FLOAT GetM32() const { return m_Matrix._32; }
        inline void SetM32(FLOAT fM32) { m_Matrix._32 = fM32; }
        inline FLOAT GetM33() const { return m_Matrix._33; }
        inline void SetM33(FLOAT fM33) { m_Matrix._33 = fM33; }
        inline FLOAT GetM34() const { return m_Matrix._34; }
        inline void SetM34(FLOAT fM34) { m_Matrix._34 = fM34; }
        inline FLOAT GetM41() const { return m_Matrix._41; }
        inline void SetM41(FLOAT fM41) { m_Matrix._41 = fM41; }
        inline FLOAT GetM42() const { return m_Matrix._42; }
        inline void SetM42(FLOAT fM42) { m_Matrix._42 = fM42; }
        inline FLOAT GetM43() const { return m_Matrix._43; }
        inline void SetM43(FLOAT fM43) { m_Matrix._43 = fM43; }
        inline FLOAT GetM44() const { return m_Matrix._44; }
        inline void SetM44(FLOAT fM44) { m_Matrix._44 = fM44; }

        static Matrix GetIdentity() { return Matrix(); }

        //static Matrix CreateFromAxisAngle(Ogre::Vector3 vec3Axis, FLOAT fAngle);

    private:
        XMMATRIX m_Matrix;
    };
}

