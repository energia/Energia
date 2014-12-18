extern "C" {
  #include "ezdsp5535_lcd.h"
}
int oled_test()
{
	Int16 i;
	Uint16 cmd[10];    // For multibyte commands
	
	/* Initialize OLED display */
    EZDSP5535_OSD9616_init( );
    
    EZDSP5535_OSD9616_send(0x00,0x2e);  // Deactivate Scrolling
    
    
    /* Fill page 0 */ 
    EZDSP5535_OSD9616_send(0x00,0x00);   // Set low column address
    EZDSP5535_OSD9616_send(0x00,0x10);   // Set high column address
    EZDSP5535_OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
    for(i=0;i<128;i++)
    {
    	EZDSP5535_OSD9616_send(0x40,0xff);
    }
    /* Write to page 0 */
    EZDSP5535_OSD9616_send(0x00,0x00);   // Set low column address
    EZDSP5535_OSD9616_send(0x00,0x10);   // Set high column address
    EZDSP5535_OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
    for(i=0;i<22;i++)
    {
    	EZDSP5535_OSD9616_send(0x40,0x00);  // Spaces
    }
    EZDSP5535_OSD9616_printLetter(0x32,0x49,0x49,0x26);  // S
    EZDSP5535_OSD9616_printLetter(0x01,0x7F,0x01,0x01);  // T
    EZDSP5535_OSD9616_printLetter(0x7F,0x30,0x0E,0x7F);  // N
    EZDSP5535_OSD9616_printLetter(0x41,0x49,0x49,0x7F);  // E
    EZDSP5535_OSD9616_printLetter(0x7F,0x06,0x06,0x7F);  // M
    EZDSP5535_OSD9616_printLetter(0x3F,0x40,0x40,0x3F);  // U
    EZDSP5535_OSD9616_printLetter(0x46,0x29,0x19,0x7F);  // R
    EZDSP5535_OSD9616_printLetter(0x01,0x7F,0x01,0x01);  // T
    EZDSP5535_OSD9616_printLetter(0x32,0x49,0x49,0x26);  // S
    EZDSP5535_OSD9616_printLetter(0x7F,0x30,0x0E,0x7F);  // N
    EZDSP5535_OSD9616_printLetter(0x00,0x7F,0x00,0x00);  // I
    for(i=0;i<5;i++)
    {
    	EZDSP5535_OSD9616_send(0x40,0x00);  // Spaces
    }
    EZDSP5535_OSD9616_printLetter(0x32,0x49,0x49,0x26);  // S
    EZDSP5535_OSD9616_printLetter(0x7C,0x09,0x0A,0x7C);  // A
    EZDSP5535_OSD9616_printLetter(0x63,0x1C,0x1C,0x63);  // X
    EZDSP5535_OSD9616_printLetter(0x41,0x49,0x49,0x7F);  // E
    EZDSP5535_OSD9616_printLetter(0x01,0x7F,0x01,0x01);  // T    
    
    for(i=0;i<23;i++)
    {
    	EZDSP5535_OSD9616_send(0x40,0x00);  // Spaces
    }
    /* Fill page 1*/ 
    EZDSP5535_OSD9616_send(0x00,0x00);   // Set low column address
    EZDSP5535_OSD9616_send(0x00,0x10);   // Set high column address
    EZDSP5535_OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    for(i=0;i<128;i++)
    {
    	EZDSP5535_OSD9616_send(0x40,0xff);
    }
    
    /* Write to page 1*/ 
    EZDSP5535_OSD9616_send(0x00,0x00);   // Set low column address
    EZDSP5535_OSD9616_send(0x00,0x10);   // Set high column address
    EZDSP5535_OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    for(i=0;i<46;i++)
    {
    	EZDSP5535_OSD9616_send(0x40,0x00);
    }
    
   	EZDSP5535_OSD9616_printLetter(0x06,0x09,0x09,0x7F);  // P
    EZDSP5535_OSD9616_printLetter(0x32,0x49,0x49,0x26);  // S
    EZDSP5535_OSD9616_printLetter(0x3E,0x41,0x41,0x7F);  // D	
    EZDSP5535_OSD9616_printLetter(0x43,0x4D,0x51,0x61);  // Z
    EZDSP5535_OSD9616_printLetter(0x10,0x58,0x58,0x30);  // e
    for(i=0;i<5;i++)
    {
    	EZDSP5535_OSD9616_send(0x40,0x00);  // Spaces
    }
    EZDSP5535_OSD9616_printLetter(0x31,0x49,0x49,0x2F);  // 5
   	EZDSP5535_OSD9616_printLetter(0x36,0x49,0x49,0x22);  // 3
    EZDSP5535_OSD9616_printLetter(0x31,0x49,0x49,0x2F);  // 5
   	EZDSP5535_OSD9616_printLetter(0x31,0x49,0x49,0x2F);  // 5
    EZDSP5535_OSD9616_printLetter(0x22,0x41,0x41,0x3E);  // C

    for(i=0;i<47;i++)
    {
    	EZDSP5535_OSD9616_send(0x40,0x00);       // Spaces
    }

    EZDSP5535_OSD9616_send(0x00,0x2e);  // Deactivate Scrolling
    
    /* Set vertical and horizontal scrolling */
    cmd[0] = 0x00;
    cmd[1] = 0x29;  // Vertical and Right Horizontal Scroll
    cmd[2] = 0x00;  // Dummy byte
    cmd[3] = 0x00;  // Define start page address
    cmd[4] = 0x03;  // Set time interval between each scroll step
    cmd[5] = 0x01;  // Define end page address
    cmd[6] = 0x01;  // Vertical scrolling offset
    EZDSP5535_OSD9616_multiSend( cmd, 7 );
    EZDSP5535_OSD9616_send(0x00,0x2f);
    
    /* Keep first 8 rows from vertical scrolling  */
    cmd[0] = 0x00;
    cmd[1] = 0xa3;  // Set Vertical Scroll Area
    cmd[2] = 0x08;  // Set No. of rows in top fixed area
    cmd[3] = 0x08;  // Set No. of rows in scroll area
    EZDSP5535_OSD9616_multiSend( cmd, 4 );

	return 0;
}

void setup() {
    oled_test( );
}

void loop() {

}
