/*
  ************************************************************************
  *	Wire.cpp
  *
  *	Arduino core files for MSP430
  *		Copyright (c) 2012 Robert Wessels. All right reserved.
  *
  *
  ***********************************************************************
  Derived from:
  TwoWire.cpp - TWI/I2C library for Wiring & Arduino
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

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
 
  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
*/

//extern "C" {
//  #include <stdlib.h>
//  #include <string.h>
//  #include <inttypes.h>
//  #include "Energia.h" // for digitalWrite
//  #include "twi.h"
//  #include "usci_isr_handler.h"
//}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Energia.h"
#include "wiring_private.h"
#include "usci_isr_handler.h"



#include "Wire.h"

// Initialize Class Variables //////////////////////////////////////////////////




// Constructors ////////////////////////////////////////////////////////////////

TwoWire::TwoWire(uint8_t moduleNbr, uint16_t sclPinMode, uint16_t sdaPinMode, uint8_t sclPin, uint8_t sdaPin) : moduleNbr(moduleNbr), sclPinMode(sclPinMode), sdaPinMode(sdaPinMode), sclPin(sclPin), sdaPin(sdaPin)
{
#if defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) \
 || defined(__MSP430_HAS_USCI_B1__)
	if(moduleNbr == 1) {
		UCBxCTL0 =     &UCB1CTL0;
		UCBxCTL1 =     &UCB1CTL1;
		UCBxBR0 =      &UCB1BR0;
		UCBxBR1 =      &UCB1BR1;
		UCBxSTAT =     &UCB1STAT;
		UCBxRXBUF =    &UCB1RXBUF;
		UCBxTXBUF =    &UCB1TXBUF;
		UCBxIE =       &UCB1IE;
		UCBxIFG =      &UCB1IFG;
		UCBxIV =       &UCB1IV;
		UCBxI2COA =    &UCB1I2COA;
		UCBxI2CSA =    &UCB1I2CSA;
	}
	else {
		UCBxCTL0 =     &UCB0CTL0;
		UCBxCTL1 =     &UCB0CTL1;
		UCBxBR0 =      &UCB0BR0;
		UCBxBR1 =      &UCB0BR1;
		UCBxSTAT =     &UCB0STAT;
		UCBxRXBUF =    &UCB0RXBUF;
		UCBxTXBUF =    &UCB0TXBUF;
		UCBxIE =       &UCB0IE;
		UCBxIFG =      &UCB0IFG;
		UCBxIV =       &UCB0IV;
		UCBxI2COA =    &UCB0I2COA;
		UCBxI2CSA =    &UCB0I2CSA;
	}
#endif

	rxBufferIndex = 0;
	rxBufferLength = 0;

	txAddress = 0;
	txBufferIndex = 0;
	txBufferLength = 0;

	transmitting = 0;
	user_onRequest = NULL;
	user_onReceive = NULL;

	twi_state = TWI_IDLE;
	twi_sendStop = true;
	twi_inRepStart = false;
	twi_error = TWI_ERRROR_NO_ERROR;

	twi_masterBufferIndex = 0;
	twi_masterBufferLength = 0; // ??

	twi_txBufferIndex = 0;
	twi_txBufferLength = 0; // ??

	#if defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) \
	 || defined(__MSP430_HAS_USCI_B1__) || defined(__MSP430_HAS_EUSCI_B0__)
	twi_rxBufferIndex = 0;
	#endif

	#if defined(__MSP430_HAS_USI__)
	twi_slarw = 0;
	twi_my_addr = 0;
	#endif
}

// Private Methods /////////////////////////////////////////////////////////////


/*
 * Function twi_init
 * Desc     readys twi pins and sets twi bitrate
 * Input    none
 * Output   none
 */
