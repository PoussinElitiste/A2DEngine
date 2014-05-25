#ifndef INC_ADVANCED2D_A2DSPRITE_HPP
#define INC_ADVANCED2D_A2DSPRITE_HPP

// local include
#include <A2DEntity.hpp>
#include <A2DTemplate.hpp>
#include <A2DVector3.hpp>

namespace Advanced2D
{
   enum A2DCollisionType : int32
   {
      COLLISION_NONE = 0,
      COLLISION_RECT,
      COLLISION_DIST
   }; // Enum

   enum A2DSpriteDim : uint32
   {
      WIDTH = 0,
      HEIGHT,
      MAX_DIM
   }; // Enum

   struct A2DSpriteInfos
      : public A2DBaseCategory< Advanced2D::A2DSpriteDim, Advanced2D::MAX_DIM, uint32 >
   {
      A2DSpriteInfos(int32 aWidth, int32 aHeight) { set(WIDTH, aWidth); set(HEIGHT, aHeight); }
      //virtual void set( Category aCoord, const ObjType& aValue ) { mObj[aCoord] = aValue; }
      //virtual const ObjType& operator()( Category aCoord ) const { return mObj[aCoord]; }
   };

   class A2DTexture;
   typedef std::tr1::shared_ptr<A2DTexture> A2DTexturePtr;

   class A2DSprite;
   typedef std::tr1::shared_ptr<A2DSprite> A2DSpritePtr;

   class A2DSprite
      : public A2DEntity
   {
   public:
      typedef A2DVectCoordinate Coordinate;

   private:
      A2DVector3 mPosition;
      A2DVector3 mVelocity;
      bool8 mImageLoaded;
      int32 mState;
      int32 mDirection;

   protected:
      A2DSprite();

      A2DTexturePtr  mpImage;
      int32          mAnimColumns;

      int32 mFrameStart;
      int32 mFrameTimer;

      int32 mMoveStart;
      int32 mMoveTimer;

      int32 mCurFrame;
      int32 mTotalFrame;
      int32 mAnimDir;

      bool8             mCollidable;
      A2DCollisionType  mCollisionMethod;

      double64 mFaceAngle;
      double64 mMoveAngle;

      int32 mAnimStartX;
      int32 mAnimStartY;

      double64 mRotation;
      double64 mScaling;

      D3DXMATRIX mMatRotation;
      D3DXMATRIX mMatScale;
      void Transform();

      D3DCOLOR mColor;
      A2DSpriteInfos mDimensions;

   public:
      virtual ~A2DSprite();

      static A2DSpritePtr create();
      const A2DVector3 &getPosition() { return mPosition; }
      void setPosition(const A2DVector3 &aPosition) { mPosition = aPosition; }
      void setPosition(double64 aX, double64 aY) { mPosition.set(aX, aY, 0.); }
      double64 get(Coordinate aCoord) { return mPosition(aCoord); }
      // Not advice to do this, risk of confusion
      // TODO: find better solution
      void set(Coordinate aCoord, double64 aValue) { mPosition(aCoord) = aValue; }

      const A2DVector3 &getVelocity() { return mVelocity; }
      void setVelocity(const A2DVector3 &aVelocity) { mVelocity = aVelocity; }
      void setVelocity(double64 aVx, double64 aVy) { mVelocity.set(aVx, aVy, 0.); }

      void setSize(int32 aWidth, int32 aHeight) { mDimensions.set(WIDTH, aWidth); mDimensions.set(HEIGHT, aHeight); }
      void setDimension(A2DSpriteDim aDim, int32 aValue) { mDimensions.set(aDim, aValue); }
      uint32 get(A2DSpriteDim aDim) { return mDimensions(aDim); }

      int32 getState() { return mState; }
      void setState(int32 aValue) { mState = aValue; }

      int32 getDirection() { return mDirection; }
      void setDirection(int32 aValue) { mDirection = aValue; }

      int32 getColumns() { return mAnimColumns; }
      void setColumns(int32 aValue) { mAnimColumns = aValue; }

      int32 getFrameTimer() { return mFrameTimer; }
      void setFrameTimer(int32 aValue) { mFrameTimer = aValue; }

      int32 getCurrentFrame() { return mCurFrame; }
      void setCurrentFrame(int32 aValue) { mCurFrame = aValue; }

      int32 getTotalFrames() { return mTotalFrame; }
      void setTotalFrames(int32 aValue) { mTotalFrame = aValue; }

      int32 getAnimationDirection() { return mAnimDir; }
      void setAnimationDirection(int32 aValue) { mAnimDir = aValue; }

      double64 getRotation() { return mRotation; }
      void setRotation(double64 aValue) { mRotation = aValue; }

      double64 getScale() { return mScaling; }
      void setScale(double64 aValue) { mScaling = aValue; }

      void setColor(D3DCOLOR aCol) { mColor = aCol; }

      int32 getMoveTimer() { return mMoveTimer; }
      void setMoveTimer(int32 aValue) { mMoveTimer = aValue; }

      bool8 isCollidable() { return mCollidable; }
      void setCollidable(bool8 aValue) { mCollidable = aValue; }

      A2DCollisionType getCollisionMethod() { return mCollisionMethod; }
      void setCollisionMethod(A2DCollisionType aType) { mCollisionMethod = aType; }

   public:
      bool8 loadSpriteImage(const A2DString &aFilename, D3DCOLOR aTranscolor = D3DCOLOR_XRGB(255,0,255));
      void setImage(A2DTexturePtr aTexture);
      void move();
      void animate();
      void draw();
   }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DSPRITE_HPP