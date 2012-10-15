#ifndef INC_ADVANCED2D_A2DMESH_HPP
#define INC_ADVANCED2D_A2DMESH_HPP

// external include
#include <d3dx9mesh.h>
#include <d3dx9math.h>

// local include 
#include "A2DEngine.hpp"
#include "A2DVector3.hpp"

namespace Advanced2D
{
    class A2DMesh
    {
    public:
        struct A2DTransformationInfos
         {
             A2DTransformationInfos( const A2DVector3& aPosition = A2DVector3()
                 , const A2DVector3& aVelocity = A2DVector3()
                 , const A2DVector3& aRotation = A2DVector3()
                 , const A2DVector3& aScale = A2DVector3(1.f, 1.f, 1.f) );

             A2DVector3 mPosition;
             A2DVector3 mVelocity;
             A2DVector3 mRotate;
             A2DVector3 mScale;
         }; // A2DTransformationInfos

    private:
        LPD3DXMESH          mpMesh;

        LPD3DXBUFFER        mpMatBuffer;
        LPD3DXMATERIAL     mpD3DXMaterials;

        D3DMATERIAL9*       mpMaterials;
        LPDIRECT3DTEXTURE9* mpTextures;

        DWORD              mMaterialCount;

        A2DTransformationInfos mTransform;

        D3DXMATRIX mMatRotate;
        D3DXMATRIX mMatScale;
        D3DXMATRIX mMatTranslate;

        D3DXMATRIX mMatWorld;

   public:
        A2DMesh();
        virtual ~A2DMesh();

        uint32 GetFaceCount() const { return mpMesh->GetNumFaces(); }
        uint32 GetVertexCount() const { return mpMesh->GetNumVertices(); }

        bool Load(const char* aFileName);
        void CreateSphere(float aRadius, int aSlices, int aStacks);
        void CreateCube(float aWidth, float aHeight, float aDepth);

        void Update();
        void LimitBoundary(float left, float right, float top, float bottom, float back, float front);
        void Rotate(const A2DVector3& aRot); // in degree
        void Rotate(float x, float y, float z); // in degree
        void Tranform();
        void Draw();
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DMESH_HPP