// Local Include
#include "A2DTimer.hpp"

namespace Advanced2D
{
    A2DTimer::A2DTimer(void)
        : mTimerStart(timeGetTime())
    {
        Reset();
    }

    A2DTimer::~A2DTimer(void)
    {
    }

    DWORD A2DTimer::GetTimer() const
    {
        return static_cast<DWORD>(timeGetTime());
    }

    DWORD A2DTimer::GetStartTime() const
    {
        return static_cast<DWORD>(timeGetTime() - mTimerStart);
    }

    void A2DTimer::Sleep(int32 aMilliSecond)
    {
        DWORD start = GetTimer();
        while (start + aMilliSecond > GetTimer()) {}
    }

    void A2DTimer::Reset()
    {
        mStopWatchStart = GetTimer();
    }

    bool8 A2DTimer::StopWatch(int32 aMilliSecond)
    {
        if ( timeGetTime() > mStopWatchStart + aMilliSecond ) 
        {
            mStopWatchStart = GetTimer();
            return true;
        }
        else 
        { return false; }
    }
}; // namespace