void TwoWire::twi_init(void)
{
	// initialize state
	twi_state = TWI_IDLE;
	twi_sendStop = true;		// default value
	twi_inRepStart = false;

#if defined(__MSP430_HAS_USI__)
	/* 100 KHz for all */
#if (F_CPU >= 16000000L) || (F_CPU >= 12000000L)
	USICKCTL = USIDIV_7;
#elif defined(CALBC1_8MHZ_) && (F_CPU >= 8000000L)
	USICKCTL = USIDIV_6;
#elif defined(CALBC1_1MHZ_) && (F_CPU >= 1000000L)
	USICKCTL = USIDIV_3;
#endif
	/* Enable USI I2C mode. */
	USICTL1 = USII2C;
	/* SDA/SCL port enable and hold in reset */
	USICTL0 = (USIPE6 | USIPE7 | USISWRST);
	/* SMCLK and SCL inactive state is high */
	USICKCTL |= (USISSEL_2 | USICKPL);
	/* Disable automatic clear control */
	USICNT |= USIIFGCC;
	/* Enable USI */
	USICTL0 &= ~USISWRST;
	/* Counter interrupt enable */
	USICTL1 |= USIIE;
#elif defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
    /* Calling this dummy function prevents the linker
     * from stripping the USCI interupt vectors.*/
    usci_isr_install();

    //Disable the USCI module and clears the other bits of control register
    *UCBxCTL1 = UCSWRST;

     /*
     * Configure as I2C Master, in transit mode
     * UCMODE_3 = I2C mode
     * UCSYNC = Synchronous mode
     * UCCLK = SMCLK
     */
    *UCBxCTL0 = UCMST | UCMODE_3 | UCSYNC;
    *UCBxCTL1 |= UCSSEL_2 | UCTR;

    /*
     * Compute the clock divider that achieves less than or
     * equal to 100kHz.  The numerator is biased to favor a larger
     * clock divider so that the resulting clock is always less than or equal
     * to the desired clock, never greater.
     */
    *UCBxBR0 = (unsigned char)((F_CPU / TWI_FREQ) & 0xFF);
    *UCBxBR1 = (unsigned char)((F_CPU / TWI_FREQ) >> 8);

    /* Set pins to I2C mode */
    pinMode_int(sclPin, sclPinMode);
    pinMode_int(sdaPin, sdaPinMode);

    // Enable the USCI module
    *UCBxCTL1 &= ~(UCSWRST);

#if defined(__MSP430_HAS_USCI__)
    /* Set I2C state change interrupt mask */
    UCB0I2CIE |= (UCALIE|UCNACKIE|UCSTTIE|UCSTPIE);
    /* Enable state change and TX/RX interrupts */
    UC0IE |= UCB0RXIE | UCB0TXIE;
#else
    /* Set I2C state change interrupt mask and TX/RX interrupts */
    *UCBxIE |= (UCALIE|UCNACKIE|UCSTTIE|UCSTPIE|UCRXIE|UCTXIE);
    *UCBxIFG = ~(UCALIE|UCNACKIE|UCSTTIE|UCSTPIE|UCRXIE|UCTXIE);  // Clear I2C interrupt sources
#endif

#elif defined(__MSP430_HAS_EUSCI_B0__)
    P1SEL1 |= BIT6 + BIT7;                  // Pin init

    //Disable the USCI module and clears the other bits of control register
    UCB0CTLW0 = UCSWRST;

    //Configure Automatic STOP condition generation
    UCB0CTLW1 &= ~UCASTP_3;
    //UCB0CTLW1 |= autoSTOPGeneration;

    //Byte Count Threshold
    //UCB0TBCNT = byteCounterThreshold;
    /*
     * Configure as I2C master mode.
     * UCMST = Master mode
     * UCMODE_3 = I2C mode
     * UCSYNC = Synchronous mode
     * UCCLK = SMCLK
     */
    UCB0CTLW0 = UCMODE_3 | UCSSEL__SMCLK | UCSYNC | UCSWRST;

    /*
     * Compute the clock divider that achieves the fastest speed less than or
     * equal to the desired speed.  The numerator is biased to favor a larger
     * clock divider so that the resulting clock is always less than or equal
     * to the desired clock, never greater.
     */
    UCB0BRW = (unsigned short)(F_CPU / 400000);
    UCB0CTLW0 &= ~(UCSWRST);
    UCB0IE |= (UCRXIE0|UCTXIE0|UCSTTIE|UCSTPIE); // Enable I2C interrupts
#endif
}

/*
 * Function twi_setAddress
 * Desc     sets slave address and enables interrupt
 * Input    none
 * Output   none
 */
void TwoWire::twi_setAddress(uint8_t address)
{
#if defined(__MSP430_HAS_USI__)
	twi_my_addr = address << 1;
#elif defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
	/* UCGCEN = respond to general Call */
	*UCBxI2COA = (address | UCGCEN);
#elif defined(__MSP430_HAS_EUSCI_B0__)
	/* UCGCEN = respond to general Call */
	UCB0I2COA0 = (address | UCOAEN | UCGCEN);
#endif
}

/*
 * Function twi_readFrom
 * Desc     attempts to become twi bus master and read a
 *          series of bytes from a device on the bus
 * Input    address: 7bit i2c device address
 *          data: pointer to byte array
 *          length: number of bytes to read into array
 * Output   number of bytes read
 */
