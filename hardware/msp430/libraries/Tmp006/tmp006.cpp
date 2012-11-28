/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

/*******************************************************************************
 *
 * tmp006.c -Energia Library for TMP006 Module.
 *
 *  Yining Yang
 *  Texas Instruments Inc.
 *  November 2012
 *  Built with CCE Version: 5.2.1 and IAR Embedded Workbench Version: 6.4
 ******************************************************************************/

#include "tmp006.h"

/*******************************************************************************
 *
 * USER LEVEL LIBRARY CALLS
 *
 ******************************************************************************/

/*!
 * PRINT FUNCTION
 *			 
 * Prints the temperature to Energia's serial monitor 
 *
 * @param  Print_structure 
 *          Enable - Prints temp structure data (can be used for debugging)
 *			Disable - Prints just temperature 
 *
 * @return   None
 *
 */
void Print_Temp(char Print_structure)

{
    /*Intialize Serial line for serial printing*/
    Serial.begin(9600);
    
	TempReading tempstruct = Get_Temp_data();
	float temperature = tempstruct.temp;
	signed int RawV = tempstruct.vObj;
	signed int RawT = tempstruct.tDie;
	float tempkel = tempstruct.tDie_K;
	float tempvolt = tempstruct. vObj_V;
	int i;

	
	if (Print_structure)
	{
		Serial.print ("The temperature in celsius is: ");
		Serial.println (temperature);
		Serial.print ("The raw value from Volt register is: ");
		Serial.println (RawV);
		Serial.print ("The raw value from the Temp register is: ");
		Serial.println (RawT);
		Serial.println (" ");
        
    /* We need some sort of delay for the serial monitor of Eneriga to work with serial.print
     or else garbage data results */
         for (i = 0; i <100; i++)
        {
            __delay_cycles(50000);
        }
    }
	else 
	{
		Serial.println(temperature);
    
     for (i = 0; i <50; i++)
        {
            __delay_cycles(50000);
        }
	}
	    
}


 /*!
 * INITIALIZATION FUNCTION
 * Initializes the TMP006 and sets up I2C for operation.
 *
 * The temperature sensor is initialized with DRDY enabled.
 * Address pins are selected as ADR1 = 0 & ADR0 = 0.
 * The MSP430 is in master synchronous mode with BRCLK = 100khz
 *
 * @param Total_samples: Total number of averaged samples
 *                       \b One \n
 *                       \b Two  \n
 *                       \b Four \n
 *                       \b Eight \n
 *                       \b Sixteen  \n
 *
 * @return None
 */
void TMP006_Init(unsigned int Total_samples)
{	
    // Initialize Wire
    Wire.begin();
    // Reset TMP006 
    Write_toTMP(Config_REG, Reset);
    // Configure TMP006 for initialization 
    Write_toTMP(Config_REG, Power_Up + Total_samples + Conversion_BitEN);
    	
}


/*!
 * SLEEP FUNCTION
 * Wakes up TMP006 from power down mode without reconfiguration.
 *
 * @param None
 *
 * @return None
 *
 */
void TMP006_Wakeup(void)
{
    unsigned int current_settings;

    // Read and save current settings 
    current_settings = Read_fromTMP(Config_REG);
    // Power-up TMP006 with current settings*/
    current_settings |= Power_Up;
    // Writes to Config register*/
    Write_toTMP(Config_REG, current_settings);
}
	

 /*!
 * WAKEUP FUNCTION
 * Disables TMP006 by putting it into power down mode.
 *
 * @param None
 *
 * @return None
 *
 */
void TMP006_Sleep(void)
{
    unsigned int settings;

    /* Read current settings */
    settings = Read_fromTMP(Config_REG);
    /* Mask out and power down TMP006 */
    settings &= ~(Power_Up);
    /* Power down TMP006 */
    Write_toTMP(Config_REG, settings);
}


 /*******************************************************************************
 *
 * LOWER LEVEL LIBRARY CALLS
 * Allows for more customization, most new users will have no need to  directly 
 * use or configure any of the following code
 * These functions are called on by user level library calls
 *
 ******************************************************************************/   
 
    
/*!
 * READY FUNCTION
 * Function to poll and check if object voltage and ambient temperature results are ready to read.
 *
 * @param None
 *
 * @return \b 0 \b - Data not ready \n
 *         \b 1 \b - Data is ready
 *
 */
