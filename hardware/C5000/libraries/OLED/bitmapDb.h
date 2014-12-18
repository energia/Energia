/**************************************************************************
 *
 * FILE NAME:			bitmapDb.h
 * FILE DESCRIPTION:	Database of all bitmaps in the system
 *
 * FILE CREATION DATE:	24-07-2009
 *
 *==========================================================================
 *
 * Modification history:
 * --------------------
 * 01a,24jul09 erd written
 *
 ***************************************************************************/
/** @file bitmapDb.h
 *
 *  @brief Bitmap database for OLED module
 *
 */
#ifndef __BITMAP_DB_H_
#define __BITMAP_DB_H_

#include "tistdtypes.h"

/** \brief  This structure describes a single character's display information
*/
typedef struct
{
    /** width, in bits (or pixels), of the character */
	const Uint8 widthBits;	
    /** height, in bits (or pixels), of the character */	
	const Uint8 heightBits;
	/** offset of the character's bitmap, in bytes, into the the FONT_INFO's data array */
	const Uint16 offset;					 
} FONT_CHAR_INFO;

/** \brief  This structure describes a single font
*/
typedef struct
{
	const Uint8 			heightPages;	/**< height, in pages (8 pixels), of the font's characters */
	const Uint8 			startChar;		/**< the first character in the font (e.g. in charInfo and data) */
	const Uint8 			endChar;		/**< the last character in the font */
	//const Uint8			spacePixels;	/**< number of pixels that a space character takes up */
	const FONT_CHAR_INFO*	charInfo;		/**< pointer to array of char information */
	const Uint8*			data;			/**< pointer to generated array of character visual representation */
} FONT_INFO;

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set:
//    DL = 1; 8-bit interface data
//    N = 0; 1-line display
//    F = 0; 5x8 dot character font
// 3. Display on/off control:
//    D = 0; Display off
//    C = 0; Cursor off
//    B = 0; Blinking off
// 4. Entry mode set:
//    I/D = 1; Increment by 1
//    S = 0; No shift
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// OLED constructor is called).
//
//  Font data for Arial 8pt
//

