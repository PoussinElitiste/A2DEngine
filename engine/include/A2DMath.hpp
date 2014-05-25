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
      static double64 toDegrees(double64 aRadian);
      static double64 toRadians(double64 aDegree);
      static double64 wrapAngleDegs(double64 aDegs);
      static double64 wrapAngleRads(double64 aRads);
      static double64 linearVelocityX(double64 aAngle);
      static double64 linearVelocityY(double64 aAngle);
      static A2DVector3 linearVelocity(double64 aAngle);
      static double64 angleToTarget(double64 aX1, double64 aY1, double64 aX2, double64 aY2);
      static double64 angleToTarget(A2DVector3 &aSource, A2DVector3 &aTarget);
      static double64 distance(double64 aX1, double64 aY1, double64 aX2, double64 aY2);
      static double64 distance(A2DVector3 &aVec1, A2DVector3 &aVec2);
      static double64 length(double64 aX, double64 aY, double64 aZ);
      static double64 length(A2DVector3 &aVector);
      static double64 dotProduct(double64 aX1, double64 aY1, double64 aZ1, double64 aX2, double64 aY2, double64 aZ2);
      static double64 dotProduct(A2DVector3 &aVec1, A2DVector3 &aVec2);
      static A2DVector3 crossProduct(double64 aX1, double64 aY1, double64 aZ1, double64 aX2, double64 aY2, double64 aZ2);
      static A2DVector3 crossProduct(A2DVector3 &aVec1, A2DVector3 &aVec2);
      static A2DVector3 normal(double64 aX, double64 aY, double64 aZ);
      static A2DVector3 normal(A2DVector3 &aVector);
      }; // class
} // namespace

#endif // INC_ADVANCED2D_A2DMATH_HPP