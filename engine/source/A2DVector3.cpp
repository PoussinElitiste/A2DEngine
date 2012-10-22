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
        memset(mVect, 0, sizeof(mVect));
    }

    A2DVector3::A2DVector3(double64 aX, double64 aY, double64 aZ)
    { 
        Set(aX, aY, aZ); 
    }

    A2DVector3::A2DVector3(int32 aX, int32 aY, int32 aZ)
    {
        Set( static_cast<double64>(aX), static_cast<double64>(aY), static_cast<double64>(aZ) );
    }

    A2DVector3::A2DVector3(const A2DVector3& aVect)
    { 
        *this = aVect; 
    }

    A2DVector3::~A2DVector3()
    {}

    void A2DVector3::Set( double64 aX, double64 aY, double64 aZ )
    {
        mVect[X] = aX;
        mVect[Y] = aY;
        mVect[Z] = aZ;
    }

    void A2DVector3::Set(const A2DVector3& aVect)
    {
        mVect[X] = aVect(X);
        mVect[Y] = aVect(Y);
        mVect[Z] = aVect(Z);
    }

    const A2DVector3& A2DVector3::Move( const A2DVector3& aMove )
    {
        mVect[X] += aMove(X);
        mVect[Y] += aMove(Y);
        mVect[Z] += aMove(Z);

        return *this;
    }

    const A2DVector3& A2DVector3::Scale( double64 aValue )
    {
        mVect[X] *= aValue;
        mVect[Y] *= aValue;
        mVect[Z] *= aValue;

        return *this;
    }

    void A2DVector3::operator+=( const A2DVector3& aVect )
    {  
        Move(aVect); 
    }

    void A2DVector3::operator-=( const A2DVector3& aVect )
    { 
        mVect[X] -= aVect(X);
        mVect[Y] -= aVect(Y);
        mVect[Z] -= aVect(Z); 
    }

    void A2DVector3::operator*=( const A2DVector3& aVect )
    {
        mVect[X] *= aVect(X);
        mVect[Y] *= aVect(Y);
        mVect[Z] *= aVect(Z);
    }
    void A2DVector3::operator/=( const A2DVector3& aVect )
    {
        mVect[X] /= aVect(X);
        mVect[Y] /= aVect(Y);
        mVect[Z] /= aVect(Z);
    }

    bool8 A2DVector3::operator==( const A2DVector3& aVect ) const
    {
        return (
            (((aVect(X) - EPSILON) < mVect[X]) && (mVect[X] < (aVect(X) + EPSILON))) &&
            (((aVect(Y) - EPSILON) < mVect[Y]) && (mVect[Y] < (aVect(Y) + EPSILON))) &&
            (((aVect(Z) - EPSILON) < mVect[Z]) && (mVect[Z] < (aVect(Z) + EPSILON))) );
    }

    bool8 A2DVector3::operator!=( const A2DVector3& aVect ) const
    {
        return (!(*this == aVect));
    }

    A2DVector3& A2DVector3::operator=( const A2DVector3& aVect )
    {
        Set(aVect);
        return *this;
    }

    double64 A2DVector3::Distance2D( const A2DVector3& aVect )
    {
        return sqrt( 
            (aVect(X) - mVect[X]) * (aVect(X) - mVect[X]) + 
            (aVect(Y) - mVect[Y]) * (aVect(Y) - mVect[Y]) );
    }

    double64 A2DVector3::Length()
    {
        return sqrt( DotProduct(*this) );
    }

    double64 A2DVector3::DotProduct( const A2DVector3& aVect )
    {
        return mVect[X]*aVect(X) + mVect[Y]*aVect(Y) + mVect[Z]*aVect(Z);
    }

    A2DVector3 A2DVector3::CrossProduct( const A2DVector3& aVect )
    {
        double64 nX = ( mVect[Y] * aVect(Z) ) - ( mVect[Z] * aVect(Y) );
        double64 nY = ( mVect[Z] * aVect(X) ) - ( mVect[X] * aVect(Z) );
        double64 nZ = ( mVect[X] * aVect(Y) ) - ( mVect[Y] * aVect(X) );

        return A2DVector3( nX, nY, nZ );
    }

    // calculate normale vector
    A2DVector3 A2DVector3::Normal()
    {
        double64 length;
        if ( Length() == 0 )
        { length = 0; }
        else
        { length = 1 / Length(); }

        double64 nX = mVect[X] * length;
        double64 nY = mVect[Y] * length;
        double64 nZ = mVect[Z] * length;

        return A2DVector3( nX, nY, nZ );
    }

    // calculate inverse vector
    A2DVector3 A2DVector3::Inverse()
    {
        return A2DVector3(*this).Scale(-1.f);
    }

} // Advanced2D