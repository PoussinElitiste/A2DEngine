#ifndef INC_ADVANCED2D_A2DCONSOLE_HPP
#define INC_ADVANCED2D_A2DCONSOLE_HPP

// local include
#include <A2DArray.hpp>
#include <A2DTypes.hpp>
#include <A2DSprite.hpp>

namespace Advanced2D
{
    class A2DSprite;
    class A2DFont;
    class A2DConsole
    {
    public:
        A2DConsole();
        virtual ~A2DConsole();

    private:
        bool8 mShowing;
        A2DSprite* mpPanel;
        A2DFont* mpFont;
        int32 mCurrentLine;
        A2DArray<A2DString> mTextlines;
        A2DArray<A2DString>::iterator mIter;

     public:
        bool8 Init();
        void Draw();
        void Clear();
        void Print(A2DString aText, int32 aLine = -1);
        bool8 IsShowing() { return mShowing; }
        void Show() { mShowing = true; }
        void Hide() { mShowing = false; }
        void SetShowing(bool8 aValue) { mShowing = aValue; }
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DCONSOLE_HPP