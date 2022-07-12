#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "main.h"
#include "PrechargeM.h"

void main(void)
{
  /* put your own code here */
	DisableInterrupts;
  PLL_Init();
  ECT_Init();
  CAN_Init();
  data();
  PIT_Init();
  EnableInterrupts;

  for(;;)
  {
    _FEED_COP(); /* feeds the dog */
    Node_Poll();
    //CAN1_In_Out();
    //CAN1_inte();
  } /* loop forever */
  /* please make sure that you never leave main */
}
