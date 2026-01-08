#include "task.h"

extern uint8_t button_short_wait;
extern uint8_t button_long_wait;
extern uint16_t adc_values[5];
extern float adc_voltages[5];
extern int32_t usc_underload_counter;

extern ADC_HandleTypeDef hadc1;

TASK_STATE_CHARGER s_chrg = TASK_CHARGER_INIT;
TASK_STATE_CLEANER s_cln = TASK_CLEANER_INIT;
TASK_STATE_POWER s_pwr = TASK_POWER_INIT;
TASK_STATE_FREQ_CHANGER s_fchn = TASK_FREQ_CHANGER_INIT;

uint8_t charger_state;
GPIO_PinState hall_state;
GPIO_PinState vusb_state;

volatile uint16_t usc_freq = 400;
int32_t usc_cost = USC_COST;

void Read_Inputs() {
	charger_state = HAL_GPIO_ReadPin(CHRG_STAT_1_GPIO_Port, CHRG_STAT_1_Pin) == GPIO_PIN_RESET ? 0x01 : 0x00;
	hall_state = Read_Hall();
	vusb_state = Read_VUSB();
}

void Task_Charger() {
	static volatile uint8_t dir = 1;
	static volatile uint16_t val = 0;

	static uint8_t charger_enable;
	charger_enable = Read_Charge_Enable();

	switch(s_chrg) {
		case TASK_CHARGER_INIT:
			if(vusb_state == 0 || charger_enable == 0) s_chrg = TASK_CHARGER_IDLE_ENTRY;
			else if(charger_state == 1) s_chrg = TASK_CHARGER_CHARGING_ENTRY;
			else if(charger_state == 0) s_chrg = TASK_CHARGER_STANDBY_ENTRY;
			break;

		case TASK_CHARGER_IDLE_ENTRY:
			if(val > 0) --val;
			else s_chrg = TASK_CHARGER_IDLE;
			Set_Chrg_LED(val);
			break;

		case TASK_CHARGER_IDLE:
			if(vusb_state == 1 && charger_enable == 1 && charger_state == 1) s_chrg = TASK_CHARGER_CHARGING_ENTRY;
			else if(vusb_state == 1 && charger_enable == 1 && charger_state == 0) s_chrg = TASK_CHARGER_STANDBY_ENTRY;
			break;

		case TASK_CHARGER_CHARGING_ENTRY:
			dir = 1;
			s_chrg = TASK_CHARGER_CHARGING;
			break;

		case TASK_CHARGER_CHARGING:
			if(dir == 1) {
				if(val < 999) ++val;
				else dir = 0;
			}
			else {
				if(val > 0) --val;
				else dir = 1;
			}
			Set_Chrg_LED(val);

			if(vusb_state == 0 || charger_enable == 0) s_chrg = TASK_CHARGER_IDLE_ENTRY;
			else if(charger_state == 0) s_chrg = TASK_CHARGER_STANDBY_ENTRY;
			break;

		case TASK_CHARGER_STANDBY_ENTRY:
			if(val < 999) ++val;
			else s_chrg = TASK_CHARGER_STANDBY;
			Set_Chrg_LED(val);
			break;

		case TASK_CHARGER_STANDBY:
			if(vusb_state == 0 || charger_enable == 0) s_chrg = TASK_CHARGER_IDLE_ENTRY;
			else if(charger_state == 1) s_chrg = TASK_CHARGER_CHARGING_ENTRY;
			break;
	}
}

