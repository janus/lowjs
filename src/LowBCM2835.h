// -----------------------------------------------------------------------------
//  LowBCM2835.h
// -----------------------------------------------------------------------------

#ifndef __LOWBCM2835_H__
#define __LOWBCM2835_H__

#include "LowDataCallback.h"
#include "LowLoopCallback.h"

#include<stdint.h>


struct low_main_t;

enum
{

    LOWBCM2835_PHASE_INIT,
    LOWBCM2835_PHASE_CLOSE,
    LOWBCM2835_PHASE_SETDEBUG,
    LOWBCM2835_PHASE_FSEL,
    LOWBCM2835_PHASE_SETOUTPIN,
    LOWBCM2835_PHASE_CLEAROUTPIN,
    LOWBCM2835_PHASE_READPIN
};

class LowBCM2835
    : public LowDataCallback
    , public LowLoopCallback
{
  public:
    LowBCM2835(low_main_t *low);
    virtual ~LowBCM2835();

    void Init(int callIndex);
    void Close(int callIndex);
    void SetDebug(uint8_t debug, int callIndex);
    void Fsel(uint8_t pin, uint8_t mode, int callIndex);
    void SetOutPin(uint8_t pin, int callIndex);
    void ClearOutPin(uint8_t pin, int callIndex);
    void ReadPin(uint8_t pin, int callIndex);
    
  protected:
    virtual bool OnData();
    virtual bool OnLoop();

  private:
    low_main_t *mLow;
    uint8_t mPin;
    uint8_t mMode;
    uint8_t mDebug;


    int mCallID;
    int mPhase, mError;
};

#endif /* __LOWFSMISC_H__ */
