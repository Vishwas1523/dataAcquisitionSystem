#ifndef INC_HAL_DMA_H_
#define INC_HAL_DMA_H_
#include "stm32f446xx.h"
#include <stdint.h>

//-------------------------------- DMA Registers -----------------------------------

typedef struct{
	volatile uint32_t LISR;
	volatile uint32_t HISR;
	volatile uint32_t LIFCR;
	volatile uint32_t HIFCR;
}DMA_Type;

typedef struct{
	volatile uint32_t CR;
	volatile uint32_t NDTR;
	volatile uint32_t PAR;
	volatile uint32_t M0AR;
	volatile uint32_t M1AR;
	volatile uint32_t FCR;
}DMA_Stream_Type;

//------------------------------- DMA Configuration ---------------------------------

typedef enum{
	DMA_DISABLE = 0,		//For direct mode Disable is Enable & Enable is disable
	DMA_ENABLE = 1
}DMA_FunctionalState_t;		/* Generic DMA configuration enable-disable function */

typedef enum{
	DMA_DIRECTION_PER_TO_MEM = 0,
	DMA_DIRECTION_MEM_TO_PER = 1,
	DMA_DIRECTION_MEM_TO_MEM = 2
}DMA_Direction_t;	/* Helps in configuring the direction of data transfer */

typedef enum{
	DMA_DATA_SIZE_BYTE = 0,
	DMA_DATA_SIZE_HALF_WORD = 1,
	DMA_DATA_SIZE_WORD = 2
}DMA_Size_t;	/* Helps in configuring size of data which will be transferred */

typedef enum{
	DMA_PRIORITY_LOW = 0,
	DMA_PRIORITY_MEDIUM = 1,
	DMA_PRIORITY_HIGH = 2,
	DMA_PRIORITY_VERY_HIGH = 3
}DMA_Priority_t;	/* Helps in configuring priority of the stream */

typedef enum{
	DMA_CHANNEL0 = 0,
	DMA_CHANNEL1 = 1,
	DMA_CHANNEL2 = 2,
	DMA_CHANNEL3 = 3,
	DMA_CHANNEL4 = 4,
	DMA_CHANNEL5 = 5,
	DMA_CHANNEL6 = 6,
	DMA_CHANNEL7 = 7,
}DMA_Channel_t;	/* Helps in choosing the channel of a stream for transfer */


typedef enum{
	DMA_FIFO_1_BY_4	= 0,
	DMA_FIFO_1_BY_2 = 1,
	DMA_FIFO_3_BY_4	= 2,
	DMA_FIFO_FULL	= 3
}DMA_FIFO_Mode_t;	/* Helps in configuring when the fifo will transfer data */

typedef struct __attribute__((packed)) {
	DMA_Direction_t direction;
	DMA_FunctionalState_t circularMode;
	DMA_FunctionalState_t peripheralIncrementMode;
	DMA_FunctionalState_t memoryIncrementMode;
	DMA_FunctionalState_t doubleBufferMode;
	DMA_FunctionalState_t directModeDisable;
	DMA_FIFO_Mode_t fifoMode;
	DMA_Size_t PSIZE;
	DMA_Size_t MSIZE;
	DMA_Priority_t priority;
	DMA_Channel_t channel;
}DMA_Stream_Config_t;

//------------------------------ DMA Handler ------------------------------------

typedef struct __attribute__((packed)) {
	DMA_Type* controller;
	DMA_Stream_Type* instance;
	DMA_Stream_Config_t* config;
}DMA_Handle_t;

//------------------------DMA1 Streams and their addresses---------------------
#define DMA1_Stream_0				(DMA_Stream_Type*)0x40026010
#define DMA1_Stream_1				(DMA_Stream_Type*)0x40026028
#define DMA1_Stream_2				(DMA_Stream_Type*)0x40026040
#define DMA1_Stream_3				(DMA_Stream_Type*)0x40026058
#define DMA1_Stream_4				(DMA_Stream_Type*)0x40026070
#define DMA1_Stream_5				(DMA_Stream_Type*)0x40026088
#define DMA1_Stream_6				(DMA_Stream_Type*)0x400260A0
#define DMA1_Stream_7				(DMA_Stream_Type*)0x400260B8

//------------------------DMA2 Streams and their addresses---------------------
#define DMA2_Stream_0				(DMA_Stream_Type*)0x40026410
#define DMA2_Stream_1				(DMA_Stream_Type*)0x40026428
#define DMA2_Stream_2				(DMA_Stream_Type*)0x40026440
#define DMA2_Stream_3				(DMA_Stream_Type*)0x40026458
#define DMA2_Stream_4				(DMA_Stream_Type*)0x40026470
#define DMA2_Stream_5				(DMA_Stream_Type*)0x40026488
#define DMA2_Stream_6				(DMA_Stream_Type*)0x400264A0
#define DMA2_Stream_7				(DMA_Stream_Type*)0x400264B8

//------------------------DMA BIT MANIPULATION & MASKING----------------------
#define DMA_CR_EN					(1<<0)
#define DMA_CR_CHSEL_Pos			 25UL
#define DMA_CR_PL_Pos				 16UL
#define DMA_CR_DIR_Pos				 6UL
#define DMA_CR_PINC_Pos				 9UL
#define DMA_CR_MINC_Pos				 10UL
#define DMA_CR_CIRC_Pos				 8UL
#define DMA_CR_PSIZE_Pos			 11UL
#define DMA_CR_MSIZE_Pos			 13UL
#define DMA_FCR_DMDIS_DIS			(1<<2)
#define DMA_FCR_FTH_Pos				 0UL
#define DMA1_CLOCK_EN				(RCC->AHB1ENR |= (1<<21))
#define DMA2_CLOCK_EN				(RCC->AHB1ENR |= (1<<22))
#define DMA_CR_PINC_EN				(1<<9)
#define DMA_CR_MINC_EN				(1<<10)
#define DMA_CR_DBM_Pos				 18UL
#define DMA_CR_CT_EN				(1UL<<19UL)

//----------------------------DMA CONTROLLER--------------------------------------

#define DMA_1						(DMA_Type*)0x40026000
#define DMA_2						(DMA_Type*)0x40026400

//-----------------------------------DMA FUNCTIONS----------------------------------
void DMA_Init(DMA_Handle_t* hdma);
void DMA_Start(DMA_Handle_t* hdma, uint32_t srcAddress, uint32_t dstAddress, uint16_t numOfTransfers);
void DMA_DeInit(DMA_Handle_t* hdma);
void DMA_DoubleBuffer_Start(DMA_Handle_t* hdma, uint32_t srcAddress, uint32_t dstAddress1, uint32_t dstAddress2, uint16_t numOfTransfers);

#endif /* INC_HAL_DMA_H_ */
