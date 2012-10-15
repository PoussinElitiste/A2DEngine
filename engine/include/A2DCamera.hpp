#ifndef INC_ADVANCED2D_A2DCAMERA_HPP
#define INC_ADVANCED2D_A2DCAMERA_HPP

// local include
#include <A2DEngine.hpp>
#include <A2DVector3.hpp>

namespace Advanced2D
{
    class A2DCamera
    {
    public:
        struct A2DLocalisationInfos
        {
            A2DLocalisationInfos( const A2DVector3& aPosition = A2DVector3()
                , const A2DVector3& aTarget = A2DVector3() );

            A2DVector3 mPosition;
            A2DVector3 mTarget;
        }; // A2DLocalisationInfos

        struct A2DPrespectiveInfos
        {
            A2DPrespectiveInfos( float32 aNearRange = 0.f
                , float32 aFarRange = 0.f
                , float32 aAspectRatio = 0.f
                , float32 aFOV = 0.f );

            float32 mNearRange;
            float32 mFarRange;
            float32 mAspectRatio;
            float32 mFOV;
        }; // A2DPrespectiveInfos

    private:
        D3DXMATRIX mMatrixProj;
        D3DXMATRIX mMatrixView;
        A2DVector3 mUpDir;

        A2DLocalisationInfos mLocalisation;
        A2DPrespectiveInfos mPerspective;
    public:
        A2DCamera();
        virtual ~A2DCamera();

        void SetPerspective(const A2DPrespectiveInfos& aPerspective) { mPerspective = aPerspective; }
        A2DPrespectiveInfos& GetPerspective() { return mPerspective; }
        const A2DPrespectiveInfos& GetPerspective() const { return mPerspective; }

        void SetLocalisation(const A2DLocalisationInfos& aLocalisation) { mLocalisation = aLocalisation; }
        const A2DLocalisationInfos& GetLocalisation() const { return mLocalisation; }

        void Update();

    }; // A2DCamera
} // Advanced2D

#endif // INC_ADVANCED2D_A2DCAMERA_HPP