/** \brief  Character bitmaps for Arial 8pt
*/
static const Uint8 arial_8ptBitmaps[] =
{
	// @0 ' ' (2 pixels wide)
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	0x00, 0x00,
	0x00, 0x00,

	// @4 '!' (1 pixels wide)
	// #
	//
	// #
	// #
	// #
	// #
	// #
	// #
	0xFD,

	// @5 '"' (3 pixels wide)
	// # #
	// # #
	// # #
	0x70, 0x00, 0x70,

	// @8 '#' (5 pixels wide)
	// # #
	// # #
	// #####
	//  # #
	//  # #
	// #####
	//   # #
	//   # #
	0x27, 0x3C, 0xE7, 0x3C, 0xE4,

	// @14 '$' (5 pixels wide)
	//   #
	//  ###
	// # # #
	//   ##
	//  ##
	// # # #
	//  ###
	//   #
	0x24, 0x52, 0xFF, 0x4A, 0x24,
	0x00, 0x00, 0x00, 0x00, 0x00,

	// @23 '%' (9 pixels wide)
	//   #   ##
	//    # #  #
	//    # #  #
	//     # ##
	//  ## #
	// #  # #
	// #  # #
	//  ##   #
	0x60, 0x90, 0x91, 0x66, 0x18, 0x66, 0x89, 0x09, 0x06,

	// @32 '&' (6 pixels wide)
	//  ### #
	// #   #
	// #   ##
	//  # #
	//   ##
	//  #  #
	//  #  #
	//   ##
	0x06, 0x69, 0x91, 0x99, 0x66, 0x05,

	// @38 ''' (1 pixels wide)
	//
	//
	//
	//
	//
	// #
	// #
	// #
	0xE0,

	// @39 '(' (3 pixels wide)
    //   #
    //  #
    // #
    // #
    // #
    // #
    //  #
    //   #
	0x3C, 0x42, 0x81,
	0x00, 0x00, 0x00,

	// @45 ')' (3 pixels wide)
	// @39 '(' (3 pixels wide)
	// #
	//  #
	//   #
	//   #
	//   #
	//   #
	//  #
	// #
	0x81, 0x42, 0x3C,
	0x00, 0x00, 0x00,

	// @51 '*' (3 pixels wide)
	// # #
	//  #
	// ###
	//  #
	0x05, 0x0E, 0x05,

	// @54 '+' (5 pixels wide)
	//   #
	//   #
	// #####
	//   #
	//   #
	0x04, 0x04, 0x1F, 0x04, 0x04,

	// @59 ',' (1 pixels wide)
	// #
	// #
	// #
	0x07,

	// @60 '-' (3 pixels wide)
	// ###
	0x01, 0x01, 0x01,

	// @63 '.' (1 pixels wide)
	// #
	0x01,

	// @64 '/' (3 pixels wide)
	// #
	// #
	//  #
	//  #
	//  #
	//  #
	//   #
	//   #
	0x03, 0x3C, 0xC0,

	// @67 '0' (5 pixels wide)
	//  ###
	// #   #
	// #   #
	// #   #
	// #   #
	// #   #
	// #   #
	//  ###
	0x7E, 0x81, 0x81, 0x81, 0x7E,

	// @72 '1' (3 pixels wide)
	//   #
	//   #
	//   #
	//   #
	//   #
	// # #
	//  ##
	//   #
	0x20, 0x40, 0xFF,

	// @75 '2' (5 pixels wide)
	// #####
	//  #
	//   #
	//    #
	//     #
	//     #
	// #   #
	//  ###
	0x41, 0x83, 0x85, 0x89, 0x71,

	// @80 '3' (5 pixels wide)
	//  ###
	// #   #
	//     #
	//     #
	//   ##
	//     #
	// #   #
	//  ###
	0x42, 0x81, 0x91, 0x91, 0x6E,

	// @85 '4' (5 pixels wide)
	//    #
	//    #
	// #####
	// #  #
	//  # #
	//  # #
	//   ##
	//    #
	0x0C, 0x34, 0x44, 0xFF, 0x04,

	// @90 '5' (5 pixels wide)
	//  ###
	// #   #
	//     #
	//     #
	// ####
	// #
	//  #
	//  ####
	0x32, 0xD1, 0x91, 0x91, 0x8E,

	// @95 '6' (5 pixels wide)
	//  ###
	// #   #
	// #   #
	// #   #
	// ####
	// #
	// #   #
	//  ###
	0x7E, 0x91, 0x91, 0x91, 0x4E,

	// @100 '7' (5 pixels wide)
	//  #
	//  #
	//  #
	//   #
	//   #
	//    #
	//    #
	// #####
	0x80, 0x87, 0x98, 0xE0, 0x80,

	// @105 '8' (5 pixels wide)
	//  ###
	// #   #
	// #   #
	// #   #
	//  ###
	// #   #
	// #   #
	//  ###
	0x6E, 0x91, 0x91, 0x91, 0x6E,

	// @110 '9' (5 pixels wide)
	//  ###
	// #   #
	//     #
	//  ####
	// #   #
	// #   #
	// #   #
	//  ###
	0x72, 0x89, 0x89, 0x89, 0x7E,

	// @115 ':' (1 pixels wide)
	// #
	//
	//
	//
	//
	// #
	0x21,

	// @116 ';' (1 pixels wide)
	// #
	// #
	// #
	//
	//
	//
	//
	// #
	0x87,

	// @117 '<' (5 pixels wide)
	//    ##
	//  ##
	// #
	//  ##
	//    ##
	0x04, 0x0A, 0x0A, 0x11, 0x11,

	// @122 '=' (5 pixels wide)
	// #####
	//
	// #####
	0x05, 0x05, 0x05, 0x05, 0x05,

	// @127 '>' (5 pixels wide)
	// ##
	//   ##
	//     #
	//   ##
	// ##
	0x11, 0x11, 0x0A, 0x0A, 0x04,

	// @132 '?' (5 pixels wide)
	//   #
	//
	//   #
	//   #
	//    #
	//     #
	// #   #
	//  ###
	0x40, 0x80, 0x8D, 0x90, 0x60,

	// @137 '@' (10 pixels wide)
	//   #######
	//  #       #
	// #  ## ##
	// # #  ## #
	// #  #  ## #
	// #   ## # #
	//  #       #
	//   #######
	0x3C, 0x42, 0x89, 0x95, 0xA5, 0xA9, 0x9D, 0xB5, 0x89, 0x72,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	// @157 'A' (7 pixels wide)
	// #     #
	// #     #
	//  #####
	//  #   #
	//   # #
	//   # #
	//   # #
	//    #
	0x03, 0x0C, 0x74, 0x84, 0x74, 0x0C, 0x03,

	// @164 'B' (6 pixels wide)
	// #####
	// #    #
	// #    #
	// #    #
	// ######
	// #    #
	// #    #
	// #####
	0xFF, 0x91, 0x91, 0x91, 0x91, 0x7E,

	// @170 'C' (6 pixels wide)
	//   ###
	//  #   #
	// #
	// #
	// #
	// #
	//  #   #
	//   ###
	0x3C, 0x42, 0x81, 0x81, 0x81, 0x42,

	// @176 'D' (6 pixels wide)
	// ####
	// #   #
	// #    #
	// #    #
	// #    #
	// #    #
	// #   #
	// ####
	0xFF, 0x81, 0x81, 0x81, 0x42, 0x3C,

	// @182 'E' (5 pixels wide)
	// #####
	// #
	// #
	// #
	// #####
	// #
	// #
	// #####
	0xFF, 0x91, 0x91, 0x91, 0x91,

	// @187 'F' (5 pixels wide)
	// #
	// #
	// #
	// #
	// ####
	// #
	// #
	// #####
	0xFF, 0x90, 0x90, 0x90, 0x80,

	// @192 'G' (7 pixels wide)
	//   ###
	//  #   #
	// #     #
	// #   ###
	// #
	// #     #
	//  #   #
	//   ###
	0x3C, 0x42, 0x81, 0x81, 0x89, 0x4A, 0x2C,

	// @199 'H' (6 pixels wide)
	// #    #
	// #    #
	// #    #
	// #    #
	// ######
	// #    #
	// #    #
	// #    #
	0xFF, 0x10, 0x10, 0x10, 0x10, 0xFF,

	// @205 'I' (1 pixels wide)
	// #
	// #
	// #
	// #
	// #
	// #
	// #
	// #
	0xFF,

	// @206 'J' (4 pixels wide)
	//  ##
	// #  #
	// #  #
	//    #
	//    #
	//    #
	//    #
	//    #
	0x06, 0x01, 0x01, 0xFE,

	// @210 'K' (6 pixels wide)
	// #    #
	// #   #
	// #   #
	// ## #
	// # ##
	// #  #
	// #   #
	// #    #
	0xFF, 0x08, 0x10, 0x38, 0x46, 0x81,

	// @216 'L' (5 pixels wide)
	// #####
	// #
	// #
	// #
	// #
	// #
	// #
	// #
	0xFF, 0x01, 0x01, 0x01, 0x01,

	// @221 'M' (7 pixels wide)
	// #  #  #
	// #  #  #
	// # # # #
	// # # # #
	// # # # #
	// ##   ##
	// ##   ##
	// #     #
	0xFF, 0x60, 0x1C, 0x03, 0x1C, 0x60, 0xFF,

	// @228 'N' (6 pixels wide)
	// #    #
	// #   ##
	// #  # #
	// #  # #
	// # #  #
	// # #  #
	// ##   #
	// #    #
	0xFF, 0x40, 0x30, 0x0C, 0x02, 0xFF,

	// @234 'O' (7 pixels wide)
	//   ###
	//  #   #
	// #     #
	// #     #
	// #     #
	// #     #
	//  #   #
	//   ###
	0x3C, 0x42, 0x81, 0x81, 0x81, 0x42, 0x3C,

	// @241 'P' (5 pixels wide)
	// #
	// #
	// #
	// ####
	// #   #
	// #   #
	// #   #
	// ####
	0xFF, 0x88, 0x88, 0x88, 0x70,

	// @246 'Q' (7 pixels wide)
	//   ### #
	//  #   #
	// #  ## #
	// #     #
	// #     #
	// #     #
	//  #   #
	//   ###
	0x3C, 0x42, 0x81, 0x85, 0x85, 0x42, 0x3D,

	// @253 'R' (6 pixels wide)
	// #    #
	// #   #
	// #   #
	// #  #
	// #####
	// #    #
	// #    #
	// #####
	0xFF, 0x90, 0x90, 0x98, 0x96, 0x61,

	// @259 'S' (6 pixels wide)
	//  ####
	// #    #
	//      #
	//    ##
	//  ##
	// #
	// #    #
	//  ####
	0x62, 0x91, 0x91, 0x89, 0x89, 0x46,

	// @265 'T' (5 pixels wide)
	//   #
	//   #
	//   #
	//   #
	//   #
	//   #
	//   #
	// #####
	0x80, 0x80, 0xFF, 0x80, 0x80,

	// @270 'U' (6 pixels wide)
	//  ####
	// #    #
	// #    #
	// #    #
	// #    #
	// #    #
	// #    #
	// #    #
	0xFE, 0x01, 0x01, 0x01, 0x01, 0xFE,

	// @276 'V' (7 pixels wide)
	//    #
	//    #
	//   # #
	//   # #
	//  #   #
	//  #   #
	// #     #
	// #     #
	0xC0, 0x30, 0x0C, 0x03, 0x0C, 0x30, 0xC0,

	// @283 'W' (11 pixels wide)
	//   #     #
	//   #     #
	//  # #   # #
	//  # #   # #
	//  #  # #  #
	//  #  # #  #
	// #   # #   #
	// #    #    #
	0xC0, 0x3C, 0x03, 0x0C, 0x70, 0x80, 0x70, 0x0C, 0x03, 0x3C, 0xC0,

	// @294 'X' (6 pixels wide)
	// #    #
	//  #  #
	//  #  #
	//   ##
	//   ##
	//  #  #
	//  #  #
	// #    #
	0x81, 0x66, 0x18, 0x18, 0x66, 0x81,

	// @300 'Y' (7 pixels wide)
	//    #
	//    #
	//    #
	//    #
	//   # #
	//  #   #
	//  #   #
	// #     #
	0x80, 0x60, 0x10, 0x0F, 0x10, 0x60, 0x80,

	// @307 'Z' (6 pixels wide)
	// ######
	//  #
	//   #
	//   #
	//    #
	//    #
	//     #
	//  #####
	0x01, 0x83, 0x8D, 0xB1, 0xC1, 0x81,

	// @320 ']' (2 pixels wide)
	// ##
	// #
	// #
	// #
	// #
	// #
	// #
	// ##
	0xFF, 0x81,
	0x00, 0x00,

	// @317 '\' (3 pixels wide)
	//   #
	//   #
	//  #
	//  #
	//  #
	//  #
	// #
	// #
	0xC0, 0x3C, 0x03,

	// @313 '[' (2 pixels wide)
	// ##
	//  #
	//  #
	//  #
	//  #
	//  #
	//  #
	//  #
	//  #
	// ##
	0x81, 0xFF,
	0x00, 0x00,

	// @324 '^' (5 pixels wide)
	// #   #
	//  # #
	//  # #
	//   #
	0x01, 0x06, 0x08, 0x06, 0x01,

	// @329 '_' (6 pixels wide)
	// ######
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01,

	// @335 '`' (2 pixels wide)
	//
	//
	//
	//
	//
	//
	//  #
	// #
	0x80, 0x40,

	// @337 'a' (5 pixels wide)
	//  ## #
	// #  ##
	// #   #
	//  ####
	// #   #
	//  ###
	0x16, 0x29, 0x29, 0x2A, 0x1F,

	// @342 'b' (5 pixels wide)
	// # ##
	// ##  #
	// #   #
	// #   #
	// ##  #
	// # ##
	// #
	// #
	0xFF, 0x12, 0x21, 0x21, 0x1E,

	// @347 'c' (5 pixels wide)
	//  ###
	// #   #
	// #
	// #
	// #   #
	//  ###
	0x1E, 0x21, 0x21, 0x21, 0x12,

	// @352 'd' (5 pixels wide)
	//  ## #
	// #  ##
	// #   #
	// #   #
	// #  ##
	//  ## #
	//     #
	//     #
	0x1E, 0x21, 0x21, 0x12, 0xFF,

	// @357 'e' (5 pixels wide)
	//  ###
	// #   #
	// #
	// #####
	// #   #
	//  ###
	0x1E, 0x29, 0x29, 0x29, 0x1A,

	// @362 'f' (3 pixels wide)
	//  #
	//  #
	//  #
	//  #
	//  #
	// ###
	//  #
	//   #
	0x20, 0x7F, 0xA0,

	// @365 'g' (5 pixels wide)
	// ####
	//     #
	//  ## #
	// #  ##
	// #   #
	// #   #
	// #  ##
	//  ## #
	0x79, 0x85, 0x85, 0x49, 0xFE,

	// @370 'h' (5 pixels wide)
	// #   #
	// #   #
	// #   #
	// #   #
	// ##  #
	// # ##
	// #
	// #
	0xFF, 0x10, 0x20, 0x20, 0x1F,

	// @375 'i' (1 pixels wide)
	// #
	// #
	// #
	// #
	// #
	// #
	//
	// #
	0xBF,

	// @376 'j' (2 pixels wide)
	// #
	//  #
	//  #
	//  #
	//  #
	//  #
	//  #
	//  #
	//
	//  #
	0x01, 0xFE,
	0x00, 0x02,

	// @380 'k' (4 pixels wide)
	// #  #
	// # #
	// # #
	// ##
	// # #
	// #  #
	// #
	// #
	0xFF, 0x08, 0x16, 0x21,

	// @384 'l' (1 pixels wide)
	// #
	// #
	// #
	// #
	// #
	// #
	// #
	// #
	0xFF,

	// @385 'm' (7 pixels wide)
	// #  #  #
	// #  #  #
	// #  #  #
	// #  #  #
	// ## #  #
	// # ####
	0x3F, 0x10, 0x20, 0x3F, 0x20, 0x20, 0x1F,

	// @392 'n' (5 pixels wide)
	// #   #
	// #   #
	// #   #
	// #   #
	// #   #
	// ####
	0x3F, 0x20, 0x20, 0x20, 0x1F,

	// @397 'o' (5 pixels wide)
	//  ###
	// #   #
	// #   #
	// #   #
	// #   #
	//  ###
	0x1E, 0x21, 0x21, 0x21, 0x1E,

	// @402 'p' (5 pixels wide)
	// #
	// #
	// # ##
	// ##  #
	// #   #
	// #   #
	// ##  #
	// # ##
	0xFF, 0x48, 0x84, 0x84, 0x78,

	// @407 'q' (5 pixels wide)
	//     #
	//     #
	//  ## #
	// #  ##
	// #   #
	// #   #
	// #  ##
	//  ## #
	0x78, 0x84, 0x84, 0x48, 0xFF,

	// @412 'r' (3 pixels wide)
	// #
	// #
	// #
	// #
	// ##
	// # #
	0x3F, 0x10, 0x20,

	// @415 's' (5 pixels wide)
	//  ###
	// #   #
	//    #
	//  ##
	// #   #
	//  ###
	0x12, 0x29, 0x29, 0x25, 0x12,

	// @420 't' (3 pixels wide)
	//  ##
	//  #
	//  #
	//  #
	//  #
	// ###
	//  #
	//  #
	0x20, 0xFF, 0x21,

	// @423 'u' (5 pixels wide)
	//  ## #
	// #  ##
	// #   #
	// #   #
	// #   #
	// #   #
	0x3E, 0x01, 0x01, 0x02, 0x3F,

	// @428 'v' (5 pixels wide)
	//   #
	//   #
	//  # #
	//  # #
	// #   #
	// #   #
	0x30, 0x0C, 0x03, 0x0C, 0x30,

	// @433 'w' (9 pixels wide)
	//   #   #
	//   #   #
	//  # # # #
	//  # # # #
	// #  # #  #
	// #   #   #
	0x30, 0x0C, 0x03, 0x1C, 0x20, 0x1C, 0x03, 0x0C, 0x30,

	// @442 'x' (5 pixels wide)
	// #   #
	//  # #
	//   #
	//   #
	//  # #
	// #   #
	0x21, 0x12, 0x0C, 0x12, 0x21,

	// @447 'y' (5 pixels wide)
	//  #
	//   #
	//   #
	//   #
	//  # #
	//  # #
	// #   #
	// #   #
	0xC0, 0x31, 0x0E, 0x30, 0xC0,

	// @452 'z' (5 pixels wide)
	// #####
	//  #
	//   #
	//   #
	//    #
	// #####
	0x21, 0x23, 0x2D, 0x31, 0x21,

	// @457 '{' (3 pixels wide)
	//   #
	//  #
	//  #
	// #
	//  #
	//  #
	//  #
	//   #
	0x10, 0x6E, 0x81,
	0x00, 0x00, 0x00,


	// @463 '|' (1 pixels wide)
	// #
	// #
	// #
	// #
	// #
	// #
	// #
	// #
	// #
	// #
	0xFF,
	0x00,

	// @465 '}' (3 pixels wide)
	//   #
	//  #
	//  #
	// #
	//  #
	//  #
	//  #
	//   #
	0x81, 0x6E, 0x10,
	0x00, 0x00, 0x00,

	// @471 '~' (5 pixels wide)
	// # ##
	// ### #
	0x03, 0x02, 0x03, 0x01, 0x02,
};

