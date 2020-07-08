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
   set_pwm1_duty(xung_thuc_te);
   enable_interrupts(INT_RTCC);
   enable_interrupts(INT_CCP2);
}
#INT_RDA
void ngat_RS232()
{
 int8 i=0;
   for(i=0;i<2;i++)
   {
    b[i]=getc();
   } 
tocdo=atoi(b);
if (tocdo==50)
    output_E(0b111);
    
xung_thuc_te=(tocdo*2)/12;//Tinh Xung Thuc Te Chay Trong 50ms
if(xung_thuc_te==0)
  {
  set_pwm1_duty(0);
  a=0; e=0 ;e1=0; e2=0;
  }
else
   {
   set_pwm1_duty(50);
   enable_interrupts(INT_RTCC);
   enable_interrupts(INT_CCP2);
   }
}
