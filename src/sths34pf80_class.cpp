#include "sths34pf80_class.h"

/// @brief This function begins the examples/communication
/// @return Returns false if true
bool STHS34PF80::begin()
{
    if(isConnected() == false)
    {
        return true;
    }

    sths34pf80_boot_set(&sensor, 1);
    
    // delay 2.50ms to allow for sensor reset (allows for no power cycling)
    sensor.mdelay(3);


    // Set averages (AVG_TAMB = 8, AVG_TMOS = 32)
    sths34pf80_avg_tobject_num_set(&sensor, STHS34PF80_AVG_TMOS_32);
    sths34pf80_avg_tambient_num_set(&sensor, STHS34PF80_AVG_T_8);

    // Block data rate update (BDU)
    sths34pf80_block_data_update_set(&sensor, 1);

    // Set the data rate (ODR)
    sths34pf80_tmos_odr_set(&sensor, STHS34PF80_TMOS_ODR_AT_30Hz);

    // NO INT (polling mode)


    return false;
}

/// @brief This function determines whether or not the device
///  is connected to the STHS34PF80. This tests if the device ID
///  matches what is expected or not.
/// @return Error code (false is success, true is failure)
bool STHS34PF80::isConnected()
{
    uint8_t devId = 0;
    int32_t err = sths34pf80_device_id_get(&sensor, &devId);
    if(err)
        return false;
    return devId == STHS34PF80_ID;
}

/// @brief Checks to see if the data ready flag is high
/// @return Data ready code (0 for not ready, 1 for ready)
bool STHS34PF80::getDataReady()
{
    sths34pf80_tmos_drdy_status_t dataReady;

    sths34pf80_tmos_drdy_status_get(&sensor, &dataReady);

    return dataReady.drdy;
}

/// @brief This function checks the status of the of the device if 
///  there is data ready to be read. This value has 3 flags associated
///  with it - ambient temperature shock, motion, and presence. 
/// @return Flag data status for the 3 different outputs.
sths34pf80_tmos_func_status_t STHS34PF80::getStatus()
{
    sths34pf80_tmos_func_status_t statusVal; // Value to hold presence value
    //int32_t retVal; // Value to indicate if success or not

    sths34pf80_tmos_func_status_get(&sensor, &statusVal);

    // if( retVal != 0 )
    // {
    //     return -1;
    // }

    return statusVal;
}

/// @brief This function returns the presence value
///   TPRESENCE_L (0x3A) and T_PRESENCE_H (0x3B)
/// @return Presence value of the device 
int16_t STHS34PF80::getPresenceValue()
{
    // Set hysteresis 
    int16_t presenceVal;
    sths34pf80_tpresence_raw_get(&sensor, &presenceVal);

    return presenceVal;
}

/// @brief This function returns the motion value
/// @return Motion value of the device 
int16_t STHS34PF80::getMotionValue()
{
    int16_t motionVal;
    sths34pf80_tmotion_raw_get(&sensor, &motionVal);

    return motionVal;
}

// bool STHS34PF80::setData(uint32_t data)
// {
//     return false; // success
// }

// /// @brief This function checks what errors are present with 
// ///  the device once called upon
// /// @return Error code ()
// int8_t STHS34PF80::getError()
// {

// }

