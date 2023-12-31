#include "sths34pf80_class.h"

#define SPI_READ 0x80

/// @brief This function begins the examples/communication and sets
///  the required values to the control registers in order for sensor
///  use.
/// @return Error code (0 no error)
int32_t STHS34PF80::begin()
{
    if (isConnected() != 0)
    {
        return -1;
    }

    reset(); // Set boot bit to 1, delay, then reset algorithm

    // Set temperature object number set average (AVG_TMOS = 32)
    int32_t avgErr = setAverageTObjectNumber(STHS34PF80_AVG_TMOS_32);

    // Set ambient temperature average (AVG_TAMB = 8)
    int32_t tAmbErr = setAverageTAmbientNumber(STHS34PF80_AVG_T_8);

    // Set block data rate update to true
    int32_t blockErr = setBlockDataUpdate(true);

    // Set the data rate (ODR) to 1Hz
    int32_t odrErr = setTmosODR(STHS34PF80_TMOS_ODR_AT_1Hz);

    if (avgErr != 0)
    {
        return avgErr;
    }
    else if (tAmbErr != 0)
    {
        return tAmbErr;
    }
    else if (blockErr != 0)
    {
        return blockErr;
    }
    else if (odrErr != 0)
    {
        return odrErr;
    }

    // If no errors, return 0
    return 0;
}

/// @brief This function determines whether or not the device
///  is connected to the STHS34PF80. This tests if the device ID
///  matches what is expected or not.
/// @return Error code (false is success, true is failure)
int32_t STHS34PF80::isConnected()
{
    uint8_t devId = 0;
    int32_t err = sths34pf80_device_id_get(&sensor, &devId);

    if (devId != STHS34PF80_ID)
    {
        return -1;
    }
    return err; 
}

/// @brief Checks to see if the data ready flag is high
/// @return Data ready code (0 for not ready, 1 for ready)
int32_t STHS34PF80::getDataReady(sths34pf80_tmos_drdy_status_t *drdy)
{
    return sths34pf80_tmos_drdy_status_get(&sensor, drdy);
}

/// @brief This function checks the status of the of the device if
///  there is data ready to be read. This value has 3 flags associated
///  with it - ambient temperature shock, motion, and presence.
/// @return Flag data status for the 3 different outputs.
int32_t STHS34PF80::getStatus(sths34pf80_tmos_func_status_t *statusVal)
{
    return sths34pf80_tmos_func_status_get(&sensor, statusVal);
}

/// @brief This function resets the full device
/// @return Error code (0 no error)
int32_t STHS34PF80::reset()
{
    // Set boot bit to 1 in CTRL2 register
    int32_t otpErr = setBootOTP(true);

    // delay 2.50ms to allow for sensor reset (allows for no power cycling)
    sensor.mdelay(3);

    // Reset algorithm for all register values (default values)
    int32_t resetErr = resetAlgo();

    if (otpErr != 0)
    {
        return otpErr;
    }
    else if (resetErr != 0)
    {
        return resetErr;
    }
    else
    {
        return 0;
    }
}

/// @brief This function returns the presence value (units: cm^-1)
///   TPRESENCE_L (0x3A) and T_PRESENCE_H (0x3B)
/// @param presenceVal Presence value of the device
/// @return Error code (0 no error)
int32_t STHS34PF80::getPresenceValue(int16_t *presenceVal)
{
    return sths34pf80_tpresence_raw_get(&sensor, presenceVal);
}

/// @brief This function returns the motion value
/// @param motionVal Motion value of the device
/// @return Error code (0 no error)
int32_t STHS34PF80::getMotionValue(int16_t *motionVal)
{
    return sths34pf80_tmotion_raw_get(&sensor, motionVal);
}

/// @brief This function returns the temeparture data in degrees C
/// @param tempVal Value to fill with information
/// @return Error code (0 no error)
int32_t STHS34PF80::getTemperatureData(float *tempVal)
{
    int16_t tempValFill = 0;

    // As seen on page 5 of the datasheet - object temperature sensitivity
    int16_t sensitivity = 2000;

    int32_t retVal = sths34pf80_tobject_raw_get(&sensor, &tempValFill);

    // Divide the raw value by the sensitivity
    *tempVal = (float)tempValFill / sensitivity;

    return retVal;
}

/// @brief Returns the device ID of the STHS34PF80.
///   sths34pf80_device_id_get
/// @param devID Device ID to return
/// @return Error code (0 no error)
int32_t STHS34PF80::getDeviceID(uint8_t *devId)
{
    return sths34pf80_device_id_get(&sensor, devId);
}

