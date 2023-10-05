#ifndef __SparkFun_Bus_H__
#define __SparkFun_Bus_H__

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#define SPI_READ 0x80

class SFE_BusI2C
{
    public: 
        bool init(uint8_t addr, TwoWire& port=Wire);
        bool readRegs(uint8_t regAddr, uint8_t* data, uint8_t numData);
        bool writeRegs(uint8_t regAddr, const uint8_t* data, uint8_t numData);

    private:
        uint8_t devAddr;
        TwoWire* devPort;
};

class SFE_BusSPI 
{
	public:

		bool init(uint8_t cs, SPIClass& spiPort=SPI, bool bInit=false);
		bool writeRegisterRegion(uint8_t offset, const uint8_t* data, uint16_t length);
		bool readRegisterRegion(uint8_t reg, uint8_t* data, uint16_t numBytes);

	private:

		SPIClass* _spiPort; 
		// Settings are used for every transaction.
		SPISettings _sfeSPISettings;
		uint8_t _cs; 

};

#endif