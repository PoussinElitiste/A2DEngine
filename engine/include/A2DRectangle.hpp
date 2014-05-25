#ifndef INC_ADVANCED2D_A2DRECTANGLE_HPP
#define INC_ADVANCED2D_A2DRECTANGLE_HPP

// local include
#include <A2DTypes.hpp>
#include <A2DVector3.hpp>

namespace Advanced2D
{
    class A2DRectangle 
    {
    public:
        double64 mLeft, mTop, mRight, mBottom;

    public:
        A2DRectangle(int32 aLeft, int32 aTop, int32 aRight, int32 aBottom);
        A2DRectangle(double64 aLeft, double64 aTop, double64 aRight, double64 aBottom);
        virtual ~A2DRectangle() {}

        double64 getLeft() { return mLeft; }
        double64 getTop() { return mTop; }
        double64 getRight() { return mRight; }
        double64 getBottom() { return mBottom; }
        bool8 isInside(A2DVector3 aPoint);
        bool8 isInside(int32 aX, int32 aY);
        bool8 isInside(double64 aX, double64 aY);
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DRECTANGLE_HPP