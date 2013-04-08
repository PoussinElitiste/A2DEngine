// Local include
#include <A2DEngine.hpp>

namespace Advanced2D
{  
    A2DSample::A2DSample()
        : mpSample(nullptr)
        , mpChannel(nullptr)
    {
    }

    A2DSample::~A2DSample()
    {
        if ( mpSample != nullptr ) 
        {
            FMOD_Sound_Release( mpSample );
            mpSample = nullptr;
        }
    }
}; // namespace