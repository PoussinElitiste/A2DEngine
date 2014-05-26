#ifndef INC_ADVANCED2D_A2DCAMERA_HPP
#define INC_ADVANCED2D_A2DCAMERA_HPP

// local include
#include <A2DEngine.hpp>
#include <A2DVector3.hpp>

namespace Advanced2D
{
   class A2DCamera;
   typedef std::tr1::shared_ptr<A2DCamera> A2DCameraPtr;

   class A2DCamera
   {
   public:
      struct A2DLocalisationInfos
      {
         A2DLocalisationInfos( const A2DRenderVector &aPosition = A2DRenderVector()
                             , const A2DRenderVector &aTarget = A2DRenderVector() );

         A2DRenderVector mPosition;
         A2DRenderVector mTarget;
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
      A2DCamera();

      D3DXMATRIX mMatrixProj;
      D3DXMATRIX mMatrixView;
      A2DRenderVector mUpDir;

      A2DLocalisationInfos mLocalisation;
      A2DPrespectiveInfos mPerspective;
   public:
      virtual ~A2DCamera();

      static A2DCameraPtr create();

      void setPerspective(const A2DPrespectiveInfos &aPerspective) { mPerspective = aPerspective; }
      A2DPrespectiveInfos &getPerspective() { return mPerspective; }
      const A2DPrespectiveInfos &getPerspective() const { return mPerspective; }

      void setPosition(const A2DRenderVector &aValue) { mLocalisation.mPosition = aValue; }
      void setTarget(const A2DRenderVector &aValue) { mLocalisation.mTarget = aValue; }
      void setLocalisation(const A2DLocalisationInfos& aLocalisation) { mLocalisation = aLocalisation; }
      const A2DLocalisationInfos &getLocalisation() const { return mLocalisation; }

      void update();
   }; // A2DCamera
} // Advanced2D

#endif // INC_ADVANCED2D_A2DCAMERA_HPP