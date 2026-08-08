#include "stm32f446xx.h"
#include "HAL_GPIO.h"


int main(void){

	GPIO_Handle_t hgpio1 = {0};
	hgpio1.instance = GPIO_PORT_A;
	hgpio1.config.mode = GPIO_OUTPUT_MODE;
	hgpio1.config.otype = GPIO_OUTPUT_PUSHPULL;
	hgpio1.config.ospeed = GPIO_SPEED_HIGH;
	hgpio1.config.pullUp_pullDown = GPIO_NO_PULLUP_PULLDOWN;

	GPIO_Init(&hgpio1, 5);

	GPIO_Handle_t hgpio2 = {0};
	hgpio2.instance = GPIO_PORT_C;
	hgpio2.config.mode = GPIO_INPUT_MODE;
	hgpio2.config.pullUp_pullDown = GPIO_NO_PULLUP_PULLDOWN;

	GPIO_Init(&hgpio2, 13);

	while(1){
		if(GPIO_Read(&hgpio2, 13) == GPIO_LOW){
			GPIO_Toggle(&hgpio1, 5);
		}

	}
	return 0;
}


