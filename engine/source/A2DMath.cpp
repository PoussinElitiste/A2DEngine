// local include
#include <A2DEngine.hpp>

namespace Advanced2D
{
    double64 A2DMath::toDegrees(double64 aRadian)
    {
        return aRadian * PI_under_180;
    }
    
    double64 A2DMath::toRadians(double64 aDegree)
    {
        return aDegree * PI_over_180;
    }

    double64 A2DMath::wrapAngleDegs(double64 aDegs)
    {
        double64 result = fmod(aDegs, 360.0);
        if (result < 0) 
        { result += 360.0f; }
        return result;
    }

    double64 A2DMath::wrapAngleRads(double64 aRads)
    {
        double64 result = fmod(aRads, PI * 2.0);
        if (result < 0) 
        { result += PI * 2.0; }
        return result;
    }

    double64 A2DMath::linearVelocityX(double64 aAngle)
    {
        aAngle -= 90;
        if (aAngle < 0) 
        { aAngle = 360 + aAngle; }
        return cos( aAngle * PI_over_180);
    }

    double64 A2DMath::linearVelocityY(double64 aAngle)
    {
        aAngle -= 90;
        if (aAngle < 0) 
        { aAngle = 360 + aAngle; }
        return sin( aAngle * PI_over_180);
    }

    A2DVector3 A2DMath::linearVelocity(double64 aAngle)
    {
        double64 vx = linearVelocityX(aAngle);
        double64 vy = linearVelocityY(aAngle);
        return A2DVector3(vx,vy,0.0f);
    }

    double64 A2DMath::angleToTarget(double64 aX1, double64 aY1, double64 aX2, double64 aY2)
    {
        double64 deltaX = (aX2 - aX1);
        double64 deltaY = (aY2 - aY1);
        return atan2(deltaY,deltaX);
    }

    double64 A2DMath::angleToTarget(A2DVector3 &aSource, A2DVector3 &aTarget)
    {
        return angleToTarget(aSource(X), aSource(Y), aTarget(X), aTarget(Y));
    }

    double64 A2DMath::distance(double64 aX1, double64 aY1, double64 aX2, double64 aY2)
    {
        double64 deltaX = (aX2 - aX1);
        double64 deltaY = (aY2 - aY1);
        return sqrt(deltaX*deltaX + deltaY*deltaY);
    }

    double64 A2DMath::distance(A2DVector3 &aVec1, A2DVector3 &aVec2)
    {
        return distance(aVec1(X), aVec1(Y), aVec2(X), aVec2(Y));
    }

    double64 A2DMath::length(double64 aX, double64 aY, double64 aZ)
    {
        return sqrt(aX*aX + aY*aY + aZ*aZ);
    }

    double64 A2DMath::length(A2DVector3 &aVector)
    {
        return length(aVector(X), aVector(Y), aVector(Z));
    }

    double64 A2DMath::dotProduct(double64 aX1, double64 aY1, double64 aZ1, double64 aX2, double64 aY2, double64 aZ2)
    {
        return (aX1*aX2 + aY1*aY2 + aZ1*aZ2);
    }

    double64 A2DMath::dotProduct(A2DVector3 &aVec1, A2DVector3 &aVec2)
    {
        return dotProduct(aVec1(X), aVec1(Y), aVec1(Z), aVec2(X), aVec2(Y), aVec2(Z));
    }

    A2DVector3 A2DMath::crossProduct(double64 aX1, double64 aY1, double64 aZ1, double64 aX2, double64 aY2, double64 aZ2)
    {
        double64 nx = (aY1 * aZ2) - (aZ1 * aY2);
        double64 ny = (aZ1 * aY2) - (aX1 * aZ2);
        double64 nz = (aX1 * aY2) - (aY1 * aX2);
        return A2DVector3(nx, ny, nz);
    }

    A2DVector3 A2DMath::crossProduct(A2DVector3 &aVec1, A2DVector3 &aVec2)
    {
        return crossProduct(aVec1(X), aVec1(Y), aVec1(Z), aVec2(X), aVec2(Y), aVec2(Z));
    }

    A2DVector3 A2DMath::normal(double64 aX, double64 aY, double64 aZ)
    {
        double64 lng = length(aX, aY, aZ);
        double64 scale = 0.;
        if (lng != 0) 
        { scale = 1. / lng; }

        double64 nx = aX * scale;
        double64 ny = aY * scale;
        double64 nz = aZ * scale;

        return A2DVector3(nx, ny, nz);
    }

    A2DVector3 A2DMath::normal(A2DVector3 &aVector)
    {
        return normal(aVector(X), aVector(Y), aVector(Z));
    }
} // Advanced2D