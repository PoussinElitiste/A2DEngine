// local include
#include <A2DVector3.hpp>

namespace Advanced2D
{
   static const float32 EPSILON = 0.0001f;

   //-----------------------------------------------------------
   // A2DRenderVector
   //-----------------------------------------------------------
   A2DRenderVector::A2DRenderVector(float32 aX, float32 aY, float32 aZ)
      : D3DXVECTOR3(aX, aY, aZ)
   {}

   A2DRenderVector::~A2DRenderVector()
   {}

   //-----------------------------------------------------------
   // A2DVector3
   //-----------------------------------------------------------
   A2DVector3::A2DVector3()
   {
   }

   A2DVector3::A2DVector3(double64 aX, double64 aY, double64 aZ)
   { 
      set(aX, aY, aZ); 
   }

   A2DVector3::A2DVector3(int32 aX, int32 aY, int32 aZ)
   {
      set( static_cast<double64>(aX), static_cast<double64>(aY), static_cast<double64>(aZ) );
   }

   A2DVector3::A2DVector3(const A2DVector3 &aVect)
   { 
      *this = aVect; 
   }

   A2DVector3::~A2DVector3()
   {}

   void A2DVector3::set( double64 aX, double64 aY, double64 aZ )
   {
      mObj[X] = aX;
      mObj[Y] = aY;
      mObj[Z] = aZ;
   }

   void A2DVector3::set(const A2DVector3 &aVect)
   {
      mObj[X] = aVect(X);
      mObj[Y] = aVect(Y);
      mObj[Z] = aVect(Z);
   }

   const A2DVector3 &A2DVector3::move( const A2DVector3 &aMove )
   {
      mObj[X] += aMove(X);
      mObj[Y] += aMove(Y);
      mObj[Z] += aMove(Z);

      return *this;
   }

   const A2DVector3 &A2DVector3::scale( double64 aValue )
   {
      mObj[X] *= aValue;
      mObj[Y] *= aValue;
      mObj[Z] *= aValue;

      return *this;
   }

   void A2DVector3::operator+=( const A2DVector3 &aVect )
   {  
      move(aVect); 
   }

   void A2DVector3::operator-=( const A2DVector3 &aVect )
   { 
      mObj[X] -= aVect(X);
      mObj[Y] -= aVect(Y);
      mObj[Z] -= aVect(Z); 
   }

   void A2DVector3::operator*=( const A2DVector3 &aVect )
   {
      mObj[X] *= aVect(X);
      mObj[Y] *= aVect(Y);
      mObj[Z] *= aVect(Z);
   }
   void A2DVector3::operator/=( const A2DVector3 &aVect )
   {
      mObj[X] /= aVect(X);
      mObj[Y] /= aVect(Y);
      mObj[Z] /= aVect(Z);
   }

   bool8 A2DVector3::operator==( const A2DVector3 &aVect ) const
   {
      return (
         (((aVect(X) - EPSILON) < mObj[X]) && (mObj[X] < (aVect(X) + EPSILON))) &&
         (((aVect(Y) - EPSILON) < mObj[Y]) && (mObj[Y] < (aVect(Y) + EPSILON))) &&
         (((aVect(Z) - EPSILON) < mObj[Z]) && (mObj[Z] < (aVect(Z) + EPSILON))) );
   }

   bool8 A2DVector3::operator!=( const A2DVector3 &aVect ) const
   {
      return (!(*this == aVect));
   }

   A2DVector3 &A2DVector3::operator=( const A2DVector3 &aVect )
   {
      set(aVect);
      return *this;
   }

   double64 A2DVector3::distance2D( const A2DVector3 &aVect ) const
   {
      return sqrt( 
         (aVect(X) - mObj[X]) * (aVect(X) - mObj[X]) + 
         (aVect(Y) - mObj[Y]) * (aVect(Y) - mObj[Y]) );
   }

   double64 A2DVector3::length() const
   {
      return sqrt( dotProduct(*this) );
   }

   double64 A2DVector3::dotProduct( const A2DVector3 &aVect ) const
   {
      return mObj[X]*aVect(X) + mObj[Y]*aVect(Y) + mObj[Z]*aVect(Z);
   }

   A2DVector3 A2DVector3::crossProduct( const A2DVector3 &aVect ) const 
   {
      double64 nX = ( mObj[Y] * aVect(Z) ) - ( mObj[Z] * aVect(Y) );
      double64 nY = ( mObj[Z] * aVect(X) ) - ( mObj[X] * aVect(Z) );
      double64 nZ = ( mObj[X] * aVect(Y) ) - ( mObj[Y] * aVect(X) );

      return A2DVector3( nX, nY, nZ );
   }

   // calculate normale vector
   A2DVector3 A2DVector3::normal() const
   {
      double64 lng = length();
      double64 scale = 0;
      if ( lng != 0 )
      { scale = 1 / lng; }

      double64 nX = mObj[X] * scale;
      double64 nY = mObj[Y] * scale;
      double64 nZ = mObj[Z] * scale;

      return A2DVector3( nX, nY, nZ );
   }

   // calculate inverse vector
   A2DVector3 A2DVector3::inverse() const
   {
      return A2DVector3(*this).scale(-1.f);
   }

} // Advanced2D