#include "stm32f446xx.h"
#include "HAL_GPIO.h"
#include "HAL_ADC.h"

int main(void){

	GPIO_Handle_t hgpio1 = {0};
	hgpio1.instance = GPIO_PORT_A;
	hgpio1.config.mode = GPIO_ANALOG_MODE;
	hgpio1.config.pullUp_pullDown = GPIO_NO_PULLUP_PULLDOWN;
	hgpio1.config.GPIO_PinNumber = 0;
	GPIO_Init(&hgpio1, 0);

	ADC_Handle_t hadc1 = {0};
	ADC_Config_t config1 = {
			.channel[0] = ADC_CHANNEL_0,
			.continuousMode = ADC_DISABLE,
			.dmaDisableSelection = ADC_DISABLE,
			.dmaEnable = ADC_DISABLE,
			.eocEnable = ADC_ENABLE,
			.eocSelection = ADC_ENABLE,
			.extTrigEnable = ADC_TRIG_DISABLE,
			.leftDataAlignment = ADC_DISABLE,
			.numberOfConversions = ADC_1_CONVERSION,
			.overrunEnable = ADC_DISABLE,
			.resolution = ADC_12_BIT_RESOLUTION,
			.samplingTime = ADC_SAMPLING_CYCLES_480,
			.scanMode = ADC_DISABLE
	};

	hadc1.instance = ADC_1;
	hadc1.config = &config1;
	hadc1.adc = ADC_123;

	ADC_Init(&hadc1);
	ADC_Start(&hadc1);

	uint16_t sample = 0x00;
	sample = ADC_Read(&hadc1);
	(void)sample;
	while(1){


	}
	return 0;
}


