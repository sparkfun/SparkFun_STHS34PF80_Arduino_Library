#ifndef __SparkFun_STHS34PF80_Library_H__
#define __SparkFun_STHS34PF80_Library_H__

#include "sths34pf80_api/sths34pf80_reg.h"
#include "sfe_bus.h"

class STHS34PF80
{
    public:
        int32_t begin(); // Resets the device and sets the values needed for sensor use
        int32_t isConnected(); // Determines connection to device
        bool getDataReady(); // Returns if the data is ready to be read or not
        int32_t getStatus(sths34pf80_tmos_func_status_t *statusVal); // Returns the status of the device
        int32_t reset(); // Set the boot bit, wait 3ms (as per the datasheet), then resets the algorithm

        int32_t getPresenceValue(int16_t *presenceVal); // Returns the presence value detected of the device
        int32_t getMotionValue(int16_t *motionVal); // Returns the motion value 
        int32_t getTemperatureData(float *tempVal); // Returns the raw temperature value read by the device

        int32_t getDeviceID(uint8_t *devId); // Returns the ID of the STHS34PF80 

        int32_t getAverageTObjectNumber(sths34pf80_avg_tobject_num_t *val); // Returns the number of averages
        int32_t setAverageTObjectNumber(sths34pf80_avg_tobject_num_t num); // Sets the # of averages for object temperature

        int32_t getAverageTAmbientNumber(sths34pf80_avg_tambient_num_t *val); // Returns the # of averages for ambient temperature
        int32_t setAverageTAmbientNumber(sths34pf80_avg_tambient_num_t num); // Sets the # of averages for ambient temperature

        int32_t getGainMode(sths34pf80_gain_mode_t *gain); // Returns the gain mode of the temperature range
        int32_t setGainMode(sths34pf80_gain_mode_t mode); // Sets the gain mode of the temperature range

        int32_t getTmosSensitivity(float *sense); // Returns the senstivity of data of the TMOS interface data
        int32_t setTmosSensitivity(float val); // Sets the sensitivity data for the TMOS interface status

        int32_t getTmosODR(sths34pf80_tmos_odr_t *val); // Returns the block data update feature for output registers
        int32_t setTmosODR(sths34pf80_tmos_odr_t val); // Sets the block data update feature

        int32_t getBlockDataUpdate(uint8_t *val); // Enables the block data update feature 
        int32_t setBlockDataUpdate(uint8_t val); // Sets the block data

        int32_t getTmosOneShot(sths34pf80_tmos_one_shot_t *val); // Returns the state of the trigger one-shot acquisition
        int32_t setTmosOneShot(sths34pf80_tmos_one_shot_t val); // Sets the trigger one-shot acquisiton

        int32_t getMemoryBank(sths34pf80_mem_bank_t *val); // Returns the state of the access to the registers for embedded functions
        int32_t setMemoryBank(sths34pf80_mem_bank_t val); // Sets the state of access to the registers for embedded functions

        int32_t getBootOTP(uint8_t *val); // Returns the reboot OTP memory content value
        int32_t setBootOTP(uint8_t val); // Self-clears the boot OTP memory content

        int32_t getTmosFunctionStatus(sths34pf80_tmos_func_status_t *val); // Returns the struct for using flags to get the ambient temp, motion, and presence flags

        int32_t getTObjectRawValue(int16_t *val); // Returns the raw value of the TObject Regsiters
        int32_t getTAmbientRawValue(int16_t *val); // Returns the raw value of the TAmbient Registers
        int32_t getTObjectCompensatedRawValue(int16_t *val); // Returns the raw value of the TObject Compensated Registers
        int32_t getTAmbientShockRawValue(int16_t *val); // Returns the raw value of the TAmbient Shock Registers

        int32_t getLpfMotionBandwidth(sths34pf80_lpf_bandwidth_t *val); // Returns the low pass filter configuration for motion
        int32_t setLpfMotionBandwidth(sths34pf80_lpf_bandwidth_t val); // Sets the low-pass filter configuration for motion
        
