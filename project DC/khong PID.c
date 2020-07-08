#include <16f887.h>
#FUSES NOWDT, HS, NOPUT,NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#use delay(clock=8000000)
#use rs232 (baud=9600 , parity=n , xmit=pin_C6 , rcv=pin_C7 ) 
#INCLUDE <stdlib.h>
int16 xung_thuc_te;
int8 tocdo=0;
char b[3];
// PHAN THIET LAP TOC DO QUAY CUA DONG CO

#INT_RDA
void ngat_RS232()
{
 int8 i=0;
   for(i=0;i<2;i++)
   {
    b[i]=getc();
   } 
   tocdo=atoi(b);
    
   xung_thuc_te=tocdo/800*125;
   set_pwm1_duty(50);
}


void main()
 {
 setup_ccp1(CCP_PWM);
 setup_timer_2(t2_div_by_16,124,1); // tan so f = 0,833 kHz 
 set_pwm1_duty(0);
 enable_interrupts(INT_RDA);
 enable_interrupts(GLOBAL);

  while(true)
    {  
    if(input(pin_B0)==0)
      output_high(pin_C0);// dir
    else
      output_low(pin_C0);// dir
    }
 }
