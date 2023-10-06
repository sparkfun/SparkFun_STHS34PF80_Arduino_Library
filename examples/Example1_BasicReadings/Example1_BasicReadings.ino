#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;

// Values to fill with presence and motion data
int16_t presenceVal = 0;
int16_t motionVal = 0;
float temperatureVal = 0;


void setup()
{
    Serial.begin(115200);
    Serial.println("STHS34PF80 Example 1: Basic Readings");

    // Begin I2C
    if(Wire.begin() == 0)
    {
      Serial.println("I2C Error - check I2C Address");
      while(1);
    }

    // Establish communication with device 
    if(mySensor.begin() != 0)
    {
      Serial.println("Error setting up device - please check wiring.");
      while(1);
    }

    delay(1000);
}

void loop()
{
  sths34pf80_tmos_drdy_status_t dataReady;
  mySensor.getDataReady(&dataReady);

  // Check whether sensor has new data - run through loop if data is ready
  if(dataReady.drdy == 1)
  {
    sths34pf80_tmos_func_status_t status;
    mySensor.getStatus(&status);
    
    // If presence flag is high, then print data
    if(status.pres_flag == 1)
    {
      // Presence Units: cm^-1
      mySensor.getPresenceValue(&presenceVal);
      Serial.print("Presence: ");
      Serial.print(presenceVal);
      Serial.println(" cm^-1");
    }

    if(status.mot_flag == 1)
    {
      Serial.println("Motion Detected!");
    }

    if(status.tamb_shock_flag == 1)
    {
      mySensor.getTemperatureData(&temperatureVal);
      Serial.print("Temperature: ");
      Serial.print(temperatureVal);
      Serial.println(" °C");
    }
  }
      
}

