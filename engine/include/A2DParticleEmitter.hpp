#ifndef INC_ADVANCED2D_A2DPARTICULE_EMITTER_HPP
#define INC_ADVANCED2D_A2DPARTICULE_EMITTER_HPP

// external include
#include <A2DEngine.hpp>

namespace Advanced2D
{
    // Forward
    class A2DSprite;
    class A2DTexture;

    class A2DParticleEmitter
    {
    public:
        A2DParticleEmitter();
        virtual ~A2DParticleEmitter();

    private:
        typedef A2DArray<A2DSprite*> Particles;
        typedef A2DArray<A2DSprite*>::iterator iter;

        Particles mParticles;
        A2DTexture* mpImage;
        A2DVector3 mPosition;
        double64 mDirection;
        double64 mLength;
        int32 mMax;
        int32 mAlphaMin, mAlphaMax;
        int32 mMinR, mMinG, mMinB, mMaxR, mMaxG, mMaxB;
        int32 mSpread;
        double64 mVelocity;
        double64 mScale;

    public:
        void SetPosition(double64 aX, double64 aY) { mPosition.Set(aX, aY, 0); }
        void SetPosition(A2DVector3 aVec) { mPosition = aVec; }
        A2DVector3 GetPosition() { return mPosition; }
        void SetDirection(double64 aAngle) { mDirection = aAngle; }
        double64 GetDirection() { return mDirection; }
        void SetMax(int32 aNum) { mMax = aNum; }
        void SetAlphaRange(int32 aMin, int32 aMax);
        void SetColorRange(int32 aR1, int32 aG1, int32 aB1, int32 aR2, int32 aG2, int32 aB2);
        void SetSpread(int32 aValue) { mSpread = aValue; }
        void SetLength(double64 aValue) { mLength = aValue; }
        void SetVelocity(double64 aValue) { mVelocity = aValue; }
        void SetScale(double64 aValue) { mScale = aValue; }
    
    public:
        bool LoadSpriteImage(A2DString aImageFile);
        void Draw();
        void Update();
        void Add();
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DPARTICULE_EMITTER_HPP