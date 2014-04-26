#ifndef INC_ADVANCED2D_A2DMATH_HPP
#define INC_ADVANCED2D_A2DMATH_HPP

// local include
#include <A2DTypes.hpp>
#include <A2DVector3.hpp>

namespace Advanced2D
{   
    static const double64 PI = 3.1415926535;
    static const double64 PI_over_180 = PI / 180.0f;
    static const double64 PI_under_180 = 180.0f / PI;

    //-----------------------------------------------------------
    // A2DMath
    //-----------------------------------------------------------
    class A2DMath
    {
    public:
        double64 ToDegrees(double64 aRadian);
        double64 ToRadians(double64 aDegree);
        double64 WrapAngleDegs(double64 aDegs);
        double64 WrapAngleRads(double64 aRads);
        double64 LinearVelocityX(double64 aAngle);
        double64 LinearVelocityY(double64 aAngle);
        A2DVector3 LinearVelocity(double64 aAngle);
        double64 AngleToTarget(double64 aX1, double64 aY1, double64 aX2, double64 aY2);
        double64 AngleToTarget(A2DVector3 &aSource, A2DVector3 &aTarget);
        double64 Distance(double64 aX1, double64 aY1, double64 aX2, double64 aY2);
        double64 Distance(A2DVector3 &aVec1, A2DVector3 &aVec2);
        double64 Length(double64 aX, double64 aY, double64 aZ);
        double64 Length(A2DVector3 &aVector);
        double64 DotProduct(double64 aX1, double64 aY1, double64 aZ1, double64 aX2, double64 aY2, double64 aZ2);
        double64 DotProduct(A2DVector3 &aVec1, A2DVector3 &aVec2);
        A2DVector3 CrossProduct(double64 aX1, double64 aY1, double64 aZ1, double64 aX2, double64 aY2, double64 aZ2);
        A2DVector3 CrossProduct(A2DVector3 &aVec1, A2DVector3 &aVec2);
        A2DVector3 Normal(double64 aX, double64 aY, double64 aZ);
        A2DVector3 Normal(A2DVector3 &aVector);
    }; // class
} // namespace

#endif // INC_ADVANCED2D_A2DMATH_HPP