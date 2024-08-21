/******************************************************************************
  Example3_EmbeddedFunctions.ino
  
  Set the hysteresis values for the presence and motion detection, read human 
  presence detection values from the STHS34PF80 sensor, print them to terminal. 
  Prints raw IR presence (cm^-1) and if motion was detected.

  SparkFun STHS34PF80 Arduino Library
  Madison Chodikov @ SparkFun Electronics
  Original Creation Date: September 19th, 2023
  https://github.com/sparkfun/SparkFun_STHS34PF80_Arduino_Library

  Development environment specifics:

  IDE: Arduino 2.2.1
  Hardware Platform: SparkFun RedBoard Qwiic
  SparkFun Human Presence and Motion Sensor - STHS34PF80 (Qwiic) Version: 1.0
  SparkFun Qwiic Mini Human Presence and Motion Sensor - STHS34PF80 Version: 1.0

  Do you like this library? Help support SparkFun. Buy a board!

    SparkFun Human Presence and Motion Sensor - STHS34PF80 (Qwiic)
    https://www.sparkfun.com/products/22494
    
    SparkFun Qwiic Mini Human Presence and Motion Sensor - STHS34PF80
    https://www.sparkfun.com/products/23253

  Hardware Connections:
  Use a Qwiic cable to connect from the RedBoard Qwiic to the STHS34PF80 breakout (QWIIC).
  You can also choose to wire up the connections using the header pins like so:

  ARDUINO --> STHS34PF80
  SDA (A4) --> SDA
  SCL (A5) --> SCL
  3.3V --> 3.3V
  GND --> GND

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

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
    Wire.begin()

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