/// @brief Returns the number of averages for the object temperature
///   sths34pf80_avg_tobject_num_get
/// @param val TObject number to write to register
/// @return Error code (0 no error)
int32_t STHS34PF80::getAverageTObjectNumber(sths34pf80_avg_tobject_num_t *val)
{
    return sths34pf80_avg_tobject_num_get(&sensor, val);
}

/// @brief Sets the number of averages for the object temperature
/// @param num Number of averages; Must be between 0-7
/// @return Error code (0 no error)
int32_t STHS34PF80::setAverageTObjectNumber(sths34pf80_avg_tobject_num_t num)
{
    return sths34pf80_avg_tobject_num_set(&sensor, num);
}

/// @brief Returns the number of averages for the ambient temperature
/// @param val TAmbient Average to write to regsiter
/// @return Error code (0 no error)
int32_t STHS34PF80::getAverageTAmbientNumber(sths34pf80_avg_tambient_num_t *val)
{
    return sths34pf80_avg_tambient_num_get(&sensor, val);
}

/// @brief Sets the number of averages for the ambient temperature
/// @param num TAmbient number to send to device
///   STHS34PF80_AVG_T_8 = 0x0
///   STHS34PF80_AVG_T_4 = 0x1
///   STHS34PF80_AVG_T_2 = 0x2
///   STHS34PF80_AVG_T_1 = 0x3
/// @return Error code (0 no error)
int32_t STHS34PF80::setAverageTAmbientNumber(sths34pf80_avg_tambient_num_t num)
{
    return sths34pf80_avg_tambient_num_set(&sensor, num);
}

/// @brief Returns the number of averages selected for ambient temperature
/// @param gain Gain to write to device
/// @return Error code (0 no error)
int32_t STHS34PF80::getGainMode(sths34pf80_gain_mode_t *gain)
{
    return sths34pf80_gain_mode_get(&sensor, gain);
}

/// @brief Sets the gain mode of the device. This enables the device
///  to cover a wide operating temperature range for applications
///  that might be thermally heated inside of the application.
///  STHS34PF80_GAIN_WIDE_MODE     = 0x0
///  STHS34PF80_GAIN_DEFAULT_MODE  = 0x1
/// @param gain Gain to write to device
/// @return Error code (0 no error)
int32_t STHS34PF80::setGainMode(sths34pf80_gain_mode_t gain)
{
    return sths34pf80_gain_mode_set(&sensor, gain);
}

/// @brief Returns the sensitivity value in the embedded linear
///  algorithm for compensating ambient temperature variations in
///  the object temperature.
///   0x0 - 0xFF
/// @param sense Value to set the sensitivity
/// @return Error code (0 no error)
int32_t STHS34PF80::getTmosSensitivity(float *sense)
{
    uint16_t senseFill = 0;
    int32_t err = sths34pf80_tmos_sensitivity_get(&sensor, &senseFill);

    uint16_t res1 = 2048;
    float res2 = 16;

    *sense = (float)(senseFill - res1) / res2;
    return err;
}

/// @brief Sets the sensitivity value in embedded linear
///  algorithm for compensating ambient temperature variations in
///  the object temperature.
///  0x0 - 0xFF
/// @param val Sensitivity value to be converted to send to regsiter
/// @return Error code (0 no error)
int32_t STHS34PF80::setTmosSensitivity(float val)
{
    uint16_t res1 = 2048;
    uint16_t res2 = 16;

    val = (val * res2) + res1;

    uint16_t valReg = val;

    return sths34pf80_tmos_sensitivity_set(&sensor, &valReg);
}

/// @brief This function returns the output data rate.
///  0x0 - 0x8
///  STHS34PF80_TMOS_ODR_OFF
///  STHS34PF80_TMOS_ODR_AT_0Hz25
///  STHS34PF80_TMOS_ODR_AT_0Hz50
///  STHS34PF80_TMOS_ODR_AT_1Hz
///  STHS34PF80_TMOS_ODR_AT_2Hz
///  STHS34PF80_TMOS_ODR_AT_4Hz
///  STHS34PF80_TMOS_ODR_AT_8Hz
///  STHS34PF80_TMOS_ODR_AT_15Hz
///  STHS34PF80_TMOS_ODR_AT_30Hz
/// @param val Value to set the ODR rate
/// @return Error code (0 no error)
int32_t STHS34PF80::getTmosODR(sths34pf80_tmos_odr_t *val)
{
    return sths34pf80_tmos_odr_get(&sensor, val);
}

