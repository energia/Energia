//
//  Sharp BoosterPackLCD SPI
//  Example for library for Sharp BoosterPack LCD 96 and 128 with hardware SPI
//
//
//  Author :  StefanSch
//  Date   :  Mar 05, 2015
//  Version:  1.04
//  File   :  LCD_SharpBoosterPack_SPI_main.h
//
//  Based on the LCD5110 Library
//  Created by Rei VILO on 28 May 2012
//  Copyright (c) 2012 http://embeddedcomputing.weebly.com
//  Licence CC = BY SA NC
//
//  Edited 11 Jul 2015 by ReiVilo
//  Added setOrientation(), setReverse() and flushReverse()
//  Unchanged #include <OneMsTaskTimer.h>
//
//  Edited 15 Oct 2018 by ReiVilo
//  Added support for Sharp 128 with minimal change
//  Added flushReversed() for reversed display and preserved buffer
//
//  Edited 2019-03-19 by StefaSch
//  Added support for smaller memory with put LCD data to FRAM
//
//  Edited 2020-05-02 by StefanSch
//  Added support for CC13xx to support low power consuption
//  Added powerSave() function
//  Replaced OneMsTimer with RTOS function if available
//

#ifndef LCD_SharpBoosterPack_SPI_h
#define LCD_SharpBoosterPack_SPI_h

#include "Energia.h"
#include "Terminal6.h"
#include "Terminal12.h"
#include <SPI.h>
#if !defined(ti_sysbios_BIOS___VERS)
#include <OneMsTaskTimer.h>
#endif
#include <Print.h>

#define SHARP_96 96
#define SHARP_128 128

typedef enum
{
    LCDWrapNone,                         // do not wrap
    LCDWrapLine,                         // wrap, to beginning of line
    LCDWrapNextLine                      // wrap, to next line
}
tLCDWrapType;

#define NUM_OF_FONTS 2
typedef uint8_t tNumOfFontsType;

typedef enum
{
    LCDPowerSaveOff,                    // normal operation mode
    LCDPowerSaveOn,                     // power save mode enalbed
}
tLCDPowerModeType;


///
/// @brief      Class for Sharp Memory Display BoosterPack
/// @details    The screen uses a buffer.
/// @note       The class doesn't manage touch.
///
class LCD_SharpBoosterPack_SPI : public Print
{
  public:
    ///
    /// @brief	Constructor
    /// @note   For Sharp Memory LCD BoosterPack
    /// @param  model default=SHARP_96 for compatibility, SHARP_128
    /// @code
    ///     LCD_SharpBoosterPack_SPI myScreen(SHARP_96);
    /// @endcode
    ///
    LCD_SharpBoosterPack_SPI(uint8_t model = SHARP_96);

    ///
    /// @brief	Constructor with selected pins
    /// @param	pinChipSelect SPI chip select
    /// @param	pinDISP Display pin
    /// @param	pinVCC VCC pin
    /// @param  model default=SHARP_96 for compatibility, SHARP_128
    ///
    /// @note   For SensorTag CC2650
    /// @code
    ///     LCD_SharpBoosterPack_SPI myScreen(7, 10, 1, SHARP_96);
    ///     LCD_SharpBoosterPack_SPI myScreen(7, 10, 1, true, SHARP_128);
    /// @endcode
    ///
    LCD_SharpBoosterPack_SPI(uint8_t pinChipSelect, uint8_t pinDISP, uint8_t pinVCC, uint8_t model = SHARP_96);
    LCD_SharpBoosterPack_SPI(uint8_t pinChipSelect, uint8_t pinDISP, uint8_t pinVCC, bool autoVCOM, uint8_t model = SHARP_96);

    ///
    /// @brief	Initialise the screen
    ///
    void begin();

    ///
    /// @brief	Stop screen access
    ///
    void end();

    ///
    /// @brief	Return a Who Am I string
    /// @return	Who Am I string
    ///
    String WhoAmI();

    ///
    /// @brief	Clear the screen
    ///
    void clear();

    ///
    /// @brief	Clear the buffer
    ///
    void clearBuffer();

    ///
    /// @brief	Set the orientation
    /// @param	orientation 0=0°, 1=90°, 2=180°, 3=-90°
    /// @note   Screen initialised at 0=0°.
    ///
    void setOrientation(uint8_t orientation = 0);

    ///
    /// @brief	Set the reverse mode
    /// @param	reverse false=silver on white, default=true=white on silver
    /// @note   Screen initialised with false=silver on white.
    ///
    void setReverse(bool reverse = true);

    ///
    /// @brief	Reverse and display the screen
    /// @deprecated Use flushReversed() instead
    /// @note   reverseFlush() alters the buffer
    ///
    void reverseFlush();

    ///
    /// @brief	Set the font
    /// @param	font default=0, 0..1
    ///
    void setFont(tNumOfFontsType font = 0);

    ///
    /// @brief    Get size àf the screen
    /// @return   96 for 96x96 or &28 for 128x128
    ///
    uint8_t getSize();

    ///
    /// @brief    PowerSave mode. Disables the SPI module and enalbes/disables it for any following transfer
    /// @return   -
    ///
    void powerSave(tLCDPowerModeType);


    void setLineSpacing(uint8_t pixel);
    void setXY(uint8_t x, uint8_t y, uint8_t ulValue);
    //void text(uint8_t x, uint8_t y, String s);
    void text(uint8_t x, uint8_t y, String s, tLCDWrapType wrap = LCDWrapNextLine);
    void text(uint8_t x, uint8_t y, uint8_t c) ;
    
    ///
    /// @brief  Send to buffer to the screen
    /// @note   flush() preserves the buffer
    ///
    void flush();

    ///
    /// @brief  Send to buffer to the screen with reversed colours
    /// @note   flushReversed() preserves the buffer
    ///
    void flushReversed();

    void setCharXY(uint8_t x, uint8_t y);
    void drawImage(const uint8_t * image, uint8_t x, uint8_t y);

    virtual size_t write(uint8_t c);
    //virtual size_t write(const uint8_t *buffer, size_t size);

    using Print::write; // pull in write(str) and write(buf, size) from Print

  private:
    uint16_t _index(uint8_t x, uint8_t y);
    tNumOfFontsType _font;
    void LCD_enableVCOMToggle();
    void LCD_turnOff();
    uint8_t _orientation;
    bool _reverse;
};
#endif

