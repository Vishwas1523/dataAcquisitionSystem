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

//-------------------------- TIMER Configurations --------------------------------


typedef enum{

}TIM_Channel_t;

typedef enum {

} TIM_Channel_Dir_t;	/* Defines the direction of channels (Input/Output)
						 * as well as the used input */

typedef enum {

} TIM_OC_Mode_t;

typedef enum {

} TIM_IC_Prescaler_t;

typedef enum {

} TIM_IC_Filter_t;

typedef enum {

} TIM_Function_t;

typedef enum {

} TIM_Polarity_t;

typedef enum {

} TIM_Direction_t;

typedef enum {

} TIM_CenterAlign_t;

typedef struct __attribute__((packed)){
	uint16_t ARR;
	uint32_t Counter;	/* Value is 32 Bit for TIM2 and TIM5 only */
	TIM_Channel_t channel;
	TIM_Channel_Dir_t channelDir;
	TIM_OC_Mode_t ocMode;
	TIM_IC_Prescaler_t icPSC;
	TIM_IC_Filter_t icFilter;
	TIM_Function_t ocPreloadEnable;
	TIM_Function_t ocARREnable;
	TIM_Polarity_t ocPolarity;
	TIM_Direction_t ocdirection;
	TIM_CenterAlign_t centerAlignMode;
}TIM_Config_t;

//------------------------------ TIMER Handler ------------------------------------------

typedef struct __attribute__((packed)){
	TIM_Type* instance;
	TIM_Config_t config;
}TIM_Handle_t;



















#endif /* INC_HAL_TIMER_H_ */
