#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;

// Values to fill with presence data
int16_t presenceVal = 0;


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

    // Set the ODR to a faster rate for quicker outputs
    mySensor.setTmosODR(STHS34PF80_TMOS_ODR_AT_2Hz);

    delay(500);
}

void loop()
{

  bool dataReady = mySensor.getDataReady();
    
  if(dataReady == true)
  {
    sths34pf80_tmos_func_status_t status = mySensor.getStatus();
    
    // If the flag is high, then read out the information
    if(status.pres_flag == 1)
    {
      // Presence Units: cm^-1
      mySensor.getPresenceValue(&presenceVal);
      Serial.print("Presence: ");
      Serial.print(presenceVal);
      Serial.println("cm^-1");
    }

    // Motion detected or not
    if(status.mot_flag == 1)
    {
      Serial.println("Motion detected! ");
    }
  }
      
}
