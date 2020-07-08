void Motor_speed_PID(long int des_speed)
{
   rSpeed=(Pulses/50)*(10^3)*60/200;  //van toc trong thoi gian lay mau
   pre_pulses=pulses; // luu lai so xung
   Err=des_speed-abs(rSpeed); //sai so van toc
   // cac thanh phan PID
   pPart=Kp*Err;
   dPart=Kd*(Err-pre_Err)/Sampling_time;
   iPart+=Ki*sampling_time*Err/1000;
   Output+=pPart+dPart+iPart; 
   // 
   if(Output>=
   
