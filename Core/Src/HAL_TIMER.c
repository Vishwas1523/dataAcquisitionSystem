#include "HAL_TIMER.h"

void PWM_Init(TIM_Handle_t* htim){

	switch (htim->config->channel){
	case TIM_CHANNEL_1:
		/* Configuring TIM in output mode */
		htim->instance->CCMR1	&= ~(3U	<< 0U);
		htim->instance->CCMR1	|= TIM_OUTPUT_MODE << 0;

		/* Configuring Mode of Output Compare Mode */
		htim->instance->CCMR1	&= ~(7U	<< 4U);
		htim->instance->CCMR1	|=	TIM_OC_PWM_MODE1 << 4U;

		/* Configuring the polarity of Channel for PWM */
		htim->instance->CCER	&= ~(1U << 1U);
		htim->instance->CCER    |= htim->config->ocPolarity	<< 1U;
		break;

	case TIM_CHANNEL_2:
		/* Configuring TIM in output mode */
		htim->instance->CCMR1	&= ~(3U	<< 8U);
		htim->instance->CCMR1	|= TIM_OUTPUT_MODE << 8;

		/* Configuring Mode of Output Compare Mode */
		htim->instance->CCMR1	&= ~(7U	<< 12U);
		htim->instance->CCMR1	|=	TIM_OC_PWM_MODE1 << 12U;

		/* Configuring the polarity of Channel for PWM */
		htim->instance->CCER	&= ~(1U << 5U);
		htim->instance->CCER    |= htim->config->ocPolarity	<< 5U;
		break;

	case TIM_CHANNEL_3:
		/* Configuring TIM in output mode */
		htim->instance->CCMR2	&= ~(3U	<< 0U);
		htim->instance->CCMR2	|= TIM_OUTPUT_MODE << 0;

		/* Configuring Mode of Output Compare Mode */
		htim->instance->CCMR2	&= ~(7U	<< 4U);
		htim->instance->CCMR2	|=	TIM_OC_PWM_MODE1 << 4U;

		/* Enabling Channel 3 */
		htim->instance->CCER	&= ~(1U << 8U);
		htim->instance->CCER	|= (1U << 8U);
		/* Configuring the polarity of Channel for PWM */
		htim->instance->CCER	&= ~(1U << 9U);
		htim->instance->CCER    |= htim->config->ocPolarity	<< 9U;
		break;

	case TIM_CHANNEL_4:
		break;
	}

	/* Configuring Direction of the counting */
	htim->instance->CR1		&= ~(1U << 4U);
	htim->instance->CR1		|= htim->config->ocdirection << 4U;

	/* Configuring the TIM as edge aligned */
	htim->instance->CR1		&= ~(3U << 5U);
	htim->instance->CR1		|= TIM_EDGE_ALIGNED_MODE << 5U;

	/* Giving values to these registers which can give:
	 * A duty cycle of 50% and a frequency of 1khz */
	htim->instance->ARR	= 0xAFC7;
	htim->instance->CCR3 = 0x57E4;
	htim->instance->PSC = 0;

	/* Enabling timer 2 clock */
	TIM2_CLK_ENABLE;
}


void PWM_Start(TIM_Handle_t* htim){
	htim->instance->CR1 |= 1U	<<	0U;
}