uint8_t TwoWire::twi_readFrom(uint8_t address, uint8_t* data, uint8_t length, uint8_t sendStop)
{
	uint8_t i;

#if defined(__MSP430_HAS_USI__)
	/* Disable START condition interrupt */
	USICTL1 &= ~USISTTIE;
	/* I2C master mode */
	USICTL0 |= USIMST;
#elif defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
    *UCBxCTL1 |= UCSWRST;                     // Enable SW reset
//    UCBxCTL1 |= (UCSSEL_2);                  // I2C Master, synchronous mode
//    UCBxCTL0 |= (UCMST | UCMODE_3 | UCSYNC); // I2C Master, synchronous mode
    *UCBxCTL1 &= ~(UCTR);                     // Configure in receive mode
    *UCBxI2CSA = address;                     // Set Slave Address
    *UCBxCTL1 &= ~UCSWRST;                    // Clear SW reset, resume operation
#if defined(__MSP430_HAS_USCI__)
    UCB0I2CIE |= (UCALIE|UCNACKIE|UCSTPIE);  // Enable I2C interrupts
    UC0IE |= (UCB0RXIE | UCB0TXIE);          // Enable I2C interrupts
#else
    *UCBxIE |= (UCALIE|UCNACKIE|UCSTPIE|UCRXIE|UCTXIE);  // Enable I2C interrupts
    *UCBxIFG = ~(UCALIE|UCNACKIE|UCSTTIE|UCSTPIE|UCRXIE|UCTXIE); // Clear I2C interrupt sources
#endif

#elif defined(__MSP430_HAS_EUSCI_B0__)
    UCB0CTLW0 = UCSWRST;                      // Enable SW reset
    UCB0CTLW0 |= (UCMST | UCMODE_3 | UCSYNC | UCSSEL__SMCLK);   // I2C Master, synchronous mode
    UCB0CTLW0 &= ~(UCTR);                     // Configure in receive mode
    UCB0I2CSA = address;                      // Set Slave Address
    UCB0CTLW0 &= ~UCSWRST;                    // Clear SW reset, resume operation
    UCB0IE |= (UCRXIE0|UCALIE|UCNACKIFG|UCSTTIFG|UCSTPIFG); // Enable I2C interrupts
#endif
	// ensure data will fit into buffer
	if(TWI_BUFFER_LENGTH < length){
		return 0;
	}

	// initialize buffer iteration vars
	twi_masterBufferIndex = 0;
	twi_masterBufferLength = length-1;  // This is not intuitive, read on...
	// On receive, the previously configured ACK/NACK setting is transmitted in
	// response to the received byte before the interrupt is signalled.
	// Therefor we must actually set NACK when the _next_ to last byte is
	// received, causing that NACK to be sent in response to receiving the last
	// expected byte of data.

#if defined(__MSP430_HAS_USI__)
	/* build sla+w, slave device address + w bit */
	twi_slarw = 1;
	twi_slarw |= address << 1;

	// send start condition
	twi_state = TWI_SND_START;
	// this will trigger an interrupt kicking off the state machine in the isr
	USICTL1 |= USIIFG;

#elif defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
    twi_state =  TWI_MRX;                     // Master receive mode
    *UCBxCTL1 |= UCTXSTT;                      // I2C start condition

    if(length == 1) {                         // When only receiving 1 byte..
        while(*UCBxCTL1 & UCTXSTT);            // Wait for start bit to be sent
        *UCBxCTL1 |= UCTXSTP;                  // Send I2C stop condition after recv
    }

#elif defined(__MSP430_HAS_EUSCI_B0__)
    twi_state =  TWI_MRX;                     // Master receive mode
    while (UCB0CTLW0 & UCTXSTP);              // Ensure stop condition got sent
    UCB0CTLW0 |= UCTXSTT;                     // I2C start condition
#endif

	/* Wait in low power mode for read operation to complete */
	while(twi_state != TWI_IDLE){
		__bis_SR_register(LPM0_bits);
	}

	if (twi_masterBufferIndex < length)
		length = twi_masterBufferIndex;

	for(i = 0; i < length; ++i){
		data[i] = twi_masterBuffer[i];
	}

#if defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
	/* Ensure stop condition got sent before we exit. */
	while (*UCBxCTL1 & UCTXSTP);
#endif
	return length;
}

/*
 * Function twi_writeTo
 * Desc     attempts to become twi bus master and write a
 *          series of bytes to a device on the bus
 * Input    address: 7bit i2c device address
 *          data: pointer to byte array
 *          length: number of bytes in array
 *          wait: boolean indicating to wait for write or not
 * Output   0 .. success
 *          1 .. length to long for buffer
 *          2 .. address send, NACK received
 *          3 .. data send, NACK received
 *          4 .. other twi error (lost bus arbitration, bus error, ..)
 */
uint8_t TwoWire::twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
	uint8_t i;
	twi_error = TWI_ERRROR_NO_ERROR;
	twi_sendStop = sendStop;

#if defined(__MSP430_HAS_USI__)
	/* Disable START condition interrupt */
	USICTL1 &= ~USISTTIE;
	/* I2C master mode */
	USICTL0 |= USIMST;

#elif defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
    *UCBxCTL1 |= UCSWRST;                     // Enable SW reset
//    UCBxCTL1 |= UCSSEL_2;                    // SMCLK
//    UCBxCTL0 |= (UCMST | UCMODE_3 | UCSYNC); // I2C Master, synchronous mode
    *UCBxCTL1 |= UCTR;                        // Configure in transmit mode
    *UCBxI2CSA = address;                     // Set Slave Address
    *UCBxCTL1 &= ~UCSWRST;                    // Clear SW reset, resume operation
#if defined(__MSP430_HAS_USCI__)
    UCB0I2CIE |= (UCALIE|UCNACKIE|UCSTPIE);  // Enable I2C interrupts
    UC0IE |= UCB0TXIE;                     // Enable I2C interrupts
#else
    *UCBxIE |= (UCALIE|UCNACKIE|UCSTPIE|UCTXIE);  // Enable I2C interrupts
    *UCBxIFG = ~(UCALIE|UCNACKIE|UCSTTIE|UCSTPIE|UCRXIE|UCTXIE);  // Clear I2C interrupt sources
#endif

#elif defined(__MSP430_HAS_EUSCI_B0__)
    UCB0CTLW0 = UCSWRST;                      // Enable SW reset
    UCB0CTLW0 |= (UCMST | UCMODE_3 | UCSSEL__SMCLK | UCSYNC);   // I2C Master, synchronous mode
    UCB0CTLW0 |= UCTR;                        // Configure in transmit mode
    UCB0I2CSA = address;                      // Set Slave Address
    UCB0CTLW0 &= ~UCSWRST;                    // Clear SW reset, resume operation
    UCB0IE |= (UCTXIE0|UCALIE|UCNACKIE|UCSTPIE); // Enable I2C interrupts
#endif
	if(length == 0) {
		return 0;
	}

	/* Ensure data will fit into buffer */
	if(length > TWI_BUFFER_LENGTH){
		return TWI_ERROR_BUF_TO_LONG;
	}


	/* initialize buffer iteration vars */
	twi_masterBufferIndex = 0;
	twi_masterBufferLength = length;

	for(i = 0; i < length; ++i){
		twi_masterBuffer[i] = data[i];
	}

