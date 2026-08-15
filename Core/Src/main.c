#include "stm32f446xx.h"
#include "HAL_GPIO.h"
#include "HAL_ADC.h"
#include "HAL_TIMER.h"

ADC_Handle_t hadc1 = {0};
TIM_Handle_t htim1 = {0};
volatile uint16_t count = 0;
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
			.dmaDisableSelection = ADC_DISABLE,
			.dmaEnable = ADC_DISABLE,
			.eocEnable = ADC_ENABLE,
			.eocSelection = ADC_ENABLE,
			.extEventSelection = ADC_TIM2_CC3,
			.extTrigEnable = ADC_TRIG_RISING_EDGE,
			.leftDataAlignment = ADC_DISABLE,
//			.softwareTrigger = ADC_ENABLE,
			.numberOfConversions = ADC_1_CONVERSION,
			.overrunEnable = ADC_DISABLE,
			.resolution = ADC_12_BIT_RESOLUTION,
			.samplingTime = ADC_SAMPLING_CYCLES_3,
			.scanMode = ADC_DISABLE
	};

	TIM_Config_t config2 = {
			.channel = TIM_CHANNEL_3,
			.ocPolarity = TIM_OC_ACTIVE_HIGH,
			.ocdirection = TIM_DIR_UPCOUNTING
	};

	hadc1.instance = ADC_1;
	hadc1.config = &config1;
	hadc1.adc = ADC_123;

	htim1.instance = TIM_2;
	htim1.config = &config2;

	ADC_Init(&hadc1);
//	ADC_SwStart(&hadc1);
	PWM_Init(&htim1);
	PWM_Start(&htim1);
	volatile uint16_t sample = 0;
	while(1){
		if (hadc1.instance->SR & (1U << 1)) {
		    	count++;
				sample = hadc1.instance->DR;
				(void)sample;
		    }
		if(count > 1000) break;
	}
	uint8_t temp = count;
	(void)temp;
	return 0;
}


void ADC_IRQHandler(void) {

    if (hadc1.instance->SR & (1U << 1)) {
    }
}






