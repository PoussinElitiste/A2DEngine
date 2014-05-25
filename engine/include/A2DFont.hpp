#ifndef INC_ADVANCED2D_A2DFONT_HPP
#define INC_ADVANCED2D_A2DFONT_HPP

// local include
#include <A2DSprite.hpp>
#include <A2DString.hpp>

namespace Advanced2D
{
   class A2DFont;
   typedef std::tr1::shared_ptr<A2DFont> A2DFontPtr;

   class A2DFont
      : public A2DSprite
   {
   public:
      virtual ~A2DFont() {}
      static A2DFontPtr create();

   private:
      A2DFont();
      int32 mWidths[256]; // ASCII code offset

   public:
      void print(int32 aX,int32 aY, A2DString aText, int32 aColor = 0xFFFFFFFF);
      int32 getCharacterWidth() { return get(WIDTH); }
      int32 getCharacterHeight() { return get(HEIGHT); }
      void setCharWidth(int32 aWidth) { setDimension(WIDTH, aWidth); }
      void setCharSize(int32 aWidth, int32 aHeight) { setSize( aWidth, aHeight ); }
      bool loadWidthData(A2DString aFilename);
   }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DFONT_HPP