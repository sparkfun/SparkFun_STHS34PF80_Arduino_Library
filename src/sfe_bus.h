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