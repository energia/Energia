-stack    0x2000                /* PRIMARY STACK SIZE    */
-sysstack 0x1000                /* SECONDARY STACK SIZE  */
-heap     0x6400                /* HEAP AREA SIZE        */  

MEMORY
{
  PAGE 0:
    VEC(RWX)	  : origin = 0000100h length = 000200h
    DATA0(RWX)    : origin = 0000300h length = 05D00h 
    DATA1(RWX)    : origin = 0006000h length = 0A000h 
    SARAM0(RX)    : origin = 0010000h length = 038000h            
    SARAM1(RW)    : origin = 0048000h length = 002000h  
    SARAM2(RW)    : origin = 004A000h length = 002000h  
    SARAM3(RW)    : origin = 004C000h length = 002000h  
    
}

SECTIONS
{
  vectors       : > VEC ALIGN = 256
  .text         : > SARAM0 ALIGN = 4
  .data         : > SARAM0 
  .cinit        : > SARAM0 
  .switch       : > SARAM0
  .stack        : > DATA1 
  .sysstack     : > DATA1 
  .bss          : > SARAM0 , fill =0 
  .sysmem       : > DATA1
  .const        : > SARAM0
  .cio	        : > SARAM0
  USB_buffer1   : > SARAM1
  USB_buffer2   : > SARAM2 
  USB_buffer3   : > SARAM3 , fill =0   
  
  GROUP: align(32)
  {
	.const:twiddle32
       	.const:twiddle
	audio_buffers
	fft_buf
	
  } > DATA0
}
