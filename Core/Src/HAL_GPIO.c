#include "HAL_GPIO.h"

//---------------------------------------------------------------------------------------------------------------

void GPIO_Clock_Enable(GPIO_Handle_t* hgpio){
	if (hgpio->instance == GPIO_PORT_A){
	    GPIOA_CLK_ENABLE;
	} else if (hgpio->instance == GPIO_PORT_B){
	    GPIOB_CLK_ENABLE;
	} else if (hgpio->instance == GPIO_PORT_C){
	    GPIOC_CLK_ENABLE;
	} else if (hgpio->instance == GPIO_PORT_D){
	    GPIOD_CLK_ENABLE;
	} else if (hgpio->instance == GPIO_PORT_E){
	    GPIOE_CLK_ENABLE;
	} else if (hgpio->instance == GPIO_PORT_F){
	    GPIOF_CLK_ENABLE;
	} else if (hgpio->instance == GPIO_PORT_G){
	    GPIOG_CLK_ENABLE;
	} else if (hgpio->instance == GPIO_PORT_H){
	    GPIOH_CLK_ENABLE;
	}
}

//---------------------------------------------------------------------------------------------------------------

void GPIO_Output_Init(GPIO_Handle_t* hgpio, uint8_t pinNumber){

	/* Configuring the output type */
	hgpio->instance->OTYPER &= ~(1U << pinNumber);
	hgpio->instance->OTYPER |= (hgpio->config.otype << pinNumber);

	/* Configuring the output speed */
	hgpio->instance->OSPEEDR &= ~(3U << (2*pinNumber));
	hgpio->instance->OSPEEDR |= (hgpio->config.ospeed << (2*pinNumber));

}

//---------------------------------------------------------------------------------------------------------------

void GPIO_AF_Init(GPIO_Handle_t* hgpio, uint8_t pinNumber){
	/* Configuring alternate functions for Pin Number 0 to 7 */
	if(pinNumber < 8){
		hgpio->instance->AFRL &= ~(15U << (4*pinNumber));
		hgpio->instance->AFRL |= hgpio->config.alternateFucntion << (4*pinNumber);
	}

	/* Configuring alternate functions for Pin Number 8 to 15 */
	if (pinNumber > 7 && pinNumber < 16){
		pinNumber = pinNumber - 8;
		hgpio->instance->AFRH &= ~( 15U << (4*pinNumber));
		hgpio->instance->AFRH |= hgpio->config.alternateFucntion << (4*pinNumber);
	}
}

//---------------------------------------------------------------------------------------------------------------

void GPIO_Init(GPIO_Handle_t* hgpio, uint8_t pinNumber){

	GPIO_Clock_Enable(hgpio);		/* Enabling clocks */

	hgpio->instance->MODER &= ~(3U<<(2*pinNumber));
	hgpio->instance->MODER |= hgpio->config.mode<<(2*pinNumber); /* Configuring Mode */

	/* Configuring GPIO output mode */
	if (hgpio->config.mode == GPIO_OUTPUT_MODE)	GPIO_Output_Init(hgpio, pinNumber);

	/* Configuring GPIO alternate function mode */
	if (hgpio->config.mode == GPIO_AF_MODE)	GPIO_AF_Init(hgpio, pinNumber);

	/* Configuring Pull Up and Pull down */
	hgpio->instance->PUPDR &= ~(3U<<(2*pinNumber));
	hgpio->instance->PUPDR |= hgpio->config.pullUp_pullDown<<(2*pinNumber);
}

//---------------------------------------------------------------------------------------------------------------

void GPIO_Write(GPIO_Handle_t* hgpio, uint8_t pinNumber, GPIO_State_t state){

	if(state == GPIO_HIGH) hgpio->instance->BSRR = (1U << pinNumber);

	else if (state == GPIO_LOW) hgpio->instance->BSRR = (1U << (pinNumber + 16));

}

//---------------------------------------------------------------------------------------------------------------

inline void GPIO_Toggle(GPIO_Handle_t* hgpio, uint8_t pinNumber){

	hgpio->instance->ODR ^= (1U << pinNumber);

}

//---------------------------------------------------------------------------------------------------------------

inline GPIO_State_t GPIO_Read(GPIO_Handle_t* hgpio, uint8_t pinNumber){

	if(hgpio->instance->IDR & (1U << pinNumber)) return GPIO_HIGH;
	else return GPIO_LOW;

}

//---------------------------------------------------------------------------------------------------------------


