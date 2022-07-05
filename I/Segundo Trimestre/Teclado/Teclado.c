#include "stm32f4xx.h"

uint8_t tempo;
uint16_t teclas;
uint16_t nota;

//Definindo 4hz como frequência do CNT
//Tr = Tck_int * (PSC+1) * (ARR+1) | Tr = 16khz
#define FrequenciaPSC (4000-1)
#define FrequenciaARR (1000-1)

int main(void)
{
	//Ativando clock GPIOA e TIMER10
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;

	//Zerando e definindo PA6 como saída
	GPIOA->MODER &=~ GPIO_MODER_MODER6 | GPIO_MODER_MODER7;
	GPIOA->MODER |= GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;

	//Definindo frequências para o TIMER10
	TIM10->PSC = FrequenciaPSC;
	TIM10->ARR= FrequenciaARR;

	//Habilitando contagem do TIMER10
	TIM10->CR1 = TIM_CR1_CEN|TIM_CR1_ARPE;

  while (1)
  {
	  teclas = GPIOA->IDR & GPIO_IDR_IDR_6;
	  tempo = TIM10->SR & TIM_SR_UIF;
	  nota = TIM10->ARR;

		 switch(teclas)
		 {
		  case 1:
			  nota=1;
			  break;
		 }

		 if (teclas)
		 {
			 if (TIM10->SR & TIM_SR_UIF)
			 {
				GPIOA->ODR^=GPIO_ODR_ODR_7;
			 }
		 }
		 else
				GPIOA->ODR&=~GPIO_ODR_ODR_7;
  }
}
