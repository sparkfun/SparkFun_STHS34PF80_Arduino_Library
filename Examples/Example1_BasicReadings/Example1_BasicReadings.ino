#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;

// Value to fill with presence data
int16_t presenceVal = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("STHS34PF80 Example 1: Basic Readings");

    // Begin I2C
    if (Wire.begin() == false)
    {
        Serial.println("I2C Error - check I2C Address");
        while (1);
    }

    // Establish communication with device
    if (mySensor.begin() != 0) 
    {
        Serial.println("Sensor failed to begin - Check wiring.");
        while (1);
    }

    // Set the ODR to a faster rate for quicker outputs
    // Default ODR: 1Hz
    // mySensor.setTmosODR(STHS34PF80_TMOS_ODR_AT_2Hz);

    delay(500);
}

void loop()
{
    // Check whether sensor has new data
    // bool dataReady = mySensor.getDataReady();
    sths34pf80_tmos_drdy_status_t dataReady;
    int foo = mySensor.getDataReady(&dataReady);
    Serial.printf("%i, %i\n", dataReady.drdy, foo);
    delay(10);

    // Check if the presence (data ready) flag is high. If so, print the presence value
    if (dataReady.drdy == 1)
    {
        sths34pf80_tmos_func_status_t status;
        int32_t err = mySensor.getStatus(&status);
        // sths34pf80_tmos_func_status_t status = mySensor.getStatus();

        Serial.println("Data ready!");
        Serial.println(err);

        // Check if sensor has new data - print information if true
        if (status.pres_flag == 1)
        {
            // Presence Units: cm^-1
            mySensor.getPresenceValue(&presenceVal);
            Serial.print("Presence: ");
            Serial.print(presenceVal);
            Serial.println("cm^-1");
        }

        // Motion detected or not
        if (status.mot_flag == 1)
        {
            Serial.println("Motion detected! ");
        }

        if (status.tamb_shock_flag == 1)
        {
            Serial.println("Ambient temperature shock detected! ");
        }
    }
}
