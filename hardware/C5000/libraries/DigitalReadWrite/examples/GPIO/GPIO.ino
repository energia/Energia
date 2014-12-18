/*
  GPIO Read Write
  Configures GPIO12 as input pin and GPIO13 as output pin.
  Both the GPIO pins (pin16 and pin18 on P2)need to be shorted to check the
  functionality of the module. Set/Reset the output pin(GPIO13) P2 pin16 and
  read the value of input pin (GPIO12) P2 pin18 and compare both values. If
  both the values match, then the test passes.
*/

void setup()
{
    int status;

    Serial.println("GPIO Pin Configuration Demo");
    Serial.println("Short pin16 and pin18 on port P2 for the test");

    /* Set mode for GPIO12 and GPIO13 - This configures the Pin Muxing to
     * enable the GPIO pins. The system consists of pins that will be
     * multiplexed between various peripherals, hence configure the system to
     * multiplex those pins and enable GPIO pins.
     */
    gpioSelectMode(DSP_GPIO12);
    gpioSelectMode(DSP_GPIO13);

    // Configure GPIO12 as input pin
    status = gpioPinMode(DSP_GPIO12, INPUT);
    if(status == 0)  // Returns 0 on success
    {
        // Configure GPIO13 as output pin
        gpioPinMode(DSP_GPIO13, OUTPUT);
    }
}

/*
 * This API continuosly sets the pin value of DSP_GPIO13 pin high and low one
 * after another. Since DSP_GPIO12 is configured as input pin and DSP_GPIO13
 * is configured as output pin. Value written to DSP_GPIO13 pin should be
 * sent to DSP_GPIO12 pin, if DSP_GPIO13 and DSP_GPIO12 pins are
 * shorted externally
 */
void loop()
{
    unsigned int gpioState;

    /* DSP_GPIO12 is configured as input pin, whereas DSP_GPIO13 is configured
     * as output pin. Value written to DSP_GPIO13 pin will be sent to
     * DSP_GPIO12 pin, since DSP_GPIO13 and DSP_GPIO12 pins are shorted
     */

    /* GPIO set test - Sets GPIO pin value to high */
    gpioWrite(DSP_GPIO13, HIGH); /* set the output pin value (GPIO13) */

    /* Read the input pin value (GPIO12). gpioRead() will return the pin value
       of the requested pin, if its in 'high' state returns 1, else returns 0
       for low state */
    gpioState = gpioRead(DSP_GPIO12);
    if (gpioState == HIGH)
    {
        Serial.println("\r\nSetting GPIO Pin as High is Successful");
    }
    else
    {
        Serial.println("\r\nSetting GPIO Pin as High Failed");
    }

    delaySeconds(1);  // wait for a second

    /* GPIO reset test - Sets GPIO pin value to low */
    gpioWrite(DSP_GPIO13, LOW); /* set the output pin value (GPIO13) */

    /* Read the input pin value (GPIO12) */
    gpioState = gpioRead(DSP_GPIO12);
    if (gpioState == LOW)
    {
        Serial.println("Setting GPIO Pin as Low is Successful  ");
    }
    else
    {
        Serial.println("Setting GPIO Pin as Low Failed  ");
    }

    delaySeconds(1);  // wait for a second
}
