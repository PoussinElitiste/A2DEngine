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
   typedef std::tr1::shared_ptr<A2DFont> A2DFontPtr;

   class A2DConsole;
   typedef std::tr1::shared_ptr<A2DConsole> A2DConsolePtr;

   class A2DConsole
   {
   public:
      virtual ~A2DConsole();

   private:
      typedef A2DArray<A2DString>            StringArray;
      typedef A2DArray<A2DString>::iterator  StringArrayIt;
      A2DConsole();

      bool8          mShowing;
      A2DSpritePtr   mpPanel;
      A2DFontPtr     mpFont;
      int32          mCurrentLine;
      StringArray    mTextlines;
      StringArrayIt  mIter;

   public:
      static A2DConsolePtr create();
      bool8 init();
      void  draw();
      void  clear();
      void  print(A2DString aText, int32 aLine = -1);
      bool8 isShowing() { return mShowing; }
      void  show() { mShowing = true; }
      void  hide() { mShowing = false; }
      void  setShowing(bool8 aValue) { mShowing = aValue; }
   }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DCONSOLE_HPP