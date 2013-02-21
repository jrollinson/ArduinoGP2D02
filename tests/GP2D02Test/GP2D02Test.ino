#include <GP2D02.h>

/* Tests a single sensor */

int vIn = 2;
int vOut = 3;
GP2D02 sensor(vIn,vOut);

void setup()
{
  Serial.begin(9600);
};

void loop()
{
  Serial.println(sensor.getRawRange());
  delay(1000); //wait a second
};
