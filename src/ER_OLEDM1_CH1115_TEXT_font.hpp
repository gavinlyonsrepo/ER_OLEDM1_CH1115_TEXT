/*
* Project Name: ER_OLEDM1_CH1115_TEXT
* File: ER_OLEDM1_CH1115_TEXT_font.hpp
* Description: ER_OLEDM1 OLED driven by CH1115 controller font data file
* Light weight text only Version 
* Author: Gavin Lyons.
*/

#ifndef _ER_OLEDM1_CH1115_TEXT_font_H
#define _ER_OLEDM1_CH1115_TEXT_font_H

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#ifdef __AVR__
 #include <avr/io.h>
 #include <avr/pgmspace.h>
#else
#ifndef ESP8266
 #define PROGMEM
#endif
#endif

// Font data is in the cpp file accessed thru extern pointers.
extern const unsigned char * pFontDefaultptr;

#endif // guard header