        int32_t getLpfPresenceMotionBandwidth(sths34pf80_lpf_bandwidth_t *val); // Returns the low pass filter configuration for motion and presence
        int32_t setLpfPresenceMotionBandwidth(sths34pf80_lpf_bandwidth_t val); // Sets the low-pass filter configuration for motion and presence

        int32_t getLpfAmbientTempBandwidth(sths34pf80_lpf_bandwidth_t *val); // Returns the low pass filter config for ambient temperature shock detection
        int32_t setLpfAmbientTempBandwidth(sths34pf80_lpf_bandwidth_t val); // Sets the low-pass filter configuration for ambient temperature shock detection

        int32_t getLpfPresenceBandwidth(sths34pf80_lpf_bandwidth_t *val); // Returns the low pass filter config for the presence bandwidth
        int32_t setLpfPresenceBandwidth(sths34pf80_lpf_bandwidth_t val); //  // Sets the low-pass filter configuration for presence detection

        int32_t getTmosRouteInterrupt(sths34pf80_tmos_route_int_t *val); // Returns the Interrupts to be routed
        int32_t setTmosRouteInterrupt(sths34pf80_tmos_route_int_t val); // Sets the Interrutps to be routed

        int32_t getTmosInterruptOR(sths34pf80_tmos_int_or_t *val); // Returns the Interrupts Output type
        int32_t setTmosInterruptOR(sths34pf80_tmos_int_or_t val); // Sets the interrupts output type

        int32_t getInterruptMode(sths34pf80_int_mode_t *val); // Returns the interrupt mode currently set on the device
        int32_t setInterruptMode(sths34pf80_int_mode_t val);  // Sets the interrupt mode of the device 

        int32_t getDataReadyMode(sths34pf80_drdy_mode_t *val); // Returns the data ready mode currently set for device
        int32_t setDataReadyMode(sths34pf80_drdy_mode_t val); // Sets the data ready mode of the device (0 or 1) 
        
        int32_t getPresenceThreshold(uint16_t *val); // Returns the presence threshold value read
        int32_t setPresenceThreshold(uint16_t threshold); // Sets the presence threshold value of the device

        int32_t getMotionThreshold(uint16_t *val); // Returns the motion threshold of the device
        int32_t setMotionThreshold(uint8_t threshold); // Sets the motion threshold value of the device

        int32_t getTAmbientShockThreshold(uint16_t *val); // Returns the ambient temperature threshold of the device
        int32_t setTAmbientShockThreshold(uint16_t threshold); // Sets the ambient temperature threshold of the device

        int32_t getMotionHysteresis(uint8_t *val); // Returns the motion hysterssis of the device
        int32_t setMotionHysteresis(uint8_t hysteresis); // Sets the motion hystersis of the device

        int32_t getPresenceHysteresis(uint8_t *val); // Returns the presence hystersis of the device
        int32_t setPresenceHysteresis(uint8_t hysteresis); // Sets the presence hystersis of the device

        int32_t getTAmbientShockHysteresis(uint8_t *val); // Returns the ambient temperature shock hystersis of the device 
        int32_t setTAmbientShockHysteresis(uint16_t hysteresis); // Sets the ambient temperature shock hystersis of the device 

        int32_t getInterruptPulsed(uint8_t *val); // Returns the result of the algorithms if they are pulsed or not
        int32_t setInterruptPulsed(uint8_t pulse); // Sets the device's result of the algorithms to pulsed or not

        int32_t getTobjectAlgoCompensation(uint8_t *val); // Returns if the device is using the algorithm for compensating temp variations
        int32_t setTobjectAlgoCompensation(uint8_t comp); // Sets the devices Tobject compensation 

        int32_t getPresenceAbsValue(uint8_t *val); // Returns if there is absolute value added in the presence detection algorithm
        int32_t setPresenceAbsValue(uint8_t val); // Sets the absolute value added in the presence detection algorithm

        int32_t resetAlgo(); // Resets the algo structure of the device 

        int32_t writeFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len); // Write interface definition
        int32_t readFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len); // Read interface defintions

    protected: 
        stmdev_ctx_t sensor;

};


#endif