#if defined(__MSP430_HAS_USI__)
	/* build sla+w, slave device address + w bit */
	twi_slarw = 0;
	twi_slarw |= address << 1;

	twi_state = TWI_SND_START;
	/* This will trigger an interrupt kicking off the state machine in the isr */
	USICTL1 |= USIIFG;

#elif defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
	twi_state =  TWI_MTX;                  // Master Transmit mode
	*UCBxCTL1 |= UCTXSTT;                   // I2C start condition

#elif defined(__MSP430_HAS_EUSCI_B0__)
	twi_state =  TWI_MTX;                  // Master Transmit mode
	while (UCB0CTLW0 & UCTXSTP);           // Ensure stop condition got sent
	UCB0CTLW0 |= UCTXSTT;                  // I2C start condition
#endif

	/* Wait for the transaction to complete */
	while(twi_state != TWI_IDLE) {
		__bis_SR_register(LPM0_bits);
	}

#if defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
	/* Ensure stop/start condition got sent before we exit. */
	if(sendStop)
	{
		while (*UCBxCTL1 & UCTXSTP);	// end with stop condition
	}
	else
	{
		while (*UCBxCTL1 & UCTXSTT);	// end with (re)start condition
	}
#endif

	return twi_error;
}

/*
 * Function twi_transmit
 * Desc     fills slave tx buffer with data
 *          must be called in slave tx event callback
 * Input    data: pointer to byte array
 *          length: number of bytes in array
 * Output   1 length too long for buffer
 *          2 not slave transmitter
 *          0 ok
 */
uint8_t TwoWire::twi_transmit(const uint8_t* data, uint8_t length)
{
  uint8_t i;

  twi_state =  TWI_STX;                     // Slave transmit mode

  // ensure data will fit into buffer
  if(TWI_BUFFER_LENGTH < length){
    return 1;
  }
  // set length and copy data into tx buffer
  twi_txBufferLength = length;
  for(i = 0; i < length; ++i){
    twi_txBuffer[i] = data[i];
  }

  return 0;
}

void TwoWire::send_start()
{
#if defined(__MSP430_HAS_USI__)
	USISRL = 0x00;
	USICTL0 |= USIGE+USIOE;
	USICTL0 &= ~USIGE;
	USISRL = twi_slarw;
	USICNT = (USICNT & 0xE0) + 0x08;
#endif
}


// Public Methods //////////////////////////////////////////////////////////////

void TwoWire::begin(void)
{
  rxBufferIndex = 0;
  rxBufferLength = 0;

  txBufferIndex = 0;
  txBufferLength = 0;

  twi_init();
}

void TwoWire::begin(uint8_t address)
{
  twi_setAddress(address);
//  twi_attachSlaveTxEvent(onRequestService);
//  twi_attachSlaveRxEvent(onReceiveService);
  begin();
}

void TwoWire::begin(int address)
{
  begin((uint8_t)address);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop)
{
  // clamp to buffer length
  if(quantity > BUFFER_LENGTH){
    quantity = BUFFER_LENGTH;
  }
  // perform blocking read into buffer
  uint8_t read = twi_readFrom(address, rxBuffer, quantity, sendStop);
  // set rx buffer iterator vars
  rxBufferIndex = 0;
  rxBufferLength = read;

  return read;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

void TwoWire::beginTransmission(uint8_t address)
{
  // indicate that we are transmitting
  transmitting = 1;
  // set address of targeted slave
  txAddress = address;
  // reset tx buffer iterator vars
  txBufferIndex = 0;
  txBufferLength = 0;
}

void TwoWire::beginTransmission(int address)
{
  beginTransmission((uint8_t)address);
}

//
//	Originally, 'endTransmission' was an f(void) function.
//	It has been modified to take one parameter indicating
//	whether or not a STOP should be performed on the bus.
//	Calling endTransmission(false) allows a sketch to 
//	perform a repeated start. 
//
//	WARNING: Nothing in the library keeps track of whether
//	the bus tenure has been properly ended with a STOP. It
//	is very possible to leave the bus in a hung state if
//	no call to endTransmission(true) is made. Some I2C
//	devices will behave oddly if they do not see a STOP.
//
uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
  // transmit buffer (blocking)
  int8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, 1, sendStop);
  // reset tx buffer iterator vars
  txBufferIndex = 0;
  txBufferLength = 0;
  // indicate that we are done transmitting
  transmitting = 0;
  return ret;
}

