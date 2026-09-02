#include "stm32f446xx.h"
#include "HAL_GPIO.h"
#include "HAL_ADC.h"
#include "HAL_TIMER.h"
#include "HAL_DMA.h"
#include "HAL_UART.h"
#define BUFFER_SIZE					100
ADC_Handle_t hadc1 = {0};
TIM_Handle_t htim1 = {0};
DMA_Handle_t hdma1 = {0};
DMA_Handle_t hdma2 = {0};
UART_Handle_t huart1 = {0};
uint16_t buff1[BUFFER_SIZE] = {0};
uint16_t buff2[BUFFER_SIZE] = {0};
uint8_t ubuff1[100] = {7};
uint8_t ubuff2[100] = {0};
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
	hgpio2.config.alternateFucntion = GPIO_AF_7;
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

	UART_Config_t config4 ={
			.dmaTxEnable = UART_ENABLE,
			.intTxEnable = UART_DISABLE,
			.transmitEnable = UART_ENABLE,
			.wordLength = UART_8_BIT_DATA,
			.stopBits = UART_1_STOP_BIT,
			.baudRate = UART_BAUD_9600
	};

	DMA_Stream_Config_t config5 = {
			.direction = DMA_DIRECTION_MEM_TO_PER,
			.peripheralIncrementMode = DMA_DISABLE,
			.memoryIncrementMode = DMA_ENABLE,
			.directModeDisable = DMA_DISABLE,
			.doubleBufferMode = DMA_DISABLE,
			.fifoMode = DMA_FIFO_FULL,
			.PSIZE = DMA_DATA_SIZE_BYTE,
			.MSIZE = DMA_DATA_SIZE_BYTE,
			.priority = DMA_PRIORITY_HIGH,
			.channel = DMA_CHANNEL4
	};

	hadc1.instance = ADC_1;
	hadc1.config = &config1;
	hadc1.adc = ADC_123;

	htim1.instance = TIM_2;
	htim1.config = &config2;

	hdma1.controller = DMA_2;
	hdma1.instance = DMA2_Stream_0;
	hdma1.config = &config3;

	huart1.Instance = UART_2;
	huart1.Config = &config4;

	hdma2.controller = DMA_1;
	hdma2.instance = DMA1_Stream_6;
	hdma2.config = &config5;

	DMA1_CLOCK_EN;
	DMA2_CLOCK_EN;
	UART2_CLK_EN;
//	ADC_Init(&hadc1);
//	__NVIC_EnableIRQ(ADC_IRQn);
//	__enable_irq();
//	DMA_DoubleBuffer_Start(&hdma1, (uint32_t)&hadc1.instance->DR, (uint32_t)buff1, (uint32_t)buff2, 100);
//	PWM_Init(&htim1);
//	PWM_Start(&htim1);
	UART_Init_tx(&huart1);
	while(1){

	}

	return 0;
}


void ADC_IRQHandler(void) {

    if (hadc1.instance->SR & ADC_SR_EOC_EN) {

    }

    if (hadc1.instance->SR & ADC_SR_OVR_EN){
    	hadc1.instance->SR &= ~ADC_SR_OVR_EN;
    	ADC_DmaPingPongTx(&hadc1, &hdma1, (uint32_t)buff1, (uint32_t)buff2);
    }
}