/** \brief  Character descriptors for Arial 8pt
*/
static const FONT_CHAR_INFO arial_8ptDescriptors[] =
{
	{2, 14, 0}, 		//
	{1, 8, 4}, 		// !
	{3, 3, 5}, 		// "
	{5, 8, 8}, 		// #
	{5, 9, 13}, 		// $
	{9, 8, 23}, 		// %
	{6, 8, 32}, 		// &
	{1, 8, 38}, 		// '
	{3, 10, 39}, 		// (
	{3, 10, 45}, 		// )
	{3, 4, 51}, 		// *
	{5, 5, 54}, 		// +
	{1, 3, 59}, 		// ,
	{3, 1, 60}, 		// -
	{1, 1, 63}, 		// .
	{3, 8, 64}, 		// /
	{5, 8, 67}, 		// 0
	{3, 8, 72}, 		// 1
	{5, 8, 75}, 		// 2
	{5, 8, 80}, 		// 3
	{5, 8, 85}, 		// 4
	{5, 8, 90}, 		// 5
	{5, 8, 95}, 		// 6
	{5, 8, 100}, 		// 7
	{5, 8, 105}, 		// 8
	{5, 8, 110}, 		// 9
	{1, 6, 115}, 		// :
	{1, 8, 116}, 		// ;
	{5, 5, 117}, 		// <
	{5, 3, 122}, 		// =
	{5, 5, 127}, 		// >
	{5, 8, 132}, 		// ?
	{10, 10, 137}, 		// @
	{7, 8, 157}, 		// A
	{6, 8, 164}, 		// B
	{6, 8, 170}, 		// C
	{6, 8, 176}, 		// D
	{5, 8, 182}, 		// E
	{5, 8, 187}, 		// F
	{7, 8, 192}, 		// G
	{6, 8, 199}, 		// H
	{1, 8, 205}, 		// I
	{4, 8, 206}, 		// J
	{6, 8, 210}, 		// K
	{5, 8, 216}, 		// L
	{7, 8, 221}, 		// M
	{6, 8, 228}, 		// N
	{7, 8, 234}, 		// O
	{5, 8, 241}, 		// P
	{7, 8, 246}, 		// Q
	{6, 8, 253}, 		// R
	{6, 8, 259}, 		// S
	{5, 8, 265}, 		// T
	{6, 8, 270}, 		// U
	{7, 8, 276}, 		// V
	{11, 8, 283}, 		// W
	{6, 8, 294}, 		// X
	{7, 8, 300}, 		// Y
	{6, 8, 307}, 		// Z
	{2, 10, 313}, 		// [
	{3, 8, 317}, 		// '\'
	{2, 10, 320}, 		// ]
	{5, 4, 324}, 		// ^
	{6, 1, 329}, 		// _
	{2, 8, 335}, 		// `
	{5, 6, 337}, 		// a
	{5, 8, 342}, 		// b
	{5, 6, 347}, 		// c
	{5, 8, 352}, 		// d
	{5, 6, 357}, 		// e
	{3, 8, 362}, 		// f
	{5, 8, 365}, 		// g
	{5, 8, 370}, 		// h
	{1, 8, 375}, 		// i
	{2, 10, 376}, 		// j
	{4, 8, 380}, 		// k
	{1, 8, 384}, 		// l
	{7, 6, 385}, 		// m
	{5, 6, 392}, 		// n
	{5, 6, 397}, 		// o
	{5, 8, 402}, 		// p
	{5, 8, 407}, 		// q
	{3, 6, 412}, 		// r
	{5, 6, 415}, 		// s
	{3, 8, 420}, 		// t
	{5, 6, 423}, 		// u
	{5, 6, 428}, 		// v
	{9, 6, 433}, 		// w
	{5, 6, 442}, 		// x
	{5, 8, 447}, 		// y
	{5, 6, 452}, 		// z
	{3, 10, 457}, 		// {
	{1, 10, 463}, 		// |
	{3, 10, 465}, 		// }
	{5, 2, 471}, 		// ~
};

/** \brief  This structure describes font information for Arial 8pt
*/
static const FONT_INFO arial_8ptFontInfo =
{
	2, //  Character height
	' ', //  Start character
	'~', //  End character
	arial_8ptDescriptors, //  Character descriptor array
	arial_8ptBitmaps, //  Character bitmap array
};

#endif /* __BITMAP_DB_H_ */
