#ifndef INC_ADVANCED2D_A2DTEMPLATE_HPP
#define INC_ADVANCED2D_A2DTEMPLATE_HPP

// external include
#include <array>

// local include
#include <A2DTypes.hpp>

namespace Advanced2D
{
   //-----------------------------------------------------------
   // A2DBaseCategory
   // TODO: need to specialize getter/setter for primitive class
   //-----------------------------------------------------------
   template< typename Category, uint32 MAX, class ObjType >
   class A2DBaseCategory
   {
   protected:
      std::array<ObjType, MAX>  mObj;

   public:
      A2DBaseCategory(){}
      virtual ~A2DBaseCategory(){}

      virtual void set( Category aCoord, const ObjType &aValue ) { mObj[aCoord] = aValue; }
      virtual const ObjType &operator()( Category aCoord ) const { return mObj[aCoord]; }
      virtual ObjType &operator()( Category aCoord ) { return mObj[aCoord]; }
   }; // A2DCategoryTemplate
} // Advanced2D

#endif // INC_ADVANCED2D_A2DTEMPLATE_HPP