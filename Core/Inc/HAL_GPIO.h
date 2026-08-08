
#include <stdint.h>
#ifndef INC_HAL_GPIO_H_
#define INC_HAL_GPIO_H_
#include "stm32f446xx.h"


//-----------------------------------GPIO Registers---------------------------------------
typedef struct __attribute__((packed)){
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	const volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}GPIO_Type;

//---------------------------GPIO Ports and their addresses----------------

#define GPIO_PORT_A										(GPIO_Type*)0x40020000
#define GPIO_PORT_B										(GPIO_Type*)0x40020400
#define GPIO_PORT_C										(GPIO_Type*)0x40020800
#define GPIO_PORT_D										(GPIO_Type*)0x40020C00
#define GPIO_PORT_E										(GPIO_Type*)0x40021000
#define GPIO_PORT_F										(GPIO_Type*)0x40021400
#define GPIO_PORT_G										(GPIO_Type*)0x40021800
#define GPIO_PORT_H										(GPIO_Type*)0x40021C00


//------------------------------- GPIO Clock Configuration ---------------------------

#define GPIOA_CLK_ENABLE									(RCC->AHB1ENR |= (1<<0))
#define GPIOB_CLK_ENABLE									(RCC->AHB1ENR |= (1<<1))
#define GPIOC_CLK_ENABLE									(RCC->AHB1ENR |= (1<<2))
#define GPIOD_CLK_ENABLE									(RCC->AHB1ENR |= (1<<3))
#define GPIOE_CLK_ENABLE									(RCC->AHB1ENR |= (1<<4))
#define GPIOF_CLK_ENABLE									(RCC->AHB1ENR |= (1<<5))
#define GPIOG_CLK_ENABLE									(RCC->AHB1ENR |= (1<<6))
#define GPIOH_CLK_ENABLE									(RCC->AHB1ENR |= (1<<7))

//---------------------------------- GPIO Configuration ---------------------------------

typedef enum{
	GPIO_INPUT_MODE = 0,
	GPIO_OUTPUT_MODE,
	GPIO_AF_MODE,
	GPIO_ANALOG_MODE
}GPIO_Mode_t;			/* Helps in choosing different GPIO Modes*/


typedef enum{
	GPIO_OUTPUT_PUSHPULL = 0,
	GPIO_OUTPUT_OPENDRAIN
}GPIO_Output_t;			/* Helps in choosing different GPIO Output Types
						 * (How floating value will be treated)*/


typedef enum{
	GPIO_SPEED_LOW = 0,
	GPIO_SPEED_MEDIUM,
	GPIO_SPEED_FAST,
	GPIO_SPEED_HIGH		/* High means Very Fast */
}GPIO_OutputSpeed_t;	/* Helps in choosing different GPIO Output Speed */

typedef enum{
	GPIO_NO_PULLUP_PULLDOWN = 0,
	GPIO_PULL_UP,
	GPIO_PULLDOWN
}GPIO_PuPd_t;		/* If GPIO output type is Pull-Up and Pull-Down, these values
					 * lets us choose between pull-up and pull-down */

typedef enum{
	GPIO_AF_0 = 0, GPIO_AF_1, GPIO_AF_2, GPIO_AF_3, GPIO_AF_4,
	GPIO_AF_5, GPIO_AF_6, GPIO_AF_7, GPIO_AF_8, GPIO_AF_9,
	GPIO_AF_10, GPIO_AF_11, GPIO_AF_12, GPIO_AF_13, GPIO_AF_14, GPIO_AF_15
}GPIO_AF_t;			/* Helps in choosing different alternate function modes */


//----------------------------- GPIO State ------------------------------------------

typedef enum{
	GPIO_LOW = 0,
	GPIO_HIGH
}GPIO_State_t;


//-----------------------------GPIO Configuration ----------------------------------------------

typedef struct __attribute__((packed)){
	uint8_t GPIO_PinNumber;
	GPIO_Mode_t mode;
	GPIO_Output_t otype;
	GPIO_OutputSpeed_t ospeed;
	GPIO_PuPd_t pullUp_pullDown;
	GPIO_AF_t alternateFucntion;
}GPIO_Config_t;

//-------------------------------- GPIO Handler ------------------------------------

typedef struct __attribute__((packed)){
	GPIO_Type* instance;
	GPIO_Config_t config;
//	GPIO_State_t state;
}GPIO_Handle_t;

//----------------------------- GPIO Functions -----------------------------------------

void GPIO_Clock_Enable(GPIO_Handle_t* hgpio);
void GPIO_Init(GPIO_Handle_t* hgpio, uint8_t pinNumber);
void GPIO_Output_Init(GPIO_Handle_t* hgpio, uint8_t pinNumber);
void GPIO_AF_Init(GPIO_Handle_t* hgpio, uint8_t pinNumber);
GPIO_State_t GPIO_Read(GPIO_Handle_t* hgpio, uint8_t pinNumber);
void GPIO_Toggle(GPIO_Handle_t* hgpio, uint8_t pinNumber);
void GPIO_Write(GPIO_Handle_t* hgpio, uint8_t pinNumber, GPIO_State_t state);


#endif /* INC_HAL_GPIO_H_ */
