/*
  IO expander Interrupt Example

  Configures interrupt for IO expander and waits for the interrupt
  on IO expander pins. Interrupt on IO expander can be generated
  by changing the DIP switch states on SW1.

  Note: This demo is specific for C5535 DSP shield.
  May not work/compile for other platforms
*/

/* Variable to indicate that the interrupt has occurred  */
volatile int intr_flag = 0;

unsigned int cmd[2];
unsigned int readBuf[2];
int          status;
unsigned int bytesAvail;
unsigned int pinNum;
unsigned int pinVal;

/*
 * ISR that clears the interrupt status and disables it, finally informs
 * the setup() API that DMA transfer has completed for the current DMA channel
 */
interrupt void INT1_isr(void)
{
    CSL_CPU_REGS->IFR0 = CSL_CPU_REGS->IFR0;
    disableInterrupt(INTERRUPT_INT1);
    intr_flag = 1;
}

void setup()
{
    // Configure the state of pins to output
    pinMode(E3, OUTPUT);
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
    pinMode(E0, OUTPUT);

    // Configure IO pins as input 
    for (pinNum = IO0; pinNum <= IO9; pinNum++)
    {
        pinMode(pinNum, INPUT);
    }

    // Configure DIP switch pins as input
    pinMode(SW1, INPUT);
    pinMode(SW2, INPUT);
    pinMode(SW3, INPUT);
    pinMode(SW4, INPUT);

    // Init interrupt module
    initInterrupt(0x0000);

    // Plugin the ISR to vector table and enbale interrupts 	
    attachInterrupt(INTERRUPT_INT1, (INTERRUPT_IsrPtr)INT1_isr, 0);    
    enableInterrupt(INTERRUPT_INT1);

    Serial.print("Change any DIP switch state on SW1 to generate interrupt!\n");
}

void loop()
{
    if (intr_flag == 1)
    {
        Serial.print("\nINT1 Interrupt is triggered!!\n");
        intr_flag = 0;

        // Read all the input pin values to clear the intterupts
        for (pinNum = IO0; pinNum <= IO9; pinNum++)
        {
            pinVal = digitalRead(pinNum);
        }

        pinVal = digitalRead(SW1);
        pinVal = digitalRead(SW2);
        pinVal = digitalRead(SW3);
        pinVal = digitalRead(SW4);

        Serial.print("All the IO Expander Input pins are read\n");
        Serial.print("Change any DIP switch state on SW1 to generate interrupt!\n");
        delay(1000);
        enableInterrupt(INTERRUPT_INT1);
    }
}