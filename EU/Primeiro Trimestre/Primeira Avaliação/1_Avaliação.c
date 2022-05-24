//Rafael.V.Volkmer (4324); N° 21 - 24/05/2022. Matricula = 20000213

#include "stm32f4xx.h"

uint16_t contador;

const uint16_t mascara = 0b11110000000;

int main(void)
{

  //Habilita clock dos registradores B e C
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

  //Zerando os pinos de C
  GPIOC->MODER&=~(GPIO_MODER_MODER2 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6);
  //Saídas PC9 PC8 PC7 PC6
  GPIOC->MODER|=GPIO_MODER_MODER2_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0;

  //Entradas PB10 PB9 PB8 PB7
  GPIOB->MODER&=~(GPIO_MODER_MODER10 | GPIO_MODER_MODER9 | GPIO_MODER_MODER8 | GPIO_MODER_MODER7);

  //Zerando PULL-DOWNS
  GPIOB->PUPDR&=~(GPIO_PUPDR_PUPDR10 | GPIO_PUPDR_PUPDR9 | GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR7);
  //PB10 PB9 PB8 PB7 são PULL-DOWNS
  GPIOB->PUPDR|=GPIO_PUPDR_PUPDR10_1 | GPIO_PUPDR_PUPDR9_1 | GPIO_PUPDR_PUPDR8_1 | GPIO_PUPDR_PUPDR7_1;

    while (1)
   {
      contador=GPIOB->IDR & mascara;
      contador=contador >> 7;

      if (
       contador==0b1100
 ||contador==0b0011
 ||contador==0b1010
 ||contador==0b0101
 ||contador==0b1001
 ||contador==0b0110
||contador==0b1111
       )
        {
           GPIOC->ODR|=GPIO_ODR_ODR_2;
           GPIOC->ODR&=~GPIO_ODR_ODR_4;
           GPIOC->ODR&=~GPIO_ODR_ODR_5;
           GPIOC->ODR&=~GPIO_ODR_ODR_6;
        }
      if(
  contador==0b1000
 ||contador==0b0100
 ||contador==0b0010
 ||contador==0b0001
||contador==0b0111
||contador==0b1011
||contador==0b1101
||contador==0b1110
)
        {

             GPIOC->ODR&=~GPIO_ODR_ODR_2;
             GPIOC->ODR|=GPIO_ODR_ODR_4;
             GPIOC->ODR&=~GPIO_ODR_ODR_5;
             GPIOC->ODR&=~GPIO_ODR_ODR_6;
        }
      if(contador==0b1001)
            {
             GPIOC->ODR&=~GPIO_ODR_ODR_2;
             GPIOC->ODR&=~GPIO_ODR_ODR_4;
             GPIOC->ODR|=GPIO_ODR_ODR_5;
             GPIOC->ODR&=~GPIO_ODR_ODR_6;
            }
      if(contador==0b0010)
            {
             GPIOC->ODR&=~GPIO_ODR_ODR_2;
             GPIOC->ODR&=~GPIO_ODR_ODR_4;
             GPIOC->ODR&=~GPIO_ODR_ODR_5;
             GPIOC->ODR|=GPIO_ODR_ODR_6;
            }
      else
      {
             GPIOC->ODR&=~GPIO_ODR_ODR_2;
             GPIOC->ODR&=~GPIO_ODR_ODR_4;
             GPIOC->ODR&=~GPIO_ODR_ODR_5;
             GPIOC->ODR&=~GPIO_ODR_ODR_6;
      }

   }

}
