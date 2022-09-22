#include "arduino_secrets.h"
#include <BH1750FVI.h>
#include "thingProperties.h"
// Create the Lightsensor instance
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

void setup() 
{
  Serial.begin(115200);
  LightSensor.begin();  

    // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop()
{
  ArduinoCloud.update();
  // getting the intensity of light
  uint16_t lux = LightSensor.GetLightIntensity();
  float intensity = lux;
  
  //Checking if the intensity is large than 120 then IFTTT will be triggered and same if 
  if(intensity > 120) message = "Area is exposed to Sunlight";
  else message = "Area is under darkness";
}