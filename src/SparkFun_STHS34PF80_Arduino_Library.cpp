#include "SparkFun_STHS34PF80_Arduino_Library.h"


bool STHS34PF80_I2C::begin(uint8_t devAddr, TwoWire& wirePort)
{
    _i2cBus.init(wirePort, false);
    sensor.read_reg = STHS34PF80_I2C::read;
    sensor.write_reg = STHS34PF80_I2C::write;
    sensor.mdelay = STHS34PF80_I2C::delayMS;
    sensor.handle = this;
    deviceAddress = devAddr;

    // call super class begin -- it returns 0 on no error
    return STHS34PF80::begin() == 0;

}

int32_t STHS34PF80_I2C::read(void* device, uint8_t addr, uint8_t* data, uint16_t numData)
{
    return ((STHS34PF80_I2C*)device)->_i2cBus.readRegisterRegion(((STHS34PF80_I2C*)device)->deviceAddress, addr, data, numData);
}

int32_t STHS34PF80_I2C::write(void* device, uint8_t addr, const uint8_t* data, uint16_t numData)
{
    return ((STHS34PF80_I2C*)device)->_i2cBus.writeRegisterRegion(((STHS34PF80_I2C*)device)->deviceAddress, addr, data, numData);
}

void STHS34PF80_I2C::delayMS(uint32_t millisec)
{
    delay(millisec);
}

bool STHS34PF80_SPI::begin(uint8_t chipSelect, SPIClass &spiPort)
{
    SPISettings spiSettings = SPISettings(3000000, MSBFIRST, SPI_MODE0);
    _spiBus.init(spiPort, spiSettings, chipSelect);
    sensor.read_reg = STHS34PF80_SPI::read;
    sensor.write_reg = STHS34PF80_SPI::write;
    sensor.mdelay = STHS34PF80_SPI::delayMS;
    sensor.handle = this;

    // call super class begin -- it returns 0 on no error
    return STHS34PF80::begin() == 0;

}

int32_t STHS34PF80_SPI::read(void* device, uint8_t addr, uint8_t* data, uint16_t numData)
{
    return ((STHS34PF80_SPI*)device)->_spiBus.readRegisterRegion(0, addr, data, numData);
}

int32_t STHS34PF80_SPI::write(void* device, uint8_t addr, const uint8_t* data, uint16_t numData)
{
    return ((STHS34PF80_SPI*)device)->_spiBus.writeRegisterRegion(0, addr, data, numData);
}

void STHS34PF80_SPI::delayMS(uint32_t millisec)
{
    delay(millisec);
}
