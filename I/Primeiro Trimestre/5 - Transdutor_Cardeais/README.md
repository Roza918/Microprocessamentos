# O QUE FOI PROPOSTO:
- Criar um código que exiba os as letras dos pontos cardeais, em 3 displays de 7 segmentos, de acordo com as saídas do transdutor.

### Transdutor:
![Transdutor](https://i.imgur.com/MxGbQ1l.png)
> A carcaça do transdutor está conectado ao Terra, portanto, cuidado para não curtocircuitar a fonte.
# ESQUEMÁTICO DO CIRCUITO
![Esquemático](https://i.imgur.com/UaYZl3P.png)
# EXPLICANDO O CÓDIGO

### Inplementação de variáveis globais:
```
uint8_t contador;
```
```
const uint8_t = mascara 0b11110000;
```
```
enum {N=0,NNE,NNO,NO,ENE,NE,E,ESE,OSO,SO,O,ONO,S,SSO,SSE,SE};
```
```
#define n 0b00110111
#define s 0b01101101
#define e 0b01111001
#define o 0b00111111

#define apaga 0b00
```
```
#define DisplayC2 7
```
### Ativação de clock e definição de pinos:
```
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;
```
```
		GPIOC->MODER&=~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6);

		GPIOC->MODER|=GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0;
```
```

		GPIOC->MODER&=~(GPIO_MODER_MODER7 | GPIO_MODER_MODER8 | GPIO_MODER_MODER9 | GPIO_MODER_MODER10 | GPIO_MODER_MODER11 | GPIO_MODER_MODER12 | GPIO_MODER_MODER13);
	
		GPIOC->MODER|=GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0;
```
```
		
		GPIOB->MODER&=~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6);
		
		GPIOB->MODER|=GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0;
```
```
		
		GPIOA->MODER&=~(GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
```
```
		
		GPIOA->PUPDR&=~(GPIO_PUPDR_PUPDR4 | GPIO_PUPDR_PUPDR5 | GPIO_PUPDR_PUPDR6 | GPIO_PUPDR_PUPDR7);
		
		GPIOA->PUPDR|=GPIO_PUPDR_PUPDR4_1 | GPIO_PUPDR_PUPDR5_1 | GPIO_PUPDR_PUPDR6_1 | GPIO_PUPDR_PUPDR7_1;
```
### Laço de repetição principal:
```
  	  while (1)
  {

  		 contador=GPIOA->IDR & mascara;
  		 contador=contador >>4;
```
```
  		  	  GPIOB->ODR=apaga;
  		  	  GPIOC->ODR=apaga;
```
### Controle de saídas em função de entradas:
```
   	   	   	   	   case N:
   	   	   	   		   GPIOB->ODR=n;
   	   	   	   		   	   break;
```

```
   	   	   	   	   case NNE:
   	   	   	   		   GPIOB->ODR=n;
   	   	   	   		   GPIOC->ODR=n | (e<<DisplayC2);
   	   	   	   		   	   break;
```

```
   	   	   	   	   case NO:
   	   	   	   		   GPIOB->ODR=n;
   	   	   	   		   GPIOC->ODR=o;
   	   	   	   		   	   break;	   	   	   
```

# Circuito Funcionando:
[Link para um vídeo com o circuito funcionando](https://youtu.be/4P4yPC849So) — na falta do transdutor, foi utilizado um dipswitch de 4 chaves, para simular as 4 entradas.



> @Rafael.V.Volkmer | @ImZadoc | 10/05/2022 |
