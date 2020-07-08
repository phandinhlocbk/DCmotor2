#include <16f887.h>
#FUSES NOWDT,HS,NOPUT,NOPROTECT,NODEBUG,NOBROWNOUT,NOLVP,NOCPD,NOWRT
#USE delay(clock=8000000)
#use rs232(baud=9600, parity=n,xmit=pin_C6,rcv=pin_C7)
#include <stdlib.h>

#use FAST_IO(E)
#use FAST_IO(D)
#define LCD_RS PIN_E0                        
#define LCD_RW PIN_E1
#define LCD_EN PIN_E2
#define LCD_D4 PIN_D4                 
#define LCD_D5 PIN_D5
#define LCD_D6 PIN_D6
#define LCD_D7 PIN_D7 

#include "lcd.c"
#include <var.h>

int8  count=0; 
int16 read_pulses=0, pulses;
char read_angle[4],c[4];
int16 str[4];

#INT_RDA
void interrupts_rs232()
{
   int8 i=0;
   for(i=0;i<3;i++)
   {
      read_angle[i]=getc();
   }
   read_pulses=atol(read_angle);
   
   pulses = (read_pulses*10)/36; 
   enable_interrupts(INT_CCP2);
   set_pwm1_duty(11);
   disable_interrupts(INT_RDA);
}
#INT_CCP2
void interrupts_ccp2()
{
   count =count+1;
   itoa(count,10,c);
}
void main()
{
   set_tris_A(0x00);
   output_A(0x00);
   LCD_Init();
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_CAPTURE_RE);
   setup_timer_2(t2_div_by_16,124,1);
   set_pwm1_duty(0);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   output_high(pin_C0);
   while(true)
   {
      sprintf(str,c);
      LCD_Gotoxy(1,0);
      LCD_puts(str);
      if(count>(pulses/2+2)||pulses==0)
      {
        set_pwm1_duty(0);
      }
      //else if(count>=(pulses-10))
      //{
        //set_pwm1_duty(0);
        //delay_ms(3000);
        //count =0;
      //}
   }
}
   

