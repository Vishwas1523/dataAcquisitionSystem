#include "stm32f446xx.h"
#include "HAL_GPIO.h"
#include "HAL_ADC.h"
#include "HAL_TIMER.h"
#include "HAL_DMA.h"

ADC_Handle_t hadc1 = {0};
TIM_Handle_t htim1 = {0};
DMA_Handle_t hdma1 = {0};
uint16_t buff1[100] = {0};
uint16_t buff2[100] = {0};
uint16_t count = 0;
int main(void){

	GPIO_Handle_t hgpio1 = {0};
	hgpio1.instance = GPIO_PORT_A;
	hgpio1.config.mode = GPIO_ANALOG_MODE;
	hgpio1.config.pullUp_pullDown = GPIO_NO_PULLUP_PULLDOWN;
	hgpio1.config.GPIO_PinNumber = 1;
	GPIO_Init(&hgpio1, 1);

	GPIO_Handle_t hgpio2 = {0};
	hgpio2.instance = GPIO_PORT_A;
	hgpio2.config.mode = GPIO_AF_MODE;
	hgpio2.config.pullUp_pullDown = GPIO_NO_PULLUP_PULLDOWN;
	hgpio2.config.alternateFucntion = GPIO_AF_1;
	hgpio2.config.GPIO_PinNumber = 2;

	GPIO_Init(&hgpio2, 2);

	ADC_Config_t config1 = {
			.channel[0] = ADC_CHANNEL_1,
			.continuousMode = ADC_DISABLE,
			.dmaDisableSelection = ADC_ENABLE,
			.dmaEnable = ADC_ENABLE,
			.eocEnable = ADC_ENABLE,
			.eocSelection = ADC_ENABLE,
			.extEventSelection = ADC_TIM2_CC3,
			.extTrigEnable = ADC_TRIG_RISING_EDGE,
			.leftDataAlignment = ADC_DISABLE,
//			.softwareTrigger = ADC_ENABLE,
			.numberOfConversions = ADC_1_CONVERSION,
			.overrunEnable = ADC_ENABLE,
			.resolution = ADC_12_BIT_RESOLUTION,
			.samplingTime = ADC_SAMPLING_CYCLES_3,
			.scanMode = ADC_DISABLE
	};

	TIM_Config_t config2 = {
			.channel = TIM_CHANNEL_3,
			.ocPolarity = TIM_OC_ACTIVE_HIGH,
			.ocdirection = TIM_DIR_UPCOUNTING
	};

	DMA_Stream_Config_t config3 = {
			.direction = DMA_DIRECTION_PER_TO_MEM,
			.peripheralIncrementMode = DMA_DISABLE,
			.memoryIncrementMode = DMA_ENABLE,
			.doubleBufferMode = DMA_ENABLE,
			.PSIZE = DMA_DATA_SIZE_HALF_WORD,
			.MSIZE = DMA_DATA_SIZE_HALF_WORD,
			.priority = DMA_PRIORITY_VERY_HIGH,
			.channel = DMA_CHANNEL0
	};


	hadc1.instance = ADC_1;
	hadc1.config = &config1;
	hadc1.adc = ADC_123;

	htim1.instance = TIM_2;
	htim1.config = &config2;

	hdma1.controller = DMA_2;
	hdma1.instance = DMA2_Stream_0;
	hdma1.config = &config3;

	DMA2_CLOCK_EN;
	ADC_Init(&hadc1);
	DMA_Init(&hdma1);
	DMA_DoubleBuffer_Start(&hdma1, (uint32_t)&hadc1.instance->DR, (uint32_t)&buff1, (uint32_t)&buff2, 100);
	PWM_Init(&htim1);
	PWM_Start(&htim1);
	volatile uint16_t sample = 11;
	while(1){
		sample = hadc1.instance->DR;
		(void)sample;
		count++;
		if(count > 1000) break;
	}
	uint16_t temp = count;
	(void)temp;
	return 0;
}


void ADC_IRQHandler(void) {

    if (hadc1.instance->SR & ADC_SR_EOC_EN) {

    }

    if (hadc1.instance->SR & ADC_SR_OVR_EN){
    	hadc1.instance->SR &= ~ADC_SR_OVR_EN;
    	ADC_DmaPingPongTx(&hadc1, &hdma1, (uint32_t)&buff1, (uint32_t)&buff2);
    }
}

	/* This program is not working */




