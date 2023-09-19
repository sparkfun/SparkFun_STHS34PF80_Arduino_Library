#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;
// STHS34PF80_SPI mySensor; 

int16_t presenceVal = 0;
int16_t motionVal = 0;

sths34pf80_mem_bank_t bankDisable = STHS34PF80_MAIN_MEM_BANK;
sths34pf80_mem_bank_t bankEnable = STHS34PF80_EMBED_FUNC_MEM_BANK;

uint16_t threshold = 500;
uint8_t hysteresis = 100;


void setup()
{
    Serial.begin(115200);
    Serial.println("STHS34PF80 Example 3: Embedded Functions");

    Wire.begin();

    if(mySensor.begin() == false)
    {
      Serial.println("Error"); // fix this print message
      while(1);
    }

    // Enter power-down mode
    

    // Enable access to embedded functions registers
    mySensor.setMemoryBank(bankEnable);
    
    // Set threshold for the presence sensing
    // NOTE: Presence Flag goes high when presence read is above threshold
    mySensor.setPresenceThreshold(threshold);
    // Set threshold for the motion sensing
    mySensor.setMotionThreshold(threshold);
    // Set hysteresis for the presence sensing (default value: 50LSB)
    mySensor.setPresenceHysteresis(hysteresis);
    // Set hysteresis for the motion sensing
    mySensor.setMotionHysteresis(hysteresis);


    // Disable access to embedded functions registers
    mySensor.setMemoryBank(bankDisable);
    // Enter continuous mode 

    delay(1000);
}

void loop() 
{
    // General presence and motion read (from example 1)
  bool dataReady = mySensor.getDataReady();
    
  if(dataReady == true)
  {
    sths34pf80_tmos_func_status_t status = mySensor.getStatus();
    
    // Presence Flag - Only reads if the flag is high 
    if(status.pres_flag == 1)
    {
      mySensor.getPresenceValue(&presenceVal);
      Serial.print("Presence: ");
      Serial.println(presenceVal);
    }
    // Motion Flag
    if(status.mot_flag == 1)
    {
      mySensor.getMotionValue(&motionVal);
      Serial.print("Motion: ");
      Serial.println(motionVal);
    }
  }
}
