#ifndef __SparkFun_STHS34PF80_Library_H__
#define __SparkFun_STHS34PF80_Library_H__

#include "SparkFun_STHS34PF80_Arduino_Library.h"

bool STHS34PF80_I2C::begin(uint8_t devAddr)
{
    bus.init(devAddr, Wire);
    sensor.read_reg = read;
    sensor.write_reg = write;
    sensor.mdelay = delayMS;
    sensor.handle = &bus;

    STHS34PF80::begin();
}

int32_t STHS34PF80_I2C::read(void* bus, uint8_t addr, uint8_t* data, uint16_t numData)
{
    ((SFE_BusI2C*) bus)->readRegs(addr, data, numData);
}

int32_t STHS34PF80_I2C::write(void* bus, uint8_t addr, const uint8_t* data, uint16_t numData)
{
    ((SFE_BusI2C*) bus)->writeRegs(addr, data, numData);
}

void STHS34PF80_I2C::delayMS(uint32_t millisec)
{
    delay(millisec);
}

#endif