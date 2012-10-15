// local include
#include "A2DMesh.hpp"

// external include
#include <string.h>

namespace Advanced2D
{
    A2DMesh::A2DTransformationInfos::A2DTransformationInfos( const A2DVector3& aPosition, const A2DVector3& aVelocity
                 , const A2DVector3& aRotation, const A2DVector3& aScale )
        : mPosition(aPosition)
        , mVelocity(aVelocity)
        , mRotate(aRotation)
        , mScale(aScale)
    {}

    A2DMesh::A2DMesh()
        : mpMesh(NULL)
        , mpD3DXMaterials(NULL)
        , mpMatBuffer(NULL)
        , mpMaterials(NULL)
        , mpTextures(NULL)
        , mMaterialCount(0)
        , mTransform(A2DTransformationInfos())
    {}

    A2DMesh::~A2DMesh()
    {
        if (mpMaterials != NULL) { delete[] mpMaterials; }

        //remove textures from memory
        if (mpTextures != NULL) 
        {
            for( DWORD i = 0; i < mMaterialCount; ++i)
            {
                if (mpTextures[i] != NULL)
                { mpTextures[i]->Release(); }
            }

            delete[] mpTextures;
        }

        if (mpMesh != NULL) { mpMesh->Release(); }
    }

    bool A2DMesh::Load(const char* aFileName)
    {
        HRESULT result;

        // load mesh from the specified file
        result = D3DXLoadMeshFromX( aFileName // filename
            , D3DXMESH_SYSTEMMEM //mesh options
            , gpEngine->GetDevice() //Direct3D device
            , NULL //adjacency buffer
            , &mpMatBuffer //material buffer
            , NULL //special effects
            , &mMaterialCount //number of materials
            , &mpMesh ); //resulting mesh

        if (result != D3D_OK) 
            { return false; }

        // extract material properties and texture names from material buffer
        mpD3DXMaterials = static_cast<LPD3DXMATERIAL>(mpMatBuffer->GetBufferPointer());
        mpMaterials = new D3DMATERIAL9[mMaterialCount];
        mpTextures = new LPDIRECT3DTEXTURE9[mMaterialCount];

        // create the materials and textures
        for (DWORD i=0; i < mMaterialCount; ++i)
        {
            // grab the material
            mpMaterials[i] = mpD3DXMaterials[i].MatD3D;

            // set ambient color for material
            mpMaterials[i].Ambient = mpMaterials[i].Diffuse;
            // mpMaterials[i].Emissive = mpMaterials[i].Diffuse;
            mpMaterials[i].Power = 0.5f;
            // mpMaterials[i].Specular = mpMaterials[i].Diffuse;

            mpTextures[i] = NULL;

            if( mpD3DXMaterials[i].pTextureFilename != NULL &&
                lstrlen(mpD3DXMaterials[i].pTextureFilename) > 0 )
            {
                // load texture file specified in .x file
                result = D3DXCreateTextureFromFile( gpEngine->GetDevice()
                            , mpD3DXMaterials[i].pTextureFilename
                            , &mpTextures[i] );

                if (result != D3D_OK) 
                { return false; }
            }
        }
        
        //done using material buffer
        mpMatBuffer->Release();

        return true;
    }

    void A2DMesh::CreateSphere(float aRadius, int aSlices, int aStacks)
    {
        D3DXCreateSphere(gpEngine->GetDevice(), aRadius, aSlices, aStacks, &mpMesh, NULL);
    }

    void A2DMesh::CreateCube(float aWidth, float aHeight, float aDepth)
    {
        D3DXCreateBox(gpEngine->GetDevice(), aWidth, aHeight, aDepth, &mpMesh, NULL);
    }

    void A2DMesh::Draw()
    {
        if (mMaterialCount == 0) 
        {
            mpMesh->DrawSubset(0);
        }
        else 
        {
            // draw each mesh subset
            for( DWORD i=0; i < mMaterialCount; ++i )
            {
                // Set the material and texture for this subset
                gpEngine->GetDevice()->SetMaterial( &mpMaterials[i] );

                if (mpTextures[i])
                {
                    if (mpTextures[i]->GetType() == D3DRTYPE_TEXTURE)
                    {
                        D3DSURFACE_DESC desc;
                        mpTextures[i]->GetLevelDesc(0, &desc);
                        if (desc.Width > 0)
                        {
                            gpEngine->GetDevice()->SetTexture( 0, mpTextures[i] );
                        }
                    }
                }

                // Draw the mesh subset
                mpMesh->DrawSubset( i );
            }
        }
    }

    void A2DMesh::Tranform()
    {
        //set rotation matrix
        float x = D3DXToRadian(mTransform.mRotate.x);
        float y = D3DXToRadian(mTransform.mRotate.y);
        float z = D3DXToRadian(mTransform.mRotate.z);
        D3DXMatrixRotationYawPitchRoll(&mMatRotate, x, y, z);

        //set scaling matrix
        D3DXMatrixScaling(&mMatScale, mTransform.mScale.x, mTransform.mScale.y, mTransform.mScale.z);

        //set translation matrix
        D3DXMatrixTranslation(&mMatTranslate, mTransform.mPosition.x, mTransform.mPosition.y, mTransform.mPosition.z);

        //transform the mesh
        mMatWorld = mMatRotate * mMatScale * mMatTranslate;
        gpEngine->GetDevice()->SetTransform(D3DTS_WORLD, &mMatWorld);
    }

    void A2DMesh::Rotate(const A2DVector3& aRot)
    {
        Rotate(aRot.x, aRot.y, aRot.z);
    }

    void A2DMesh::Rotate(float x, float y, float z)
    {
        mTransform.mRotate.x += x;
        mTransform.mRotate.y += y;
        mTransform.mRotate.z += z;
    }

    void A2DMesh::Update()
    {
        mTransform.mPosition.x += mTransform.mVelocity.x;
        mTransform.mPosition.y += mTransform.mVelocity.y;
        mTransform.mPosition.z += mTransform.mVelocity.z;
    }

    void A2DMesh::LimitBoundary(float left, float right, float top, float bottom, float back, float front)
    {
        const A2DVector3& position = mTransform.mPosition; 
        if ( position.x < left || position.x > right) 
        {
            mTransform.mVelocity.x *= -1;
        }

        if (position.y < bottom || position.y > top) 
        {
            mTransform.mVelocity.y *= -1;
        }

        if (position.z < front || position.z > back) 
        {
            mTransform.mVelocity.z *= -1;
        }
    }
}; // namespace