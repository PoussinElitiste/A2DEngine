#ifndef INC_ADVANCED2D_A2DPARTICULE_EMITTER_HPP
#define INC_ADVANCED2D_A2DPARTICULE_EMITTER_HPP

// external include
#include <A2DEngine.hpp>

namespace Advanced2D
{
   // Forward
   class A2DSprite;
   typedef std::tr1::shared_ptr<A2DSprite> A2DSpritePtr;

   class A2DTexture;
   typedef std::tr1::shared_ptr<A2DTexture> A2DTexturePtr;

   class A2DParticleEmitter
   {
   public:
      A2DParticleEmitter();
      virtual ~A2DParticleEmitter();

   private:
      typedef A2DArray<A2DSpritePtr>             ParticleList;
      typedef A2DArray<A2DSpritePtr>::iterator   ParticleListIt;

      ParticleList    mParticles;
      A2DTexturePtr   mpImage;
      A2DVector3      mPosition;
      double64        mDirection;
      double64        mLength;
      int32           mMax;
      int32           mAlphaMin, mAlphaMax;
      int32           mMinR, mMinG, mMinB, mMaxR, mMaxG, mMaxB;
      int32           mSpread;
      double64        mVelocity;
      double64        mScale;

   public:
      // getter
      A2DVector3  getPosition() { return mPosition; }
      double64    getDirection() { return mDirection; }

      // Setter
      void setPosition(double64 aX, double64 aY) { mPosition.set(aX, aY, 0); }
      void setPosition(A2DVector3 aVec) { mPosition = aVec; }
      void setDirection(double64 aAngle) { mDirection = aAngle; }
      void setMax(int32 aNum) { mMax = aNum; }
      void setAlphaRange(int32 aMin, int32 aMax);
      void setColorRange(int32 aR1, int32 aG1, int32 aB1, int32 aR2, int32 aG2, int32 aB2);
      void setSpread(int32 aValue) { mSpread = aValue; }
      void setLength(double64 aValue) { mLength = aValue; }
      void setVelocity(double64 aValue) { mVelocity = aValue; }
      void setScale(double64 aValue) { mScale = aValue; }
    
   public:
      bool LoadSpriteImage(A2DString aImageFile);
      void draw();
      void Update();
      void Add();
   }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DPARTICULE_EMITTER_HPP