#include "acio_driver.h"

LogicInput_HandleTypeDef hli_button;
NthInputController_HandleTypeDef hnic_button;

volatile uint8_t button_short_wait = 0;
volatile uint8_t button_long_wait = 0;

uint8_t acio_init_flag = 0;

void ACIO_Init() {
	hli_button.get_state = ACIO_Read_Button;

	NthInputController_ConfigTypeDef cfgnic;
	cfgnic.debounce_tick = 30;
	cfgnic.event_interval_tick = 10;
	cfgnic.max_nth = 2;
	cfgnic.hli = &hli_button;

	NthInputController_CallbackTypeDef cbnic;
	cbnic.nth_clicked = ACIO_Button_Click_Callback;
	cbnic.nth_long_pressed = ACIO_Button_Long_Callback;
	cbnic.nth_after_released = ACIO_Button_After_Release_Callback;

	ACIO_NthInputController_SetConfig(&hnic_button, &cfgnic);
	ACIO_NthInputController_SetCallback(&hnic_button, &cbnic);
	ACIO_NthInputController_Init(&hnic_button);

	acio_init_flag = 1;
}

void ACIO_Update() {
	ACIO_NthInputController_Update(&hnic_button);
}

ACIO_InputState ACIO_Read_Button() {
	return Read_Button() == GPIO_PIN_SET ? ACIO_INPUTSTATE_PRESSED : ACIO_INPUTSTATE_RELEASED;
}

void ACIO_Button_Click_Callback(unsigned char nth) {
	if(nth == 1) {
		button_short_wait = 1;
	}
}

void ACIO_Button_Long_Callback(unsigned char nth, unsigned short iter) {
	if(nth == 1 && iter >= 100) {
		button_long_wait = 1;
	}
}

void ACIO_Button_After_Release_Callback(unsigned char nth, unsigned short iter) {
	if(nth == 1 && iter < 30) {
		button_short_wait = 1;
	}

}
