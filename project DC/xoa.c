#include <16f887.h>
#FUSES NOWDT, HS, NOPUT,NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#use delay(clock=8000000)
#use rs232 (baud=9600 , parity=n , xmit=pin_C6 , rcv=pin_C7 ) 
#INCLUDE <stdlib.h>

//#include <main.h>
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

int8 a=0;
int16 time=0,xung_thuc_te;
int8 tocdo=0;
float Kp,Ki,Kd,T,a0,a1,a2,e,e1=0,e2=0,u,u1=0;
int8 do_rong_xung;
char b[3], c[4];
int8 str[4];
// PHAN THIET LAP TOC DO QUAY CUA DONG CO

#INT_EXT
void ngat_EXT()
{
 tocdo=65;
 xung_thuc_te=tocdo/60;//Tinh Xung Thuc Te Chay Trong 10ms
 set_pwm1_duty(125);
 disable_interrupts(INT_EXT);
 enable_interrupts(INT_CCP2);
 enable_interrupts(INT_RTCC);
}

#INT_RTCC
void ngat_timer0()
{
time=time+1;
//set_timer0(5);

if(time==5)
{
 
itoa(a,10,c);
sprintf(str,c);
LCD_Gotoxy(1,0);
LCD_puts(str);
e=a-xung_thuc_te;
u=u1+a0*e+a1*e1+a2*e2;
u1=u;
e2=e1;
e1=e;
if(u<=0)
{
do_rong_xung=0;
}
else if(u>=12)
{
do_rong_xung=251;
}
else
{
do_rong_xung=(int8)(u*20.833);
}
set_pwm1_duty(do_rong_xung);
a=0;
time=0;
}
}


#INT_CCP2
void ngat_CCP2()
{
a=a+1;
}

void main()
 {
 LCD_Init();
  
 Kp=0.1;//Chi su dung khau Kp=0.05,khong dung Ki va Kd.
 Ki=0.000084;
 Kd=0.1;
 T=0.1;
 a0=Kp+(Ki*T)/2+Kd/T;
 a1=-Kp+(Ki*T)/2-(2*Kd)/T;
 a2=Kd/T;
 setup_ccp1(CCP_PWM);
 setup_ccp2(CCP_CAPTURE_RE);//  CCP_CAPTURE_DIV_1
 setup_timer_2(t2_div_by_16,250,1); //tan so xung f=1,245 kHz
 set_pwm1_duty(0);
 setup_timer_0(RTCC_INTERNAL|RTCC_DIV_16); // ngat sau 2.04 ms
 //set_timer0(255); //
 enable_interrupts(INT_EXT);
 ext_int_edge( H_TO_L );   // Sets up EXT
 enable_interrupts(GLOBAL);

while(true)
    {  
    ;
    }
 }
