#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;
// STHS34PF80_SPI mySensor; 

// Values to fill with presence and motion data
int16_t presenceVal = 0;
int16_t motionVal = 0;


void setup()
{
    Serial.begin(115200);
    Serial.println("STHS34PF80 Example 1: Basic Readings");

    // Begin I2C
    Wire.begin();

    // Establish communication with device 
    if(mySensor.begin() == false)
    {
      Serial.println("Error"); // fix this print message
      while(1);
    }

    delay(1000);
}

void loop()
{
  bool dataReady =  mySensor.getDataReady();
    
  if(dataReady == 1)
  {
    sths34pf80_tmos_func_status_t status;
    mySensor.getStatus(&status);
    
    // If the flag is high, then read out the information
    if(status.pres_flag == 1)
    {
      // Presence Units: cm^-1
      mySensor.getPresenceValue(&presenceVal);
      Serial.print("Presence: ");
      Serial.println(presenceVal);
    }

    if(status.mot_flag == 1)
    {
      Serial.println("Motion Detected!");
    }
  }
      
}