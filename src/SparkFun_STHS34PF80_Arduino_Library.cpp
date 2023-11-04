



#include "SparkFun_STHS34PF80_Arduino_Library.h"



bool STHS34PF80_I2C::begin(uint8_t devAddr, TwoWire& wirePort)
{
    bus.init(devAddr, Wire);
    sensor.read_reg = STHS34PF80_I2C::read;
    sensor.write_reg = STHS34PF80_I2C::write;
    sensor.mdelay = STHS34PF80_I2C::delayMS;
    sensor.handle = &bus;

    // call super class begin -- it returns 0 on no error
    return STHS34PF80::begin() == 0;

}

int32_t STHS34PF80_I2C::read(void* bus, uint8_t addr, uint8_t* data, uint16_t numData)
{
    ((SFE_BusI2C*) bus)->readRegs(addr, data, numData);

    return 0; // returns error code here
}

int32_t STHS34PF80_I2C::write(void* bus, uint8_t addr, const uint8_t* data, uint16_t numData)
{
    ((SFE_BusI2C*) bus)->writeRegs(addr, data, numData);

    return 0; // returns error code here
}

void STHS34PF80_I2C::delayMS(uint32_t millisec)
{
    delay(millisec);
}

bool STHS34PF80_SPI::begin(uint8_t chipSelect, SPIClass &spiPort)
{
    bus.init(chipSelect, spiPort, false);
    sensor.read_reg = STHS34PF80_SPI::read;
    sensor.write_reg = STHS34PF80_SPI::write;
    sensor.mdelay = STHS34PF80_SPI::delayMS;
    sensor.handle = &bus;

    // call super class begin -- it returns 0 on no error
    return STHS34PF80::begin() == 0;

}

int32_t STHS34PF80_SPI::read(void* bus, uint8_t addr, uint8_t* data, uint16_t numData)
{
    return ((SFE_BusSPI*) bus)->readRegisterRegion(0, data, numData);
}

int32_t STHS34PF80_SPI::write(void* bus, uint8_t addr, const uint8_t* data, uint16_t numData)
{
    return ((SFE_BusSPI*) bus)->writeRegisterRegion(0, data, numData);
}

void STHS34PF80_SPI::delayMS(uint32_t millisec)
{
    delay(millisec);
}
