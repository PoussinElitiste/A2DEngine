#ifndef INC_ADVANCED2D_A2DTIMER_HPP
#define INC_ADVANCED2D_A2DTIMER_HPP

// external include
#include <time.h>
#include <windows.h>

// Local include
#include "A2DTypes.hpp"

namespace Advanced2D
{
    class A2DTimer
    {
    public:
        A2DTimer();
        ~A2DTimer();
        DWORD GetTimer() const;
        DWORD GetStartTime() const; // in Milli second
        void Sleep(int32 aMilliSecond);
        void Reset();
        bool8 StopWatch(int32 aMilliSecond);

    private:
        DWORD mTimerStart;
        DWORD mStopWatchStart;
    }; // class

}; // namespace
#endif // INC_ADVANCED2D_A2DTIMER_HPP