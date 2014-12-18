/*
  Direct Memory Access
  Configures all the DMA channels for data transfer.
  Data in the source buffer is copied into the destination buffer.
  DMA is configured with proper source and destination address and data length.
  Configured values are read back and are verified with the original values.
*/

#define DMA_BUFFER_SIZE    (512u)

/* Variables to store Source and Destination buffer addresses used during DMA
   transfers */
unsigned short *dmaSRCBuff = NULL;
unsigned short *dmaDESTBuff = NULL;

void setup()
{
    DMAConfig      dmaConfig;
    int            status;
    unsigned short chanNumber;
    unsigned short index;

    dmaSRCBuff  = NULL;
    dmaDESTBuff = NULL;

    /* DMA.dmaInit() creates DMA data buffers and initializes the config buffer
     * The DMA.dmaInit() API will initialize the config structure passed to it
     * with the default config values
     */
    DMA.dmaInit(&dmaConfig, DMA_BUFFER_SIZE);

    dmaSRCBuff  = dmaConfig.srcAddr;
    dmaDESTBuff = dmaConfig.destAddr;

    /* Initialize DMA */
    DMA.init();

    Serial.print("\n Initiating DMA data transfer on different channels\n");

    /* Test all the DMA channels by opening each of the channels, configuring
     * them to transfer data from 'dmaSRCBuff' and 'dmaDESTBuff' buffers.
     * Once the DMA transfer completes compare the source and
     * destination buffer contents
     */
    for (chanNumber = 0; chanNumber < DMA_CHANNEL_MAX; chanNumber++)
    {
        /* Initialize the DMA Source and Destination buffers */
        for (index = 0; index < DMA_BUFFER_SIZE; index++)
        {
            dmaSRCBuff[index]  = index;
            dmaDESTBuff[index] = 0x0000;
        }

        Serial.print("\n Buffer transfer using DMA Channel No :\t");
        Serial.print(chanNumber);

        /* Opens the respective DMA channel */
        status = DMA.openChannel(chanNumber);
        if (status != 0)
        {
            break;
        }

        /* Configure the respective DMA channel */
        status = DMA.configChannel(chanNumber, dmaConfig);
        if (status != 0)
        {
            break;
        }

        /* Start DMA transfer for the respective DMA channel */
        status = DMA.start(chanNumber);
        if (status != 0)
        {
            break;
        }

        /* Wait for the respective DMA transfer to complete */
        while(DMA.getStatus(chanNumber));

        /* Close the respective DMA channel */
        status = DMA.closeChannel(chanNumber);
        if (status != 0)
        {
            break;
        }

        for(index = 0; index < DMA_BUFFER_SIZE; index++)
        {
            if(dmaSRCBuff[index] != dmaDESTBuff[index])
            {
                Serial.print("Buffer miss matched at position");
                Serial.print(index);
                break;
            }
        }

        /* When index will be equal to DMA_BUFFER_SIZE, then both the source
           and destination buffers would have matched */
        if (index == DMA_BUFFER_SIZE)
        {
            Serial.print(" Success");
        }
    }

    DMA.dmaDeInit(&dmaConfig);
}

void loop()
{
}
