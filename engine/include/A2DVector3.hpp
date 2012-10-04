#ifndef INC_ADVANCED2D_A2DVECTOR3_HPP
#define INC_ADVANCED2D_A2DVECTOR3_HPP

// external include
#include <d3dx9Math.h>

// local include
#include <A2DTypes.hpp>

namespace Advanced2D
{
    struct A2DVector3
        : public D3DXVECTOR3
    {
        A2DVector3(float32 x = 0.f, float32 y = 0.f, float32 z = 0.f);
        virtual ~A2DVector3();
    }; // A2DVector3
} // Advanced2D

#endif // INC_ADVANCED2D_A2DVECTOR3_HPP