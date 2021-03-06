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
   {}

   A2DSpritePtr A2DSprite::create()
   {
      return A2DSpritePtr(new A2DSprite());
   }

   bool8 A2DSprite::loadSpriteImage(const A2DString &aFilename, D3DCOLOR aTranscolor)
   {
      //create texture and load image
      mpImage = A2DTexture::create();
      if (mpImage->load(aFilename, aTranscolor))
      {
         setSize(mpImage->getWidth(),mpImage->getHeight());
         mImageLoaded = true;
         return true;
      }
      else
      { return false; }
   }

   void A2DSprite::setImage(A2DTexturePtr aTexture)
{
      mpImage = aTexture;
      setSize(aTexture->getWidth(), aTexture->getHeight());
      mImageLoaded = false;
   }

   void A2DSprite::Transform()
   {
      D3DXMATRIX mat;
      D3DXVECTOR2 scale( (float32)mScaling, (float32)mScaling );
      D3DXVECTOR2 center( (float32)( get(WIDTH)*mScaling )/2, (float32)( get(HEIGHT)*mScaling )/2 );
      D3DXVECTOR2 trans( (float32)get(X), (float32)get(Y) );
      D3DXMatrixTransformation2D( &mat, NULL, 0, &scale, &center, (float32)mRotation, &trans );

      gpEngine->getSpriteHandle()->SetTransform(&mat);
   }

   void A2DSprite::draw()
   {
      //calculate source frame location
      int32 fx = (mCurFrame % mAnimColumns) * get(WIDTH);
      int32 fy = (mCurFrame / mAnimColumns) * get(HEIGHT);
      RECT srcRect = { fx, fy, fx + get(WIDTH), fy + get(HEIGHT) };

      //draw the sprite frame
      Transform();
      gpEngine->getSpriteHandle()->Draw( mpImage->getTexture(), &srcRect, NULL, NULL, mColor );
   }

   void A2DSprite::move()
   {
      if (mMoveTimer > 0) 
      {
         if (timeGetTime() > (DWORD)(mMoveStart + mMoveTimer)) 
         {
               //reset move timer
               mMoveStart = timeGetTime();

               //move sprite by velocity amount
               setPosition(get(X) + mVelocity(X), get(Y) + mVelocity(Y));
         }
      }
      else 
      {
         //no movement timer- -update at cpu clock speed
         setPosition(get(X) + mVelocity(X), get(Y) + mVelocity(Y));
      }
   }

   void A2DSprite::animate()
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