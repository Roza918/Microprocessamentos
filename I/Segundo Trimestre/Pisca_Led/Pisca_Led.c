#include "stm32f4xx.h"

uint8_t tempo;
uint8_t flag = TIM_SR_UIF;
uint8_t habilitado = TIM_CR1_CEN;

//Definindo 4hz como frequência do CNT
//Tr = Tck_int * (PSC+1) * (ARR+1) | Tck_int = 16khz
#define FrequenciaPSC (4000-1)
#define FrequenciaARR (1000-1)

const int EstadoDoLed[2]=
{
		0b00000000, //Desligado
		0b01000000  //Ligado
};

int main(void)
{
	//Ativando clock GPIOA e TIMER10
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;

	//Zerando e definindo PA6 como saída
	GPIOA->MODER &=~ GPIO_MODER_MODER6;
	GPIOA->MODER |= GPIO_MODER_MODER6_0;

	//Definindo frequências para o TIMER10
	TIM10->PSC = FrequenciaPSC;
	TIM10->ARR = FrequenciaARR;
	
	//Habilitando contagem do TIMER10
	TIM10->CR1 = habilitado;

  while (1)
  {
	  //Mascara com o bit de estouro do TIMER10
	  tempo = TIM10->SR & flag;

	  GPIOA->ODR = EstadoDoLed[tempo];
	  
	  //Zerando o bit de estouro do TIMER10
	  TIM10->SR &=~ falg;
  }
}
