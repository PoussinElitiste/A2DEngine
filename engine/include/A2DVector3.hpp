#ifndef INC_ADVANCED2D_A2DVECTOR3_HPP
#define INC_ADVANCED2D_A2DVECTOR3_HPP

// external include
#include <d3dx9Math.h>

// local include
#include <A2DTypes.hpp>

namespace Advanced2D
{
    //-----------------------------------------------------------
    // A2DRenderVector
    // Note: Only use for engine compatibility
    //-----------------------------------------------------------
    struct A2DRenderVector
        : public D3DXVECTOR3
    {
        A2DRenderVector(float32 x = 0.f, float32 y = 0.f, float32 z = 0.f);
        virtual ~A2DRenderVector();
    }; // A2DRenderVector

    //-----------------------------------------------------------
    // A2DVector3
    //-----------------------------------------------------------
    class A2DVector3
    {
    public:
        enum Coordinate
        {
            X = 0,
            Y,
            Z,
            MAX
        };

    private:
        double64 mVect[MAX];
 
    public:
        A2DVector3();
        A2DVector3( double64 aX, double64 aY, double64 aZ );
        A2DVector3( int32 aX, int32 aY, int32 aZ );
        A2DVector3( const A2DVector3& aVect );
        virtual ~A2DVector3();
       
        void Set( double64 aX, double64 aY, double64 aZ );
        void Set( const A2DVector3& aVect );
        void Set( Coordinate aCoord, double64 aValue ) { mVect[aCoord] = aValue; }
        //double64 Get(Coordinate aCoord) { return mVect[aCoord]; }
        double64 operator()( Coordinate aCoord ) const { return mVect[aCoord]; }
        A2DVector3& operator=( const A2DVector3& aVect );

        const A2DVector3& Move( const A2DVector3& aMove );
        const A2DVector3& Scale( double64 aValue );

        void operator+=( const A2DVector3& aVect );
        void operator-=( const A2DVector3& aVect );
        void operator*=( const A2DVector3& aVect );
        void operator/=( const A2DVector3& aVect );

        bool8 operator==( const A2DVector3& aVect ) const;
        bool8 operator!=( const A2DVector3& aVect ) const;

        double64 Distance2D( const A2DVector3& aVect );
        double64 Length();
        double64 DotProduct( const A2DVector3& aVect );
        A2DVector3 CrossProduct( const A2DVector3& aVect );
        A2DVector3 Normal();
        A2DVector3 Inverse();
    }; // A2DVector3
} // Advanced2D

#endif // INC_ADVANCED2D_A2DVECTOR3_HPP