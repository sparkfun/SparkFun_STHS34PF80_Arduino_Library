#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;

int16_t presenceVal = 0;
int16_t motionVal = 0;

uint16_t threshold = 1000;
uint8_t hysteresis = 100;


void setup()
{
    Serial.begin(115200);
    Serial.println("STHS34PF80 Example 3: Using Embedded Functions");

    // Begin I2C
    if(Wire.begin() == false)
    {
      Serial.println("I2C Error - check I2C Address");
      while(1);
    }

    // Establish communication with device 
    if(mySensor.begin() == false)
    {
      Serial.println("Error setting up device - please check wiring.");
      while(1);
    }

    // Steps below follow Section 2.1 in the Application Note AN5867
    // Enter power-down mode by setting ODR to 0
    mySensor.setTmosODR(STHS34PF80_TMOS_ODR_OFF);
    // Enable access to embedded functions registers
    mySensor.setMemoryBank(STHS34PF80_EMBED_FUNC_MEM_BANK);

    // Set threshold for the presence sensing (Default = 0xC8)
    // NOTE: Presence Flag goes high when presence read is above threshold
    mySensor.setPresenceThreshold(threshold);
    Serial.print("Presence value set: ");
    Serial.println(threshold);
    // Set hysteresis for the presence sensing (default value: 50LSB)
    mySensor.setPresenceHysteresis(hysteresis);
    // Set hysteresis for the motion sensing (Default = 0x32)
    mySensor.setMotionHysteresis(hysteresis);
    Serial.print("Presence and Motion Hysteresis Set: ");
    Serial.println(hysteresis);

    // Disable access to embedded functions registers
    mySensor.setMemoryBank(STHS34PF80_MAIN_MEM_BANK);
    // Enter continuous mode 
    mySensor.setTmosODR(STHS34PF80_TMOS_ODR_AT_1Hz);

    delay(1000);
}

void loop() 
{
  // General presence and motion read (from example 1)
  sths34pf80_tmos_drdy_status_t dataReady;
  mySensor.getDataReady(&dataReady);

  // Check whether sensor has new data - run through loop if data is ready
  if(dataReady.drdy == 1)
  {
    sths34pf80_tmos_func_status_t status;
    mySensor.getStatus(&status);
    
    // Check if the presence (data ready) flag is high. If so, print the presence value
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