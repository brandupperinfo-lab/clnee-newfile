#include "bsp.h"
#include "tim.h"
#include "gpio.h"

int32_t usc_underload_counter = 0;

extern uint16_t usc_freq;
extern float adc_voltages[];

uint8_t charger_enable_status = 1;

void Set_Stat_LED(uint16_t brightness) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, brightness);
}

void Set_Chrg_LED(uint16_t brightness) {
	__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, brightness);
}

void Set_UV_C(uint8_t b) {
	HAL_GPIO_WritePin(UV_EN_GPIO_Port, UV_EN_Pin, b ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Set_UV_IND(uint16_t brightness) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, brightness);
}

void Set_USC(uint8_t b) {
	if(b) {
		MX_TIM1_Init();
		Set_USC_Freq(usc_freq);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	}
	else {
//		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
//		TIM1_Pin_Idle_Init();
		HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	}
}

void Set_Charge_Enable(uint8_t b) {
	charger_enable_status = b;
	HAL_GPIO_WritePin(CHRG_CTRL_GPIO_Port, CHRG_CTRL_Pin, charger_enable_status ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void Set_USC_Freq(uint16_t pv) {
	__HAL_TIM_SET_AUTORELOAD(&htim1, pv);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pv >> 1);
}

void Update_USC(float intensity) {
	const float th_h = 0.020;
	const float th_l = 0.008;
	static uint8_t state = 1;
	++usc_underload_counter;

	if(state == 0) {
		if(intensity > th_h) {
			Set_USC(0);
			state = 1;
			usc_underload_counter = 0;
		}
	}
	else {
		if(intensity < th_l) {
			Set_USC(1);
			state = 0;
		}
	}
}

void Set_Hall_Power(uint8_t b) {
	if(b) {
		HAL_GPIO_WritePin(H_EN_GPIO_Port, H_EN_Pin, GPIO_PIN_SET);
	}
	else {
		HAL_GPIO_WritePin(H_EN_GPIO_Port, H_EN_Pin, GPIO_PIN_RESET);
	}
}

float Get_Temperature() {
	return adc_voltages[ADC_VAL_IDX_NTC];
}

GPIO_PinState Read_Button() {
	return HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);
}

GPIO_PinState Read_Hall() {
	return HAL_GPIO_ReadPin(H_SENSE_GPIO_Port, H_SENSE_Pin);
}

GPIO_PinState Read_VUSB() {
	return HAL_GPIO_ReadPin(VUSB_DIV_GPIO_Port, VUSB_DIV_Pin);
}

uint8_t Read_Charge_Enable() {
	return charger_enable_status;
}

void Standby_Mode() {
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WUF);
	Set_Hall_Power(0);
	HAL_PWREx_EnablePullUpPullDownConfig();
	HAL_PWREx_EnableGPIOPullUp(PWR_GPIO_A, PWR_GPIO_BIT_1);
	HAL_PWREx_EnableGPIOPullUp(PWR_GPIO_A, PWR_GPIO_BIT_3);

//	HAL_DBGMCU_EnableDBGStandbyMode();

	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1_HIGH);
	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN4_HIGH);
	HAL_PWR_EnterSTANDBYMode();
}
