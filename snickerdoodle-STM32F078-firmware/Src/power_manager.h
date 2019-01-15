#include "stm32f0xx_hal.h"

/**
 *Power management routine to duty-cycle 17 subsystems controlled by STM32
 */
HAL_StatusTypeDef HAL_pwr_management_off(uint32_t packetInfo) {

	//uint32_t pInfo = packetInfo & 0b00000000000000111111111111111111;
	uint32_t pInfo = packetInfo;
	/* Reset and release all peripherals */  
	//__HAL_RCC_AHB_FORCE_RESET();
	//__HAL_RCC_AHB_RELEASE_RESET();
	//__HAL_RCC_APB1_FORCE_RESET();
	//__HAL_RCC_APB1_RELEASE_RESET();
	//__HAL_RCC_APB2_FORCE_RESET();
	//__HAL_RCC_APB2_RELEASE_RESET();

	
	//Reset Peripherals As Needed
	if((pInfo>>4)&1) {
		__HAL_RCC_GPIOA_FORCE_RESET();
	}
	if((pInfo>>5)&1) {
		__HAL_RCC_GPIOB_FORCE_RESET();
	}
	if((pInfo>>6)&1) {
		__HAL_RCC_GPIOC_FORCE_RESET();
	}
	if((pInfo>>7)&1) {
		__HAL_RCC_GPIOF_FORCE_RESET();
	}
	if((pInfo>>8)&1) {
		__HAL_RCC_TIM3_FORCE_RESET();
	}
	if((pInfo>>9)&1) {
		__HAL_RCC_TIM14_FORCE_RESET();
	}
	if((pInfo>>10)&1) {
		__HAL_RCC_WWDG_FORCE_RESET();
	}
	if((pInfo>>11)&1) {
		__HAL_RCC_I2C1_FORCE_RESET();
	}
	if((pInfo>>12)&1) {
		__HAL_RCC_PWR_FORCE_RESET();
	}
	if((pInfo>>13)&1) {
		__HAL_RCC_SYSCFG_FORCE_RESET();
	}
	if((pInfo>>14)&1) {
		__HAL_RCC_ADC1_FORCE_RESET();
	}
	if((pInfo>>15)&1) {
		__HAL_RCC_TIM1_FORCE_RESET();
	}
	if((pInfo>>16)&1) {
		__HAL_RCC_SPI1_FORCE_RESET();
	}
	if((pInfo>>17)&1) {
		__HAL_RCC_USART1_FORCE_RESET();
	}
	if((pInfo>>18)&1) {
		__HAL_RCC_TIM16_FORCE_RESET();
	}
	if((pInfo>>19)&1) {
		__HAL_RCC_TIM17_FORCE_RESET();
	}
	if((pInfo>>20)&1) {
		__HAL_RCC_DBGMCU_FORCE_RESET();
	}
	
	/* Return function status */
	return HAL_OK;
}

HAL_StatusTypeDef HAL_pwr_management_on(uint32_t packetInfo) {
	
	uint32_t pInfo = packetInfo;
	
	//Release Peripherals When Needed
	if((pInfo>>4)&1) {
		__HAL_RCC_GPIOA_RELEASE_RESET();
	}
	if((pInfo>>5)&1) {
		__HAL_RCC_GPIOB_RELEASE_RESET();
	}
	if((pInfo>>6)&1) {
		__HAL_RCC_GPIOC_RELEASE_RESET();
	}
	if((pInfo>>7)&1) {
		__HAL_RCC_GPIOF_RELEASE_RESET();
	}
	if((pInfo>>8)&1) {
		__HAL_RCC_TIM3_RELEASE_RESET();
	}
	if((pInfo>>9)&1) {
		__HAL_RCC_TIM14_RELEASE_RESET();
	}
	if((pInfo>>10)&1) {
		__HAL_RCC_WWDG_RELEASE_RESET();
	}
	if((pInfo>>11)&1) {
		__HAL_RCC_I2C1_RELEASE_RESET();
	}
	if((pInfo>>12)&1) {
		__HAL_RCC_PWR_RELEASE_RESET();
	}
	if((pInfo>>13)&1) {
		__HAL_RCC_SYSCFG_RELEASE_RESET();
	}
	if((pInfo>>14)&1) {
		__HAL_RCC_ADC1_RELEASE_RESET();
	}
	if((pInfo>>15)&1) {
		__HAL_RCC_TIM1_RELEASE_RESET();
	}
	if((pInfo>>16)&1) {
		__HAL_RCC_SPI1_RELEASE_RESET();
	}
	if((pInfo>>17)&1) {
		__HAL_RCC_USART1_RELEASE_RESET();
	}
	if((pInfo>>18)&1) {
		__HAL_RCC_TIM16_RELEASE_RESET();
	}
	if((pInfo>>19)&1) {
		__HAL_RCC_TIM17_RELEASE_RESET();
	}
	if((pInfo>>20)&1) {
		__HAL_RCC_DBGMCU_RELEASE_RESET();
	}
	
	return HAL_OK;
}

/*Power management Requests*/
void pm_req(uint32_t packetInfo) {
	uint32_t pInfo = (packetInfo>>1) & 0x03;
	if(pInfo == 0x00) {
		HAL_pwr_management_off(packetInfo);
	}else if (pInfo == 0x01) {
		HAL_pwr_management_on(packetInfo);
	}else {
		HAL_pwr_management_off(packetInfo);
		HAL_pwr_management_on(packetInfo);
	}
}

/*Check if there is an external signal to make a specified signal go to sleep*/
unsigned char pm_sleepRead(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	unsigned char isSleep = 0;
	GPIO_PinState bitstatus = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
	if(bitstatus == GPIO_PIN_RESET) {
		isSleep = 1;
	}else {
		isSleep = 0;
	}
	return isSleep;
}

/*Shutdown specified peripheral for a predetermined amount of ms*/
void pm_Sleep(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, volatile uint32_t Delay) {
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	HAL_Delay(Delay);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}
