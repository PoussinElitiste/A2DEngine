#ifndef INC_ADVANCED2D_A2DMESH_HPP
#define INC_ADVANCED2D_A2DMESH_HPP

// external include
#include <d3dx9math.h>

// local include 
#include <A2DEntity.hpp>
#include <A2DVector3.hpp>

namespace Advanced2D
{
   class A2DMesh;
   typedef std::tr1::shared_ptr<A2DMesh> A2DMeshPtr;

   class A2DMesh
      : public A2DEntity
   {
   public:
      struct A2DTransformationInfos
      {
            A2DTransformationInfos( const A2DRenderVector &aPosition = A2DRenderVector()
                                  , const A2DRenderVector &aVelocity = A2DRenderVector()
                                  , const A2DRenderVector &aRotation = A2DRenderVector()
                                  , const A2DRenderVector &aScale    = A2DRenderVector(1.f, 1.f, 1.f) );

            A2DRenderVector mPosition;
            A2DRenderVector mVelocity;
            A2DRenderVector mRotate;
            A2DRenderVector mScale;
      }; // A2DTransformationInfos

   private:
      LPD3DXMESH         mpMesh;

      LPD3DXBUFFER       mpMatBuffer;
      LPD3DXMATERIAL     mpD3DXMaterials;

      D3DMATERIAL9       *mpMaterials;
      LPDIRECT3DTEXTURE9 *mpTextures;

      DWORD              mMaterialCount;

      A2DTransformationInfos mTransform;

      D3DXMATRIX mMatRotate;
      D3DXMATRIX mMatScale;
      D3DXMATRIX mMatTranslate;

      D3DXMATRIX mMatWorld;

   public:
      virtual ~A2DMesh();

   public:
      static A2DMeshPtr create();
      void setTransformation(const A2DTransformationInfos &aTransform);

   protected:
      A2DMesh();
      void transform();
    
   // Service
   public:
      uint32 getFaceCount() const { return mpMesh->GetNumFaces(); }
      uint32 getVertexCount() const { return mpMesh->GetNumVertices(); }

      bool load(const char8 *aFileName);
      void createSphere(float32 aRadius, int32 aSlices, int32 aStacks);
      void createCube(float32 aWidth, float32 aHeight, float32 aDepth);
        
      void limitBoundary(float32 left, float32 right, float32 top, float32 bottom, float32 back, float32 front);

      void rotate(const A2DRenderVector &aValue); // in degree
      void rotate(float32 x, float32 y, float32 z); // in degree
      void translate(const A2DRenderVector &aValue);
      void translate(float32 x, float32 y, float32 z); 
      void scale(const A2DRenderVector &aValue); 
      void scale(float32 x, float32 y, float32 z);
        
      // virtual
      void move();
      void animate() {}
      void draw();
   }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DMESH_HPP