/// @brief Sets the output data rate
/// @param val 0x0 - 0x8
///  STHS34PF80_TMOS_ODR_OFF
///  STHS34PF80_TMOS_ODR_AT_0Hz25
///  STHS34PF80_TMOS_ODR_AT_0Hz50
///  STHS34PF80_TMOS_ODR_AT_1Hz
///  STHS34PF80_TMOS_ODR_AT_2Hz
///  STHS34PF80_TMOS_ODR_AT_4Hz
///  STHS34PF80_TMOS_ODR_AT_8Hz
///  STHS34PF80_TMOS_ODR_AT_15Hz
///  STHS34PF80_TMOS_ODR_AT_30Hz
/// @return Error code (0 no error)
int32_t STHS34PF80::setTmosODR(sths34pf80_tmos_odr_t val)
{
    return sths34pf80_tmos_odr_set(&sensor, val);
}

/// @brief This function enables the block data update feature
///  for output registers TOBJECT (26h - 27h) and TAMBIENT (28h - 29h).
/// @param val Block data update bit (0 disabled, 1 enabled), -1 for error
/// @return Error code (0 no error)
int32_t STHS34PF80::getBlockDataUpdate(bool *val)
{
    return sths34pf80_block_data_update_get(&sensor, (uint8_t*)val);
}

/// @brief This function sets the block data update feature
///  for output registeres TOBJECT (26h - 27h) and TAMBIENT (28h - 29h).
///  Block data update bit (0 disabled, 1 enabled)
/// @param val Value to set the block data update bit
/// @return Error code (0 no error)
int32_t STHS34PF80::setBlockDataUpdate(bool val)
{
    return sths34pf80_block_data_update_set(&sensor, val);
}

/// @brief This function returns the status of the trigger one-shot
///  acquisition. Default value: 0
///   STHS34PF80_TMOS_IDLE_MODE = 0x0
///   STHS34PF80_TMOS_ONE_SHOT = 0x1
/// @param val 0 for idle, 1 for new data set acquired, -1 for error
/// @return Error code (0 no error)
int32_t STHS34PF80::getTmosOneShot(sths34pf80_tmos_one_shot_t *val)
{
    return sths34pf80_tmos_one_shot_get(&sensor, val);
}

/// @brief This function returns the status of the trigger one-shot
///  acquistion. It is self-clearing upon completion (1)
/// @param val Value to set to register
/// @return Error code (0 no error)
int32_t STHS34PF80::setTmosOneShot(sths34pf80_tmos_one_shot_t val)
{
    return sths34pf80_tmos_one_shot_set(&sensor, val);
}

/// @brief This function enables access to the registers for embedded
///  functions. Default value: 0
///   STHS34PF80_MAIN_MEM_BANK = 0x0
///   STHS34PF80_EMBED_FUNC_MEM_BANK = 0x1
/// @param val Memory bank enabled for embedded or main fucntions
/// @return Error code (0 no error)
int32_t STHS34PF80::getMemoryBank(sths34pf80_mem_bank_t *val)
{
    return sths34pf80_mem_bank_get(&sensor, val);
}

/// @brief This function enables access to the registers for embedded
///  functions. Default value: 0
///   STHS34PF80_MAIN_MEM_BANK = 0x0
///   STHS34PF80_EMBED_FUNC_MEM_BANK = 0x1
/// @param val Value to enable access to the register
/// @return Error code (0 no error)
int32_t STHS34PF80::setMemoryBank(sths34pf80_mem_bank_t val)
{
    return sths34pf80_mem_bank_set(&sensor, val);
}

/// @brief This function creates a global reset of the device -
///  Reboot OTP memory content. Self-clearing upon completion
/// @param val Value to fill for boot OTP
/// @return Error code (0 no error)
int32_t STHS34PF80::getBootOTP(uint8_t *val)
{
    return sths34pf80_boot_get(&sensor, val);
}

/// @brief This function creates a global reset of the device -
///  Reboot OTP memory content. Self-clearing upon completion
/// @param val Value to set the Boot OTP
/// @return Error code (0 no error)
int32_t STHS34PF80::setBootOTP(uint8_t val)
{
    return sths34pf80_boot_set(&sensor, val);
}

