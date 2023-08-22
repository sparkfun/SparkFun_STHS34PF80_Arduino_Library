#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;
// STHS34PF80_SPI mySensor;

void setup()
{
    Serial.begin(115200);
    Serial.println("Exmaple 1! yay");

    Wire.begin()

    mySensor.begin();
}

void loop()
{
    Serial.println(mySensor.getData());
}