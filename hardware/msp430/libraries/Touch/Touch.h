/*
  Touch.h - Capacitive Touch library 
  Copyright (c) 2012 Anton Smeenk.  All right reserved.

  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef TOUCH_H
#define TOUCH_H

#include <inttypes.h>

#define TOUCH_VERSION           1      // software version of this library

#define FILTER_COUNT            2      // nr of filter values to use
#define TOUCH_COUNT             8      // nr of touch buttons 
#define MEASURE_TICKS			312    // 312 * 32 us = 9.9 ms
#define MEASURE_OVERFLOW		1400   // 1400 * 32 us = 44.8 ms 

class TouchPin
{
public:
  TouchPin(uint8_t pin, int16_t threshold = 200 );                 // select given pin as a capacitive touch pin
  void start();
  void stop();
  void measure(uint16_t tickrate);	// integrate tickratefor measure
  void calibrate(uint16_t tickrate);// integrate tickrate for calibrate 
  int16_t  getDelta();			   	// get raw (integrated) value of calibration minus current raw value
  uint16_t  getCalibration();	   	// get raw (integrated) value of calibration
  bool isPressed();					// return true if pressed
private:
   uint16_t _integrate(uint16_t tickrate); // integrate tickrate
   uint8_t  _bit;              		// bit index within port
   uint8_t  _port;                  // port nr
   int16_t  _threshold;             // delta change  which indicates  the button is pressed
   uint16_t _filter[FILTER_COUNT];  // integration array
   uint16_t _calibration;			// integrated calibration value
   int16_t	_delta;					// current delta value (calibration value minus current measure)
};

class TouchSlider3
{
public:
  TouchSlider3(uint8_t startbit= 0 ); // select given pin index as start mask for this slider
  int8_t getPos();		              // get the position of this slider
  bool   isTouched();		          // is slider touched at all?
private:
  uint8_t _startbit;	
};
class TouchSlider4
{
public:
  TouchSlider4(uint8_t startbit= 0 ); // select given pin index as start mask for this slider
  int8_t getPos();		          // get the position of this slider
  bool isTouched();		          // is slider touched at all?
private:
  uint8_t _startbit;
};


class TouchManager
{
public:
  TouchManager();
  void registerPin(TouchPin* pin);      // register given TouchPin to the manager
  TouchPin* getTouchPin(uint8_t index);
  void recalibrate();        // restart calibration						
  void scheduler();            // call as often as possible at least every 10 ms 							
  uint16_t getBits();	
  int8_t getSliderPos();		// return the position of the slider		
private:
  TouchPin* pins[TOUCH_COUNT];					
  void _measure();
  uint8_t current;	 	 // current touchpin
  uint8_t nrpins;		 // nr of registered pins
  uint16_t bits;		 // all bits in one uint16_t
  uint8_t startupcount;
  uint32_t previousGatetime;
  uint32_t nextMeasureTime;
};

extern TouchManager Touch;
#endif
