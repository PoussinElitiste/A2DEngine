#ifndef INC_ADVANCED2D_A2DTEXTURE_HPP
#define INC_ADVANCED2D_A2DTEXTURE_HPP

// local include

namespace Advanced2D
{
   class A2DTexture;
   typedef std::tr1::shared_ptr<A2DTexture> A2DTexturePtr;

   class A2DTexture
   {
   public:
      ~A2DTexture();

      static A2DTexturePtr create();
      //	bool create(int width,int height);
      bool load(A2DString aFilename, D3DCOLOR transcolor = D3DCOLOR_XRGB(0,0,0));
      void release();

      LPDIRECT3DTEXTURE9 getTexture() { return mpTexture; }
      int getWidth();
      int getHeight();

   private:
      A2DTexture();

      LPDIRECT3DTEXTURE9 mpTexture;
      D3DXIMAGE_INFO mInfo;
   }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DTEXTURE_HPP