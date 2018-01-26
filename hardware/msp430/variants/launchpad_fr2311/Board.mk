######################################
# Board specific
ARCH = msp430
MCU = msp430fr2311
MCU_FLAG = -mmcu=$(MCU)
F_CPU = 16000000L
FLASH_SIZE = 3840
UPLOAD_COMMAND = $(MSPDEBUG) $(VERBOSE_UPLOAD) tilib --force-reset "prog build/$(SKETCH_NAME).bin"
######################################