/// @brief This function returns the TMOS function status. This holds
///  information for the presence deteciton , motion detection, and
///  ambient shock detection flags. The flags will be raised when
///  there is detection in any of those fields.
/// @param val Fills with the function status value
/// @return Error code (0 no error)
int32_t STHS34PF80::getTmosFunctionStatus(sths34pf80_tmos_func_status_t *val)
{
    return sths34pf80_tmos_func_status_get(&sensor, val);
}

/// @brief This function returns the raw output value that represents
///  the amount of infrared radiation emitted from the objects inside
///  the field of view. It is composed of TOBJECT_H and TOBJECT_L (0x27
///  and 0x26). The value is expressed as 2's complement
/// @param val Raw value from the TObject registers
/// @return Error code (0 no error)
int32_t STHS34PF80::getTObjectRawValue(int16_t *val)
{
    return sths34pf80_tobject_raw_get(&sensor, val);
}

/// @brief This function returns the raw output value for the value that
///  represents the temperature of the environment in thermal coupling
///  with the sensor. It is composed of TAMBIENT_H and TAMBIENT_L (0x28
///  and 0x29). The value is expressed as 2's complement.
///  Sensitivity = 100 LSB/°C
/// @param val Raw value from TAmbient registers
/// @return Error code (0 no error)
int32_t STHS34PF80::getTAmbientRawValue(int16_t *val)
{
    return sths34pf80_tambient_raw_get(&sensor, val);
}

/// @brief This function returns the raw output value for the data that
///  represents the amount of infrared radiation emitted from the objects
///  inside the field of view compensated through the embedded algorithm
///  for compensating ambient temperature varations. The output data is
///  composed of TOBJ_COMP_H and TOBJ_COMP_L (0x39 and 0x38). The value
///  is expressed as 2's complement.
/// @param val Raw value from TObj_Comp registers
/// @return Error code (0 no error)
int32_t STHS34PF80::getTObjectCompensatedRawValue(int16_t *val)
{
    return sths34pf80_tobj_comp_raw_get(&sensor, val);
}

/// @brief This function returns the raw output value for the data that
///  represents the ambient temperature shock data. It is composed of
///  TAMB_SHOCK_H and TAMB_SHOCK_L (0x3F and 0x3E). The value is
///  expressed as 2's complement
/// @param val Raw value from TAmb_Shock registers
/// @return Error code (0 no error)
int32_t STHS34PF80::getTAmbientShockRawValue(int16_t *val)
{
    return sths34pf80_tamb_shock_raw_get(&sensor, val);
}

/// @brief This function returns the Low Pass Filter configuration
///  for motion detection.
///    STHS34PF80_LPF_ODR_DIV_9   = 0x0
///    STHS34PF80_LPF_ODR_DIV_20  = 0x1
///    STHS34PF80_LPF_ODR_DIV_50  = 0x2
///    STHS34PF80_LPF_ODR_DIV_100 = 0x3
///    STHS34PF80_LPF_ODR_DIV_200 = 0x4
///    STHS34PF80_LPF_ODR_DIV_400 = 0x5
///    STHS34PF80_LPF_ODR_DIV_800 = 0x6
/// @param val Low Pass Filter Motion Bandwidth value
/// @return Error code (0 no error)
int32_t STHS34PF80::getLpfMotionBandwidth(sths34pf80_lpf_bandwidth_t *val)
{
    return sths34pf80_lpf_m_bandwidth_get(&sensor, val);
}

/// @brief This function sets the Low Pass Filter configuration
///  for Motion detection.
///    STHS34PF80_LPF_ODR_DIV_9   = 0x0
///    STHS34PF80_LPF_ODR_DIV_20  = 0x1
///    STHS34PF80_LPF_ODR_DIV_50  = 0x2
///    STHS34PF80_LPF_ODR_DIV_100 = 0x3
///    STHS34PF80_LPF_ODR_DIV_200 = 0x4
///    STHS34PF80_LPF_ODR_DIV_400 = 0x5
///    STHS34PF80_LPF_ODR_DIV_800 = 0x6
/// @param val LPF Motion Bandwidth configuration
/// @return Error code (0 no error)
int32_t STHS34PF80::setLpfMotionBandwidth(sths34pf80_lpf_bandwidth_t val)
{
    return sths34pf80_lpf_m_bandwidth_set(&sensor, val);
}

