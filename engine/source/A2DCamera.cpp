// Local include
#include <A2DCamera.hpp>

namespace Advanced2D
{
    A2DCamera::A2DPrespectiveInfos::A2DPrespectiveInfos( float32 aNearRange, float32 aFarRange, float32 aAspectRatio, float32 aFOV )
        : mNearRange(aNearRange)
        , mFarRange(aFarRange)
        , mAspectRatio(aAspectRatio)
        , mFOV(aFOV)
    {}

    A2DCamera::A2DLocalisationInfos::A2DLocalisationInfos( const A2DRenderVector& aPosition, const A2DRenderVector& aTarget )
        : mPosition(aPosition)
        , mTarget(aTarget)
    {}

    A2DCamera::A2DCamera()
        : mLocalisation(A2DRenderVector(0.f, 0.f, 10.f))
        , mUpDir(0.f, 1.f, 0.f)
        , mPerspective(A2DPrespectiveInfos(1.f, 2000.f, 640/480, 3.14159f/4.f))
    {}

    A2DCamera::~A2DCamera()
    {}

    void A2DCamera::Update()
    {
        // set camera's perspective matrix
        D3DXMatrixPerspectiveFovLH( &mMatrixProj
            , mPerspective.mFOV
            , mPerspective.mAspectRatio
            , mPerspective.mNearRange
            , mPerspective.mFarRange);
        gpEngine->GetDevice()->SetTransform(D3DTS_PROJECTION, &mMatrixProj);

        //set the camera’s view matrix
        D3DXMatrixLookAtLH( &mMatrixView
            , &mLocalisation.mPosition
            , &mLocalisation.mTarget
            , &mUpDir);
        gpEngine->GetDevice()->SetTransform(D3DTS_VIEW, &mMatrixView);
    }
} // Advanced2D