void Task_Cleaner() {
	static uint16_t ind_val = 0;
	static uint16_t stat_val = 0;
	static int32_t timer = 0;
	static uint16_t counter = 0;
	static uint8_t stat_dir = 1;
	static uint16_t scan_tick = 0;

	if(usc_cost < USC_COST && s_cln != TASK_CLEANER_CLEAN_USC) ++usc_cost;

	switch(s_cln) {
		case TASK_CLEANER_INIT:
			Set_Charge_Enable(1);
			s_cln = TASK_CLEANER_IDLE;
			break;

		case TASK_CLEANER_IDLE:
			Set_Charge_Enable(1);
			if(button_short_wait == 1) {
				s_cln = TASK_CLEANER_CLEAN_ENTRY;
				HAL_ADCEx_Calibration_Start(&hadc1);
				button_short_wait = 0;
				button_long_wait = 0;
			}
			else if(button_long_wait == 1) {
				s_cln = TASK_CLEANER_BATT_CHECK;
				button_short_wait = 0;
				button_long_wait = 0;
			}
			break;

		case TASK_CLEANER_CLEAN_ENTRY:
			if(vusb_state == GPIO_PIN_SET && usc_cost > (30 * 1000)) {
				s_cln = TASK_CLEANER_CLEAN_USC;
				timer = 5 * 60 * 1000;
				stat_dir = 1;
				scan_tick = 0;
			}
			else if(hall_state == GPIO_PIN_RESET) {
				s_cln = TASK_CLEANER_CLEAN_UV;
				timer = 5 * 60 * 1000;
				stat_dir = 1;
				ind_val = 999;
				stat_val = 999;
				Set_UV_C(1);
			}
			else {
				counter = 5;
				timer = 100;
				s_cln = TASK_CLEANER_CLEAN_DONE;
			}
			break;

		case TASK_CLEANER_CLEAN_UV:
			if(button_short_wait == 1 || timer == 0 || hall_state == GPIO_PIN_SET || adc_voltages[ADC_VAL_IDX_VBAT_DIV] < 3.5) {
				counter = 5;
				timer = 100;
				s_cln = TASK_CLEANER_CLEAN_DONE;
			}
			else {
				--timer;
			}
			break;

		case TASK_CLEANER_CLEAN_USC:
			Set_Charge_Enable(0);
			Update_USC(adc_voltages[ADC_VAL_IDX_ISENSE]);

			if(stat_dir == 1) {
				if(stat_val < 999) stat_val += 3;
				else stat_dir = 0;
			}
			else {
				if(stat_val > 0) stat_val -= 3;
				else stat_dir = 1;
			}

			if(hall_state == GPIO_PIN_RESET) {
				ind_val = 999;
				Set_UV_C(1);
			}
			else {
				ind_val = 0;
				Set_UV_C(0);
			}

			if(adc_voltages[ADC_VAL_IDX_NTC] < 0.80 /*timer == 0*/ || button_short_wait == 1 || vusb_state == GPIO_PIN_RESET || usc_cost == 0) {
				counter = 5;
				timer = 100;
				Update_USC(0.9);
				s_cln = TASK_CLEANER_CLEAN_DONE;
			}
			else {
				--timer;
				--usc_cost;
			}

			break;

		case TASK_CLEANER_CLEAN_DONE:
			Set_Charge_Enable(1);
			ind_val = 0;
			Set_USC(0);
			Set_UV_C(0);
			if(timer == 0) {
				if(--counter & 0x01) {
					stat_val = 999;
				}
				else {
					stat_val = 0;
				}
				timer = 100;
			}
			else --timer;

			if(counter == 0) {
				s_cln = TASK_CLEANER_IDLE;
				button_short_wait = 0;
				button_long_wait = 0;
			}
			break;

		case TASK_CLEANER_BATT_CHECK:
			s_cln = TASK_CLEANER_IDLE;
			break;
	}
	Set_Stat_LED(stat_val);
	Set_UV_IND(ind_val);
}

void Task_Power() {
	static uint16_t timer = 0;

	switch(s_pwr) {
		case TASK_POWER_INIT:
			timer = 10000;
			s_pwr = TASK_POWER_WFIDLE;
			break;

		case TASK_POWER_WFIDLE:
			if(timer > 0) {
				if(s_chrg != TASK_CHARGER_IDLE || s_cln != TASK_CLEANER_IDLE || usc_cost != USC_COST) {
					timer = 10000;
				}
				--timer;
			}
			else {
				s_pwr = TASK_POWER_STANDBY;
			}
			break;

		case TASK_POWER_STANDBY:
			Standby_Mode();
			break;
	}
}

void Task_Freq_Changer() {
	const uint16_t ar_init = 381;
//	const uint16_t ar_init = 492;
//	const uint16_t ar_init = 532;
	const uint16_t ar_max = ar_init + 10;
	const uint16_t ar_min = ar_init - 10;

	switch(s_fchn) {
		case TASK_FREQ_CHANGER_INIT:
			usc_freq = ar_init;
			s_fchn = TASK_FREQ_CHANGER_RISING;
			Set_USC_Freq(usc_freq);
			break;

		case TASK_FREQ_CHANGER_RISING:
			if(++usc_freq >= ar_max) {
				s_fchn = TASK_FREQ_CHANGER_FALLING;
			}
			Set_USC_Freq(usc_freq);
			break;

		case TASK_FREQ_CHANGER_FALLING:
			if(--usc_freq <= ar_min) {
				s_fchn = TASK_FREQ_CHANGER_RISING;
			}
			Set_USC_Freq(usc_freq);
			break;
	}
}
