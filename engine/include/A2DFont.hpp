#ifndef INC_ADVANCED2D_A2DFONT_HPP
#define INC_ADVANCED2D_A2DFONT_HPP

// local include
#include <A2DSprite.hpp>
#include <A2DString.hpp>

namespace Advanced2D
{
    class A2DFont
        : public A2DSprite
    {
    public:
        A2DFont();
        virtual ~A2DFont() {}

    private:
        int32 mWidths[256]; // ASCII code offset

    public:
        void Print(int32 aX,int32 aY, A2DString aText, int32 aColor = 0xFFFFFFFF);
        int32 GetCharacterWidth() { return Get(WIDTH); }
        int32 GetCharacterHeight() { return Get(HEIGHT); }
        void SetCharWidth(int32 aWidth) { SetDimension(WIDTH, aWidth); }
        void SetCharSize(int32 aWidth, int32 aHeight) { SetSize( aWidth, aHeight ); }
        bool LoadWidthData(A2DString aFilename);
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DFONT_HPP