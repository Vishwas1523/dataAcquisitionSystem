#include "stm32f446xx.h"
#include "HAL_GPIO.h"
#include "HAL_ADC.h"

ADC_Handle_t hadc1 = {0};

int main(void){

	GPIO_Handle_t hgpio1 = {0};
	hgpio1.instance = GPIO_PORT_A;
	hgpio1.config.mode = GPIO_ANALOG_MODE;
	hgpio1.config.pullUp_pullDown = GPIO_NO_PULLUP_PULLDOWN;
	hgpio1.config.GPIO_PinNumber = 1;
	GPIO_Init(&hgpio1, 1);

	ADC_Config_t config1 = {
			.channel[0] = ADC_CHANNEL_1,
			.continuousMode = ADC_DISABLE,
			.dmaDisableSelection = ADC_DISABLE,
			.dmaEnable = ADC_DISABLE,
			.eocEnable = ADC_ENABLE,
			.eocSelection = ADC_ENABLE,
			.extTrigEnable = ADC_TRIG_DISABLE,
			.leftDataAlignment = ADC_DISABLE,
			.softwareTrigger = ADC_ENABLE,
			.numberOfConversions = ADC_1_CONVERSION,
			.overrunEnable = ADC_DISABLE,
			.resolution = ADC_12_BIT_RESOLUTION,
			.samplingTime = ADC_SAMPLING_CYCLES_3,
			.scanMode = ADC_DISABLE
	};

	hadc1.instance = ADC_1;
	hadc1.config = &config1;
	hadc1.adc = ADC_123;

	ADC_Init(&hadc1);

	NVIC_EnableIRQ(ADC_IRQn);
	__enable_irq();

	while(1){
		ADC_SwStart(&hadc1);
	}
	return 0;
}


void ADC_IRQHandler(void) {

    if (hadc1.instance->SR & (1U << 1)) {

    }
}






