#include "SparkFun_STHS34PF80_Arduino_Library.h"

int32_t STHS34PF80_I2C::begin(uint8_t devAddr, TwoWire wireSet)
{
    int32_t busErr = bus.init(devAddr, Wire);
    sensor.read_reg = STHS34PF80_I2C::read;
    sensor.write_reg = STHS34PF80_I2C::write;
    sensor.mdelay = STHS34PF80_I2C::delayMS;
    sensor.handle = &bus;

    int32_t beginErr = STHS34PF80::begin();

    if((beginErr != 0) | (busErr != 0))
    {
        return true;
    }

    return false; 
}

int32_t STHS34PF80_I2C::read(void* bus, uint8_t addr, uint8_t* data, uint16_t numData)
{
    return ((SFE_BusI2C*) bus)->readRegs(addr, data, numData);
}

int32_t STHS34PF80_I2C::write(void* bus, uint8_t addr, const uint8_t* data, uint16_t numData)
{
    return ((SFE_BusI2C*) bus)->writeRegs(addr, data, numData);
}

void STHS34PF80_I2C::delayMS(uint32_t millisec)
{
    delay(millisec);
}

int32_t STHS34PF80_SPI::begin(uint8_t chipSelect, SPIClass &spiPort)
{
    int32_t busErr = bus.init(chipSelect, spiPort, false);
    sensor.read_reg = STHS34PF80_SPI::read;
    sensor.write_reg = STHS34PF80_SPI::write;
    sensor.mdelay = STHS34PF80_SPI::delayMS;
    sensor.handle = &bus;

    int32_t beginErr = STHS34PF80::begin();

    if((beginErr != 0) | (busErr != 0))
    {
        return true;
    }

    return false; 
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
