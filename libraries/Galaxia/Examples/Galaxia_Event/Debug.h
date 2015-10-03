///
/// @file		Debug.h
/// @brief		Header
/// @details	Basic debugger with format and variables
/// @n	
/// @n @b		Project LCD_screen_115
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
/// 
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
///
/// @date		Feb 02, 2014
/// @version	101
/// 
/// @copyright	(c) Rei Vilo, 2010-2015
/// @copyright	All rights reserved
///
/// @see		ReadMe.txt for references
///


// Core library - IDE-based
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad MSP430 G2 and F5529, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#elif defined(MICRODUINO) // Microduino specific
#include "Arduino.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

#ifndef debug_h
#define debug_h

#include "stdarg.h"

/// int printf ( const char * format, ... );
///
/// A format specifier follows this prototype:
/// %[flags][width][.precision][length]specifier

/// Where the specifier character at the end is the most significant component, since it defines the type and the interpretation of its corresponding argument:
/// @b specifier	Output	Example
/// *   d or i	Signed decimal integer	392
/// *   u	Unsigned decimal integer	7235
/// *   o	Unsigned octal	610
/// *   x	Unsigned hexadecimal integer	7fa
/// *   X	Unsigned hexadecimal integer (uppercase)	7FA
/// *   f	Decimal floating point, lowercase	392.65
/// *   F	Decimal floating point, uppercase	392.65
/// *   e	Scientific notation (mantissa/exponent), lowercase	3.9265e+2
/// *   E	Scientific notation (mantissa/exponent), uppercase	3.9265E+2
/// *   g	Use the shortest representation: %e or %f	392.65
/// *   G	Use the shortest representation: %E or %F	392.65
/// *   a	Hexadecimal floating point, lowercase	-0xc.90fep-2
/// *   A	Hexadecimal floating point, uppercase	-0XC.90FEP-2
/// *   c	Character	a
/// *   s	String of characters	sample
/// *   p	Pointer address	b8000000
/// *   n	Nothing printed.
/// The corresponding argument must be a pointer to a signed int.
/// The number of characters written so far is stored in the pointed location.
/// %	A % followed by another % character will write a single % to the stream.	%
///
/// The format specifier can also contain sub-specifiers: flags, width, .precision and modifiers (in that order), which are optional and follow these specifications:
///
/// @b flags	description
/// *   -	Left-justify within the given field width; Right justification is the default (see width sub-specifier).
/// *   +	Forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a - sign.
/// *   (space)	If no sign is going to be written, a blank space is inserted before the value.
/// *   #	Used with o, x or X specifiers the value is preceeded with 0, 0x or 0X respectively for values different than zero.
/// Used with a, A, e, E, f, F, g or G it forces the written output to contain a decimal point even if no more digits follow. By default, if no digits follow, no decimal point is written.
/// *   0	Left-pads the number with zeroes (0) instead of spaces when padding is specified (see width sub-specifier).
///
/// @b width	description
/// *   (number)	Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger.
/// *   *	The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.
///
/// @b .precision	description
/// *   .number	For integer specifiers (d, i, o, u, x, X): precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0.
/// For a, A, e, E, f and F specifiers: this is the number of digits to be printed after the decimal point (by default, this is 6).
/// For g and G specifiers: This is the maximum number of significant digits to be printed.
/// For s: this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered.
/// If the period is specified without an explicit value for precision, 0 is assumed.
/// *   .*	The precision is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.
///
/// @b The length sub-specifier modifies the length of the data type. This is a chart showing the types used to interpret the corresponding arguments with and without length specifier (if a different type is used, the proper type promotion or conversion is performed, if allowed):
/// specifiers
/// @b length	d i	u o x X	f F e E g G a A	c	s	p	n
/// *   (none)	int	unsigned int	double	int	char*	void*	int*
/// *   hh	signed char	unsigned char					signed char*
/// *   h	short int	unsigned short int					short int*
/// *   l	long int	unsigned long int		wint_t	wchar_t*		long int*
/// *   ll	long long int	unsigned long long int					long long int*
/// *   j	intmax_t	uintmax_t					intmax_t*
/// *   z	size_t	size_t					size_t*
/// *   t	ptrdiff_t	ptrdiff_t					ptrdiff_t*
/// *   L			long double
/// Note that the c specifier takes an int (or wint_t) as argument, but performs the proper conversion to a char value (or a wchar_t) before formatting it for output.
///
/// Note: Yellow rows indicate specifiers and sub-specifiers introduced by C99. See <cinttypes> for the specifiers for extended types.
///
/// @b ... (additional arguments)
/// Depending on the format string, the function may expect a sequence of additional arguments, each containing a value to be used to replace a format specifier in the format string (or a pointer to a storage location, for n).
/// There should be at least as many of these arguments as the number of values specified in the format specifiers. Additional arguments are ignored by the function.


///
/// @brief      debugPort
/// @details	Define the serial port used by //debug()
///
extern Stream * debugPort;


///
/// @brief      Debug
/// @details	Send formatted text to Serial
/// @param      format format with standard codes
/// @param      ... list of values
/// @see        http://www.cplusplus.com/reference/cstdio/printf/?kw=printf for codes
///
void debug(const char * format, ... );

///
/// @brief      Debug with CRLF
/// @details	Send formatted text to Serial
/// @param      format format with standard codes
/// @param      ... list of values
/// @see        http://www.cplusplus.com/reference/cstdio/printf/?kw=printf for codes
///
void debugln(const char * format, ... );

#endif
