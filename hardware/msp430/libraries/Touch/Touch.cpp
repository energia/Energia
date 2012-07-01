/*
 Touch.cpp - Capacitive Touch driver for lauchpad MSP430
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

#include <Touch.h>
#include "Energia.h"


extern volatile uint32_t wdtCounter;
// slidervalue on index         0,1,2,3,4,5,6,7,8,9,A,
const uint8_t mask2slider3[] = {0,1,3,2,5,6,4};
const uint8_t mask2slider4[] = {0,1,3,2,5,0,4,0,7,8,6,0,0,0,0,0};



  TouchPin::TouchPin(uint8_t pin, int16_t threshold ){                 // select given pin as a capacitive touch pin
  	_bit  = digitalPinToBitMask(pin);
	_port = digitalPinToPort(pin);
	volatile uint16_t *reg = portSelRegister(_port);
	*reg  &= ~_bit; //reset portselect bit
	reg = portSel2Register(_port);
	*reg  &= ~_bit; //reset portselect2 bit
	

  	reg = portDirRegister(_port);
	*reg  &= ~_bit; //set port as input 
  	reg = portRenRegister(_port);
	*reg  |= _bit; //enable pullup register when port is input 

	_threshold = threshold;
  }
  
  void TouchPin::start(){					// enable the pin oscilator function
	TACTL  = 0x0324;                        // reset timer 0, switch to clock input to pin
	volatile uint16_t *reg = portSel2Register(_port);
	*reg  |= _bit; // enable the touch pin 
  }
  void TouchPin::stop(){					// disable the pin oscilator function
	volatile uint16_t *reg = portSel2Register(_port);
	*reg  &= ~_bit; // disable the touch pin 
  }

  void TouchPin::measure(uint16_t tickrate){ // integrate tickrate for measure
  		int32_t temp = _calibration;
  		temp -= _integrate(tickrate);
  		_delta = (int16_t) temp;
  }

  void TouchPin::calibrate(uint16_t tickrate){	// integrate tickrate for calibration 
 	_calibration = _integrate(tickrate);
  }
  int16_t  TouchPin::getDelta(){			// get raw (integrated) value of calibration minus current raw value
  	    return _delta;
  }
  uint16_t  TouchPin::getCalibration(){	// get raw (integrated) value of calibration
  		return _calibration;
  }
  bool TouchPin::isPressed(){				// return true if pressed
  		return (_delta > _threshold);
  }
  
  uint16_t TouchPin::_integrate(uint16_t tickrate){ //integrate captured tickrate 

	// filter the measured value
	uint32_t added = tickrate;
  	for (int i = 0; i < FILTER_COUNT; i++){
  		added += _filter[i];
  	}
	added = added / (FILTER_COUNT+1);

	// replace the values in the filter wiht the previous value

  	for (int i = 0; i < FILTER_COUNT -1; i++){
  		_filter[i] = _filter[i+1];
  	}
  	_filter[FILTER_COUNT -1] = tickrate;
  	return (uint16_t) (added);
  }


  TouchSlider3::TouchSlider3(uint8_t startbit){ // select given pin index as start mask for this slider
    _startbit = startbit;
  }
  int8_t TouchSlider3::getPos(){		      // get the position of this slider
  	uint16_t mask = (7<< _startbit); 
  	uint16_t value = Touch.getBits();
  	value &= mask;
  	value = value >> _startbit;
  	return mask2slider3[value];

  }
  bool TouchSlider3::isTouched(){		          // is slider touched at all?
  	uint16_t mask = (0x7 << _startbit); 
  	uint16_t value = Touch.getBits();
  	value &= mask;
   	return value > 0;
  }
  
  TouchSlider4::TouchSlider4(uint8_t startbit){ // select given pin index as start mask for this slider
    _startbit = startbit;
  }
  int8_t TouchSlider4::getPos(){		      // get the position of this slider
  	uint16_t mask = (0xF << _startbit); 
  	uint16_t value = Touch.getBits();
  	value &= mask;
  	value = value >> _startbit;
  	return mask2slider4[value];

  }
  bool TouchSlider4::isTouched(){		          // is slider touched at all?
  	uint16_t mask = (0xF << _startbit); 
  	uint16_t value = Touch.getBits();
  	value &= mask;
   	return value > 0;
  }



  TouchManager::TouchManager(){
  }
  TouchPin* TouchManager::getTouchPin(uint8_t index){
  	return pins[index];
  }
  
  void TouchManager::registerPin(TouchPin* pin){      // register given TouchPin to the manager
	  pins[nrpins++] = pin;
  }
  void TouchManager::recalibrate(){        // call every 10 ms to calibrate calibrate							
  	startupcount = 0;
  }
  void TouchManager::scheduler(){          // call every 10 ms to measure measure		
  	uint32_t now = wdtCounter;
  	if (now > (previousGatetime + MEASURE_TICKS)){
  		_measure();
  	}
  }

  uint16_t TouchManager::getBits(){
  	return bits;
  }
  void TouchManager::_measure(){
    uint32_t now = wdtCounter;
    while (now == wdtCounter){}          // block until wdtTimer increments

  	uint32_t ticks = TAR;  // capture timerA value

 	uint16_t gatetime 			= wdtCounter - previousGatetime;
 	previousGatetime 			= wdtCounter; 
	int next = (current + 1) % nrpins;
	pins[current]->stop();
	pins[next]->start();

 	if (wdtCounter < 500){
 		return; //watchdog timer overflow case
 	}
 	if(gatetime > MEASURE_OVERFLOW){
 		return;  // gate time too long timer 0 overflows. With 3 Mhz maximum gate time is 46 ms
 	}
	// shift left 8 bits to keep accuracy. Not an absolute value in ticks/sec, just to let it fit in an uint16_t
	uint16_t result = (uint16_t) ( (ticks << 8) / gatetime);
	
  	if (startupcount < 100){
  		startupcount++;
		pins[current]->calibrate(result);
	}else{
		pins[current]->measure(result);
  	}
	uint16_t bitmask = (1 << current);
  	if (pins[current]->isPressed()){
  		bits |= bitmask;
  	}else{
  		bits &= ~bitmask;
  	}


	current = next;
 }

  // instantiate 
  TouchManager Touch;

