#ifndef INC_ADVANCED2D_A2DAUDIO_HPP
#define INC_ADVANCED2D_A2DAUDIO_HPP

// local include
#include <A2DEngine.hpp>

namespace Advanced2D
{   
   class A2DSample;
   typedef std::tr1::shared_ptr<A2DSample> A2DSamplePtr;

   class A2DAudio
   {
      typedef A2DArray<A2DSamplePtr>             Samples;
      typedef A2DArray<A2DSamplePtr>::iterator   Iterator;

   public:
      A2DAudio();
      virtual ~A2DAudio();

   private:
      FMOD_SYSTEM *mpSystem;
      Samples mSamples;

   public:
      FMOD_SYSTEM *getSystem() { return mpSystem; }

   public:
      bool8 init();
      void update(); //must be called once per frame
      bool8 load(A2DString aFilename, A2DString aName);
      A2DSamplePtr load(A2DString aFilename);
      bool8 play(A2DString aName);
      bool8 play(A2DSamplePtr aSample);
      void stop(A2DString aName);
      void stopAll();
      void stopAllExcept(A2DString aName);
      bool8 isPlaying(A2DString aName);
      bool8 isPlaying(A2DSamplePtr apSample);
      bool8 sampleExists(A2DString aName);
      A2DSamplePtr findSample(A2DString aName);
   }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DAUDIO_HPP