/// @brief This function returns the Low Pass Filter configuration
///  for presence and motion detection.
///    STHS34PF80_LPF_ODR_DIV_9   = 0x0
///    STHS34PF80_LPF_ODR_DIV_20  = 0x1
///    STHS34PF80_LPF_ODR_DIV_50  = 0x2
///    STHS34PF80_LPF_ODR_DIV_100 = 0x3
///    STHS34PF80_LPF_ODR_DIV_200 = 0x4
///    STHS34PF80_LPF_ODR_DIV_400 = 0x5
///    STHS34PF80_LPF_ODR_DIV_800 = 0x6
/// @param val Value to fill with Low Pass Filter configuration
/// @return Low Pass Filter Motion Bandwidth value, -1 for error
int32_t STHS34PF80::getLpfPresenceMotionBandwidth(sths34pf80_lpf_bandwidth_t *val)
{
    return sths34pf80_lpf_p_m_bandwidth_get(&sensor, val);
}

/// @brief This function sets the Low Pass Filter configuration
///  for Presence and Motion detection.
///    STHS34PF80_LPF_ODR_DIV_9   = 0x0
///    STHS34PF80_LPF_ODR_DIV_20  = 0x1
///    STHS34PF80_LPF_ODR_DIV_50  = 0x2
///    STHS34PF80_LPF_ODR_DIV_100 = 0x3
///    STHS34PF80_LPF_ODR_DIV_200 = 0x4
///    STHS34PF80_LPF_ODR_DIV_400 = 0x5
///    STHS34PF80_LPF_ODR_DIV_800 = 0x6
/// @param val Value to set the LPF configuration
/// @return Error code (0 no error)
int32_t STHS34PF80::setLpfPresenceMotionBandwidth(sths34pf80_lpf_bandwidth_t val)
{
    return sths34pf80_lpf_p_m_bandwidth_set(&sensor, val);
}

/// @brief This function returns the Low Pass Filter configuration
///  for Ambient Temperature Shock detection.
///    STHS34PF80_LPF_ODR_DIV_9   = 0x0
///    STHS34PF80_LPF_ODR_DIV_20  = 0x1
///    STHS34PF80_LPF_ODR_DIV_50  = 0x2
///    STHS34PF80_LPF_ODR_DIV_100 = 0x3
///    STHS34PF80_LPF_ODR_DIV_200 = 0x4
///    STHS34PF80_LPF_ODR_DIV_400 = 0x5
///    STHS34PF80_LPF_ODR_DIV_800 = 0x6
/// @param val Value to fill with the LPF ambient temp shock detection
/// @return Low Pass Filter Ambient Temperature Shock Bandwidth value, -1 for error
int32_t STHS34PF80::getLpfAmbientTempBandwidth(sths34pf80_lpf_bandwidth_t *val)
{
    return sths34pf80_lpf_a_t_bandwidth_get(&sensor, val);
}

/// @brief This function sets the Low Pass Filter configuration
///  for Ambient Temperature Shock detection.
///    STHS34PF80_LPF_ODR_DIV_9   = 0x0
///    STHS34PF80_LPF_ODR_DIV_20  = 0x1
///    STHS34PF80_LPF_ODR_DIV_50  = 0x2
///    STHS34PF80_LPF_ODR_DIV_100 = 0x3
///    STHS34PF80_LPF_ODR_DIV_200 = 0x4
///    STHS34PF80_LPF_ODR_DIV_400 = 0x5
///    STHS34PF80_LPF_ODR_DIV_800 = 0x6
/// @param val Value to set the ambient tempertature shock detection
/// @return Error code (0 no error)
int32_t STHS34PF80::setLpfAmbientTempBandwidth(sths34pf80_lpf_bandwidth_t val)
{
    return sths34pf80_lpf_a_t_bandwidth_set(&sensor, val);
}

/// @brief This function returns the Low Pass Filter configuration
///  for Ambient Temperature Shock detection.
///    STHS34PF80_LPF_ODR_DIV_9   = 0x0
///    STHS34PF80_LPF_ODR_DIV_20  = 0x1
///    STHS34PF80_LPF_ODR_DIV_50  = 0x2
///    STHS34PF80_LPF_ODR_DIV_100 = 0x3
///    STHS34PF80_LPF_ODR_DIV_200 = 0x4
///    STHS34PF80_LPF_ODR_DIV_400 = 0x5
///    STHS34PF80_LPF_ODR_DIV_800 = 0x6
/// @param val Value to fill with the LPF presence bandwidth value
/// @return Error code (0 no error)
int32_t STHS34PF80::getLpfPresenceBandwidth(sths34pf80_lpf_bandwidth_t *val)
{
    return sths34pf80_lpf_p_bandwidth_get(&sensor, val);
}

