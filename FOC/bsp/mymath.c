#include "math.h"
#include "mymath.h"
#include "as5600.h"
#include "main.h"




/* 位置PID */
void pid_sum(Str_pid *pid)
{
	pid->erro = pid->target - pid->now;
	pid->i_sum += pid->erro;
	pid->out = pid->Kp * pid->erro + pid->Ki * pid->i_sum + pid->Kd * (pid->erro - pid->erro_last);
	pid->erro_last=	pid->erro;
	
}


void setTorque(float Uq,dianya *dy) {
  float Ualpha,Ubeta;
  float angle_el = bsp_as5600GetAngle();
  angle_el	= (angle_el*jiduishu)*PI/180.0;
  Uq=_constrain(Uq,-voltage_power_supply/2,voltage_power_supply/2);
	
  // 帕克逆变换
  Ualpha =  -Uq*sin(angle_el); 
  Ubeta =   Uq*cos(angle_el); 

  // 克拉克逆变换
  dy->Ua = Ualpha + voltage_power_supply/2;
  dy->Ub = (sqrt(3)*Ubeta-Ualpha)/2 + voltage_power_supply/2;
  dy->Uc = (-Ualpha-sqrt(3)*Ubeta)/2 + voltage_power_supply/2;
	
  _constrain(dy->Ua,0,voltage_power_supply);	
  _constrain(dy->Ub,0,voltage_power_supply);	
  _constrain(dy->Uc,0,voltage_power_supply);	
	
  dy->Pwm_Ua = (int)(dy->Ua / voltage_power_supply * Arr);
  dy->Pwm_Ub = (int)(dy->Ub / voltage_power_supply * Arr);
  dy->Pwm_Uc = (int)(dy->Uc / voltage_power_supply * Arr);	
  
  GET_TIM->GEI_CCR1 = dy->Pwm_Ua;
  GET_TIM->GEI_CCR2 = dy->Pwm_Ub;
  GET_TIM->GEI_CCR3 = dy->Pwm_Uc;
	
}

void foc_ControlAngle(float target,Str_pid *pid_ca,dianya *dyca)
{
	pid_ca->now = bsp_as5600GetAngle();
	if(pid_ca->now<180)pid_ca->now = -pid_ca->now;
	else 
	{
		pid_ca->now = 360-pid_ca->now; 
	}
	pid_ca->target = target;
	pid_sum(pid_ca);
	setTorque(pid_ca->out,dyca);
	GET_TIM->GEI_CCR1 = dyca->Pwm_Ua;
	GET_TIM->GEI_CCR2 = dyca->Pwm_Ub;
	GET_TIM->GEI_CCR3 = dyca->Pwm_Uc;
}


