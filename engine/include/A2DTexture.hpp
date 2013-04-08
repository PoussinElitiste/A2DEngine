#ifndef INC_ADVANCED2D_A2DTEXTURE_HPP
#define INC_ADVANCED2D_A2DTEXTURE_HPP

// local include

namespace Advanced2D
{
    class A2DTexture
    {
    public:
        A2DTexture();
        ~A2DTexture();
    //	bool create(int width,int height);
        bool Load(A2DString aFilename, D3DCOLOR transcolor = D3DCOLOR_XRGB(0,0,0));
        void Release();
        LPDIRECT3DTEXTURE9 GetTexture() { return mpTexture; }
        int GetWidth();
        int GetHeight();

    private:
        LPDIRECT3DTEXTURE9 mpTexture;
        D3DXIMAGE_INFO mInfo;
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DTEXTURE_HPP