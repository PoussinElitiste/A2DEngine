// local include
#include <A2DEngine.hpp>

namespace Advanced2D
{
    A2DConsole::A2DConsole()
        : mShowing(false)
        , mCurrentLine(0)
    {   
        clear();
    }

    A2DConsole::~A2DConsole()
    {
        //delete mpFont;
        //delete mpPanel;
    }

    A2DConsolePtr A2DConsole::create()
    {
       return A2DConsolePtr(new A2DConsole());
    }

    bool8 A2DConsole::init()
    {
        // load the panel image
        mpPanel = A2DSprite::create();
        if (!mpPanel->loadSpriteImage("../../asset/system/panel.tga")) 
        { return false; }

        double64 scale = gpEngine->getScreenProperties().mWidth / 640.0f;
        mpPanel->setScale(scale);
        mpPanel->setColor(0x99FFFFFF);

        // load the font
        mpFont = A2DFont::create();
        if (!mpFont->loadSpriteImage("../../asset/system/system12.tga")) 
        { return false; }

        mpFont->setColumns(16);
        mpFont->setCharSize(14,16);

        if (!mpFont->loadWidthData("../../asset/system/system12.dat")) 
        { return false; }
        return true;
    }

    void A2DConsole::draw()
    {
        int32 x = 5, y = 0;
        if (!mShowing) 
        {
            return;
        }
        
        // draw panel background
        mpPanel->draw();

        // draw text lines
        for (uint32 n = 0; n < mTextlines.size(); ++n)
        {
            mpFont->print(x, y*14, mTextlines[n], 0xFF000000);
            y += 1;
            if (y > 26) 
            {
                if (x > 10) break;
                x = gpEngine->getScreenProperties().mWidth/2 + 5;
                y = 0;
            }
        }
    }

    void A2DConsole::print(A2DString aText, int32 aLine)
    {
        if (aLine > -1) 
        { mCurrentLine = aLine; }

        mTextlines[mCurrentLine] = aText;

        if (mCurrentLine++ > 52) 
        { mCurrentLine = 0; }
    }

    void A2DConsole::clear()
    {
        for (int32 n=0; n<55; ++n)
        {
            mTextlines.push_back("");
        }
    }
}; // namespace