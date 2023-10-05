#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;

// Global Presence Value
int16_t presenceVal = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("STHS34PF80 Example 5: Arduino Serial Plotter Presence Output");

    Wire.begin();

    if(mySensor.begin() == false)
    {
      Serial.println("Error"); // fix this print message
      while(1);
    }

    mySensor.begin();

    // Sets the data update to the fastest rate
    mySensor.setBlockDataUpdate(STHS34PF80_TMOS_ODR_AT_30Hz);

    Serial.println("Open the Serial Plotter for graphical viewing");

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