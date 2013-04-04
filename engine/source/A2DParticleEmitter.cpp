// local include
#include <A2DEngine.hpp>

namespace Advanced2D 
{
    A2DParticleEmitter::A2DParticleEmitter()
        : mpImage(NULL)
        , mMax(100)
        , mLength(100)
        , mDirection(0)
        , mAlphaMin(254)
        , mAlphaMax(255)
        , mMinR(0)
        , mMaxR(255)
        , mMinG(0)
        , mMaxG(255)
        , mMinB(0)
        , mMaxB(255)
        , mSpread(10)
        , mVelocity(1.0f)
        , mScale(1.0f)
    {}

    A2DParticleEmitter::~A2DParticleEmitter()
    {
        delete mpImage;

        //destroy particles
        for (iter item = mParticles.begin(); item != mParticles.end(); ++item)
        {
            delete *item;
        }

        mParticles.clear();
    }

    bool8 A2DParticleEmitter::LoadSpriteImage(string aImageFile)
    {
        mpImage = new A2DTexture();
        return mpImage->Load(aImageFile);
    }

    void A2DParticleEmitter::Add()
    {
        static double64 PI_DIV_180 = 3.1415926535 / 180.0f;
        double64 vx,vy;

        //create a new particle
        A2DSprite* pSprite = new A2DSprite();
        pSprite->SetImage(mpImage);
        pSprite->SetPosition(mPosition(X), mPosition(Y));
        
        //add some randomness to the spread
        double64 variation = (rand() % mSpread - mSpread/2) / 100.0f;

        //set linear velocity
        double64 dir = mDirection - 90.0;
        vx = cos( dir * PI_DIV_180) + variation;
        vy = sin( dir * PI_DIV_180) + variation;
        pSprite->SetVelocity(vx * mVelocity, vy * mVelocity);

        //set random color based on ranges
        int32 r = rand() % (mMaxR - mMinR) + mMinR;
        int32 g = rand() % (mMaxG - mMinG) + mMinG;
        int32 b = rand() % (mMaxB - mMinB) + mMinB;
        int32 a = rand() % (mAlphaMax - mAlphaMin) + mAlphaMin;
        pSprite->SetColor(D3DCOLOR_RGBA(r, g, b, a));

        //set the scale
        pSprite->SetScale( mScale );

        //add particle to the emitter
        mParticles.push_back(pSprite);
    }

    void A2DParticleEmitter::Draw()
    {
        //draw particles
        for (iter item = mParticles.begin(); item != mParticles.end(); ++item)
        {
            (*item)->Draw();
        }
    } 

    void A2DParticleEmitter::Update()
    {
        static A2DTimer timer;

        //do we need to add a new particle?
        if ((int32)mParticles.size() < mMax)
        {
            //trivial but necessary slowdown
            if (timer.StopWatch(1)) 
            { Add(); }
        }
        
        for (iter item = mParticles.begin(); item != mParticles.end(); ++item)
        {
            //update particle’s position
            (*item)->Move();

            //is particle beyond the emitter’s range?
            const A2DVector3& pos = (*item)->GetPosition();
            if ( pos.Distance2D(mPosition) > mLength)
            {
                //reset particle to the origin
                (*item)->SetPosition(mPosition(X), mPosition(Y));
            }
        }
    }

    void A2DParticleEmitter::SetAlphaRange(int32 aMin,int32 aMax)
    {
        mAlphaMin = aMin;
        mAlphaMax = aMax;
    }

    void A2DParticleEmitter::SetColorRange(int32 aR1, int32 aG1, int32 aB1, int32 aR2, int32 aG2, int32 aB2)
    {
        mMinR = aR1; mMaxR = aR2;
        mMinG = aG1; mMaxG = aG2;
        mMinB = aB1; mMaxB = aB2;
    }

}; // namespace