/// @brief This function sets the Low Pass Filter configuration
///  for Presence detection.
///    STHS34PF80_LPF_ODR_DIV_9   = 0x0
///    STHS34PF80_LPF_ODR_DIV_20  = 0x1
///    STHS34PF80_LPF_ODR_DIV_50  = 0x2
///    STHS34PF80_LPF_ODR_DIV_100 = 0x3
///    STHS34PF80_LPF_ODR_DIV_200 = 0x4
///    STHS34PF80_LPF_ODR_DIV_400 = 0x5
///    STHS34PF80_LPF_ODR_DIV_800 = 0x6
/// @param val Value to set the LPF presence bandwidth
/// @return Error code (0 no error)
int32_t STHS34PF80::setLpfPresenceBandwidth(sths34pf80_lpf_bandwidth_t val)
{
    return sths34pf80_lpf_p_bandwidth_set(&sensor, val);
}

/// @brief This function returns the interrupts to be routed.
///  See page 26, Table 10.9 of the datasheet for more information
///   STHS34PF80_TMOS_INT_HIZ = 0x0
///   STHS34PF80_TMOS_INT_DRDY = 0x1
///   STHS34PF80_TMOS_INT_OR = 0x2
/// @param val Value to fill with the types of interrupts to be routed
/// @return Error code (0 no error)
int32_t STHS34PF80::getTmosRouteInterrupt(sths34pf80_tmos_route_int_t *val)
{
    return sths34pf80_tmos_route_int_get(&sensor, val);
}

/// @brief This function sets the interrupts to be routed.
///  See page 26, Table 9 of the datasheet for more information
///   STHS34PF80_TMOS_INT_HIZ = 0x0
///   STHS34PF80_TMOS_INT_DRDY = 0x1
///   STHS34PF80_TMOS_INT_OR = 0x2
/// @param val Value to set the interrupts to be routed
/// @return Error code (0 no error)
int32_t STHS34PF80::setTmosRouteInterrupt(sths34pf80_tmos_route_int_t val)
{
    return sths34pf80_tmos_route_int_set(&sensor, val);
}

/// @brief This function returns the selects interrupts output
///   STHS34PF80_TMOS_INT_NONE = 0x0
///   STHS34PF80_TMOS_INT_TSHOCK = 0x1
///   STHS34PF80_TMOS_INT_MOTION = 0x2
///   STHS34PF80_TMOS_INT_TSHOCK_MOTION = 0x3
///   STHS34PF80_TMOS_INT_PRESENCE = 0x4
///   STHS34PF80_TMOS_INT_TSHOCK_PRESENCE = 0x5
///   STHS34PF80_TMOS_INT_MOTION_PRESENCE = 0x6
///   STHS34PF80_TMOS_INT_ALL = 0x7
/// @param val Value to fill with the select interrupt output type
/// @return Error code (0 no error)
int32_t STHS34PF80::getTmosInterruptOR(sths34pf80_tmos_int_or_t *val)
{
    return sths34pf80_tmos_int_or_get(&sensor, val);
}

/// @brief This function sets the selects interrupts output
///   STHS34PF80_TMOS_INT_NONE = 0x0
///   STHS34PF80_TMOS_INT_TSHOCK = 0x1
///   STHS34PF80_TMOS_INT_MOTION = 0x2
///   STHS34PF80_TMOS_INT_TSHOCK_MOTION = 0x3
///   STHS34PF80_TMOS_INT_PRESENCE = 0x4
///   STHS34PF80_TMOS_INT_TSHOCK_PRESENCE = 0x5
///   STHS34PF80_TMOS_INT_MOTION_PRESENCE = 0x6
///   STHS34PF80_TMOS_INT_ALL = 0x7
/// @param val Value to write to the register. See above defines
///  for what can be used
/// @return Error code (0 no error)
int32_t STHS34PF80::setTmosInterruptOR(sths34pf80_tmos_int_or_t val)
{
    return sths34pf80_tmos_int_or_set(&sensor, val);
}

/// @brief This function returns the interrupt trigger mode
///  for the push-pull/open-drain selection on INT1 and INT2 pins.
///   STHS34PF80_ACTIVE_HIGH = 0x0
///   STHS34PF80_ACTIVE_LOW = 0x1
/// @param val Interrupt mode (H or L), -1 for error
/// @return Error code (0 no error)
int32_t STHS34PF80::getInterruptMode(sths34pf80_int_mode_t *val)
{
    return sths34pf80_int_mode_get(&sensor, val);
}

