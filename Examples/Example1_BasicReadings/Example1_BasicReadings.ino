#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;
// STHS34PF80_SPI mySensor; 


void setup()
{
    Serial.begin(115200);
    Serial.println("Exmaple 1! yay");

    Wire.begin();

    mySensor.begin();
}

void loop()
{

    bool dataReady = mySensor.getDataReady();

    if(dataReady == true)
    {
      sths34pf80_tmos_func_status_t status = mySensor.getStatus();
      Serial.println(status.pres_flag);
      Serial.println(status.mot_flag);
      Serial.println(status.tamb_shock_flag);
      
    }

    // If presence flag is raised, get presence value
    sths34pf80_tmos_func_status_t status = mySensor.getStatus();
    if(status.pres_flag == 1)
    {
      int presenceVal = mySensor.getPresenceValue();
      Serial.println(presenceVal);
    }

    // if(status.pres_flag == 1)
    // {
    //   Serial.println("Presence Flag");
    // }

    // if(status.mot_flag == 1)
    // {
    //   Serial.println("Presence Flag");
    // }

    // if(status.tamb_shock_flag == 1)
    // {
    //   Serial.println("Presence Flag");
    // }

    //Serial.println();
}

