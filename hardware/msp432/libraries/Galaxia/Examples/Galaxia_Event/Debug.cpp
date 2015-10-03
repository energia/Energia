//
// file		Debug.cpp
// brief	Header
// details	Basic debugger with format and variables
//
// Project LCD_screen_115
// Developed with [embedXcode+](http://embedXcode.weebly.com)
//
// author		Rei Vilo
// author		http://embeddedcomputing.weebly.com
//
// date		Feb 02, 2014
// version	101
//
// copyright	(c) Rei Vilo, 2010-2015
// copyright	All rights reserved
//
// see		ReadMe.txt for references
//



#include "Debug.h"

// Debug utility
// Declare the port for be used by //debug()
Stream * debugPort = &Serial;

void debug(const char * format, ... )
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    debugPort->print(buffer);
    va_end(args);
}

void debugln(const char * format, ... )
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    debugPort->println(buffer);
    va_end(args);
}

