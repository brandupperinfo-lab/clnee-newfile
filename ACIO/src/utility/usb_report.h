#pragma once

#include "ACIO.h"
#include "keycode.h"

typedef struct __attribute__((packed)) {
	uint8_t modifier;
	uint8_t key[13];
} NKRO_ReportTypeDef;

typedef struct __attribute__((packed)) {
	int8_t x;
	int8_t y;
	uint16_t button;
	uint8_t _padding;
} KONAMI_Joystick_ReportTypeDef;

void NKRO_Press_Modifier(NKRO_ReportTypeDef *report, Keyboard_Modifier modifier);
void NKRO_Release_Modifier(NKRO_ReportTypeDef *report, Keyboard_Modifier modifier);
void NKRO_Press_Key(NKRO_ReportTypeDef *report, NKRO_Key nkro_key);
void NKRO_Release_Key(NKRO_ReportTypeDef *report, NKRO_Key nkro_key);

void KONAMI_Joystick_Press_Button(KONAMI_Joystick_ReportTypeDef *report, uint8_t button);
void KONAMI_Joystick_Release_Button(KONAMI_Joystick_ReportTypeDef *report, uint8_t button);
