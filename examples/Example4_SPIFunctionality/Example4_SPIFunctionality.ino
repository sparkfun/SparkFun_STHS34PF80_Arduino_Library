#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <SPI.h>

SPIClass vspi(VSPI);

STHS34PF80_SPI mySensor; 

// Presence and Motion variables to fill
int16_t presenceVal = 0;
int16_t motionVal = 0;

// Set your chip select pin according to your setup.
uint8_t chipSelect = 12;

void setup()
{
    // SPI begin - initialize values with the pins according to your setup.
    // vspi.begin(CLOCK, MISO, MOSI, CS)
    vspi.begin(21, 27, 15, 12);

    Serial.begin(115200);

    // Configure the chip select pin
    pinMode(chipSelect, OUTPUT);
	  digitalWrite(chipSelect, HIGH);

    Serial.println("STHS34PF80 Example 4: SPI Functionality");

    if( !mySensor.begin(chipSelect, vspi) ){
		  Serial.println("Did not begin.");
	    while(1);
	  }

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
