#ifndef __SparkFun_Bus_H__
#define __SparkFun_Bus_H__

#include <Arduino.h>
#include <Wire.h>


class SFE_BusI2C
{
    public: 
        bool init(uint8_t addr, TwoWire& port);
        bool readRegs(uint8_t regAddr, uint8_t* data, uint8_t numData);
        bool writeRegs(uint8_t regAddr, const uint8_t* data, uint8_t numData);

    private:
        uint8_t devAddr;
        TwoWire* devPort;
};


// class SFE_BusSPI
// {
//     public: 
// 		SfeSPI(void);

//     private:
// 		SPIClass* _spiPort; 
// 		// Settings are used for every transaction.
// 		SPISettings _sfeSPISettings;
// 		uint8_t _cs; 
// };


#endif