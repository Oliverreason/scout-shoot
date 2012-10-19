#pragma once
#include "std.h"

namespace kXNA
{
    class Vector3
    {
    public:
        Vector3(void);
        ~Vector3(void);

        //inline FLOAT GetX() const { return m_Vector.x; }
        //inline void SetX(FLOAT fX) { m_Vector.x = fX; }
        //inline FLOAT GetY() const { return m_Vector.y; }
        //inline void SetY(FLOAT fY) { m_Vector.y = fY; }
        //inline FLOAT GetZ() const { return m_Vector.z; }
        //inline void SetZ(FLOAT fZ) { m_Vector.z = fZ; }

    private:
        XMVECTOR m_Vector;
    };
}

