// local include
#include <A2DEngine.hpp>
#include <A2DFStream.hpp>
#include <A2DTypes.hpp>

namespace Advanced2D
{
    A2DFont::A2DFont() 
        : A2DSprite()
    {
        //set character widths to default
        memset(&mWidths, 0, sizeof(mWidths));
    }

    void A2DFont::Print(int32 aX, int32 aY, A2DString aText, int32 aColor)
    {
        float32 fx = static_cast<float32>(aX);
        float32 fy = static_cast<float32>(aY);

        // Set A2DFont color
        SetColor( aColor );
        //draw each character of the string
        for (uint32 n=0; n<aText.length(); ++n) 
        {
            int32 frame = static_cast<int32>(aText[n]);
            SetCurrentFrame( frame );
            SetPosition(A2DVector3(fx, fy));
            Draw();

            //use proportional width if available
            if (mWidths[frame] == 0) 
            { mWidths[frame] = mDimensions(WIDTH);}
            fx += static_cast<float32>(mWidths[frame] * mScaling);
        }
    }

    bool A2DFont::LoadWidthData(A2DString aFilename)
    {
        uchar8 buffer[512];
        //open A2DFont width data file
        A2DIFStream infile;
        infile.open(aFilename.c_str(), std::ios::binary);
        if (!infile) 
        { return false; }

        //read 512 bytes (2 bytes per character)
        infile.read( (char8*)(&buffer), 512 );
        if (infile.bad()) 
        { return false; }
        infile.close();

        //convert raw data to proportional width data
        for (int32 n=0; n<256; ++n) 
        {
            mWidths[n] = static_cast<int32>(buffer[n*2]);
        }

        return true;
    }
}; // namespace