//	This provides backwards compatibility with the original
//	definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void)
{
  return endTransmission(true);
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(uint8_t data)
{
  if(transmitting){
  // in master transmitter mode
    // don't bother if buffer is full
    if(txBufferLength >= BUFFER_LENGTH){
      setWriteError();
      return 0;
    }
    // put byte in tx buffer
    txBuffer[txBufferIndex] = data;
    ++txBufferIndex;
    // update amount in buffer   
    txBufferLength = txBufferIndex;
  }else{
  // in slave send mode
    // reply to master
    twi_transmit(&data, 1);
  }
  return 1;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
  if(transmitting){
  // in master transmitter mode
    for(size_t i = 0; i < quantity; ++i){
      write(data[i]);
    }
  }else{
  // in slave send mode
    // reply to master
    twi_transmit(data, quantity);
  }
  return quantity;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::available(void)
{
  return rxBufferLength - rxBufferIndex;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::read(void)
{
  int value = -1;
  
  // get each successive byte on each call
  if(rxBufferIndex < rxBufferLength){
    value = rxBuffer[rxBufferIndex];
    ++rxBufferIndex;
  }

  return value;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::peek(void)
{
  int value = -1;
  
  if(rxBufferIndex < rxBufferLength){
    value = rxBuffer[rxBufferIndex];
  }

  return value;
}

void TwoWire::flush(void)
{
  // XXX: to be implemented.
}

// behind the scenes function that is called when data is received
void TwoWire::onReceiveService(uint8_t* inBytes, int numBytes)
{
  // don't bother if user hasn't registered a callback
  if(!user_onReceive){
    return;
  }
  // don't bother if rx buffer is in use by a master requestFrom() op
  // i know this drops data, but it allows for slight stupidity
  // meaning, they may not have read all the master requestFrom() data yet
  if(rxBufferIndex < rxBufferLength){
    return;
  }
  // copy twi rx buffer into local read buffer
  // this enables new reads to happen in parallel
  for(uint8_t i = 0; i < numBytes; ++i){
    rxBuffer[i] = inBytes[i];    
  }
  // set rx iterator vars
  rxBufferIndex = 0;
  rxBufferLength = numBytes;
  // alert user program
  user_onReceive(numBytes);
}

// behind the scenes function that is called when data is requested
void TwoWire::onRequestService(void)
{
  // don't bother if user hasn't registered a callback
  if(!user_onRequest){
    return;
  }
  // reset tx buffer iterator vars
  // !!! this will kill any pending pre-master sendTo() activity
  txBufferIndex = 0;
  txBufferLength = 0;
  // alert user program
  user_onRequest();
}

// sets function called on slave write
void TwoWire::onReceive( void (*function)(int) )
{
  user_onReceive = function;
}

// sets function called on slave read
void TwoWire::onRequest( void (*function)(void) )
{
  user_onRequest = function;
}

void TwoWire::I2C_Usi_handler(void) {
#if defined(__MSP430_HAS_USI__)
		if (!(USICTL0 & USIMST) && (USICTL1 & USISTTIFG)) {
			twi_state = TWI_SL_START;
		}

		switch(twi_state){
		/* Master transmit / receive */
		case TWI_SND_START:
			send_start();
			twi_state = TWI_PREP_SLA_ADDR_ACK;
			break;
		case TWI_PREP_SLA_ADDR_ACK: // reveive (N)ACK
			USICTL0 &= ~USIOE; // SDA = input
			USICNT |= 0x01; // Bit counter=1
			twi_state = TWI_MT_PROC_ADDR_ACK;
			break;
		case TWI_MT_PROC_ADDR_ACK:
			if (USISRL & 0x01) {
				twi_error = TWI_ERROR_ADDR_NACK;
				USICTL0 |= USIOE;
				USISRL = 0x00;
				USICNT |=  0x01;
				twi_state = TWI_EXIT;
				break;
			}

			if(twi_slarw & 1)
				goto mtre;
			else
				goto mtpd;

			break;
		/* Prepare to receive data (N)ACK */
		case TWI_MT_PREP_DATA_ACK:
			/* SDA = input */
			USICTL0 &= ~USIOE;
			/* Bit counter = 1 */
			USICNT |= 0x01;
			twi_state = TWI_MT_PROC_DATA_ACK;
			break;
		case TWI_MT_PROC_DATA_ACK:
	mtpd:
			if (USISRL & 0x01) {
				twi_error = TWI_ERROR_DATA_NACK;
				USICTL0 |= USIOE;
				USISRL = 0x00;
				USICNT |=  0x01;
				twi_state = TWI_EXIT;
				break;
			}

			if(twi_masterBufferIndex == twi_masterBufferLength) {
				USICTL0 |= USIOE;
				USISRL = 0x00;
				USICNT |=  0x01;
				twi_state = TWI_EXIT;
				break;
			}

			USICTL0 |= USIOE;
			USISRL = twi_masterBuffer[twi_masterBufferIndex++];
			USICNT |=  0x08;
			twi_state = TWI_MT_PREP_DATA_ACK;
			break;
		// Master receiver
	mtre:
		case TWI_MR_PREP_DATA_RECV:
			/* SDA input */
			USICTL0 &= ~USIOE;
			/* bit counter = 8 */
			USICNT |=  0x08;
			twi_state = TWI_MR_PROC_DATA_RECV;
			break;
		case TWI_MR_PROC_DATA_RECV:
			/* SDA output */
			USICTL0 |= USIOE;

			twi_masterBuffer[twi_masterBufferIndex++] = USISRL;
			if(twi_masterBufferIndex > twi_masterBufferLength ) {
				USISRL = 0xFF; // that was the last byte send NACK
				twi_state = TWI_MR_PREP_STOP;
			} else {
				USISRL = 0x00; // keep on receiving and send ACK
				twi_state = TWI_MR_PREP_DATA_RECV;
			}

			USICNT |= 0x01;
			break;
		case TWI_MR_PREP_STOP:
			USICTL0 |= USIOE;
			USISRL = 0x00;
			USICNT |=  0x01;
			twi_state = TWI_EXIT;
			break;
		/* All */
		case TWI_EXIT:
			/* Load FF into output shift register */
			USISRL = 0x0FF;
			/* Output latch transparant. MSB of USISR to the SDO pin. */
			USICTL0 |= USIGE;
			/* Latch disabled and make SDA input */
			USICTL0 &= ~(USIGE+USIOE);
			twi_state = TWI_IDLE;
			break;
		case TWI_IDLE:
	                /* Nothing to do. Fall thru and clear interrupt flag. */
		default:
			break;
		}

		/* Clear counter interrupt */
		USICTL1 &= ~USIIFG;

	}
#endif
}

void TwoWire::I2C_Usci_txrx_handler()  // RX/TX Service
{
#if defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
	/* USCI I2C mode. USCI_B0 receive interrupt flag.
	 * UCB0RXIFG is set when UCB0RXBUF has received a complete character. */
#if defined(__MSP430_HAS_USCI__)
	if (UC0IFG & UCB0RXIFG){
#else
	if (*UCBxIFG & UCRXIFG){
#endif
		/* Master receive mode. */
		if (twi_state ==  TWI_MRX) {
			twi_masterBuffer[twi_masterBufferIndex++] = *UCBxRXBUF;
			if(twi_masterBufferIndex == twi_masterBufferLength )
				/* Only one byte left. Generate STOP condition.
				 * In master mode a STOP is preceded by a NACK */
				*UCBxCTL1 |= UCTXSTP;
			if(twi_masterBufferIndex > twi_masterBufferLength ) {
				/* All bytes received. We are idle*/
				__bic_SR_register(LPM0_bits);
				twi_state = TWI_IDLE;
			}
		/* Slave receive mode. (twi_state = TWI_SRX) */
		} else {
			// if there is still room in the rx buffer
			if(twi_rxBufferIndex < TWI_BUFFER_LENGTH){
				// put byte in buffer and ack
				twi_rxBuffer[twi_rxBufferIndex++] = *UCBxRXBUF;
			}else{
				// otherwise nack
				*UCBxCTL1 |= UCTXNACK;   // Generate NACK condition
			}
		}
	}
	/* USCI I2C mode. USCI_B0 transmit interrupt flag.
	 * UCB0TXIFG is set when UCB0TXBUF is empty.*/
#if defined(__MSP430_HAS_USCI__)
	if (UC0IFG & UCB0TXIFG){
#else
	if (*UCBxIFG & UCTXIFG){
#endif
		/* Master transmit mode */
		if (twi_state == TWI_MTX) {
			// if there is data to send, send it, otherwise stop
			if(twi_masterBufferIndex < twi_masterBufferLength){
				// Copy data to output register and ack.
				*UCBxTXBUF = twi_masterBuffer[twi_masterBufferIndex++];
			}else{
				if (twi_sendStop) {
					/* All done. Generate STOP condition and IDLE */
					*UCBxCTL1 |= UCTXSTP;
					twi_state = TWI_IDLE;
					__bic_SR_register(LPM0_bits);
				} else {
					twi_inRepStart = true;  // we're gonna send the START
					// don't enable the interrupt. We'll generate the start, but we
					// avoid handling the interrupt until we're in the next transaction,
					// at the point where we would normally issue the start.
					*UCBxCTL1 |= UCTXSTT;
					twi_state = TWI_IDLE;
					__bic_SR_register(LPM0_bits);
				}
			}
		/* Slave transmit mode (twi_state = TWI_STX) */
		} else {
			// copy data to output register
			*UCBxTXBUF = twi_txBuffer[twi_txBufferIndex++];
			// if there is more to send, ack, otherwise nack
			if(twi_txBufferIndex < twi_txBufferLength){
			}else{
				*UCBxCTL1 |= UCTXNACK;    // Generate NACK condition
			}
		}
	}
#endif
}

void TwoWire::I2C_Usci_state_handler()  // I2C Service
{
#if defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
	/* Arbitration lost interrupt flag */
#if defined(__MSP430_HAS_USCI__)
	if (UCB0STAT & UCALIFG) {
		UCB0STAT &= ~UCALIFG;
#else
	if (*UCBxIFG & UCALIFG) {
		*UCBxIFG &= ~UCALIFG;
#endif
		/* TODO: Handle bus arbitration lost */
	}
	/* Not-acknowledge received interrupt flag.
	 * UCNACKIFG is automatically cleared when a START condition is received.*/
#if defined(__MSP430_HAS_USCI__)
	if (UCB0STAT & UCNACKIFG) {
		UCB0STAT &= ~UCNACKIFG;
#else
	if (*UCBxIFG & UCNACKIFG) {
		*UCBxIFG &= ~UCNACKIFG;
#endif
		*UCBxCTL1 |= UCTXSTP;
		twi_state = TWI_IDLE;
		/* TODO: This can just as well be an address NACK.
		 * Figure out a way to distinguish between ANACK and DNACK */
		twi_error = TWI_ERROR_DATA_NACK;
		__bic_SR_register(LPM0_bits);
	}
	/* Start condition interrupt flag.
	 * UCSTTIFG is automatically cleared if a STOP condition is received. */
#if defined(__MSP430_HAS_USCI__)
	 if (UCB0STAT & UCSTTIFG) {
		UCB0STAT &= ~UCSTTIFG;
#else
	 if (*UCBxIFG & UCSTTIFG) {
		*UCBxIFG &= ~UCSTTIFG;
#endif
		/* UCTR is automagically set by the USCI module upon a START condition. */
		if (*UCBxCTL1 & UCTR) {
			/* Slave TX mode. */
			twi_state =  TWI_STX;
			/* Ready the tx buffer index for iteration. */
			twi_txBufferIndex = 0;
			/* Set tx buffer length to be zero, to verify if user changes it. */
			twi_txBufferLength = 0;
			/* Request for txBuffer to be filled and length to be set. */
			/* note: user must call twi_transmit(bytes, length) to do this */
			onRequestService();
			/* If they didn't change buffer & length, initialize it
			 * TODO: Is this right? Shouldn't we reply with a NACK if there is no data to send? */
			if (0 == twi_txBufferLength) {
				twi_txBufferLength = 1;
				twi_txBuffer[0] = 0x00;
			}
		} else {
			/* Slave receive mode. */
			twi_state =  TWI_SRX;
			/* Indicate that rx buffer can be overwritten and ACK */
			twi_rxBufferIndex = 0;
		}
	}
	/* Stop condition interrupt flag.
	 * UCSTPIFG is automatically cleared when a START condition is received. */
#if defined(__MSP430_HAS_USCI__)
	if (UCB0STAT & UCSTPIFG) {
		UCB0STAT &= ~UCSTPIFG;
#else
	if (*UCBxIFG & UCSTPIFG) {
		*UCBxIFG &= ~UCSTPIFG;
#endif
		if (twi_state ==  TWI_SRX) {
			/* Callback to user defined callback */
			onReceiveService(twi_rxBuffer, twi_rxBufferIndex);
		}
		twi_state =  TWI_IDLE;
	}
#endif
}



void TwoWire::I2C_Eusci_handler(void)
{
#if defined(__MSP430_HAS_EUSCI_B0__)
//	switch(twi_state){
  switch(UCB0IV){
    case USCI_NONE:            // No Interrupt pending
      break;
    case USCI_I2C_UCALIFG:     // USCI I2C Mode: UCALIFG
      // enter slave transmitter mode
      twi_state = TWI_STX;
      // ready the tx buffer index for iteration
      twi_txBufferIndex = 0;
      // set tx buffer length to be zero, to verify if user changes it
      twi_txBufferLength = 0;
      // request for txBuffer to be filled and length to be set
      // note: user must call twi_transmit(bytes, length) to do this
      onRequestService()
      // if they didn't change buffer & length, initialize it
      if(0 == twi_txBufferLength){
        twi_txBufferLength = 1;
        twi_txBuffer[0] = 0x00;
      }
      // transmit first byte from buffer, fall
      // copy data to output register
      UCB0TXBUF = twi_txBuffer[twi_txBufferIndex++];
      // if there is more to send, ack, otherwise nack
      if(twi_txBufferIndex < twi_txBufferLength){
        //twi_reply(1);
      }else{
		UCB0CTLW0 |= UCTXNACK;                // Generate NACK condition
      }
      // leave slave receiver state
      twi_state = TWI_IDLE;

      break;
    case USCI_I2C_UCNACKIFG:   // USCI I2C Mode: UCNACKIFG
        // leave slave receiver state
        twi_state = TWI_IDLE;
		twi_error = TWI_ERROR_DATA_NACK;
        __bic_SR_register_on_exit(CPUOFF); // Exit LPM0
      break;
    case USCI_I2C_UCSTTIFG:    // USCI I2C Mode: UCSTTIFG
		UCB0IFG &= ~UCSTTIFG;
		if (twi_state ==  TWI_IDLE){
			if (UCB0CTLW0 & UCTR){
				twi_state = TWI_STX;      // Slave Transmit mode
				// ready the tx buffer index for iteration
				twi_txBufferIndex = 0;
				// set tx buffer length to be zero, to verify if user changes it
				twi_txBufferLength = 0;
				// request for txBuffer to be filled and length to be set
				// note: user must call twi_transmit(bytes, length) to do this
				onRequestService();
				// if they didn't change buffer & length, initialize it
				if(0 == twi_txBufferLength){
					twi_txBufferLength = 1;
					twi_txBuffer[0] = 0x00;
				}
			}else{
				twi_state =  TWI_SRX;      // Slave receive mode
				// indicate that rx buffer can be overwritten and ack
				twi_rxBufferIndex = 0;
			}
		}
      break;
    case USCI_I2C_UCSTPIFG:    // USCI I2C Mode: UCSTPIFG
        	UCB0IFG &= ~UCSTPIFG;
		if (twi_state ==  TWI_SRX){
			// callback to user defined callback
			onReceiveService(twi_rxBuffer, twi_rxBufferIndex);
		}
		twi_state =  TWI_IDLE; // IDLE mode
		/* Work around for:
		 * If the master does a read and then a write the START interrupt occurs
		 * but the RX interrupt never fires. Clearing bit 4 and 5 of UCB0CTLW0 solves this.
		 * bit 4 and 5 are however marked as reserved in the datasheet.
		 */
		UCB0CTLW0 &= ~0x18;

		__bic_SR_register_on_exit(CPUOFF); // Exit LPM0
      break;
    case USCI_I2C_UCRXIFG3:    // USCI I2C Mode: UCRXIFG3
      break;
    case USCI_I2C_UCTXIFG3:    // USCI I2C Mode: UCTXIFG3
      break;
    case USCI_I2C_UCRXIFG2:    // USCI I2C Mode: UCRXIFG2
      break;
    case USCI_I2C_UCTXIFG2:    // USCI I2C Mode: UCTXIFG2
      break;
    case USCI_I2C_UCRXIFG1:    // USCI I2C Mode: UCRXIFG1
      break;
    case USCI_I2C_UCTXIFG1:    // USCI I2C Mode: UCTXIFG1
      break;
    case USCI_I2C_UCRXIFG0:    // USCI I2C Mode: UCRXIFG0
		UCB0IFG &= ~UCRXIFG;                  // Clear USCI_B0 TX int flag
		if (twi_state ==  TWI_MRX) {      // Master receive mode
			twi_masterBuffer[twi_masterBufferIndex++] = UCB0RXBUF; // Get RX data
			if(twi_masterBufferIndex == twi_masterBufferLength )
				UCB0CTLW0 |= UCTXSTP;  // Generate I2C stop condition
			if(twi_masterBufferIndex > twi_masterBufferLength ) {
				twi_state = TWI_IDLE; //Idle
			} else {
			}
		} else {
			// if there is still room in the rx buffer
			if(twi_rxBufferIndex < TWI_BUFFER_LENGTH){
				// put byte in buffer and ack
				twi_rxBuffer[twi_rxBufferIndex++] = UCB0RXBUF;
			}else{
				// otherwise nack
				UCB0CTLW0 |= UCTXNACK;                // Generate NACK condition
			}
		}
      break;
    case USCI_I2C_UCTXIFG0:    // USCI I2C Mode: UCTXIFG0
		UCB0IFG &= ~UCTXIFG;                  // Clear USCI_B0 TX int flag
		if (twi_state == TWI_MTX) {      // Master receive mode
			// if there is data to send, send it, otherwise stop
			if(twi_masterBufferIndex < twi_masterBufferLength){
				// copy data to output register and ack
				UCB0TXBUF = twi_masterBuffer[twi_masterBufferIndex++];                 // Transmit data at address PTxData
			}else{
			   if (twi_sendStop)
				UCB0CTLW0 |= UCTXSTP;                // Generate I2C stop condition
			   else {
				 twi_inRepStart = true;   // we're gonna send the START
				 // don't enable the interrupt. We'll generate the start, but we
				 // avoid handling the interrupt until we're in the next transaction,
				 // at the point where we would normally issue the start.
				 UCB0CTLW0 |= UCTXSTT;
				 twi_state = TWI_IDLE;
			   }
			}
		} else {
			// copy data to output register
			UCB0TXBUF = twi_txBuffer[twi_txBufferIndex++];
			// if there is more to send, ack, otherwise nack
			if(twi_txBufferIndex < twi_txBufferLength){
			}else{
				UCB0CTLW0 |= UCTXNACK;                // Generate NACK condition
			}
		}
      break;
    case USCI_I2C_UCBCNTIFG:   // USCI I2C Mode: UCBCNTIFG
      break;
    case USCI_I2C_UCCLTOIFG:   // USCI I2C Mode: UCCLTOIFG/
      break;
    case USCI_I2C_UCBIT9IFG:   // USCI I2C Mode: UCBIT9IFG
      break;
	}
#endif
}



// Interrupt handling //////////////////////////////////////////////////////////


#if defined(__MSP430_HAS_USI__)
__attribute__((interrupt(USI_VECTOR)))
void USI_ISR(void)
{
	Wire::I2C_Usi_handler();
}


#elif defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
#if defined(__MSP430_HAS_USCI_B0__)
__attribute__((interrupt(USCI_B0_VECTOR)))
void USCIB0_ISR(void)
{
	/* USCI_B0 I2C state change interrupt. */
	if ((UCB0CTL0 & UCMODE_3) == UCMODE_3 && (UCB0IFG & (UCALIFG | UCNACKIFG | UCSTTIFG | UCSTPIFG)) != 0)
		Wire.I2C_Usci_state_handler();
	/* USCI_B0 I2C TX RX interrupt. */
	if ((UCB0CTL0 & UCMODE_3) == UCMODE_3 && (UCB0IFG & (UCTXIFG | UCRXIFG)) != 0)
		Wire.I2C_Usci_txrx_handler();
}
#endif
#if defined(__MSP430_HAS_USCI_B1__)
__attribute__((interrupt(USCI_B1_VECTOR)))
void USCIB1_ISR(void)
{
	/* USCI_B1 I2C state change interrupt. */
	if ((UCB1CTL0 & UCMODE_3) == UCMODE_3 && (UCB1IFG & (UCALIFG | UCNACKIFG | UCSTTIFG | UCSTPIFG)) != 0)
		Wire1.I2C_Usci_state_handler();
	/* USCI_B1 I2C TX RX interrupt. */
	if ((UCB1CTL0 & UCMODE_3) == UCMODE_3 && (UCB1IFG & (UCTXIFG | UCRXIFG)) != 0)
		Wire1.I2C_Usci_txrx_handler();
}
#endif

#elif defined(__MSP430_HAS_EUSCI_B0__)
__attribute__((interrupt(USCI_B0_VECTOR)))
void USCI_B0_ISR(void)
{
	Wire.I2C_Eusci_handler();
}
#endif


// Preinstantiate Objects //////////////////////////////////////////////////////

TwoWire Wire = TwoWire(0, TWISCL_SET_MODE, TWISDA_SET_MODE, TWISCL, TWISDA);
#if defined(__MSP430_HAS_USCI_B1__)
TwoWire Wire1 = TwoWire(1, TWISCL_SET_MODE1, TWISDA_SET_MODE1, TWISCL2, TWISDA2);
#endif
