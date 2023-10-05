#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;
// STHS34PF80_SPI mySensor; 

// Values to fill with presence and motion data
int16_t presenceVal = 0;
int16_t motionVal = 0;

// Change the pin number to the pin that has been chosen for your setup
int intPin = 12;

sths34pf80_tmos_route_int_t interruptRoute = STHS34PF80_TMOS_INT_DRDY;


void setup()
{
    Serial.begin(115200);
    Serial.println("STHS34PF80 Example 2: Interrupts");

    // Begin I2C transactions
    Wire.begin();

    // Checks established connection
    if(mySensor.begin() == false)
    {
      Serial.println("Error"); // fix this print message
      while(1);
    }

    // Data Ready signal routed to the INT pin
    mySensor.setTmosRouteInterrupt(interruptRoute);

    // **FINISH READING INTERRUPT SECTION TO MAKE SURE NO MORE IS NEEDED**

    // Set INT pin to be triggered on rising and falling edges of INT pin
    pinMode(intPin, INPUT);

    delay(1000);
}

void loop() 
{

  // Value to read interrupt pin status
  int interruptVal = digitalRead(intPin);
    
  if(interruptVal == HIGH)
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