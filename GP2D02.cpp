/*
  GP2D02.cpp - library for the Sharp GP2D02 infrared sensor
  Created by Joseph Rollinson, 4 November 2011
  Public Domain
*/

#include "WProgram.h"
#include "GP2D02.h"

/* METHODS FOR GP2D02 */

GP2D02::GP2D02(int pinVin, int pinVout)
{    
     _pinVin = pinVin;
     _pinVout = pinVout;
     pinMode(_pinVin, OUTPUT);
     pinMode(_pinVout, INPUT);
};


//getRawRange() is adapted from this post
//http://slab.concordia.ca/2009/arduino/ir-range-finder/
//to get the raw range of the sensor
//start with a LOW voltage
//do 8 cycles of low/high pulses 100 microseconds apart
//read digital value that comes from the Vout pin
//set Vin to HIGH, then back down to LOW
//return the value

byte GP2D02::getRawRange()
{
    byte val = 0;
    
    digitalWrite(_pinVin, LOW);
    delay(70);
 
    for(int i = 7; i >= 0; i--)
    {
		digitalWrite(_pinVin, HIGH);
     	delayMicroseconds(100);  
     	digitalWrite(_pinVin, LOW);
     	delayMicroseconds(100);
 
     	val |= (digitalRead(_pinVout) << i);
    }
    
	digitalWrite(_pinVin, HIGH);
    delay(2);
    digitalWrite(_pinVin, LOW);
    
	return val;
};

/* METHODS FOR nGP2D02 */

nGP2D02::nGP2D02(int pinVins[], int pinVouts[],int nSensors)
{
	_nSensors = nSensors;
	for(int i = 0;i < nSensors; i++) {
		_pinVins[i] = pinVins[i];
		_pinVouts[i] = pinVouts[i];
		pinMode(_pinVins[i], OUTPUT);
		pinMode(_pinVouts[i], INPUT); }
	
	
};

/*  Returns the raw range of all sensors. This is much faster than polling each
 *  sensor separately. 
 */
void nGP2D02::getRawRanges(byte* ranges)
{
    byte val[_nSensors];
	for(int i = 0; i < _nSensors; i++) {val[i] = 0;}
    
	for(int i = 0; i < _nSensors; i++) { digitalWrite(_pinVins[i], LOW); }
    delay(70);
    for(int j = 7; j >= 0; j--)
    {
    	for (int i = 0; i < _nSensors; i++) {digitalWrite(_pinVins[i], HIGH);}
    	
		delayMicroseconds(100);  
     	
		for (int i = 0; i < _nSensors; i++) {digitalWrite(_pinVins[i], LOW);}
     	
		delayMicroseconds(100);
	 
	 	for (int i = 0; i < _nSensors; i++) {
			val[i] |= (digitalRead(_pinVouts[i]) << j);
		}
     	//Serial.print(digitalRead(IR_VOUT));
    }
	
	for (int i = 0; i < _nSensors; i++) { digitalWrite(_pinVins[i], HIGH); }
    
	delay(2);
	
	for (int i = 0; i < _nSensors; i++) { digitalWrite(_pinVins[i], LOW); }
    
	for (int i = 0; i < _nSensors; i++) { *(ranges+i) = val[i]; }
};

//returns the raw range for a single sensor in the group.
byte nGP2D02::getRawRange(int nSensor)
{
	byte val = 0;
    
    digitalWrite(_pinVins[nSensor], LOW);
    delay(70);
 
    for(int i = 7; i >= 0; i--)
    {
    	digitalWrite(_pinVins[nSensor], HIGH);
     	delayMicroseconds(100);  
     	digitalWrite(_pinVins[nSensor], LOW);
     	delayMicroseconds(100);
 
     	val |= (digitalRead(_pinVouts[nSensor]) << i);
     	//Serial.print(digitalRead(IR_VOUT));
    }
    digitalWrite(_pinVins[nSensor], HIGH);
    delay(2);
    digitalWrite(_pinVins[nSensor], LOW);
    return val;
}
