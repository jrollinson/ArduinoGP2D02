/* Tests a single sensor */

#include <GP2D02.h>;
int vIn[] = {2,3,4};
int vOut[] = {5,6,7};
int nSensors = 3;
nGP2D02 sensors(vIn,vOut,nSensors);

void setup()
{
  Serial.begin(9600);
};

void loop()
{
  byte ranges[nSensors];
  sensors.getRawRanges(&ranges[0]);
  for (int i = 0; i < nSensors; i++) 
  {
    int result = (int(ranges[i]))/10;
    Serial.print(result);
    Serial.print("\t");
  }
  Serial.println();
};
