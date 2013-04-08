#ifndef INC_ADVANCED2D_A2DAUDIO_HPP
#define INC_ADVANCED2D_A2DAUDIO_HPP

// local include
#include <A2DEngine.hpp>

namespace Advanced2D
{   
    class A2DSample;
    class A2DAudio
    {
        typedef A2DArray<A2DSample*> Samples;
        typedef A2DArray<A2DSample*>::iterator Iterator;

    public:
        A2DAudio();
        virtual ~A2DAudio();

    private:
        FMOD_SYSTEM* mpSystem;
        Samples mSamples;

    public:
        FMOD_SYSTEM* GetSystem() { return mpSystem; }

    public:
        bool8 Init();
        void Update(); //must be called once per frame
        bool8 Load(A2DString aFilename, A2DString aName);
        A2DSample* Load(A2DString aFilename);
        bool8 Play(A2DString aName);
        bool8 Play(A2DSample* aSample);
        void Stop(A2DString aName);
        void StopAll();
        void StopAllExcept(A2DString aName);
        bool8 IsPlaying(A2DString aName);
        bool8 IsPlaying(A2DSample* apSample);
        bool8 SampleExists(A2DString aName);
        A2DSample* FindSample(A2DString aName);
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DAUDIO_HPP