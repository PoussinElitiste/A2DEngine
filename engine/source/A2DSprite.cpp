// local include
#include <A2DEngine.hpp>

namespace Advanced2D
{
    A2DSprite::A2DSprite()
        : A2DEntity(RENDER_2D)
        , mpImage(NULL)
        , mImageLoaded(false)
        , mPosition(0, 0)
        , mVelocity(0, 0)
        , mState(0)
        , mDirection(0)
        , mDimensions(1, 1)
        , mCurFrame(0)
        , mTotalFrame(1)
        , mAnimDir(1)
        , mAnimColumns(1)
        , mFrameStart(0)
        , mFrameTimer(0)
        , mAnimStartX(0)
        , mAnimStartY(0)
        , mFaceAngle(0.0)
        , mMoveAngle(0.0)
        , mRotation(0.0)
        , mScaling(1.0)
        , mColor(0xFFFFFFFF)
        , mMoveTimer(16)
        , mMoveStart(0)
        , mCollidable(true)
        , mCollisionMethod(COLLISION_RECT)
    {}

    A2DSprite::~A2DSprite()
    {
        if (mImageLoaded)
        { delete mpImage; }
    }

    bool8 A2DSprite::LoadSpriteImage(const A2DString& aFilename, D3DCOLOR aTranscolor)
    {
        //if image already exists, free it
        if ( mImageLoaded && mpImage != NULL) 
        { delete mpImage; }

        //create texture and load image
        mpImage = new A2DTexture();
        if (mpImage->Load(aFilename, aTranscolor))
        {
            SetSize(mpImage->GetWidth(),mpImage->GetHeight());
            mImageLoaded = true;
            return true;
        }
        else
        { return false; }
    }

    void A2DSprite::SetImage(A2DTexture* apImage)
    {
        mpImage = apImage;
        SetSize(apImage->GetWidth(), apImage->GetHeight());
        mImageLoaded = false;
    }

    void A2DSprite::Transform()
    {
        D3DXMATRIX mat;
        D3DXVECTOR2 scale( (float32)mScaling, (float32)mScaling );
        D3DXVECTOR2 center( (float32)( Get(WIDTH)*mScaling )/2, (float32)( Get(HEIGHT)*mScaling )/2 );
        D3DXVECTOR2 trans( (float32)Get(X), (float32)Get(Y) );
        D3DXMatrixTransformation2D( &mat, NULL, 0, &scale, &center, (float32)mRotation, &trans );

        gpEngine->GetSpriteHandle()->SetTransform(&mat);
    }

    void A2DSprite::Draw()
    {
        //calculate source frame location
        int32 fx = (mCurFrame % mAnimColumns) * Get(WIDTH);
        int32 fy = (mCurFrame / mAnimColumns) * Get(HEIGHT);
        RECT srcRect = { fx, fy, fx + Get(WIDTH), fy + Get(HEIGHT) };

        //draw the sprite frame
        Transform();
        gpEngine->GetSpriteHandle()->Draw( mpImage->GetTexture(), &srcRect, NULL, NULL, mColor );
    }

    void A2DSprite::Move()
    {
        if (mMoveTimer > 0) 
        {
            if (timeGetTime() > (DWORD)(mMoveStart + mMoveTimer)) 
            {
                //reset move timer
                mMoveStart = timeGetTime();

                //move sprite by velocity amount
                SetPosition(Get(X) + mVelocity(X), Get(Y) + mVelocity(Y));
            }
        }
        else 
        {
            //no movement timer- -update at cpu clock speed
            SetPosition(Get(X) + mVelocity(X), Get(Y) + mVelocity(Y));
        }
    }

    void A2DSprite::Animate()
    {
        //update frame based on animdir
        if (mFrameTimer > 0) 
        {
            if ( timeGetTime() > (DWORD)( mFrameStart + mFrameTimer) ) 
            {
                //reset animation timer
                mFrameStart = timeGetTime();
                mCurFrame += mAnimDir;

                //keep frame within bounds
                if (mCurFrame < 0) { mCurFrame = mTotalFrame - 1; }
                if (mCurFrame > mTotalFrame - 1) { mCurFrame = 0; }
            }
        }
        else 
        {
            //no animation timer update at cpu clock speed
            mCurFrame += mAnimDir;

            if (mCurFrame < 0) { mCurFrame = mTotalFrame - 1; }
            if (mCurFrame > mTotalFrame - 1) { mCurFrame = 0; }
        }
    }

}; // namespace