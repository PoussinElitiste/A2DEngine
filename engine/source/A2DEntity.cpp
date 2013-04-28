// local include
#include <A2DEngine.hpp>

namespace Advanced2D
{
    A2DEntity::A2DEntity(A2DRenderType aRenderType)
        : mRenderType(aRenderType)
        , mId(-1)
        , mName("")
        , mIsVisible(true)
        , mIsAlive(true)
        , mObjectType(0)
        , mLifetimeLength(0)
        , mLifetimeTimer()
    {
    }
}; // namespace