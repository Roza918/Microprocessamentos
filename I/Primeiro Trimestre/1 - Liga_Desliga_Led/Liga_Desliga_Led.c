//Rafael.V.Volkmer (4324); N°21

#include "stm32f4xx.h"

uint16_t contador;

int main(void)
{

      // Habilita clock dos registradores B e C
      RCC->AHBE1NR|=RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;
	    
      //Entrada PB1
      GPIOB->MODER&=~PIO_MODER_MODER1;
      
      //Zerando pinos B
      GPIOC->MODER&=~PIO_MODER_MODER1;
      //Saída PB1
      GPIOC->MODER|=PIO_MODER_MODER1_0;
      
      //Zerando PULL-DOWNS
      GPIOB->PUPDR&=~GPIO_PUPDR_PUPDR2;
      //PB1 é PULL-DOWN
      GPIOB->PUPDR|=GPIO_PUPDR_PUPDR1_1;


        while (1)
       {
          	entradas=GPIOB->IDR & 0b010; //Mascara com PB1

	            if (entradas==0b010)
         
		              GPIOC->ODR=0b001; // Liga led
	            else
		              GPIOC->ODR=0b000; // Desliga led
       }
}
