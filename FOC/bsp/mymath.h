#ifndef __MYMATH_H
#define __MYMATH_H

#define _constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define GET_TIM TIM2
#define GEI_CCR1 CCR1
#define GEI_CCR2 CCR2
#define GEI_CCR3 CCR3

#define voltage_power_supply 8
#define Arr 2880
#define jiduishu 7
#define PI 3.1415926535f
typedef struct 
{
	float Ua,Ub,Uc;
	int Pwm_Ua,Pwm_Ub,Pwm_Uc;
}dianya;

typedef struct 
{
	float Kp,Ki,Kd;
	float target,erro,erro_last,now,i_sum,out;
	
}Str_pid;


void setTorque(float Uq,dianya *dy);
void foc_ControlAngle(float target,Str_pid *pid_ca,dianya *dyca);
#endif

