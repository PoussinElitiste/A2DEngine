// Local include
#include <A2DEngine.hpp>

namespace Advanced2D
{
    A2DAudio::A2DAudio()
        : mpSystem(nullptr)
    {
    }

    A2DAudio::~A2DAudio()
    {
        //release all samples
        for (Iterator it = mSamples.begin(); it != mSamples.end(); ++it)
        {
            (*it) = nullptr;
        }

        FMOD_System_Release(mpSystem);
    }

    bool8 A2DAudio::init()
    {
        if (FMOD_System_Create(&mpSystem) != FMOD_OK) 
        {
            return false;
        }

        if (FMOD_System_Init(mpSystem, 100, FMOD_INIT_NORMAL, NULL) != FMOD_OK) 
        {
            return false;
        }

        return true;
    }

    void A2DAudio::update()
    {   
        FMOD_System_Update(mpSystem);
    }
    
    A2DSamplePtr A2DAudio::load(A2DString aFilename)
    {
        if (aFilename.length() == 0) 
        { return false; }

        A2DSamplePtr pSample = A2DSample::create();
        
        FMOD_RESULT res = FMOD_System_CreateSound(
            mpSystem, //FMOD system
            aFilename.c_str(), //filename
            FMOD_DEFAULT, //default audio
            NULL, //n/a
            &pSample->mpSample); //pointer to sample

        if (res != FMOD_OK) 
        {
            pSample = nullptr;
        }

        return pSample;
    }

    bool8 A2DAudio::load(A2DString aFilename, A2DString aName)
    {
        if (aFilename.length() == 0 || aName.length() == 0) 
        { return false; }

        A2DSamplePtr pSample = A2DSample::create();
        pSample->setName(aName);

        FMOD_RESULT res = FMOD_System_CreateSound(
            mpSystem, //FMOD system
            aFilename.c_str(), //filename
            FMOD_DEFAULT, //default audio
            NULL, //n/a
            &pSample->mpSample); //pointer to sample

        if (res != FMOD_OK) 
        {
            return false;
        }

        mSamples.push_back(pSample);
        return true;
    }

    bool8 A2DAudio::isPlaying(A2DString aName)
    {
        A2DSamplePtr pSamp = findSample(aName);
        if (pSamp == nullptr) 
        { return false; }

        int32 index;
        FMOD_Channel_GetIndex(pSamp->mpChannel, &index);
        
        // FMOD returns 99 if sample is playing, 0 if not
        return (index > 0);
    }

    bool8 A2DAudio::isPlaying(A2DSamplePtr apSample)
    {
        if (apSample == nullptr) 
        { return false; }

        int32 index;
        FMOD_Channel_GetIndex(apSample->mpChannel, &index);
        
        // FMOD returns 99 if sample is playing, 0 if not
        return (index > 0);
    }

    A2DSamplePtr A2DAudio::findSample(A2DString aName)
    {
        A2DSamplePtr pSample = nullptr;
        for (Iterator it = mSamples.begin(); it != mSamples.end(); ++it)
        {
            if ((*it)->getName() == aName) 
            {
                pSample = (*it);
                break;
            }
        }

        return pSample;
    }

    bool8 A2DAudio::play(A2DString aName)
    {
        FMOD_RESULT res;
        A2DSamplePtr pSample = findSample(aName);

        if ( pSample!= nullptr && pSample->mpSample != NULL) 
        {
            //sample found, play it
            res = FMOD_System_PlaySound(
                mpSystem,
                FMOD_CHANNEL_FREE,
                pSample->mpSample,
                true,
                &pSample->mpChannel);

            if (res != FMOD_OK)
            { return false; }

            FMOD_Channel_SetLoopCount(pSample->mpChannel, -1);
            FMOD_Channel_SetPaused(pSample->mpChannel, false);
        }

        return true;
    }

    bool8 A2DAudio::play(A2DSamplePtr apSample)
    {
        FMOD_RESULT res;
        if (apSample == nullptr) 
        { return false; }

        if (apSample->mpSample == nullptr) 
        { return false; }
        
        res = FMOD_System_PlaySound(
            mpSystem,
            FMOD_CHANNEL_FREE,
            apSample->mpSample,
            true,
            &apSample->mpChannel);

        if (res!= FMOD_OK) 
        { return false; }

        FMOD_Channel_SetLoopCount( apSample->mpChannel, -1 );
        FMOD_Channel_SetPaused( apSample->mpChannel, false );

        return true;
    }

    void A2DAudio::stop(A2DString aName)
    {
        if (!isPlaying(aName)) 
        { return; }

        A2DSamplePtr pSample = findSample(aName);

        if ( pSample == nullptr ) 
        { return; }

        FMOD_Channel_Stop(pSample->mpChannel);
    }

    void A2DAudio::stopAll()
    {
        for (Iterator it = mSamples.begin(); it != mSamples.end(); ++it)
        {
            FMOD_Channel_Stop( (*it)->mpChannel );
        }
    }

    void A2DAudio::stopAllExcept(A2DString name)
    {
        for (Iterator it = mSamples.begin(); it != mSamples.end(); ++it)
        {
            if ( (*it)->getName() != name ) 
            {
                FMOD_Channel_Stop( (*it)->mpChannel );
            }
        }
    }

}; // namespace