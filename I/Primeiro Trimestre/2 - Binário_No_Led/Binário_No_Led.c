//Rafael.V.Volkmer (4324); N° 21

#include "stm32f4xx.h"

uint8_t contador;

int main(void)
{

  //Habilita clock dos registradores B e C
  RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;
  
  //Zerando os pinos de C
  GPIOC->MODER&=~(GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3);
  //Saídas PC1 PC2 e PC3
  GPIOC->MODER|=GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 |  GPIO_MODER_MODER3_0;
  
  //Entradas PB1 e PB2
  GPIOB->MODER&=~(GPIO_MODER_MODER1 | GPIO_MODER_MODER2);
  
  //Zerando PULL-DOWNS
  GPIOB->PUPDR&=~(GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR2);
  //PB1 e PB2 são PULL-DOWNS
  GPIOB->PUPDR|=GPIO_PUPDR_PUPDR1_1 | GPIO_PUPDR_PUPDR2_1;

    while (1)
   {
      contador=GPIOB->IDR & 0b0110;
      contador = contador >>1;

         switch(contador)
           {

              case 1:
                GPIOC->ODR=0b010;
                    break;

              case 2:
                GPIOC->ODR=0b110;
                    break;

              case 3:
                 GPIOC->ODR=0b1110;
                    break;
                    
             default:
                  GPIOC->ODR=0b0;

           }
  }
}
