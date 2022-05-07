//Rafael.V.Volkmer (4324); Nº21 - 06/05/2022.

#include "stm32f4xx.h"

uint8_t contador;

const uint8_t Mascara = 0b11110000;

//Struct que dá nome às variáveis de saída.
struct SaidasDisplay
{
	int Apaga;
	int N;
	int S;
	int E;
	int O;
};

//Struct que dá nome às variáveis de entrada.
struct EntradaTransdutor
{
	int Norte;
	int Nordeste;
	int Leste;
	int Sudeste;
	int Sul;
	int Sudoeste;
	int Oeste;
	int Noroeste;
};

int main(void)
{

	// Habilita clock dos registradores B, C e A
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

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

	//Declarando variáveis de saída.
	struct SaidasDisplay Display;

	Display.Apaga = 0b00000000;
	Display.N = 0b00110111;
	Display.S = 0b01101101;
	Display.E = 0b00111000;
	Display.O = 0b00111111;

	//Declarando variáveis de entrada.
	struct EntradaTransdutor PontosCardeais;

	PontosCardeais.Norte = 0b0000;
	PontosCardeais.Nordeste = 0b0101;
	PontosCardeais.Leste = 0b0110;
	PontosCardeais.Sudeste = 0b1111;
	PontosCardeais.Sul = 0b1100;
	PontosCardeais.Sudoeste = 0b1001;
	PontosCardeais.Oeste = 0b1010;
	PontosCardeais.Noroeste = 0b0011;

  while (1)
  {


	 contador=GPIOA->IDR & Mascara; //Mascara IDR com as entradas PA4, PA5, PA6, PA7
	 contador=contador >>4; //Faz com que PA4, PA5, PA6 e PA7 tornem-se PA0, PA1, PA2 e PA3 para parâmetros de contagem.

	 	 	if(contador==PontosCardeais.Norte){
	 	 	 	GPIOB->ODR=Display.N;
	 	 	 	GPIOC->ODR=Display.Apaga;
	 	 	}

	 	 	if(contador==PontosCardeais.Sul){
	 	 	 	GPIOB->ODR=Display.S;
	 	 		GPIOC->ODR=Display.Apaga;
	 	 	}

	 	 	if(contador==PontosCardeais.Leste){
	 	 		GPIOB->ODR=Display.E;
	 	 		GPIOC->ODR=Display.Apaga;
	 	 	}

	 	 	if(contador==PontosCardeais.Oeste){
	 	 		GPIOB->ODR=Display.O;
	 	 		GPIOC->ODR=Display.Apaga;
	 	 	}

	 	 	if(contador==PontosCardeais.Nordeste){
	 	 		GPIOB->ODR=Display.N;
	 	 		GPIOC->ODR=Display.E;
	 	 	}

	 	 	if(contador==PontosCardeais.Sudeste){
	 	 		GPIOB->ODR=Display.S;
	 	 		GPIOC->ODR=Display.E;
	 	 	}

	 	 	if(contador==PontosCardeais.Noroeste){
	 	 		GPIOB->ODR=Display.N;
	 	 		GPIOC->ODR=Display.O;
	 	 	}

	 	 	if(contador==PontosCardeais.Sudoeste){
	 	 	 	GPIOB->ODR=Display.S;
	 	 	 	GPIOC->ODR=Display.O;
	 	 	}
	 	 		else{
	 	 			GPIOB->ODR=Display.Apaga;
	 	 			GPIOC->ODR=Display.Apaga;
	 	 		}
  }

}
