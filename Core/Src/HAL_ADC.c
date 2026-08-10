#include "HAL_ADC.h"

static void ADC_SamplingCycleConfig(ADC_Handle_t* hadc);
static void ADC_SequenceConfig(ADC_Handle_t* hadc);

void ADC_Init(ADC_Handle_t* hadc){
	/* Configuring EOC interrupt */
	hadc->instance->CR1     &= ~(1U << 5);
	hadc->instance->CR1		|= hadc->config->eocEnable << 5;

	/* Configuring Scan Mode */
	hadc->instance->CR1     &= ~(1U << 8);
	hadc->instance->CR1     |= hadc->config->scanMode << 8;

	/* Configuring Resolution of Channel */
	hadc->instance->CR1     &= ~(3U << 24);
	hadc->instance->CR1     |= hadc->config->resolution << 24;

	/* Configuring Overrun Interrupt */
	hadc->instance->CR1     &= ~(1U << 26);
	hadc->instance->CR1		|= hadc->config->overrunEnable << 26;

	/* Configuring Continuous mode */
	hadc->instance->CR2		&= ~(1U << 1);
	hadc->instance->CR2		|= hadc->config->continuousMode << 1;

	/* Configuring DMA mode */
	hadc->instance->CR2		&= ~(1U << 8);
	hadc->instance->CR2		|= hadc->config->dmaEnable << 8;

	/* Configuring DMA Disable Selection Bit */
	hadc->instance->CR2		&= ~(1U << 9);
	hadc->instance->CR2		|= hadc->config->dmaDisableSelection << 9;

	/* Configuring End of Conversion selection Bit */
	hadc->instance->CR2		&= ~(1U << 10);
	hadc->instance->CR2		|= hadc->config->eocSelection << 10;

	/* Configuring if the alignment of data in ADC_DR register will be left or right*/
	hadc->instance->CR2     &= ~(1U << 11);
	hadc->instance->CR2		|= hadc->config->leftDataAlignment << 11;

	/* Configuring which external event will trigger the ADC conversion */
	hadc->instance->CR2		&= ~(15U << 24);
	hadc->instance->CR2		|= hadc->config->extEventSelection << 24;

	/* Configuring if external source will trigger the conversion and the polarity
	 *  of the trigger source */
	hadc->instance->CR2		&= ~(3U << 28);
	hadc->instance->CR2		|= hadc->config->extTrigEnable	<< 28;

	/* Configuring Sequence of ADC Channels */
	ADC_SequenceConfig(hadc);

	/* Configuring Sampling time of each channel */
	ADC_SamplingCycleConfig(hadc);
}


static void ADC_SequenceConfig(ADC_Handle_t* hadc){

	/* Configuring number of conversions in a sequence */
	hadc->instance->SQR1 	&= ~(0xF << 20);
	hadc->instance->SQR1	|= 	hadc->config->numberOfConversions << 20;

	/* Configuring sequence of Channels */
	for(int i = 0; i < hadc->config->numberOfConversions; i++){
		if(i < 6){
			hadc->instance->SQR3	&= ~(31U << (5 * i));
			hadc->instance->SQR3	|= (hadc->config->channel[i] << (5 * i));
		}else if(i >= 6 && i < 12){
			hadc->instance->SQR2	&= ~(31U << (5 * (i - 6)));
			hadc->instance->SQR2	|= (hadc->config->channel[i] << (5 * (i - 6)));
		}else if(i >= 12 && i < 16){
			hadc->instance->SQR1	&= ~(31U << (5 * (i - 12)));
			hadc->instance->SQR1	|= (hadc->config->channel[i] << (5 * (i - 12)));
		}
	}
}


static void ADC_SamplingCycleConfig(ADC_Handle_t* hadc){

	for(int i = 0; i < hadc->config->numberOfConversions; i++){

		if(hadc->config->channel[i] < 10){
			hadc->instance->SMPR2 &=
					~(7U << ( 3 * hadc->config->channel[i]));
			hadc->instance->SMPR2 |=
					(hadc->config->samplingTime << ( 3 * hadc->config->channel[i]));
		}
		else if(hadc->config->channel[i] >= 10){
			hadc->instance->SMPR1 &=
					~(7U << ( 3 * (hadc->config->channel[i] - 10)));
			hadc->instance->SMPR1 |=
					(hadc->config->samplingTime << ( 3 * (hadc->config->channel[i] - 10)));
		}
	}

}


void ADC_Start(ADC_Handle_t* hadc){

	/* Enabling Clock for ADC Engines */
	if(hadc->instance == ADC_1)	ADC1_CLK_EN;
	else if(hadc->instance == ADC_2)	ADC2_CLK_EN;
	else if(hadc->instance == ADC_3)	ADC3_CLK_EN;

	/*	Starting the ADC by setting ADON Bit */
	hadc->instance->CR2 	&= ~(1U	<< 0);
	hadc->instance->CR2		|= (1U << 0);

	/* Starting the ADC conversions by enabling software trigger
	 * if no external trigger is configured. */
	if(hadc->config->extTrigEnable == ADC_TRIG_DISABLE){
		hadc->instance->CR2		&= ~(1U << 30);
		hadc->instance->CR2		|= (1U << 30);
	}
}


inline uint16_t ADC_Read(ADC_Handle_t* hadc){
	return hadc->instance->DR;
}








