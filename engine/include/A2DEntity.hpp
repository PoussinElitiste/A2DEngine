#ifndef INC_ADVANCED2D_A2DENTITY_HPP
#define INC_ADVANCED2D_A2DENTITY_HPP

// local include
#include <A2DTimer.hpp>
#include <A2DString.hpp>
#include <A2DTypes.hpp>

namespace Advanced2D
{   
    enum A2DRenderType 
    {
        RENDER_2D = 0,
        RENDER_3D = 1
    };

    class A2DEntity
    {
    public:
        A2DEntity(A2DRenderType aRenderType);
        virtual ~A2DEntity() {}

   private:
        int32 mId;
        A2DString mName;
        bool8 mIsVisible;
        bool8 mIsAlive;
        A2DRenderType mRenderType;
        int32 mObjectType;
        int32 mLifetimeLength;
        A2DTimer mLifetimeTimer;

    public:
        virtual void Move() = 0;
        virtual void Animate() = 0;
        virtual void Draw() = 0;

    public:
        void SetID(int32 aValue) { mId = aValue; }
        int32 GetID() { return mId; }

        A2DRenderType GetRenderType() { return mRenderType; }
        void SetRenderType(A2DRenderType aType) { mRenderType = aType; }

        A2DString GetName() { return mName; }
        void SetName(A2DString aValue) { mName = aValue; }

        bool8 IsVisible() { return mIsVisible; }
        void SetVisible(bool8 aValue) { mIsVisible = aValue; }

        bool8 IsAlive() { return mIsAlive; }
        void SetAlive(bool8 aValue) { mIsAlive = aValue; }

        int32 GetLifetime() { return mLifetimeLength; }
        void SetLifetime(int32 aMilliseconds) 
        {
            mLifetimeLength = aMilliseconds; 
            mLifetimeTimer.Reset();
        }

        bool8 lifetimeExpired() 
        {
            return mLifetimeTimer.StopWatch(mLifetimeLength);
        }

        int32 GetObjectType() { return mObjectType; }
        void SetObjectType(int32 aValue) { mObjectType = aValue; }
    }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DENTITY_HPP