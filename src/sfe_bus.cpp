#ifndef __SparkFun_Bus_Library_H__
#define __SparkFun_Bus_Library_H__

#include "SFE_Bus.h"

bool SFE_BusI2C::init(uint8_t addr, TwoWire& port)
{
    devAddr == adrr;
    devPort = port
}

bool SFE_BusI2C::readRegs(uint8_t regAddress, uint8_t* dataBuffer, uint8_t numBytes)
{
    // Jump to desired register address
    devPort->beginTransmission(devAddr);
    devPort->write(regAddress);
    if(devPort->endTransmission())
    {
        return false;
    }

    // Read bytes from these registers
    devPort->requestFrom(devAddr, numBytes);

    // Store all requested bytes
    for(uint32_t i = 0; i < numBytes && devPort->available(); i++)
    {
        dataBuffer[i] = devPort->read();
    }

    return true;
}

bool SFE_BusI2C::writeRegs(uint8_t regAddress, const uint8_t* dataBuffer, uint8_t numBytes)
{
    // Begin transmission
    devPort->beginTransmission(devAddr);

    // Write the address
    devPort->write(regAddress);
    
    // Write all the data
    for(uint32_t i = 0; i < numBytes; i++)
    {
        devPort->write(dataBuffer[i]);
    }

    // End transmission
    if(devPort->endTransmission())
    {
        return false;
    }

    return true;
}

#endif