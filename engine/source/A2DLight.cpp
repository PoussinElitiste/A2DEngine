// local include
#include "A2DLight.hpp"

namespace Advanced2D
{
   A2DLight::A2DLight( int32 aLightNum
                     , A2DType aType
                     , const A2DRenderVector &aPosition
                     , const A2DRenderVector &aDirection
                     , double64 aRange )
      : mLightNum(aLightNum)
      , mType(aType)
   {
      ZeroMemory( &mLight, sizeof(D3DLIGHT9) );

      mLight.Diffuse.r = mLight.Ambient.r = 1.0f;
      mLight.Diffuse.g = mLight.Ambient.g = 1.0f;
      mLight.Diffuse.b = mLight.Ambient.b = 1.0f;
      mLight.Diffuse.a = mLight.Ambient.a = 1.0f;

      switch(aType)
      {
      case D3DLIGHT_POINT:
         {
               mLight.Type = D3DLIGHT_POINT;
               mLight.Position = aPosition;
               mLight.Attenuation0 = 0.1f;
               mLight.Range = static_cast<float>(aRange);
         }
         break;
      case D3DLIGHT_SPOT:
         {
               mLight.Type = D3DLIGHT_SPOT;
               mLight.Position = aPosition;
               mLight.Direction = aDirection;
               mLight.Range = static_cast<float>(aRange);
               mLight.Theta = 0.5f;
               mLight.Phi = 1.0f;
               mLight.Falloff = 1.0f;
               mLight.Attenuation0 = 1.0f;
         }
         break;
      case D3DLIGHT_DIRECTIONAL:
      default:
         {
               mLight.Type = D3DLIGHT_DIRECTIONAL;
               mLight.Range = static_cast<float>(aRange);
               //create a normalized direction
               D3DXVec3Normalize( static_cast<A2DRenderVector*>(&mLight.Direction), &aDirection );
         }
         break;
      }

      //enable the light
      show();
      update();
   }

   A2DLight::~A2DLight()
   {}

   A2DLightPtr A2DLight::create( int32 aLightNum
                              , A2DType aType 
                              , const A2DRenderVector &aPosition 
                              , const A2DRenderVector &aDirection 
                              , double64 aRange )
   {
      return A2DLightPtr(new A2DLight( aLightNum
                                    , aType
                                    , aPosition
                                    , aDirection
                                    , aRange ));
   }

   void A2DLight::update()
   {
      gpEngine->getDevice()->SetLight(mLightNum, &mLight);
   }

   void A2DLight::show()
   {
      gpEngine->getDevice()->LightEnable(mLightNum, true);
   }

   void A2DLight::hide()
   {
      gpEngine->getDevice()->LightEnable(mLightNum, false);
   }
}; // namespace