// local include
#include <A2DEngine.hpp>

namespace Advanced2D
{
    double64 A2DMath::ToDegrees(double64 aRadian)
    {
        return aRadian * PI_under_180;
    }
    
    double64 A2DMath::ToRadians(double64 aDegree)
    {
        return aDegree * PI_over_180;
    }

    double64 A2DMath::WrapAngleDegs(double64 aDegs)
    {
        double64 result = fmod(aDegs, 360.0);
        if (result < 0) 
        { result += 360.0f; }
        return result;
    }

    double64 A2DMath::WrapAngleRads(double64 aRads)
    {
        double64 result = fmod(aRads, PI * 2.0);
        if (result < 0) 
        { result += PI * 2.0; }
        return result;
    }

    double64 A2DMath::LinearVelocityX(double64 aAngle)
    {
        aAngle -= 90;
        if (aAngle < 0) 
        { aAngle = 360 + aAngle; }
        return cos( aAngle * PI_over_180);
    }

    double64 A2DMath::LinearVelocityY(double64 aAngle)
    {
        aAngle -= 90;
        if (aAngle < 0) 
        { aAngle = 360 + aAngle; }
        return sin( aAngle * PI_over_180);
    }

    A2DVector3 A2DMath::LinearVelocity(double64 aAngle)
    {
        double64 vx = LinearVelocityX(aAngle);
        double64 vy = LinearVelocityY(aAngle);
        return A2DVector3(vx,vy,0.0f);
    }

    double64 A2DMath::AngleToTarget(double64 aX1, double64 aY1, double64 aX2, double64 aY2)
    {
        double64 deltaX = (aX2 - aX1);
        double64 deltaY = (aY2 - aY1);
        return atan2(deltaY,deltaX);
    }

    double64 A2DMath::AngleToTarget(A2DVector3& aSource, A2DVector3& aTarget)
    {
        return AngleToTarget(aSource(X), aSource(Y), aTarget(X), aTarget(Y));
    }

    double64 A2DMath::Distance(double64 aX1, double64 aY1, double64 aX2, double64 aY2)
    {
        double64 deltaX = (aX2 - aX1);
        double64 deltaY = (aY2 - aY1);
        return sqrt(deltaX*deltaX + deltaY*deltaY);
    }

    double64 A2DMath::Distance(A2DVector3& aVec1, A2DVector3& aVec2)
    {
        return Distance(aVec1(X), aVec1(Y), aVec2(X), aVec2(Y));
    }

    double64 A2DMath::Length(double64 aX, double64 aY, double64 aZ)
    {
        return sqrt(aX*aX + aY*aY + aZ*aZ);
    }

    double64 A2DMath::Length(A2DVector3& aVector)
    {
        return Length(aVector(X), aVector(Y), aVector(Z));
    }

    double64 A2DMath::DotProduct(double64 aX1, double64 aY1, double64 aZ1, double64 aX2, double64 aY2, double64 aZ2)
    {
        return (aX1*aX2 + aY1*aY2 + aZ1*aZ2);
    }

    double64 A2DMath::DotProduct(A2DVector3& aVec1, A2DVector3& aVec2)
    {
        return DotProduct(aVec1(X), aVec1(Y), aVec1(Z), aVec2(X), aVec2(Y), aVec2(Z));
    }

    A2DVector3 A2DMath::CrossProduct(double64 aX1, double64 aY1, double64 aZ1, double64 aX2, double64 aY2, double64 aZ2)
    {
        double64 nx = (aY1 * aZ2) - (aZ1 * aY2);
        double64 ny = (aZ1 * aY2) - (aX1 * aZ2);
        double64 nz = (aX1 * aY2) - (aY1 * aX2);
        return A2DVector3(nx, ny, nz);
    }

    A2DVector3 A2DMath::CrossProduct(A2DVector3& aVec1, A2DVector3& aVec2)
    {
        return CrossProduct(aVec1(X), aVec1(Y), aVec1(Z), aVec2(X), aVec2(Y), aVec2(Z));
    }

    A2DVector3 A2DMath::Normal(double64 aX, double64 aY, double64 aZ)
    {
        double64 length = Length(aX, aY, aZ);
        if (length != 0) 
        { length = 1 / length; }
        double64 nx = aX * length;
        double64 ny = aY * length;
        double64 nz = aZ * length;
        return A2DVector3(nx, ny, nz);
    }

    A2DVector3 A2DMath::Normal(A2DVector3& aVector)
    {
        return Normal(aVector(X), aVector(Y), aVector(Z));
    }
} // Advanced2D