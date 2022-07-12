#define MODE_ONE PORTC_PC4
#define MODE_ONE_dir DDRC_DDRC4

#define MODE_TWO PORTC_PC5
#define MODE_TWO_dir DDRC_DDRC5

void data(void) 
{
  MODE_ONE=1;
  MODE_ONE_dir=1;
  MODE_TWO=0;
  MODE_TWO_dir=1;
}