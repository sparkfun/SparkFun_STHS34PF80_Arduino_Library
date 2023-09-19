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
        uint8_t getODR(sths34pf80_tmos_odr_t *odr);
        
        sths34pf80_tmos_func_status_t getStatus(); // Returns the status of the device
        bool getPresenceValue(int16_t *presenceVal); // Returns the presence value detected of the device
        bool getMotionValue(int16_t *motionVal); // Returns the motion value 
        bool getTemperatureData(int16_t *tempVal); // Returns the raw temperature value read by the device
        bool getDataReady(); // Returns if the data is ready to be read or not

        //uint8_t getODR();

        // -------------------- Functions from sths34pf80_reg.c files --------------------
        bool getDeviceID(uint8_t *devId); // Returns the ID of the STHS34PF80 

        bool getAverageTObjectNumber(sths34pf80_avg_tobject_num_t *val); // Returns the number of averages
        bool setAverageTObjectNumber(sths34pf80_avg_tobject_num_t num); // Sets the # of averages for object temperature

        bool getAverageTAmbientNumber(sths34pf80_avg_tambient_num_t *val); // Returns the # of averages for ambient temperature
        bool setAverageTAmbientNumber(sths34pf80_avg_tambient_num_t num); // Sets the # of averages for ambient temperature

        bool getGainMode(sths34pf80_gain_mode_t *gain); // Returns the gain mode of the temperature range
        bool setGainMode(sths34pf80_gain_mode_t mode); // Sets the gain mode of the temperature range

        bool getTmosSensitivity(uint16_t *sense); // Returns the senstivity of data of the TMOS interface data
        bool setTmosSensitivity(uint16_t *val); // Sets the sensitivity data for the TMOS interface status

        bool getTmosODR(sths34pf80_tmos_odr_t *val); // Returns the block data update feature for output registers
        bool setTmosODR(sths34pf80_tmos_odr_t val); // Sets the block data update feature

        bool getBlockDataUpdate(uint8_t *val); // Enables the block data update feature 
        bool setBlockDataUpdate(uint8_t val); // Sets the block data

        bool getTmosOneShot(sths34pf80_tmos_one_shot_t *val); // Returns the state of the trigger one-shot acquisition
        bool setTmosOneShot(sths34pf80_tmos_one_shot_t val); // Sets the trigger one-shot acquisiton

        bool getMemoryBank(sths34pf80_mem_bank_t *val); // Returns the state of the access to the registers for embedded functions
        bool setMemoryBank(sths34pf80_mem_bank_t val); // Sets the state of access to the registers for embedded functions

        bool getBootOTP(uint8_t *val); // Returns the reboot OTP memory content value
        bool setBootOTP(uint8_t val); // Self-clears the boot OTP memory content

        bool getTmosFunctionStatus(sths34pf80_tmos_func_status_t *val); // Returns the struct for using flags to get the ambient temp, motion, and presence flags

        bool getTObjectRawValue(int16_t *val); // Returns the raw value of the TObject Regsiters
        bool getTAmbientRawValue(int16_t *val); // Returns the raw value of the TAmbient Registers
        bool getTObjectCompensatedRawValue(int16_t *val); // Returns the raw value of the TObject Compensated Registers
        bool getTPresenceRawValue(int16_t *val); // Returns the raw value of the TPresence Registers
        bool getTMotionRawValue(int16_t *val); // Returns the raw value of the TMotion Registers
        bool getTAmbientShockRawValue(int16_t *val); // Returns the raw value of the TAmbient Shock Registers

        // Finish .cpp files
        bool getLpfMotionBandwidth(sths34pf80_lpf_bandwidth_t *val); // Returns the low pass filter configuration for motion
        bool setLpfMotionBandwidth(sths34pf80_lpf_bandwidth_t val); // Sets the low-pass filter configuration for motion
        
        bool getLpfPresenceMotionBandwidth(sths34pf80_lpf_bandwidth_t *val); // Returns the low pass filter configuration for motion and presence
        bool setLpfPresenceMotionBandwidth(sths34pf80_lpf_bandwidth_t val); // Sets the low-pass filter configuration for motion and presence

        bool getLpfAmbientTempBandwidth(sths34pf80_lpf_bandwidth_t *val); // Returns the low pass filter config for ambient temperature shock detection
        bool setLpfAmbientTempBandwidth(sths34pf80_lpf_bandwidth_t val); // Sets the low-pass filter configuration for ambient temperature shock detection

        bool getLpfPresenceBandwidth(sths34pf80_lpf_bandwidth_t *val); // Returns the low pass filter config for the presence bandwidth
        bool setLpfPresenceBandwidth(sths34pf80_lpf_bandwidth_t val); //  // Sets the low-pass filter configuration for presence detection

        bool getTmosRouteInterrupt(sths34pf80_tmos_route_int_t *val); // Returns the Interrupts to be routed
        bool setTmosRouteInterrupt(sths34pf80_tmos_route_int_t val); // Sets the Interrutps to be routed

        bool getTmosInterruptOR(sths34pf80_tmos_int_or_t *val); // Returns the Interrupts Output type
        bool setTmosInterruptOR(sths34pf80_tmos_int_or_t val); // Sets the interrupts output type

        bool getInterruptMode(sths34pf80_int_mode_t *val); // Returns the interrupt mode currently set on the device
        bool setInterruptMode(sths34pf80_int_mode_t val);  // Sets the interrupt mode of the device 

        bool getDataReadyMode(sths34pf80_drdy_mode_t *val); // Returns the data ready mode currently set for device
        bool setDataReadyMode(sths34pf80_drdy_mode_t val); // Sets the data ready mode of the device (0 or 1) 
        
        bool getPresenceThreshold(uint16_t *val); // Returns the presence threshold value read
        bool setPresenceThreshold(uint16_t threshold); // Sets the presence threshold value of the device

        bool getMotionThreshold(uint16_t *val); // Returns the motion threshold of the device
        bool setMotionThreshold(uint8_t threshold); // Sets the motion threshold value of the device

        bool getTAmbientShockThreshold(uint16_t *val); // Returns the ambient temperature threshold of the device
        bool setTAmbientShockThreshold(uint16_t threshold); // Sets the ambient temperature threshold of the device

        bool getMotionHysteresis(uint8_t *val); // Returns the motion hysterssis of the device
        bool setMotionHysteresis(uint8_t hysteresis); // Sets the motion hystersis of the device

        bool getPresenceHysteresis(uint8_t *val); // Returns the presence hystersis of the device
        bool setPresenceHysteresis(uint8_t hysteresis); // Sets the presence hystersis of the device

        bool getTAmbientShockHysteresis(uint8_t *val); // Returns the ambient temperature shock hystersis of the device 
        bool setTAmbientShockHysteresis(uint16_t hysteresis); // Sets the ambient temperature shock hystersis of the device 

        bool getInterruptPulsed(uint8_t *val); // Returns the result of the algorithms if they are pulsed or not
        bool setInterruptPulsed(uint8_t pulse); // Sets the device's result of the algorithms to pulsed or not

        bool getTobjectAlgoCompensation(uint8_t *val); // Returns if the device is using the algorithm for compensating temp variations
        bool setTobjectAlgoCompensation(uint8_t comp); // Sets the devices Tobject compensation 

        bool getPresenceAbsValue(uint8_t *val); // Returns if there is absolute value added in the presence detection algorithm
        bool setPresenceAbsValue(uint8_t val); // Sets the absolute value added in the presence detection algorithm

        bool resetAlgo(); // Resets the algo structure of the device 

    protected: 
        stmdev_ctx_t sensor;

        bool writeFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len); // Write interface definition
        int32_t readFunctionConfiguration(uint8_t addr, uint8_t *data, uint8_t len); // Read interface defintions
};


#endif