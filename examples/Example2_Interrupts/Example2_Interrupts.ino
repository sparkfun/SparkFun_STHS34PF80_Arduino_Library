#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;

// Values to fill with presence data
int16_t presenceVal = 0;

// Change the pin number to the pin that has been chosen for your setup
int intPin = 12;


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
    mySensor.setTmosRouteInterrupt(STHS34PF80_TMOS_INT_OR);

    // Set the interrupt to read from once triggered
    mySensor.setTmosInterruptOR(STHS34PF80_TMOS_INT_PRESENCE);

    // Set the ODR to a faster rate for quicker outputs
    mySensor.setTmosODR(STHS34PF80_TMOS_ODR_AT_1Hz);

    // Set INT pin to be triggered on rising and falling edges of INT pin
    pinMode(intPin, INPUT);

    mySensor.setInterruptPulsed(0);

    delay(500);
}

void loop() 
{
  // Value to read interrupt pin status
  int interruptVal = digitalRead(intPin);
  
  // If interrupt pulse has been triggered
  if(interruptVal == HIGH)
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
  }

}
