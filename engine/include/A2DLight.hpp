#ifndef INC_ADVANCED2D_A2DLIGHT_HPP
#define INC_ADVANCED2D_A2DLIGHT_HPP

// local include 
#include <A2DEngine.hpp>
#include <A2DVector3.hpp>

// external include
#include <d3d9types.h>

namespace Advanced2D
{
    class A2DLight
    {
    public:
        typedef D3DLIGHTTYPE    A2DType;
        typedef D3DCOLORVALUE   A2DColor;
        typedef D3DVECTOR       A2DVector;

    private:
        D3DLIGHT9           mLight;
        D3DLIGHTTYPE        mType;
        int32               mLightNum;
   public:
        A2DLight( int32 aLightNum
                , A2DType aType
                , const A2DRenderVector& aPosition
                , const A2DRenderVector& aDirection
                , double64 aRange);
        virtual ~A2DLight();

        void SetPosX(double64 aValue) { mLight.Position.x = static_cast<float>(aValue); }
        double64 GetPosX() const { return mLight.Position.x; }
        void SetPosY(double64 aValue) { mLight.Position.y = static_cast<float>(aValue); }
        double64 GetPosY() const { return mLight.Position.y; }
        void SetPosZ(double64 aValue) { mLight.Position.z = static_cast<float>(aValue); }
        double64 GetPosZ() const { return mLight.Position.z; }

        A2DType GetType() const { return mType; }

        void SetColor(A2DColor aColor) { mLight.Diffuse = aColor; }
        A2DColor GetColor() const { return mLight.Diffuse; }

        void SetDirection(const A2DRenderVector& aDirection) { mLight.Direction = aDirection; }
        const A2DVector& GetDirection() const { return mLight.Direction; }

        void SetPosition(const A2DRenderVector& aPosition) { mLight.Position = aPosition; }
        const A2DVector& GetPosition() const { return mLight.Position; }

        void Update();
        void Show();
        void Hide();
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DLIGHT_HPP