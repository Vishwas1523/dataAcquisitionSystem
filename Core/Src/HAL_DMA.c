#include "HAL_DMA.h"


inline void DMA_DeInit(DMA_Handle_t* hdma){
	hdma->instance->CR &= ~DMA_CR_EN;
}

void DMA_Init(DMA_Handle_t* hdma){
	DMA_DeInit(hdma);
	hdma->instance->CR |= hdma->config->channel		<< 	DMA_CR_CHSEL_Pos;
	hdma->instance->CR |= hdma->config->priority		<<	DMA_CR_PL_Pos;
	if(hdma->controller == DMA_1 && hdma->config->direction == DMA_DIRECTION_MEM_TO_MEM)
		return;	//Only DMA2 controller can do Memory to Memory Transfers
	hdma->instance->CR |= hdma->config->direction	<< 	DMA_CR_DIR_Pos;
	if(hdma->config->direction != DMA_DIRECTION_MEM_TO_MEM){		//There is no direct or circular mode in Memory to Memory Transfers
		hdma->instance->CR |= hdma->config->circularMode	<< DMA_CR_CIRC_Pos;
		hdma->instance->FCR	|= hdma->config->directModeDisable<<2;
		hdma->instance->CR |= hdma->config->doubleBufferMode << DMA_CR_DBM_Pos;
	} else{
		hdma->instance->CR &= ~(1<< DMA_CR_CIRC_Pos);
		hdma->instance->FCR	&= ~(1<<DMA_FCR_FTH_Pos);
	}
	hdma->instance->FCR |= hdma->config->fifoMode	<<  DMA_FCR_FTH_Pos;
	hdma->instance->CR |= hdma->config->PSIZE << DMA_CR_PSIZE_Pos;
	hdma->instance->CR |= hdma->config->MSIZE << DMA_CR_MSIZE_Pos;
	hdma->instance->CR |=	hdma->config->peripheralIncrementMode<<DMA_CR_PINC_Pos;
	hdma->instance->CR |=   hdma->config->memoryIncrementMode<<DMA_CR_MINC_Pos;
}

void DMA_Start(DMA_Handle_t* hdma, uint32_t srcAddress, uint32_t dstAddress, uint16_t numOfTransfers){
		DMA_DeInit(hdma);
		for(int i = 0; i < 100000; i++){} 	//After disabling DMA we need some time before configuring
		switch (hdma->config->direction){
			case DMA_DIRECTION_MEM_TO_MEM:
				hdma->instance->PAR = srcAddress;
				hdma->instance->M0AR = dstAddress;
				hdma->instance->NDTR = numOfTransfers;
				DMA_Init(hdma);
				break;

			case DMA_DIRECTION_MEM_TO_PER:
				hdma->instance->PAR = dstAddress;
				hdma->instance->M0AR = srcAddress;
				hdma->instance->NDTR = numOfTransfers;
				DMA_Init(hdma);
				break;

			case DMA_DIRECTION_PER_TO_MEM:
				hdma->instance->PAR = srcAddress;
				hdma->instance->M0AR = dstAddress;
				hdma->instance->NDTR = numOfTransfers;
				DMA_Init(hdma);
				break;
		}
}

void DMA_DoubleBuffer_Start(DMA_Handle_t* hdma, uint32_t srcAddress, uint32_t dstAddress1, uint32_t dstAddress2, uint16_t numOfTransfers){
	/* DMA must be disabled before changing these registers */
	hdma->instance->CR &= ~DMA_CR_EN;
	while (hdma->instance->CR & DMA_CR_EN){
	        /* Wait until DMA is actually disabled */
	}
	hdma->instance->PAR = srcAddress;
	hdma->instance->M0AR = dstAddress1;
	hdma->instance->M1AR = dstAddress2;
	hdma->instance->NDTR = numOfTransfers;
	hdma->instance->CR |= 	DMA_CR_EN;
}











