#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_SPI mySensor; 

// Presence and Motion variables to fill
int16_t presenceVal = 0;
int16_t motionVal = 0;

// Set your chip select pin according to your setup.
byte chipSelect = 12;

void setup()
{
    SPI.begin();

    Serial.begin(115200);

    pinMode(chipSelect, OUTPUT);
	  digitalWrite(chipSelect, HIGH);

    Serial.println("STHS34PF80 Example 4: SPI Functionality");

    if( !mySensor.begin(chipSelect) ){
		  Serial.println("Did not begin.");
	    while(1);
	  }


    // Start communication with sensor 
    if(mySensor.begin() == false)
    {
      Serial.println("Error"); // fix this print message
      while(1);
    }

    mySensor.begin();

    delay(1000);
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
      Serial.println(presenceVal);
    }

    if(status.mot_flag == 1)
    {
      mySensor.getMotionValue(&motionVal);
      Serial.print("Motion: ");
      Serial.println(motionVal);
    }
  }
}
