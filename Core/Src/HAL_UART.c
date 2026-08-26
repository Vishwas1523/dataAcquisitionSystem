#include "HAL_UART.h"

void UART_Init_tx(UART_Handle_t* huart){
	/* Enable the UART */
	huart->Instance->CR1 |= UART_CR1_UE;

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
	huart->Instance->BRR = huart->Config->baudRate;

	/* Configure TE Bit */
	huart->Instance->CR1 &= ~UART_CR1_TE_EN;
	huart->Instance->CR1 |= UART_CR1_TE_EN;

}


void UART_DMAtx(UART_Handle_t* huart, DMA_Handle_t* hdma, uint32_t memAddress1, uint32_t memAddress2){
	DMA_DoubleBuffer_Start(hdma, (uint32_t)&huart->Instance->DR, memAddress1, memAddress2, 100);
}













