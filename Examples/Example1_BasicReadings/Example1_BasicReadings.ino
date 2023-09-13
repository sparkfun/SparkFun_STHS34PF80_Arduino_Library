#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;
// STHS34PF80_SPI mySensor; 


void setup()
{
    Serial.begin(115200);
    Serial.println("Exmaple 1! yay");

    Wire.begin();

    // if(mySensor.begin() == false)
    // {
    //   Serial.println("Error"); // fix this print message
    //   while(1);
    // }

    mySensor.begin();

    //Serial.println(mySensor.getODR());

    delay(1000);
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
        
    if(status.pres_flag == 1)
    {
      int presenceVal = mySensor.getPresenceValue();
      Serial.println(presenceVal);
    }

    if(status.tamb_shock_flag == 1)
    {
      int tempVal = mySensor.getTemperatureData();
      Serial.print("Temperature Value: ");
      Serial.println(tempVal);
    }
  }
      
}

// "correct" code

  //   bool dataReady = mySensor.getDataReady();
    
  //   if(dataReady == true)
  //   {
  //     sths34pf80_tmos_func_status_t status = mySensor.getStatus();
  //     Serial.println(status.pres_flag);
  //     Serial.println(status.mot_flag);
  //     Serial.println(status.tamb_shock_flag);
          
  //     if(status.pres_flag == 1)
  //     {
  //       int presenceVal = mySensor.getPresenceValue();
  //       Serial.println(presenceVal);
  //     }

  //     if(status.tamb_shock_flag == 1)
  //     {
  //       int tempVal = mySensor.getTemperatureData();
  //       Serial.print("Temperature Value: ");
  //       Serial.println(tempVal);
  //     }
      
  //   }

  //   if(status.pres_flag == 1)
  //   {
  //     Serial.println("Presence Flag");
  //   }

  //   if(status.mot_flag == 1)
  //   {
  //     Serial.println("Presence Flag");
  //   }
  // }

  // Serial.println();