unsigned char Ready(void)
{
    /* Read DRDY status from Config register */
     if (Conversion_Done & Read_fromTMP(Config_REG))
        return 1;
     else
        return 0;
}


/*!
 * TEMPERATURE DATA FUNCTION
 * Function to calculate and return the temperature and raw values from TMP006
 * sensor.
 *
 * @param None
 *
 * @return TempReading structure
 *
 */
 TempReading Get_Temp_data(void)
{
     TempReading tempRead;

    /* When the data is ready. */
 	while(!Ready());
	/*Read the object voltage */
	tempRead.vObj = Read_fromTMP(Volt_REG);
	/* Read the ambient temperature */
	tempRead.tDie = Read_fromTMP(Temp_REG);
	/*Calculate the temperature in Kelvin */
	tempRead.tDie_K = ((float)(tempRead.tDie>>2) *.03125) + 273.15;
	/*Calculate the Voltage in volts*/
	tempRead.vObj_V = (float)(tempRead.vObj) * .00000015625;
	/*Calculate the Temperature with corrections in Celsius*/
	tempRead.temp = Calculate_Temp(&tempRead.tDie_K, &tempRead.vObj_V);

    return tempRead;
}



/*!
 * TEMPERATURE CALCULATION FUNCTION
 * Function to calculate temperature based on tdie and vobj
 *
 * @param tDie temperature of the die in Kelvin
 * @param vObj object in Volts
 *
 * @return temperature value in Celsius
 *
 */
float Calculate_Temp(float *tDie_K, float *vObj_V)

{
    /* Calculate TMP006. This needs to be reviewed and calibrated by TMP group */
	float S0 = 6e-14;       /* Default S0 cal value */
	float a1 = 1.75e-3;
	float a2 = -1.678e-5;
	float b0 = -2.94e-5;
	float b1 = -5.7e-7;
	float b2 = 4.63e-9;
	float c2 = 13.4;
	float Tref = 298.15;
      
    //float correctedtemp = *tDie_K - Tref;
    float S = S0*(1+a1*(*tDie_K - Tref)+a2*(*tDie_K - Tref)*(*tDie_K - Tref));
    float Vos = b0 + b1*(*tDie_K - Tref) + b2*(*tDie_K - Tref)*(*tDie_K - Tref);
    
    //float correctedvolt = *vObj_V - Vos;
    float fObj = *vObj_V - Vos + c2*(*vObj_V - Vos)*(*vObj_V - Vos);
	float Tobj = sqrt(sqrt(((*tDie_K)*(*tDie_K)*(*tDie_K)*(*tDie_K)) + (fObj/S)));
    
    
    
    return (Tobj - 273.15);
}


/*!
 * READ FROM TMP006 FUNCTION
 * Reads data out of the TMP006 in I2C Master Mode.
 * Uses functions in the Wire library
 *
 * @param Register is the name of the register you are reading from
 *
 *
 * @return Int value of Register
 *
 */
unsigned int Read_fromTMP(unsigned char Register)
{
    unsigned int value;
    
    /* Begin Tranmission at address of device on bus */
	Wire.beginTransmission(ADR1_0_ADR0_0);	  	
	/* Send Pointer Register Byte */
    Wire.write(Register);	
    /* Sends Stop */
	Wire.endTransmission();					
     /* Requests 2 bytes fron Slave */
	Wire.requestFrom(ADR1_0_ADR0_0, 2);			
     /* Wait Until 2 Bytes are Ready*/
	while(Wire.available() < 2)	{}			
	
    /* Read*/
    value = Wire.read();  
	value = value << 8;    
	value|= Wire.read(); 
	
    
    return value;
}


/*!
 * WRITE TO TMP006 FUNCTION
 * Writes data to TMP006 via I2C
 * Uses functions in the Wire library
 *
 * @param pointer is the base address of the I2C Master module.
 * @param writeByte is the bytes you want to be written.
 *
 * This function transmit data to TMP006 via the pointer and data to be
 * transmitted.
 *
 * @return None.
 *
 */
void Write_toTMP(unsigned char Register, unsigned int writeByte)
{
    /* Begin Tranmission at address of device on bus */
	Wire.beginTransmission(ADR1_0_ADR0_0);				
	/* Send Pointer Register Byte */
	Wire.write(Register);			
    /* Read*/
	Wire.write((unsigned char)(writeByte>>8));        
	Wire.write((unsigned char)(writeByte&0x00FF));   	
    /* Sends Stop */
	Wire.endTransmission();	

}
