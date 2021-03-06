// local include
#include <A2DEngine.hpp>

namespace Advanced2D
{
    A2DTexture::A2DTexture()
    {
        mpTexture = NULL;
    }

    A2DTexture::~A2DTexture()
    {
        release();
    }

    A2DTexturePtr A2DTexture::create()
    {
       return A2DTexturePtr(new A2DTexture());
    }

    int A2DTexture::getWidth() 
    { 
        return mInfo.Width; 
    };

    int A2DTexture::getHeight() 
    { 
        return mInfo.Height; 
    };

    bool A2DTexture::load(A2DString aFilename, D3DCOLOR transcolor)
    {
        //standard Windows return value
        HRESULT result;
    
        //get width and height from bitmap file
        result = D3DXGetImageInfoFromFile(aFilename.c_str(), &mInfo);
        if (result != D3D_OK) 	{
            mpTexture = NULL;
            return 1;
        }

        //create the new mpTexture by loading a bitmap image file
        D3DXCreateTextureFromFileEx( 
            gpEngine->getDevice(), //Direct3D device object
            aFilename.c_str(),      //bitmap filename
            mInfo.Width,            //bitmap image width
            mInfo.Height,           //bitmap image height
            1,                     //mip-map levels (1 for no chain)
            D3DPOOL_DEFAULT,       //the type of surface (standard)
            D3DFMT_UNKNOWN,        //surface format (default)
            D3DPOOL_DEFAULT,       //memory class for the texture
            D3DX_DEFAULT,          //image filter
            D3DX_DEFAULT,          //mip filter
            transcolor,            //color key for transparency
            &mInfo,                 //bitmap file info (from loaded file)
            NULL,                  //color palette
            &mpTexture );            //destination texture

        //make sure the bitmap textre was loaded correctly
        if (result != D3D_OK) 	
        {
            mpTexture = NULL;
            return 0;
        }

        return 1;
    }

    void A2DTexture::release()
    {
        if (mpTexture != NULL)
        { mpTexture->Release(); }
    }

    /*
    // D3DX support function used to fill texture with a solid color
    VOID WINAPI ColorFill (D3DXVECTOR4* pOut, const D3DXVECTOR2* pTexCoord, 
        const D3DXVECTOR2* pTexelSize, LPVOID pData)
    {
        *pOut = D3DXVECTOR4(pTexCoord->x, pTexCoord->y, 0.0f, 0.0f);
    }
        if (FAILED(r = D3DXFillTexture(texture, ColorFill, NULL))) 
        {
            mpTexture = NULL;
            return false;
        }
    */
    /*
    bool A2DTexture::create(int width,int height)
    {
        HRESULT r;

        r = D3DXCreateTexture(g_engine->getDevice(), width, height, 1, 0, 
            D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture );

        if (r != D3D_OK) 
        {
            mpTexture = NULL;
            return false;
        }

        LPDIRECT3DSURFACE9 surface;
        mpTexture->GetSurfaceLevel(0, &surface);
        g_engine->getDevice()->ColorFill( surface, NULL, 0xFFFFFFFF );
        surface->Release();

        return true;
    }
    */
}; // namespace