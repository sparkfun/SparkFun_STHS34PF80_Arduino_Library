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

    // Block data rate update
    // sths34pf80_block_data_update_set(&sensor, 1);

    // Set the data rate
    sths34pf80_tmos_odr_set(&sensor, STHS34PF80_TMOS_ODR_AT_1Hz);

    sths34pf80_avg_tobject_num_set(&sensor, STHS34PF80_AVG_TMOS_32);
    sths34pf80_avg_tambient_num_set(&sensor, STHS34PF80_AVG_T_8);

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

bool STHS34PF80::getDataReady()
{
    sths34pf80_tmos_drdy_status_t dataReady;

    sths34pf80_tmos_drdy_status_get(&sensor, &dataReady);

    return dataReady.drdy;
}

// This is an example placeholder - test with and then remove
// This function is current configured to pull in the object's presence
// output data. Expressed as a two's complement (needs int)
// TPRESENCE_L (0x3A) and T_PRESENCE_H (0x3B)
sths34pf80_tmos_func_status_t STHS34PF80::getStatus()
{
    sths34pf80_tmos_func_status_t presenceVal; // Value to hold presence value
    //int32_t retVal; // Value to indicate if success or not

    sths34pf80_tmos_func_status_get(&sensor, &presenceVal);

    // if( retVal != 0 )
    // {
    //     return -1;
    // }

    return presenceVal;
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

