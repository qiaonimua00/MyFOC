#include "main.h"

void bldc_start()
{
	TIM2->CCR1 = 20;
	TIM2->CCR2 = 0;	
	TIM2->CCR3 = 0;	
	HAL_Delay(100);
}



void control(unsigned char step)
{
	switch(step)
	{
		case 1:
		TIM2->CCR1 = 20;
		TIM2->CCR2 = 0;	
		TIM2->CCR3 = 0;	
		break;
		

		case 2:
		TIM2->CCR1 = 20;
		TIM2->CCR2 = 20;	
		TIM2->CCR3 = 0;	
		break;

		case 3:
		TIM2->CCR1 = 0;
		TIM2->CCR2 = 20;	
		TIM2->CCR3 = 0;	
		break;		
		
		case 4:
		TIM2->CCR1 = 0;
		TIM2->CCR2 = 20;	
		TIM2->CCR3 = 20;	
		break;		
		
		case 5:
		TIM2->CCR1 = 0;
		TIM2->CCR2 = 0;	
		TIM2->CCR3 = 20;	
		break;		
		
		case 6:
		TIM2->CCR1 = 20;
		TIM2->CCR2 = 0;	
		TIM2->CCR3 = 20;	
		break;	

		default:
		break;
	}
}
