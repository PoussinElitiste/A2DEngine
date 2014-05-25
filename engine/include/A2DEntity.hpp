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

   class A2DEntity;
   typedef std::tr1::shared_ptr<A2DEntity> A2DEntityPtr;

   class A2DEntity
   {
   public:
      virtual ~A2DEntity() {}

   protected:
      A2DEntity(A2DRenderType aRenderType);

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
      virtual void move() = 0;
      virtual void animate() = 0;
      virtual void draw() = 0;

   public:
      void setID(int32 aValue) { mId = aValue; }
      int32 getID() { return mId; }

      A2DRenderType getRenderType() { return mRenderType; }
      void setRenderType(A2DRenderType aType) { mRenderType = aType; }

      A2DString getName() { return mName; }
      void setName(A2DString aValue) { mName = aValue; }

      bool8 isVisible() { return mIsVisible; }
      void setVisible(bool8 aValue) { mIsVisible = aValue; }

      bool8 isAlive() { return mIsAlive; }
      void setAlive(bool8 aValue) { mIsAlive = aValue; }

      int32 getLifetime() { return mLifetimeLength; }
      void setLifetime(int32 aMilliseconds) 
      {
         mLifetimeLength = aMilliseconds; 
         mLifetimeTimer.Reset();
      }

      bool8 lifetimeExpired() 
      {
         return mLifetimeTimer.StopWatch(mLifetimeLength);
      }

      int32 getObjectType() { return mObjectType; }
      void setObjectType(int32 aValue) { mObjectType = aValue; }
   }; // class 
} // namespace

#endif // INC_ADVANCED2D_A2DENTITY_HPP