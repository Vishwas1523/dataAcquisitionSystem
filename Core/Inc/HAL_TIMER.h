#include "stm32f446xx.h"
#include <stdint.h>
#ifndef INC_HAL_TIMER_H_
#define INC_HAL_TIMER_H_

/* These Functions are from TIM2 to TIM5 */

//----------------------------------- TIMER Registers -----------------------------------------
typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RESERVED1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t RESERVED2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t OR;	/* Only for TIM2 and TIM5 */
}TIM_Type;

//------------------------------- TIMER Addresses --------------------------------

#define TIM_2									(TIM_Type*)0x40000000
#define TIM_3									(TIM_Type*)0x40000400
#define TIM_4									(TIM_Type*)0x40000800
#define TIM_5									(TIM_Type*)0x40000C00


//----------------------------- TIMER CLOCK ENABLE ----------------------------------

#define TIM2_CLK_ENABLE							(RCC->APB1ENR |= (1U << 0U))

//-------------------------- TIMER Configurations --------------------------------


typedef enum{
	TIM_CHANNEL_1= 0,
	TIM_CHANNEL_2,
	TIM_CHANNEL_3,
	TIM_CHANNEL_4
}TIM_Channel_t;		/* Helps in selecting channels of a timer */

typedef enum {
	TIM_OUTPUT_MODE = 0,
	TIM_IC_TI1,
	TIM_IC_TI2,
	TIM_IC_TRC,
} TIM_Channel_Dir_t;	/* Defines the direction of channels (Input/Output)
						 * as well as the used input */

typedef enum {
	TIM_OC_FROZEN_MODE = 0,
	TIM_OC_SET_ACTIVE_LVL,
	TIM_OC_SET_INACTIVE_LVL,
	TIM_OC_TOGGLE_MODE,
	TIM_OC_FORCE_ACTIVE_LVL,
	TIM_OC_FORCE_INACTIVE_LVL,
	TIM_OC_PWM_MODE1,
	TIM_OC_PWM_MODE2
} TIM_OC_Mode_t;	/* Helps in configuring output modes */

typedef enum {
	TIM_DISABLE = 0,
	TIM_ENABLE
} TIM_Function_t;	/* General Enable-Disable options */

typedef enum {
	TIM_OC_ACTIVE_HIGH = 0,
	TIM_OC_ACTIVE_LOW
} TIM_OC_Polarity_t;	/* Helps in configuring Outpute mode polarity */

typedef enum {
	TIM_DIR_UPCOUNTING = 0,
	TIM_DIR_DOWNCOUNTING
} TIM_Direction_t;	/* Helps in configuring direction of the counter */

typedef enum {
	TIM_EDGE_ALIGNED_MODE = 0,
	/*If CEN bit in CR1 Register is Set then the following modes will not work */
	TIM_CENTER_ALIGNED_MODE_1,
	TIM_CENTER_ALIGNED_MODE_2,
	TIM_CENTER_ALIGNED_MODE_3,
} TIM_CenterAlign_t;	/*Helps in configuring the central aligned mode */

typedef struct __attribute__((packed)){
	uint16_t ARR;
	uint16_t CCRx;	/* Value is 32 Bit for TIM2 and TIM5 only */
	TIM_Channel_t channel;
	TIM_Channel_Dir_t channelDir;
	TIM_OC_Mode_t ocMode;
	uint16_t icPSC;
	uint16_t icFilter;
	TIM_Function_t ocPreloadEnable;
	TIM_Function_t ocARREnable;
	TIM_OC_Polarity_t ocPolarity;
	TIM_Direction_t ocdirection;
	TIM_CenterAlign_t centerAlignMode;
	TIM_Function_t onePulseMode;
}TIM_Config_t;

//------------------------------ TIMER Handler ------------------------------------------

typedef struct __attribute__((packed)){
	TIM_Type* instance;
	TIM_Config_t* config;
}TIM_Handle_t;

//------------------------------- PWM Functions --------------------------------------

void PWM_Init(TIM_Handle_t* htim);
void PWM_Start(TIM_Handle_t* htim);














#endif /* INC_HAL_TIMER_H_ */
