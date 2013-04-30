// local include
#include <A2DEngine.hpp>

namespace Advanced2D
{
    A2DConsole::A2DConsole()
        : mShowing(false)
        , mCurrentLine(0)
    {   
        Clear();
    }

    A2DConsole::~A2DConsole()
    {
        delete mpFont;
        delete mpPanel;
    }

    bool8 A2DConsole::Init()
    {
        // load the panel image
        mpPanel = new A2DSprite();
        if (!mpPanel->LoadSpriteImage("../../asset/system/panel.tga")) 
        { return false; }

        double64 scale = gpEngine->GetScreenProperties().mWidth / 640.0f;
        mpPanel->SetScale(scale);
        mpPanel->SetColor(0x99FFFFFF);

        // load the font
        mpFont = new A2DFont();
        if (!mpFont->LoadSpriteImage("../../asset/system/system12.tga")) 
        { return false; }

        mpFont->SetColumns(16);
        mpFont->SetCharSize(14,16);

        if (!mpFont->LoadWidthData("../../asset/system/system12.dat")) 
        { return false; }
        return true;
    }

    void A2DConsole::Draw()
    {
        int32 x = 5, y = 0;
        if (!mShowing) 
        {
            return;
        }
        
        // draw panel background
        mpPanel->Draw();

        // draw text lines
        for (uint32 n = 0; n < mTextlines.size(); ++n)
        {
            mpFont->Print(x, y*14, mTextlines[n], 0xFF000000);
            y += 1;
            if (y > 26) 
            {
                if (x > 10) break;
                x = gpEngine->GetScreenProperties().mWidth/2 + 5;
                y = 0;
            }
        }
    }

    void A2DConsole::Print(A2DString aText, int32 aLine)
    {
        if (aLine > -1) 
        { mCurrentLine = aLine; }

        mTextlines[mCurrentLine] = aText;

        if (mCurrentLine++ > 52) 
        { mCurrentLine = 0; }
    }

    void A2DConsole::Clear()
    {
        for (int32 n=0; n<55; ++n)
        {
            mTextlines.push_back("");
        }
    }
}; // namespace