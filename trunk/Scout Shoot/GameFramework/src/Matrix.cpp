#include "Matrix.h"
#include "OgreVector3.h"

using namespace kXNA;

Matrix::Matrix(void)
{
    m_Matrix = XMMATRIX(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);
}

Matrix::Matrix(const XMMATRIX& matrix)
{
    m_Matrix = matrix;
}

Matrix::~Matrix(void)
{
}

//Matrix kXNA::Matrix::CreateFromAxisAngle(Ogre::Vector3 vec3Axis, FLOAT fAngle)
//{
//
//}
