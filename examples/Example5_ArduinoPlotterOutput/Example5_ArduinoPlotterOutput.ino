#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;

// Global Presence Value
int16_t presenceVal = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("STHS34PF80 Example 5: Arduino Serial Plotter Presence Output");

    // Begin I2C
    if(Wire.begin() == false)
    {
      Serial.println("I2C Error - check I2C Address");
      while(1);
    }

    // Establish communication with device 
    if(mySensor.begin() != 0)
    {
      Serial.println("Sensor failed to begin - Check wiring.");
      while(1);
    }

    Serial.println("Open the Serial Plotter for graphical viewing");

    // Default ODR: 1Hz

    delay(1000);
}

void loop()
{

  bool dataReady = mySensor.getDataReady();
    
  if(dataReady == 1)
  {
    sths34pf80_tmos_func_status_t status;
    mySensor.getStatus(&status);
    
    
    // If the flag is high, then read out the information
    if(status.pres_flag == 1)
    {
      mySensor.getPresenceValue(&presenceVal);
      Serial.println(presenceVal);
    }
  }
      
}
