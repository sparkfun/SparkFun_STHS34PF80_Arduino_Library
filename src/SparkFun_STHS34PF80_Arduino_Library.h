/******************************************************************************
SparkFun_STHS34PF80_Arduino_Library.h
SparkFun STHS34PF80 Library Definitions Header File
Madison Chodikov @ SparkFun Electronics
Original Creation Date: August 22nd, 2023
https://github.com/sparkfun/SparkFun_STHS34PF80_Arduino_Library

This file defines all of the constants used in the device library,
along with defining the registers used.

Development environment specifics:
    IDE: Arduino 2.1.0
    Hardware Platform: Arduino Uno
    STHS34PF80 Breakout Version: 1.0.0
Distributed as-is; no warranty is given.
******************************************************************************/
#ifndef __SparkFun_STHS34PF80_Arduino_Library_H__
#define __SparkFun_STHS34PF80_Arduino_Library_H__


#include "sths34pf80_class.h"
#include "sfe_bus.h"
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>


class STHS34PF80_I2C : public STHS34PF80
{
    public: 
        bool begin(uint8_t devAddr = STHS34PF80_I2C_ADDRESS, TwoWire& wirePort = Wire);
        static int32_t read(void *, uint8_t, uint8_t *, uint16_t);
        static int32_t write(void *, uint8_t, const uint8_t *, uint16_t);
        static void delayMS(uint32_t millisec);
    private:
        sfe_STHS34PF80::QwI2C _i2cBus;
        uint8_t deviceAddress;
};

class STHS34PF80_SPI : public STHS34PF80
{
    public: 
        bool begin(uint8_t chipSelect, SPIClass &spiPort=SPI);
        static int32_t read(void *, uint8_t, uint8_t *, uint16_t);
        static int32_t write(void *, uint8_t, const uint8_t *, uint16_t);
        static void delayMS(uint32_t millisec);
    
    private: 
        
        sfe_STHS34PF80::SfeSPI _spiBus; 
        
};



#endif