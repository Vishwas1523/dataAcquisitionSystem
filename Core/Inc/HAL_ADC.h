#include "stm32f446xx.h"
#include <stdint.h>
#ifndef INC_HAL_ADC_H_
#define INC_HAL_ADC_H_

//--------------------------------- ADC Registers -------------------------------------
typedef struct{
	volatile uint32_t SR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMPR1;
	volatile uint32_t SMPR2;
	volatile uint32_t JOFR[4];
	volatile uint32_t HTR;
	volatile uint32_t LTR;
	volatile uint32_t SQR1;
	volatile uint32_t SQR2;
	volatile uint32_t SQR3;
	volatile uint32_t JSQR;
	volatile uint32_t JDR[4];
	volatile uint32_t DR;
}ADC_Type;				/* Registers that are specific to each ADC controller */

typedef struct{
	volatile uint32_t CSR;
	volatile uint32_t CCR;
	volatile uint32_t CDR;
}ADC_Common_Type;		/* Registers shared by all the ADC controllers */

//------------------------------- ADC addresses ----------------------------------

#define ADC_1									(ADC_Type*)0x40012000
#define ADC_2									(ADC_Type*)0x40012100
#define ADC_3									(ADC_Type*)0x40012200
#define ADC_123									(ADC_Common_Type*)0x40012300

//------------------------------- ADC Clock Configurations ------------------------------

#define ADC1_CLK_EN								(RCC->APB2ENR	|= (1U	<<	8))
#define ADC2_CLK_EN								(RCC->APB2ENR	|= (1U	<<	9))
#define ADC3_CLK_EN								(RCC->APB2ENR	|= (1U	<<	10))

//------------------------------- ADC Configuration --------------------------------------

typedef enum{
	ADC_DISABLE = 0,
	ADC_ENABLE
}ADC_Function_t;	/* Helps is disabling and enabling various ADC configs*/

typedef enum{
	ADC_12_BIT_RESOLUTION = 0,	/* Takes 15 ADCCLK Cycles */
	ADC_10_BIT_RESOLUTION,		/* Takes 13 ADCCLK Cycles */
	ADC_8_BIT_RESOLUTION,		/* Takes 11 ADCCLK Cycles */
	ADC_6_BIT_RESOLUTION,		/* Takes 9 ADCCLK Cycles */
}ADC_Resolution_t;		/* Helps in selecting the resolution of ADC conversions */

typedef enum{
	ADC_TIM1_CC1_TRIG = 0,
	ADC_TIM1_CC2,
	ADC_TIM1_CC3,
	ADC_TIM2_CC2,
	ADC_TIM2_CC3,
	ADC_TIM2_CC4,
	ADC_TIM2_TRGO,
	ADC_TIM3_CC1,
	ADC_TIM3_TRGO,
	ADC_TIM4_CC4,
	ADC_TIM5_CC1,
	ADC_TIM5_CC2,
	ADC_TIM5_CC3,
	ADC_TIM8_CC1,
	ADC_TIM8_TRGO,
	ADC_EXTI_LINE_11
}ADC_ExtEvent_t;	/* Helps in choosing external event to start ADC conversion */

typedef enum{
	ADC_TRIG_DISABLE = 0,
	ADC_TRIG_RISING_EDGE,
	ADC_TRIG_FALLING_EDGE,
	ADC_TRIG_RISING_AND_FALLING_EDGE
}ADC_ExtTrig_t;		/* Helps in selecting the polarity of external Trigger */

typedef enum{
	ADC_SAMPLING_CYCLES_3 = 0,
	ADC_SAMPLING_CYCLES_15,
	ADC_SAMPLING_CYCLES_28,
	ADC_SAMPLING_CYCLES_56,
	ADC_SAMPLING_CYCLES_84,
	ADC_SAMPLING_CYCLES_112,
	ADC_SAMPLING_CYCLES_144,
	ADC_SAMPLING_CYCLES_480
}ADC_SamplingTime_t;	/* Helps in selecting the sampling time for each channel */

typedef enum{
	ADC_CHANNEL_0 = 0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
	ADC_CHANNEL_8,
	ADC_CHANNEL_9,
	ADC_CHANNEL_10,
	ADC_CHANNEL_11,
	ADC_CHANNEL_12,
	ADC_CHANNEL_13,
	ADC_CHANNEL_14,
	ADC_CHANNEL_15,
	/* Channel 16, 17 and 18 are special channels */
	ADC_CHANNEL_16, 	/* Temperature Sensor */
	ADC_CHANNEL_17,		/* Reference Voltage */
	ADC_CHANNEL_18		/* Temperature Sensor */
}ADC_ChannelConfig_t; /* Helps in selecting the channel sequence */

typedef enum{
	ADC_1_CONVERSION = 0,
	ADC_2_CONVERSIONS,
	ADC_3_CONVERSIONS,
	ADC_4_CONVERSIONS,
	ADC_5_CONVERSIONS,
	ADC_6_CONVERSIONS,
	ADC_7_CONVERSIONS,
	ADC_8_CONVERSIONS,
	ADC_9_CONVERSIONS,
	ADC_10_CONVERSIONS,
	ADC_11_CONVERSIONS,
	ADC_12_CONVERSIONS,
	ADC_13_CONVERSIONS,
	ADC_14_CONVERSIONS,
	ADC_15_CONVERSIONS,
	ADC_16_CONVERSIONS,
}ADC_NumberOfConversions_t;		/* Helps in configuring number of conversions */

typedef struct __attribute__((packed)){
	ADC_Function_t eocEnable;
	ADC_Function_t scanMode;
	ADC_Resolution_t resolution;
	ADC_Function_t overrunEnable;
	ADC_Function_t continuousMode;
	ADC_Function_t dmaEnable;
	ADC_Function_t dmaDisableSelection;
	ADC_Function_t eocSelection;
	ADC_Function_t leftDataAlignment;	/* ALIGN BIT in CR2 Register -> 0 = Right Alignment, 1 = Left Alignment */
	ADC_ExtEvent_t extEventSelection;
	ADC_ExtTrig_t extTrigEnable;
	ADC_Function_t softwareTrigger;
	ADC_SamplingTime_t samplingTime;	/* Keeping same sample time for all the channels as of now */
	ADC_NumberOfConversions_t numberOfConversions;
	ADC_ChannelConfig_t channel[16];
}ADC_Config_t;		/* ADC configurations */

//------------------------------- ADC Handler ------------------------------------------

typedef struct __attribute__((packed)){
	ADC_Type* instance;
	ADC_Common_Type* adc;
	ADC_Config_t* config;
}ADC_Handle_t;

//-------------------------------- ADC Functions --------------------------------------

void ADC_Init(ADC_Handle_t* hadc);
void ADC_Start(ADC_Handle_t* hadc);
uint16_t ADC_Read(ADC_Handle_t* hadc);

#endif /* INC_HAL_ADC_H_ */
