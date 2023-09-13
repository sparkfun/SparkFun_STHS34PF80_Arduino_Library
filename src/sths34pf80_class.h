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
        uint8_t getODR();
        
        sths34pf80_tmos_func_status_t getStatus(); // Returns the status of the device
        int16_t getPresenceValue(); // Returns the presence value detected of the device
        int16_t getMotionValue(); // Returns the motion value 
        bool getDataReady(); // Returns if the data is ready to be read or not

        int16_t getTemperatureData(); // Returns the raw temperature value read by the device
        //uint8_t getODR();



        // -------------------- Functions from sths34pf80_reg.c files --------------------
        int32_t getDeviceID(); // Returns the ID of the STHS34PF80 

        int8_t getAverageTObjectNumber(); // Returns the number of averages
        int8_t setAverageTObjectNumber(sths34pf80_avg_tobject_num_t num); // Sets the # of averages for object temperature

        int8_t getAverageTAmbientNumber(); // Returns the # of averages for ambient temperature
        int8_t setAverageTAmbientNumber(sths34pf80_avg_tobject_num_t num); // Sets the # of averages for ambient temperature

        int8_t getGainMode(); // Returns the gain mode of the temperature range
        int8_t setGainMode(sths34pf80_gain_mode_t mode); // Sets the gain mode of the temperature range

        uint16_t getTmosSensitivity(); // Returns the senstivity of data of the TMOS interface data
        int8_t setTmosSensitivity(uint16_t val); // Sets the sensitivity data for the TMOS interface status

        int8_t getTmosODR(); // Returns the block data update feature for output registers
        int8_t setTmosODR(sths34pf80_tmos_odr_t val); // Sets the block data update feature

        int8_t getBlockDataUpdate(); // Enables the block data update feature 
        int8_t setBlockDataUpdate(uint8_t val); // Sets the block data

        int8_t getTmosOneShot(); // Returns the state of the trigger one-shot acquisition
        int8_t setTmosOneShot(sths34pf80_tmos_one_shot_t val); // Sets the trigger one-shot acquisiton

        int8_t getMemoryBank(); // Returns the state of the access to the registers for embedded functions
        int8_t setMemoryBank(sths34pf80_mem_bank_t val); // Sets the state of access to the registers for embedded functions

        uint8_t getBootOTP(); // Returns the reboot OTP memory content value
        int8_t setBootOTP(uint8_t val); // Self-clears the boot OTP memory content

        sths34pf80_tmos_func_status_t getTmosFunctionStatus(); // Returns the struct for using flags to get the ambient temp, motion, and presence flags

        int16_t getTObjectRawValue(); // Returns the raw value of the TObject Regsiters
        int16_t getTAmbientRawValue(); // Returns the raw value of the TAmbient Registers
        int16_t getTObjectCompensatedRawValue(); // Returns the raw value of the TObject Compensated Registers
        int16_t getTPresenceRawValue(); // Returns the raw value of the TPresence Registers
        int16_t getTMotionRawValue(); // Returns the raw value of the TMotion Registers
        int16_t TAmbientShockRawValue(); // Returns the raw value of the TAmbient Shock Registers


        // Finish .cpp files
        int8_t getLpfMotionBandwidth(); // Returns the low pass filter configuration for motion
        int8_t setLpfMotionBandwidth(sths34pf80_lpf_bandwidth_t val); // Sets the low-pass filter configuration for motion
        
        int8_t getLpfPresenceMotionBandwidth(); // Returns the low pass filter configuration for motion and presence
        int8_t setLpfPresenceMotionBandwidth(sths34pf80_lpf_bandwidth_t val); // Sets the low-pass filter configuration for motion and presence

        int8_t getLpfAmbientTempBandwidth(); // Returns the low pass filter config for ambient temperature shock detection
        int8_t setLpfAmbientTempBandwidth(sths34pf80_lpf_bandwidth_t val); // Sets the low-pass filter configuration for ambient temperature shock detection

        int8_t getLpfPresenceBandwidth(); // Returns the low pass filter config for the presence bandwidth
        int8_t setLpfPresenceBandwidth(sths34pf80_lpf_bandwidth_t val); //  // Sets the low-pass filter configuration for presence detection

        int8_t getTmosRouteInterrupt(); // Returns the Interrupts to be routed
        int8_t setTmosRouteInterrupt(sths34pf80_tmos_route_int_t val); // Sets the Interrutps to be routed

        int8_t getTmosInterruptOR(); // Returns the Interrupts Output type
        int8_t setTmosInterruptOR(sths34pf80_tmos_int_or_t val); // Sets the interrupts output type

/*
        int8_t getInterruptMode(); // Returns the interrupt mode currently set on the device
        int8_t setInterruptMode(sths34pf80_int_mode_t val);  // Sets the interrupt mode of the device 
*/

        int8_t getDataReadyMode(); // Returns the data ready mode currently set for device
        int8_t setDataReadyMode(sths34pf80_drdy_mode_t val); // Sets the data ready mode of the device (0 or 1) 
        
        uint16_t getPresenceThreshold(); // Returns the presence threshold value read
        int8_t setPresenceThreshold(uint16_t threshold); // Sets the presence threshold value of the device

        uint16_t getMotionThreshold(); // Returns the motion threshold of the device
        int8_t setMotionThreshold(uint8_t threshold); // Sets the motion threshold value of the device

        uint16_t getTAmbientShockThreshold(); // Returns the ambient temperature threshold of the device
        int8_t setTAmbientShockThreshold(uint16_t threshold); // Sets the ambient temperature threshold of the device

        uint8_t getMotionHysteresis(); // Returns the motion hystersis of the device
        int8_t setMotionHysteresis(uint8_t hysteresis); // Sets the motion hystersis of the device

        uint8_t getPresenceHysteresis(); // Returns the presence hystersis of the device
        int8_t setPresenceHysteresis(uint8_t hysteresis); // Sets the presence hystersis of the device

        uint8_t getTAmbientShockHysteresis(); // Returns the ambient temperature shock hystersis of the device 
        int8_t setTAmbientShockHysteresis(uint16_t hysteresis); // Sets the ambient temperature shock hystersis of the device 

        uint8_t getInterruptPulsed(); // Returns the result of the algorithms if they are pulsed or not
        int8_t setInterruptPulsed(uint8_t pulse); // Sets the device's result of the algorithms to pulsed or not

        uint8_t getTobjectAlgoCompensation(); // Returns if the device is using the algorithm for compensating temp variations
        int8_t setTobjectAlgoCompensation(uint8_t comp); // Sets the devices Tobject compensation 

        uint8_t getPresenceAbsValue(); // Returns if there is absolute value added in the presence detection algorithm
        int8_t setPresenceAbsValue(uint8_t val); // Sets the absolute value added in the presence detection algorithm

        int8_t resetAlgo(); // Resets the algo structure of the device 

    protected: 
        stmdev_ctx_t sensor;

        int8_t writeFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len); // Write interface definition
        int32_t readFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len); // Read interface defintions
};


#endif