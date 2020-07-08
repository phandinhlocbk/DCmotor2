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
int16 time=0,xung_thuc_te,v;
int16 tocdo=0;
float Kp,Ki,Kd,T,a0,a1,a2,e,e1=0,e2=0,u,u1=0;
int8 do_rong_xung;
char b[3], c[4];
int8 str[4];
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
xung_thuc_te=(tocdo*41)/600;//Tinh Xung Thuc Te Chay Trong41ms
if(xung_thuc_te==0)
  {
  set_pwm1_duty(0);
  a=0; e=0 ;e1=0; e2=0;
  }
else
   {
   set_pwm1_duty(125);
   enable_interrupts(INT_CCP2);
   enable_interrupts(INT_RTCC);
   }
   disable_interrupts(INT_RDA);
}

#INT_RTCC
void ngat_timer0()
{
time=time+1;
//set_timer0(5);

if(time==20)
{
if(a==5)
 output_high(pin_B0);
 
itoa(v,10,c);
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
else if(u>=20)
{
do_rong_xung=250;
}
else
{
do_rong_xung=(int8)(u*12.5);
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
v=(a*600)/41;
}

void main()
 {
 set_tris_B(0b00000010);
 output_B(0);
 LCD_Init();
  
 Kp=0.007;
 Ki=0.0000535;
 Kd=0.000015;
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
 enable_interrupts(INT_RDA);
 enable_interrupts(GLOBAL);

while(true)
    {  
    ;
    }
 }