/// @brief This function sets the interrupt trigger mode
///  for the push-pull/open-drain selection on INT1 and INT2 pins.
///   STHS34PF80_ACTIVE_HIGH = 0x0
///   STHS34PF80_ACTIVE_LOW = 0x1
/// @param val Value the user sets to write to the device (0 or 1)
/// @return Error code (0 no error)
int32_t STHS34PF80::setInterruptMode(sths34pf80_int_mode_t val)
{
    return sths34pf80_int_mode_set(&sensor, val); // Returns the error code
}

/// @brief This function returns the data ready mode to pulsed (0)
///  on the INT pin, or latched (1).
///    STHS34PF80_DRDY_PULSED = 0x0
///    STHS34PF80_DRDY_LATCHED = 0x1
/// @param val Data ready mode (pulsed or latched)
/// @return Error code (0 no error)
int32_t STHS34PF80::getDataReadyMode(sths34pf80_drdy_mode_t *val)
{
    return sths34pf80_drdy_mode_get(&sensor, val);
}

/// @brief This function sets the data ready mode to be pulsed (0)
///  on the INT pin, or latched (1).
///    STHS34PF80_DRDY_PULSED = 0x0
///    STHS34PF80_DRDY_LATCHED = 0x1
/// @param val Value the user sets to write to the device (0 or 1)
/// @return Error code (0 no error)
int32_t STHS34PF80::setDataReadyMode(sths34pf80_drdy_mode_t val)
{
    return sths34pf80_drdy_mode_set(&sensor, val);
}

/// @brief This function returns the presence threshold of the device.
///  Default value is 200 (0x008C)
/// @param val Presence threshold of the device
/// @return Error code (0 for no error)
int32_t STHS34PF80::getPresenceThreshold(uint16_t *val)
{
    return sths34pf80_presence_threshold_get(&sensor, val);
}

/// @brief This function sets the presence threshold for the device.
///  Default value is 200 (0x00C8).
/// @param threshold 15-bit unsigned integer
/// @return Error code (0 for no error)
int32_t STHS34PF80::setPresenceThreshold(uint16_t threshold)
{
    return sths34pf80_presence_threshold_set(&sensor, threshold);
}

/// @brief This function returns the motion threshold of the device.
///  Default value is 200 (0x00C8)
/// @param val Motion threshold
/// @return Error code (0 for no error)
int32_t STHS34PF80::getMotionThreshold(uint16_t *val)
{
    return sths34pf80_motion_threshold_get(&sensor, val);
}

/// @brief This function sets the motion threshold of the device.
///  Default value is 200 (0x00C8).
/// @param threshold 15-bit unsigned integer
/// @return Error code (0 for no error)
int32_t STHS34PF80::setMotionThreshold(uint8_t threshold)
{
    return sths34pf80_motion_threshold_set(&sensor, threshold);
}

/// @brief This function returns the ambient temperature threshold of
///  the device. Default value is 10 (0x000A).
/// @param val Ambient temperature shock threshold
/// @return Error code (0 for no error)
int32_t STHS34PF80::getTAmbientShockThreshold(uint16_t *val)
{
    return sths34pf80_tambient_shock_threshold_get(&sensor, val);
}

/// @brief This function sets the ambient temperature threshold of the
///  device. Default value is 10 (0x000A).
/// @param threshold 15-bit unsigned integer
/// @return Error code (0 for no error)
int32_t STHS34PF80::setTAmbientShockThreshold(uint16_t threshold)
{
    return sths34pf80_tambient_shock_threshold_set(&sensor, threshold);
}

/// @brief This function sets the motion hysteresis of the device.
///  Default value is 0x32.
/// @param val Motion hysteresis
/// @return Error code (0 for no error)
int32_t STHS34PF80::getMotionHysteresis(uint8_t *val)
{
    return sths34pf80_motion_hysteresis_get(&sensor, val);
}

/// @brief This function returns the motion hysteresis of the device.
///  Default value is 0x32.
/// @param hysteresis 8-bit unsigned integer
/// @return Error code (0 for no error)
int32_t STHS34PF80::setMotionHysteresis(uint8_t hysteresis)
{
    return sths34pf80_motion_hysteresis_set(&sensor, hysteresis);
}

/// @brief This function returns the presence hysteresis of the
///  device. Default value is 0x32.
/// @param val Presence hysteresis
/// @return Error code (0 for no error)
int32_t STHS34PF80::getPresenceHysteresis(uint8_t *val)
{
    return sths34pf80_presence_hysteresis_get(&sensor, val);
}

