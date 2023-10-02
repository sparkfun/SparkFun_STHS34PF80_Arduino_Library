#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <SPI.h>

STHS34PF80_SPI mySensor; 

// Presence and Motion variables to fill
int16_t presenceVal = 0;

// Set your chip select pin according to your setup
uint8_t chipSelect = 12;

void setup()
{
    Serial.begin(115200);
    Serial.println("STHS34PF80 Example 4: SPI Functionality");

    // Configure the chip select pin
    pinMode(chipSelect, OUTPUT);
	  digitalWrite(chipSelect, HIGH);

    // Begin SPI
    if( !mySensor.begin(chipSelect) ){
		  Serial.println("Did not begin.");
	    while(1);
	  }

    // Set the ODR to a faster rate for quicker outputs
    // Default ODR: 1Hz
    mySensor.setTmosODR(STHS34PF80_TMOS_ODR_AT_2Hz);

    delay(500);
}

void loop() 
{
  bool dataReady = mySensor.getDataReady();
    
  // Check if the presence (data ready) flag is high. If so, print the presence value
  if(dataReady == 1)
  {
    sths34pf80_tmos_func_status_t status;
    mySensor.getStatus(&status);
    
    Serial.println("Data ready!");
    
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

    if(status.tamb_shock_flag == 1)
    {
      Serial.println("Ambient temperature shock detected! ");
    }
  }
}
