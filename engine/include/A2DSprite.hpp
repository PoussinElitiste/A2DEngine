#ifndef INC_ADVANCED2D_A2DSPRITE_HPP
#define INC_ADVANCED2D_A2DSPRITE_HPP

// local include
#include <A2DEntity.hpp>

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
        A2DSpriteInfos(int32 aWidth, int32 aHeight) { Set(WIDTH, aWidth); Set(HEIGHT, aHeight); }
        //virtual void Set( Category aCoord, const ObjType& aValue ) { mObj[aCoord] = aValue; }
        //virtual const ObjType& operator()( Category aCoord ) const { return mObj[aCoord]; }
    };

    class A2DTexture;
    class A2DSprite
        : public A2DEntity
    {
    public:
        typedef A2DVectCoordinate Coordinate;

    private:
        bool8 mIsVisible;
        bool8 mIsAlive;
        int32 mLifeTimeLength;
        A2DTimer mLifeTimeTimer;
        int32 mObjectType;

        A2DVector3 mPosition;
        A2DVector3 mVelocity;
        bool8 mImageLoaded;
        int32 mState;
        int32 mDirection;

    protected:
        A2DTexture* mpImage;
        int32 mAnimColumns;

        int32 mFrameStart;
        int32 mFrameTimer;

        int32 mMoveStart;
        int32 mMoveTimer;

        int32 mCurFrame;
        int32 mTotalFrame;
        int32 mAnimDir;

        bool8 mCollidable;
        A2DCollisionType mCollisionMethod;

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
        A2DSprite();
        virtual ~A2DSprite();

        const A2DVector3& GetPosition() { return mPosition; }
        void SetPosition(const A2DVector3& aPosition) { mPosition = aPosition; }
        void SetPosition(double64 aX, double64 aY) { mPosition.Set(aX, aY, 0.); }
        double64 Get(Coordinate aCoord) { return mPosition(aCoord); }
        //void Set(Coordinate aCoord, double64 aValue) { mPosition.Set(aCoord, aValue); }

        const A2DVector3& GetVelocity() { return mVelocity; }
        void SetVelocity(const A2DVector3& aVelocity) { mVelocity = aVelocity; }
        void SetVelocity(double64 aVx, double64 aVy) { mVelocity.Set(aVx, aVy, 0.); }

        void SetSize(int32 aWidth, int32 aHeight) { mDimensions.Set(WIDTH, aWidth); mDimensions.Set(HEIGHT, aHeight); }
        void SetDimension(A2DSpriteDim aDim, int32 aValue) { mDimensions.Set(aDim, aValue); }
        uint32 Get(A2DSpriteDim aDim) { return mDimensions(aDim); }

        bool8 IsVisible() const { return mIsVisible; }
        void SetVisible(bool8 aFlag) { mIsVisible = aFlag; }

        bool8 IsAlive() const { return mIsAlive; }
        void SetAlive(bool8 aFlag) { mIsAlive = aFlag; }

        int32 GetState() { return mState; }
        void SetState(int32 aValue) { mState = aValue; }

        int32 GetDirection() { return mDirection; }
        void SetDirection(int32 aValue) { mDirection = aValue; }

        int32 GetColumns() { return mAnimColumns; }
        void SetColumns(int32 aValue) { mAnimColumns = aValue; }

        int32 GetFrameTimer() { return mFrameTimer; }
        void SetFrameTimer(int32 aValue) { mFrameTimer = aValue; }

        int32 GetCurrentFrame() { return mCurFrame; }
        void SetCurrentFrame(int32 aValue) { mCurFrame = aValue; }

        int32 GetTotalFrames() { return mTotalFrame; }
        void SetTotalFrames(int32 aValue) { mTotalFrame = aValue; }

        int32 GetAnimationDirection() { return mAnimDir; }
        void SetAnimationDirection(int32 aValue) { mAnimDir = aValue; }

        double64 GetRotation() { return mRotation; }
        void SetRotation(double64 aValue) { mRotation = aValue; }

        double64 GetScale() { return mScaling; }
        void SetScale(double64 aValue) { mScaling = aValue; }

        void SetColor(D3DCOLOR aCol) { mColor = aCol; }

        int32 GetMoveTimer() { return mMoveTimer; }
        void SetMoveTimer(int32 aValue) { mMoveTimer = aValue; }

        bool8 IsCollidable() { return mCollidable; }
        void SetCollidable(bool8 aValue) { mCollidable = aValue; }

        A2DCollisionType GetCollisionMethod() { return mCollisionMethod; }
        void SetCollisionMethod(A2DCollisionType aType) { mCollisionMethod = aType; }

    public:
        bool8 LoadSpriteImage(const A2DString& aFilename, D3DCOLOR aTranscolor = D3DCOLOR_XRGB(255,0,255));
        void SetImage(A2DTexture* aTexture);
        void Move();
        void Animate();
        void Draw();
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DSPRITE_HPP