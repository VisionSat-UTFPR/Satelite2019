#include <Arduino.h>
#include <Wire.h>
#include <HMC5883L_Simple.h>
 
HMC5883L_Simple Compass;
 
void setup()
{
  Serial.begin(9600);
  Wire.begin();
    
  Compass.SetDeclination(-21, 30, 'W');  // Aqui vai depender da sua região, utilizar esse site para descobrir http://www.magnetic-declination.com/
  Compass.SetSamplingMode(COMPASS_SINGLE);
  Compass.SetScale(COMPASS_SCALE_130);
  Compass.SetOrientation(COMPASS_HORIZONTAL_X_NORTH);
}
 
void loop()
{
   float heading = Compass.GetHeadingDegrees();
   
   Serial.print("Heading: ");
   Serial.println( heading );   
   delay(1000);
}
