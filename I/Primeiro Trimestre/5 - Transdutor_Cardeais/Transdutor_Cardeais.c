//Rafael.V.Volkmer (4324); Nº21.

#include "stm32f4xx.h"

uint16_t contador;

const uint8_t Mascara = 0b11110000;

struct SaidasDisplay
{
	const int Apaga = 0b00000000;
	const int N = 0b00110111;
	const int S = 0b01101101;
	const int E = 0b00111000;
	const int O = 0b00111111;
}Display;

struct EntradaTransdutor
{
	const int Norte = 0b0000;       // 0 decimal
	const int Nordeste = 0b0101;    // 5 decimal
	const int Leste = 0b0110;       // 6 decimal
	const int Sudeste = 0b1111;     // 15 decimal
	const int Sul = 0b1100;         // 12 decimal
	const int Sudoeste = 0b1001;    // 9 decimal
	const int Oeste = 0b1010;       // 10 decimal
	const int Noroeste = 0b0011;    // 3 decimal
}PontosCardeais;

int main(void)
{

	// Habilita clock dos registradores B, C e A
	RCC->AHBE1NR|=RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

	//Zerando os pinos C
	GPIOC->MODER&=~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6);
	//Saídas - PC0, PC1, PC2, PC3, PC4, PC5, PC6
	GPIOC->MODER|=GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0;

	//Zerando os pinos B
	GPIOB->MODER&=~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6);
	//Saídas - PB0, PB1, PB2, PB3, PB4, PB5, PB6
	GPIOB->MODER|=GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0;

	//Zerando os pinos A | Entradas PC4, PC5, PC6, PC7
	GPIOA->MODER&=~(GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7);

	// Zerando os os pinos PULL UP
	GPIOA->PUPDR&=~(GPIO_PUPDR_PUPDR4 | GPIO_PUPDR_PUPDR5 | GPIO_PUPDR_PUPDR6 | GPIO_PUPDR_PUPDR7);
	//Entradas - PC4, PC5, PC6, PC7 são PULL UP
	GPIOA->PUPDR|=GPIO_PUPDR_PUPDR4_0 | GPIO_PUPDR_PUPDR5_0 | GPIO_PUPDR_PUPDR6_0 | GPIO_PUPDR_PUPDR7_0;



  while (1)
  {

	 contador=GPIOC->IDR & Mascara; //Mascara IDR com as entradas PC0, PC1, PC2, PC3
	 contador = contador >>4;

			  switch(contador)
			 {
			  case PontosCardeais.Norte:
				  GPIOB->ODR=Display.N | GPIOA->ODR=Display.Apaga;
				  	  	  	  break;

			  case PontosCardeais.Sul:
				  GPIOB->ODR=Display.S | GPIOA->ODR=Display.Apaga;
				  	  	  	  break;

			  case PontosCardeais.Leste:
				  GPIOB->ODR=Display.E | GPIOA->ODR=Display.Apaga;
			  				  break;

			  case PontosCardeais.Oeste:
				  GPIOB->ODR=Display.O | GPIOA->ODR=Display.Apaga;
			  				  break;

			  case PontosCardeais.Nordeste:
				  GPIOB->ODR=Display.N | GPIOA->ODR=Display.E;
			  				  break;

			  case PontosCardeais.Sudeste:
				  GPIOB->ODR=Display.S | GPIOA->ODR=Display.E;
			  				  break;

			  case PontosCardeais.Noroeste:
				  GPIOB->ODR=Display.N | GPIOA->ODR=Display.O;
			  				  break;

			  case PontosCardeais.Sudoeste:
				  GPIOB->ODR=Display.S | GPIOA->ODR=Display.O;
			  				  break;

			  default:
				  GPIOB->ODR=0b0;

			 }

  }

}
