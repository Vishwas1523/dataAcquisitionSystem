#ifndef INC_HAL_UART_H_
#define INC_HAL_UART_H_
#include "HAL_DMA.h"
#include <stdint.h>
//------------------------------- UART Registers -----------------------------------
typedef struct{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}UART_Type;

//---------------------------- UART Controllers -------------------------------------

#define UART_1									(UART_Type*)0x40011000
#define UART_2									(UART_Type*)0x40004400
#define UART_3									(UART_Type*)0x40004800
#define UART_4									(UART_Type*)0x40004C00
#define UART_5									(UART_Type*)0x40005000
#define UART_6									(UART_Type*)0x40011400

//------------------------------ UART Bit Masks --------------------------------------

#define UART_CR1_UE								(1U << 13U)
#define UART_CR1_M_Pos							12U
#define UART_CR2_STOP_Pos						12U
#define UART_CR3_DMAT_Pos						7U
#define UART_CR1_TE_EN							(1U << 3U)
#define UART2_CLK_EN							(RCC->APB1ENR |= (1U << 17U))

//---------------------------- UART Configurations ----------------------------------

typedef enum{
	UART_DISABLE = 0,
	UART_ENABLE = 1
}UART_FunctionalState_t; /* General enable-disable UART configuration */

typedef enum{
	UART_8_BIT_DATA = 0,
	UART_9_BIT_DATA
}UART_WordLength_t;	/* UART data length */

typedef enum{
	UART_1_STOP_BIT = 0,
	UART_2_STOP_BIT = 2
}UART_StopBits_t;	/* UART stop bits */

typedef enum{
    UART_BAUD_9600   = 9600,
    UART_BAUD_115200 = 115200
}UART_BaudRate_t;

typedef struct{
	UART_WordLength_t wordLength;
	UART_StopBits_t stopBits;
	UART_FunctionalState_t dmaTxEnable;
	UART_FunctionalState_t intTxEnable;
	UART_FunctionalState_t dmaRxEnable;
	UART_FunctionalState_t intRxEnable;
	UART_FunctionalState_t recieveEnable;
	UART_FunctionalState_t transmitEnable;
	UART_BaudRate_t baudRate;
}UART_Config_t;	/* UART configuration structure */


//----------------------------- UART Handler ----------------------------------------

typedef struct{
	UART_Type* Instance;
	UART_Config_t* Config;
}UART_Handle_t;

//------------------------------ UART Functions ---------------------------------------------

void UART_Init_tx(UART_Handle_t* huart);
void UART_DMAtx(UART_Handle_t* huart, DMA_Handle_t* hdma, uint32_t memAddress1, uint32_t memAddress2);







#endif /* INC_HAL_UART_H_ */
