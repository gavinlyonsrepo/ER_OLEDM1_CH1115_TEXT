/*
Example file name : ER_OLEDM1_CH1115_TEXT.ino
Description:
Test file for ER_OLEDM1_CH1115_TEXT library, 
URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115_TEXT

Test 0 clear screen
Test 0.5 bitmap
Test 1 String function and goto function
Test 2 clear page function
Test 3 character function
Test 4 print entire ASCII font with character function 0-127
Test 5 print extended ASCII font 128-255.
Test 6 OLED enable and disable
Test 7 inverse
Test 8 OLED flip
Test 9 contrast
Test 10 OLED scroll
Test 11 fade ~ breath effect
*/

#include "ER_OLEDM1_CH1115_TEXT.hpp"

#define OLEDcontrast 0x80  //Constrast 00 to FF , 0x80 is default. user adjust

// Hardware SPI Setup 
// GPIO 5-wire SPI interface
#define RES 8  // GPIO pin number pick any you want
#define DC 9   // "
#define CS 10  // "
// GPIO pin number SCK(UNO 13) , HW SPI , SCK
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI

ERMCH1115 myOLED(DC, RES, CS);  

// Software SPI Setup,  comment this block in for SW SPI 
/*
// GPIO 5-wire SPI interface
#define RES 8  // GPIO pin number pick any you want
#define DC 9   // "
#define CS 10  // "
#define SCL 7 // " , Software SPI only 
#define SDA  6 // ", Software SPI only 
ERMCH1115  myOLED(DC, RES, CS, SCL, SDA); 
*/

// 'small image', 20x24px
const PROGMEM uint8_t smallImage[60] = {
  0xff, 0x3f, 0x0f, 0x07, 0x03, 0x13, 0x33, 0x39, 0x39, 0x79, 0xf9, 0xf9, 
  0xfb, 0xf3, 0xf7, 0xe3, 0x87, 0x0f, 0x1f, 0xff, 0xf9, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x1d, 0x19, 0x10, 0x19, 
  0x0f, 0x00, 0xc0, 0xf0, 0x0f, 0x0f, 0x0f, 0x0e, 0x0c, 0x0c, 0x08, 0x08,
  0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x0c, 0x0c, 0x0e, 0x0f, 0x0f, 0x0f
};

void Tests(void);
void FunctionTests(void);

// ************* SETUP ***************
void setup() {
  myOLED.OLEDbegin(OLEDcontrast);  // initialize the OLED
  myOLED.OLEDFillScreen(0x33, 0);  // Fill screen with effect
  delay(500);
}

// ************** MAIN LOOP ***********
void loop() {

  Tests();
  FunctionTests();
  while (1){delay(1);}
}
// ************** END OF MAIN ***********

void Tests() {
  //Test 0 clear screen

  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen
  delay(500);

  // Test 0.5 bitmap
  myOLED.OLEDBitmap(10, 10, 20, 24, smallImage);
  delay(2000);

  unsigned char test0_1[] = "This is page 0";
  unsigned char test1_2[] = "123456789012345678";
  unsigned char test1_3[] = "This is page 7";

  // Test 1 String function and goto function
  myOLED.OLEDGotoXY(0, 0);     // (Col , page ) Col 0 to 191 , page 0 to 7
  myOLED.OLEDString(test0_1);  // Write a character string
  myOLED.OLEDGotoXY(0, 4);
  myOLED.OLEDString(test1_2);
  myOLED.OLEDGotoXY(0, 7);
  myOLED.OLEDString(test1_3);
  delay(5000);

  // Test 2 clear page function

  myOLED.OLEDFillPage(7, 0x00, 0);  // Clear page
  delay(1000);
  myOLED.OLEDFillPage(6, 0x7E, 0);  // Write pattern (0111 1110) to a page
  delay(4000);
  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen

  // Test 3 character function
  myOLED.OLEDGotoXY(100, 2);
  myOLED.OLEDChar('H');  // write single  character
  myOLED.OLEDChar('2');
  delay(2000);
  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen

  // Test 4 print entire font with character function
  // NOTE For characters 32-127 for charcters comment in UC_FONT_MOD_ONE  n font file ER_OLEDM1_CH1115_font.h.
  myOLED.OLEDGotoXY(0, 0);
  uint8_t row = 1;

  for (unsigned char i = 0; i < 126; i++) {
    if (i % 18 == 0) myOLED.OLEDGotoXY(0, row++);
    myOLED.OLEDChar(i);
    delay(5);
  }
  delay(3000);
  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen

  // TEST 5 print ASCII font 128-255 with character function
  // For characters after 'z{|}' in ASCII table user can comment in UC_FONT_MOD_TWO in font file
  // (NOTE: this will increase program size)
  myOLED.OLEDGotoXY(0, 0);
  row = 1;
  for (unsigned char k = 128; k < 255; k++) {
    if (k % 18 == 0) myOLED.OLEDGotoXY(0, row++);
    myOLED.OLEDChar(k);
    delay(5);
  }
  delay(3000);
  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen
}

