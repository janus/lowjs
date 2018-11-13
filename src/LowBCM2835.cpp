// -----------------------------------------------------------------------------
//  LowBCM2835.cpp
// -----------------------------------------------------------------------------


#include "LowBCM2835.h"
#include "bcm2835.h"
#include "low_alloc.h"
#include "low_config.h"
#include "low_data_thread.h"
#include "low_loop.h"
#include "low_main.h"
#include "low_system.h"

#include "duktape.h"

#include <cstdlib>
#include <unistd.h>
#include <stdint.h>


// -----------------------------------------------------------------------------
//  LowBCM2835::LowBCM2835
// -----------------------------------------------------------------------------

LowBCM2835::LowBCM2835(low_main_t *low) :
    LowDataCallback(low), LowLoopCallback(low), mLow(low), mCallID(0)
{
}


// -----------------------------------------------------------------------------
//  LowBCM2835::~LowBCM2835
// -----------------------------------------------------------------------------

LowBCM2835::~LowBCM2835()
{
    low_data_clear_callback(mLow, this);

    if(mCallID)
    {
        low_remove_stash(mLow, mCallID);
        mLow->run_ref--;
    }
}


// -----------------------------------------------------------------------------
//  LowBCM2835::Init
// -----------------------------------------------------------------------------

void LowBCM2835::Init(int callID)
{



    mCallID = callID;
    mPhase = LOWBCM2835_PHASE_INIT;
    low_data_set_callback(mLow, this, LOW_DATA_THREAD_PRIORITY_MODIFY);
}


// -----------------------------------------------------------------------------
//  LowBCM2835::Close
// -----------------------------------------------------------------------------

void LowBCM2835::Close(int callID)
{


    mPhase = LOWBCM2835_PHASE_CLOSE;
    low_data_set_callback(mLow, this, LOW_DATA_THREAD_PRIORITY_MODIFY);
}


// -----------------------------------------------------------------------------
//  LowBCM2835::SetDebug
// -----------------------------------------------------------------------------

void LowBCM2835::SetDebug(uint8_t debug, int callID)
{

    if(callID) {
        mCallID = low_add_stash(mLow, callID);
        mLow->run_ref++;
    }
    mDebug = debug;

    mPhase = LOWBCM2835_PHASE_SETDEBUG;
    low_data_set_callback(mLow, this, LOW_DATA_THREAD_PRIORITY_READ);
}


// -----------------------------------------------------------------------------
//  LowBCM2835::Fsel
// -----------------------------------------------------------------------------

void LowBCM2835::Fsel(uint8_t pin, uint8_t mode, int callID)
{

    if(callID) {
        mCallID = low_add_stash(mLow, callID);
        mLow->run_ref++;
    }
    mPin = pin;
    mMode = mode;

    mPhase = LOWBCM2835_PHASE_FSEL;
    low_data_set_callback(mLow, this, LOW_DATA_THREAD_PRIORITY_MODIFY);
}



// -----------------------------------------------------------------------------
//  LowBCM2835::SetOutPin
// -----------------------------------------------------------------------------

void LowBCM2835::SetOutPin(uint8_t pin, int callID)
{
    if(callID) {
        mCallID = low_add_stash(mLow, callID);
        mLow->run_ref++;
    }
    mPin = pin;

    mPhase = LOWBCM2835_PHASE_SETOUTPIN;
    low_data_set_callback(mLow, this, LOW_DATA_THREAD_PRIORITY_MODIFY);
}

// -----------------------------------------------------------------------------
//  LowBCM2835::ClearOutPin
// -----------------------------------------------------------------------------

void LowBCM2835::ClearOutPin(uint8_t pin, int callID)
{

    if(callID) {
        mCallID = low_add_stash(mLow, callID);
        mLow->run_ref++;
    }
    mPin = pin;

    mPhase = LOWBCM2835_PHASE_CLEAROUTPIN;
    low_data_set_callback(mLow, this, LOW_DATA_THREAD_PRIORITY_MODIFY);
}

// -----------------------------------------------------------------------------
//  LowBCM2835::ReadPin
// -----------------------------------------------------------------------------

void LowBCM2835::ReadPin(uint8_t pin, int callID)
{

    if(callID) {
        mCallID = low_add_stash(mLow, callID);
        mLow->run_ref++;
    }
    mPin = pin;

    mPhase = LOWBCM2835_PHASE_CLEAROUTPIN;
    low_data_set_callback(mLow, this, LOW_DATA_THREAD_PRIORITY_MODIFY);
}


// -----------------------------------------------------------------------------
//  LowBCM2835::OnData
// -----------------------------------------------------------------------------


bool LowBCM2835::OnData()
{
    switch(mPhase)
    {
        case LOWBCM2835_PHASE_INIT:
            if (bcm2835_init() == 0) {
               duk_generic_error(mLow->duk_ctx, "Init: failed"); 
            }
            
            return false;

        case LOWBCM2835_PHASE_CLOSE:
            mError = 0;
            if(bcm2835_close() == 0){
                duk_generic_error(mLow->duk_ctx, "Close: failed");
            }


            return false;;

        case LOWBCM2835_PHASE_SETDEBUG:
            bcm2835_set_debug(mDebug);


            low_loop_set_callback(mLow, this);
            break; 
        
        case LOWBCM2835_PHASE_FSEL:
            bcm2835_gpio_fsel(mPin, mMode);


            low_loop_set_callback(mLow, this);
            break;  
        
        case LOWBCM2835_PHASE_SETOUTPIN:
            bcm2835_gpio_set(mPin);


            low_loop_set_callback(mLow, this);
            break;
        
        case LOWBCM2835_PHASE_CLEAROUTPIN:
            bcm2835_gpio_clr(mPin);


            low_loop_set_callback(mLow, this);
            break;
        
        case LOWBCM2835_PHASE_READPIN:
            //int rnt = bcm2835_gpio_lev(mPin);
            // Add get ctx from low
            duk_push_int(mLow->duk_ctx, bcm2835_gpio_lev(mPin));
            


            low_loop_set_callback(mLow, this);
            break;

    }
    return true;
}

// -----------------------------------------------------------------------------
//  LowBCM2835::OnLoop
// -----------------------------------------------------------------------------

bool LowBCM2835::OnLoop()
{
    if(mCallID) {
        int callID = mCallID;
        mCallID = 0;
        mLow->run_ref--;

        low_push_stash(mLow, callID, true);
        duk_call(mLow->duk_ctx, 1);
        
    } else if(mPhase == LOWBCM2835_PHASE_INIT || mPhase == LOWBCM2835_PHASE_CLOSE ){
        int callID = mCallID;
        mCallID = 0;
        mLow->run_ref--;

        low_push_stash(mLow, callID, true);
        duk_call(mLow->duk_ctx, 1);
        
    }

    return false;
}
