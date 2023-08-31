#ifndef __SparkFun_STHS34PF80_Library_H__
#define __SparkFun_STHS34PF80_Library_H__

#include "sths34pf80_api/sths34pf80_reg.h"
#include "sfe_bus.h"

class STHS34PF80
{
    public:
        bool begin();
        bool isConnected();
        int8_t getError();
        
        sths34pf80_tmos_func_status_t getStatus();
        int16_t getPresenceValue();
        int16_t getMotionValue();
        bool getDataReady();


        /* Get functions */

        // bool getDataReady(); // Returns true (data is ready) or false (data is not ready)
        // int32_t getPresenceThreshold(); // Returns the presence threshold value read (in __)
        // int32_t getMotionThreshold();
        // int32_t getTAmbientShockThreshold();
        // int32_t getMotionHysteresis();
        // int32_t getPresenceHysteresis();
        // int32_t getTAmbientShockHysteresis();
        // int32_t getINTORpulsed();
        // int32_t getTobjectAlgoCompensation();
        // int32_t getPresenceAbsValue();


        /* Set functions */

        //bool setData(uint32_t data);

        // bool setDataReady(uint8_t ready);
        // bool setPresenceThreshold(uint16_t threshold);
        // bool setMotionThreshold(uint8_t threshold);
        // bool setTAmbientShockThreshold(uint8_t threshold);
        

    protected: 
        stmdev_ctx_t sensor;
};


#endif