void FunctionTests(void) {
  
  unsigned char test6[] = "OLED Disable test";
  unsigned char test7[] = "OLED Inverse test ";
  unsigned char test8[] = "Flip test";
  unsigned char test9[] = "Contrast test";
  unsigned char test10[] = "Scroll test";
  unsigned char test11[] = "fade effect test";
  unsigned char testEnd[] = "End of tests";

  //  ** Test 6 OLED enable and disable **
  myOLED.OLEDGotoXY(0, 30);
  myOLED.OLEDString(test6);

  delay(2000);  //display message
  myOLED.OLEDEnable(0);  //turn off display (sleep mode 500uA measured)
  delay(2000);  //wait for 2
  myOLED.OLEDEnable(1);  //turn on
  delay(2000);  //display message
  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen

  // ** Test 7 inverse **
  myOLED.OLEDGotoXY(0, 10);
  myOLED.OLEDString(test7);
  delay(2000);
  myOLED.OLEDInvert(1);  // Inverted
  delay(5000);
  myOLED.OLEDInvert(0);
  delay(1000);


  // ** Test 8 OLED flip **
  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen
  myOLED.OLEDGotoXY(5, 5);
  myOLED.OLEDString(test8);
  delay(5000);
  myOLED.OLEDFlip(1);
  delay(5000);
  myOLED.OLEDFlip(0);
  delay(1000);

  // ** Test 9 contrast **
  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen
  myOLED.OLEDGotoXY(0, 0);
  myOLED.OLEDString(test9);
  
  delay(2000);
  myOLED.OLEDFillScreen(0x77, 0);  // fill screen

  myOLED.OLEDContrast(0x00);
  delay(1000);
  myOLED.OLEDContrast(0x80);
  delay(1000);
  myOLED.OLEDContrast(0xFF);
  delay(1000);
  myOLED.OLEDContrast(OLEDcontrast);
  delay(1000);
  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen


  // ** Test 10 OLED scroll **
  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen
  myOLED.OLEDGotoXY(0, 40);
  myOLED.OLEDString(test10);
  
  delay(2000);

  // See .cpp file for more info on these parmeters.
  uint8_t timeInterval = 0x00;     // 6 frames 0x00 - 0x07
  uint8_t scrollDirection = 0x26;  //right 0x26 or 0x27
  uint8_t scrollMode = 0x28;       // contiunous 0x28-0x2A,
  myOLED.OLEDscrollSetup(timeInterval, scrollDirection, scrollMode);
  myOLED.OLEDscroll(1);  //start scroll
  delay(15000);
  myOLED.OLEDscroll(0);  // stop Scroll

  delay(1);

  timeInterval = 0x02;     // 64 frames , 0x00 - 0x07
  scrollDirection = 0x27;  // left , 0x26 or 0x27
  scrollMode = 0x29;       // contiunous 0x28 one shot 0x29 , one col 0x2A,
  myOLED.OLEDscrollSetup(timeInterval, scrollDirection, scrollMode);
  myOLED.OLEDscroll(1);  //start
  delay(15000);
  myOLED.OLEDscroll(0);  // stop

  // ** TEST 11 fade ~ breath effect **
  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen
  myOLED.OLEDGotoXY(5, 5);
  myOLED.OLEDString(test11);
  
  delay(2000);
  myOLED.OLEDfadeEffect();
  myOLED.OLEDFillScreen(0xE3, 0);
  delay(10000);
  myOLED.OLEDfadeEffect(0x00);  // switch off fade

  myOLED.OLEDFillScreen(0x00, 0);  // Clear the screen
  myOLED.OLEDGotoXY(5, 5);
  myOLED.OLEDString(testEnd);
  
  delay(5000);
}