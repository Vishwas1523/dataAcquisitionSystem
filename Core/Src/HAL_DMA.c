#include "HAL_DMA.h"


void DMA_Init(DMA_Handle_t* hdma){
	hdma->instance->CR &= ~DMA_CR_EN;
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
	hdma->instance->CR |= DMA_CR_TCIE_EN;
}

void DMA_Start(DMA_Handle_t* hdma, uint32_t srcAddress, uint32_t dstAddress, uint16_t numOfTransfers){
	hdma->instance->CR &= ~DMA_CR_EN;
	while (hdma->instance->CR & DMA_CR_EN){
	        /* Wait until DMA is actually disabled */
	}
		switch (hdma->config->direction){
			case DMA_DIRECTION_MEM_TO_MEM:
				hdma->instance->PAR = srcAddress;
				hdma->instance->M0AR = dstAddress;
				break;

			case DMA_DIRECTION_MEM_TO_PER:
				hdma->instance->PAR = dstAddress;
				hdma->instance->M0AR = srcAddress;
				break;

			case DMA_DIRECTION_PER_TO_MEM:
				hdma->instance->PAR = srcAddress;
				hdma->instance->M0AR = dstAddress;
				break;
		}
		hdma->instance->NDTR = numOfTransfers;
		DMA_Init(hdma);
		hdma->instance->CR |= DMA_CR_EN;
}

void DMA_DoubleBuffer_Start(DMA_Handle_t* hdma, uint32_t perAddress, uint32_t memAddress1, uint32_t memAddress2, uint16_t numOfTransfers){
	/* DMA must be disabled before changing these registers */
	hdma->instance->CR &= ~DMA_CR_EN;
	while (hdma->instance->CR & DMA_CR_EN){
	        /* Wait until DMA is actually disabled */
	}

	/*For memory to peripheral mode this register act as destination address*/
	hdma->instance->PAR = perAddress;

	/* For memory to peripheral mode these registers act as source address*/
	hdma->instance->M0AR = memAddress1;
	hdma->instance->M1AR = memAddress2;

	hdma->instance->NDTR = numOfTransfers;
	DMA_Init(hdma);
	hdma->instance->CR |= 	DMA_CR_EN;
}











