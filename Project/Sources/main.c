#include <hidef.h>
#include "derivative.h"

#define MODE_ONE PORTC_PC4
#define MODE_ONE_dir DDRC_DDRC4
#define MODE_TWO PORTC_PC5
#define MODE_TWO_dir DDRC_DDRC5

void main(void)
{
    DisableInterrupts;
    MODE_ONE=1;
    MODE_ONE_dir=1;
    MODE_TWO=0;
    MODE_TWO_dir=1;
    PLL_Init();
    ECT_Init();
    CAN_Init();
    PIT_Init();
    EnableInterrupts;

    for(;;)
    {
        _FEED_COP();
        //Node_Poll();
    }
}
