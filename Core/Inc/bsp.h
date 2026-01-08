#pragma once

#include "main.h"
#include "tim.h"

#define ADC_VAL_IDX_VBAT_DIV 0
#define ADC_VAL_IDX_ISENSE 1
#define ADC_VAL_IDX_TEMP 2
#define ADC_VAL_IDX_VREF 3
#define ADC_VAL_IDX_NTC 4

#define NTC_TO_TEMP(x) (9.72763 * (3.1022 - x))

void Set_Stat_LED(uint16_t brightness);
void Set_Chrg_LED(uint16_t brightness);
void Set_UV_C(uint8_t b);
void Set_UV_IND(uint16_t brightness);
void Set_USC_Freq(uint16_t pv);
void Set_USC(uint8_t b);
void Set_Charge_Enable(uint8_t b);
void Update_USC(float intensity);
void Set_Hall_Power(uint8_t b);
float Get_Temperature();
GPIO_PinState Read_Button();
GPIO_PinState Read_Hall();
GPIO_PinState Read_VUSB();
uint8_t Read_Charge_Enable();

void Standby_Mode();
