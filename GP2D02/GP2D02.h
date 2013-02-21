/*
  GP2D02.h - library for the Sharp GP2D02 infrared sensor
  Created by Joseph Rollinson, 4 November 2011
  Public Domain
*/

#ifndef GP2D02_h
#define GP2D02_h

#include "Arduino.h"

/* A simple object that represents a single GP2D02 sensor */
class GP2D02
{
  public:
    GP2D02(int pinVin, int pinVout);
    byte getRawRange(); 
  private:
    int _pinVin;
    int _pinVout;
};

/* An object that represents multiple GP2D02. 
   Much more efficient than simply using multiple GP2D02 classes. */
class nGP2D02
{
	public:
		nGP2D02(int pinVins[], int pinVouts[],int nSensors);
		void getRawRanges(byte* ranges); 
		byte getRawRange(int nSensor);
	private:
		int _pinVins[6]; //max length due to size of arduino
		int _pinVouts[6];
		int _nSensors;
             

};
#endif
