/*=============================================================================
 * Author: Fernando Ezequiel Daniele <fernandodaniele1993@gmai.com>
 * Date: 2020/09/26
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "PCSE_TPFinal.h"
#include "sapi.h"
#include "mcufriend.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/
#define BLUE    "31"
#define RED     "63488"
#define GREEN   "2016"//0x07E0
#define CYAN    "2047"//0x07FF
#define MAGENTA "63519"//0xF81F
#define YELLOW  "65504"//0xFFE0
#define WHITE   "65535"//0xFFFF
#define BLACK   "0"//0x0000

#define t		700

int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();

   spiConfig( SPI0 );

   uartConfig(UART_USB, 115200);

   tftInit();
   delay(t);

   // ----- Repeat for ever -------------------------
   while( true ) {
      tftFillScreen(RED);
	  delay(t);
	  tftDrawRect("10", "30", "20", "20", BLACK);
	  delay(t);
	  tftSetCursor("40","30");
	  delay(t);
	  tftSetTextColor(BLUE);
	  delay(t);
	  tftSetTextSize("03");
	  delay(t);
	  tftPrint("TP final", 8);
      delay(t);
      tftDrawRect("10", "70", "20", "20", BLACK);
      delay(t);
      tftSetTextColor(GREEN);
      delay(t);
      tftSetCursor("40","70");
      delay(t);
      tftSetTextSize("03");
      delay(t);
      tftPrint("Protocolos",10);
      delay(t);
      tftDrawLine("10","30", "30", "50", GREEN);
      delay(t);
      tftDrawLine("10","70", "30", "90", BLUE);
      delay(5000);
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
