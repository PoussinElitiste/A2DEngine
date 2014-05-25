#ifndef INC_ADVANCED2D_A2DSAMPLE_HPP
#define INC_ADVANCED2D_A2DSAMPLE_HPP

// local include 
#include <A2DEngine.hpp>

namespace Advanced2D
{
    // Wrapper to interact with FMOD
   class A2DSample;
   typedef std::tr1::shared_ptr<A2DSample> A2DSamplePtr;

   class A2DSample
   {
   public:
      virtual ~A2DSample();
      static A2DSamplePtr create();

   private:
      A2DSample();
      A2DString mName;

   public:
      FMOD_SOUND* mpSample;
      FMOD_CHANNEL* mpChannel;
      A2DString getName() { return mName; }
      void setName(A2DString aValue) { mName = aValue; }
   }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DSAMPLE_HPP