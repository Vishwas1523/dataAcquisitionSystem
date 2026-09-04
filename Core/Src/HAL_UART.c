#include "HAL_UART.h"

void UART_Init_tx(UART_Handle_t* huart){
	/* Disable the UART */
	huart->Instance->CR1 &= ~UART_CR1_UE;

	/* Configure the word length */
	huart->Instance->CR1 &= ~(1U << UART_CR1_M_Pos);
	huart->Instance->CR1 |= huart->Config->wordLength	<< UART_CR1_M_Pos;

	/* Configure the number of stop bits */
	huart->Instance->CR2 &= ~(3U << UART_CR2_STOP_Pos);
	huart->Instance->CR2 |= huart->Config->stopBits << UART_CR2_STOP_Pos;

	/* Configure DMA Transfer*/
	huart->Instance->CR3 &= ~(1U << UART_CR3_DMAT_Pos);
	huart->Instance->CR3 |= (huart->Config->dmaTxEnable << UART_CR3_DMAT_Pos);

	/* Configure Baud Rate */
	if(huart->Instance == UART_1 || huart->Instance == UART_6)
	   huart->Instance->BRR = (90000000 + huart->Config->baudRate / 2U)/huart->Config->baudRate;
	else if (huart->Instance == UART_2)
	   huart->Instance->BRR = (16000000 + huart->Config->baudRate / 2U)/huart->Config->baudRate;

	/* Configure TE Bit */
	huart->Instance->CR1 &= ~UART_CR1_TE_EN;
	huart->Instance->CR1 |= UART_CR1_TE_EN;

	/* Enable the UART */
	huart->Instance->CR1 |= UART_CR1_UE;

}


void UART_DMAtx_Init(UART_Handle_t* huart, DMA_Handle_t* hdma){
	/* Disabling DMA controller before configuring */
	hdma->instance->CR &= ~DMA_CR_EN;
	while (hdma->instance->CR & DMA_CR_EN){
	        /* Wait until DMA is actually disabled */
	}

	/* Configuring channel number */
	hdma->instance->CR &= ~(7U << DMA_CR_CHSEL_Pos);
	hdma->instance->CR |= hdma->config->channel	<< DMA_CR_CHSEL_Pos;

	/* Configuring priority */
	hdma->instance->CR &= ~(3U << DMA_CR_PL_Pos);
	hdma->instance->CR |= hdma->config->priority<<DMA_CR_PL_Pos;

	/* Configuring Double Buffer Mode */
	hdma->instance->CR |= hdma->config->doubleBufferMode << DMA_CR_DBM_Pos;

	/* Hardcoding DMA Direction */
	hdma->instance->CR &= ~(3U << DMA_CR_DIR_Pos);
	hdma->instance->CR |= DMA_DIRECTION_MEM_TO_PER << DMA_CR_DIR_Pos;

	/* Hardcoding peripheral and memory data size */
	hdma->instance->CR &= ~(3U << DMA_CR_PSIZE_Pos);
	hdma->instance->CR |= DMA_DATA_SIZE_BYTE << DMA_CR_PSIZE_Pos;
	hdma->instance->CR &= ~(3U << DMA_CR_MSIZE_Pos);
	hdma->instance->CR |= DMA_DATA_SIZE_BYTE << DMA_CR_MSIZE_Pos;

	/* Hardcoding memory and peripheral increment modes */
	hdma->instance->CR &=	~(1U << DMA_CR_PINC_Pos);
	hdma->instance->CR |=   DMA_ENABLE << DMA_CR_MINC_Pos;

	/* Hardcoding peripheral address */
	hdma->instance->PAR = (uint32_t)&huart->Instance->DR;

}

void UART_DMAtx(UART_Handle_t* huart, DMA_Handle_t* hdma, uint8_t* data, uint16_t bufferSize){
	/* Disabling DMA controller before configuring */
	hdma->instance->CR &= ~DMA_CR_EN;
	while (hdma->instance->CR & DMA_CR_EN){
	        /* Wait until DMA is actually disabled */
	}
	/* Configuring Memory address */
	hdma->instance->M0AR = (uint32_t)data;

	/* Configuring number of transfers */
	hdma->instance->NDTR = bufferSize;

	/* Configure DMA Transfer*/
	huart->Instance->CR3 &= ~(1U << UART_CR3_DMAT_Pos);
	huart->Instance->CR3 |= (1 << UART_CR3_DMAT_Pos);

	/* Enabling DMA transfer */
	hdma->instance->CR |= DMA_CR_EN;
}

void UART_DoubleBuffer_DMAtx(UART_Handle_t* huart, DMA_Handle_t* hdma, uint8_t* data1, uint8_t* data2, uint16_t bufferSize){
	/* Disabling DMA controller before configuring */
	hdma->instance->CR &= ~DMA_CR_EN;
	while (hdma->instance->CR & DMA_CR_EN){
	        /* Wait until DMA is actually disabled */
	}
	/* Configuring Memory address 1 */
	hdma->instance->M0AR = (uint32_t)data1;

	/* Configuring Memory address 2 */
	hdma->instance->M1AR = (uint32_t)data2;

	/* Configuring number of transfers */
	hdma->instance->NDTR = bufferSize;

	/* Configure DMA Transfer*/
	huart->Instance->CR3 &= ~(1U << UART_CR3_DMAT_Pos);
	huart->Instance->CR3 |= (1 << UART_CR3_DMAT_Pos);

	/* Enabling DMA transfer */
	hdma->instance->CR |= DMA_CR_EN;
}











