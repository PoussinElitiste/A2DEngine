// Local Include
#include <A2DEngine.hpp>

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

    DWORD A2DTimer::getTimer() const
    {
        return static_cast<DWORD>(timeGetTime());
    }

    DWORD A2DTimer::getStartTime() const
    {
        return static_cast<DWORD>(timeGetTime() - mTimerStart);
    }

    void A2DTimer::Sleep(int32 aMilliSecond)
    {
        DWORD start = getTimer();
        while (start + aMilliSecond > getTimer()) {}
    }

    void A2DTimer::Reset()
    {
        mStopWatchStart = getTimer();
    }

    bool8 A2DTimer::StopWatch(int32 aMilliSecond)
    {
        if ( timeGetTime() > mStopWatchStart + aMilliSecond ) 
        {
            mStopWatchStart = getTimer();
            return true;
        }
        else 
        { return false; }
    }
}; // namespace