/// @brief This function sets the presence hysteresis of the device.
///  Default value is 0x32.
/// @param hysteresis 8-bit unsigned integer.
/// @return Error code (0 for no error)
int32_t STHS34PF80::setPresenceHysteresis(uint8_t hysteresis)
{
    return sths34pf80_presence_hysteresis_set(&sensor, hysteresis);
}

/// @brief This function returns the ambient temperature shock hysteresis
///  of the device. Default value is 10 (0xA).
/// @param val Ambient temperature shock hysteresis value
/// @return Error code (0 for no error)
int32_t STHS34PF80::getTAmbientShockHysteresis(uint8_t *val)
{
    return sths34pf80_tambient_shock_hysteresis_get(&sensor, val);
}

/// @brief This function sets the ambient temperature shock hysteresis
///  of the device. Default value is 10 (0xA).
/// @param hysteresis 15-bit unsigned integer for temp ambient shock hysteresis
/// @return Error code (0 for no error)
int32_t STHS34PF80::setTAmbientShockHysteresis(uint16_t hysteresis)
{
    return sths34pf80_tambient_shock_hysteresis_set(&sensor, hysteresis);
}

/// @brief This function returns if the flag is latched or pulsed
///  on the INT pin. Default value = 0.
/// @param val Latched (0) or Pulsed (1)
/// @return Error code (0 for no error)
int32_t STHS34PF80::getInterruptPulsed(uint8_t *val)
{
    return sths34pf80_int_or_pulsed_get(&sensor, val);
}

/// @brief This function sets the flag for if the result of the
///  algorithms are pulsed (high for ODR defined) on the INT pin.
///  Default value = 0
/// @param pulse int_pulsed value (0, 1)
/// @return Error code (0 no error)
int32_t STHS34PF80::setInterruptPulsed(uint8_t pulse)
{
    return sths34pf80_int_or_pulsed_set(&sensor, pulse);
}

/// @brief This function returns the Tobject compnesation. This is
///  an embedded linear algorithm for compensating ambient temperature
///  variations in the object temperature. Default value is 0.
/// @param val Disabled (0) or Enabled (1)
/// @return Error code (0 no error)
int32_t STHS34PF80::getTobjectAlgoCompensation(uint8_t *val)
{
    return sths34pf80_tobject_algo_compensation_get(&sensor, val);
}

/// @brief This function sets the Tobject compnesation. This is
///  an embedded linear algorithm for compensating ambient temperature
///  variations in the object temperature. Default value is 0.
/// @param comp Ambient compensation for object temperature (0, 1)
/// @return Error code (0 no error)
int32_t STHS34PF80::setTobjectAlgoCompensation(uint8_t comp)
{
    return sths34pf80_tobject_algo_compensation_set(&sensor, comp);
}

/// @brief This function returns the enable/disable bit for setting
///  the presence absolute value algorithm
/// @param val Absolute value NOT applied (0) or applied (1)
/// @return Error code (0 no error)
int32_t STHS34PF80::getPresenceAbsValue(uint8_t *val)
{
    return sths34pf80_presence_abs_value_get(&sensor, val);
}

/// @brief This function returns the enable/disable bit for setting
///  the presence absolute value algorithm
/// @param val Presence absolute value (0, 1)
/// @return Error code (0 no error)
int32_t STHS34PF80::setPresenceAbsValue(uint8_t val)
{
    return sths34pf80_presence_abs_value_set(&sensor, val);
}

/// @brief This function resets the algorithm whenever parameters
///  are modified. The user is required to call this after modifying
///  any parameters.
/// @return Error code (0 no error)
int32_t STHS34PF80::resetAlgo()
{
    return sths34pf80_algo_reset(&sensor);
}

/// @brief This function writes/sets data to the desired address for the desired
///  number of bytes.
/// @param addr embedded register address
/// @param data embedded register data
/// @param len  embedded register data len
/// @return Interface status (0 for no error, -1 for error)
int32_t STHS34PF80::writeFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len)
{
    return sths34pf80_func_cfg_write(&sensor, addr, data, len);
}

/// @brief This function returns/gets data from the desired address for the chosen
///  number of bytes. Note that this is limited to a 32 bit value for length.
/// @param addr embedded register address
/// @param data embedded register data
/// @param len  embedded register data len
/// @return Interface status (0 for no error, -1 for error)
int32_t STHS34PF80::readFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len)
{
    return sths34pf80_func_cfg_read(&sensor, addr, data, len);
}
