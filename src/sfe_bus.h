#ifndef __SparkFun_Bus_H__
#define __SparkFun_Bus_H__

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#define SPI_READ 0x80

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

class SfeSPI //: public QwIDeviceBus
{
	public:

		// SfeSPI(void);

		bool init(uint8_t cs, bool bInit=false);

		bool init(SPIClass& spiPort, SPISettings& ismSPISettings, uint8_t cs,  bool bInit=false);

		bool writeRegisterByte(uint8_t address, uint8_t offset, uint8_t data);

		int writeRegisterRegion(uint8_t address, uint8_t offset, const uint8_t* data, uint16_t length);

		int readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t* data, uint16_t numBytes);

	private:

		SPIClass* _spiPort; 
		// Settings are used for every transaction.
		SPISettings _sfeSPISettings;
		uint8_t _cs; 
};

#endif