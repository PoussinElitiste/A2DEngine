// local include
#include <A2DEngine.hpp>

namespace Advanced2D
{
    A2DRectangle::A2DRectangle(int32 aLeft, int32 aTop, int32 aRight, int32 aBottom)
    {
        mLeft = static_cast<double64>(aLeft);
        mTop = static_cast<double64>(aTop);
        mRight = static_cast<double64>(aRight);
        mBottom = static_cast<double64>(aBottom);
    }

    A2DRectangle::A2DRectangle(double64 aLeft, double64 aTop, double64 aRight, double64 aBottom)
    {
        mLeft = aLeft;
        mTop = aTop;
        mRight = aRight;
        mBottom = aBottom;
    }

    bool8 A2DRectangle::IsInside(A2DVector3 aPoint)
    {
        return IsInside(aPoint(X), aPoint(Y));
    }

    bool8 A2DRectangle::IsInside(int32 aX, int32 aY)
    {
        return IsInside(static_cast<double64>(aX), static_cast<double64>(aY));
    }

    bool8 A2DRectangle::IsInside(double64 aX, double64 aY)
    {
        return ( aX > mLeft && aX < mRight 
               && aY > mTop && aY < mBottom );
    }
}; // namespace