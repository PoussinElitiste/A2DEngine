#ifndef INC_ADVANCED2D_A2DSAMPLE_HPP
#define INC_ADVANCED2D_A2DSAMPLE_HPP

// local include 
#include <A2DEngine.hpp>

namespace Advanced2D
{
    class A2DSample
    {
    public:
        A2DSample();
        virtual ~A2DSample();

    private:
        A2DString mName;

    public:
        FMOD_SOUND* mpSample;
        FMOD_CHANNEL* mpChannel;
        A2DString GetName() { return mName; }
        void SetName(A2DString aValue) { mName = aValue; }
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DSAMPLE_HPP