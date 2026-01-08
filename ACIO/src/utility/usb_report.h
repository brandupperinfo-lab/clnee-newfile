/*
 * [미사용 코드 - 주석 처리]
 * 이 파일은 USB 키보드/조이스틱 리포트 관련 코드로,
 * 현재 프로젝트(초음파 세척기/UV 살균기)에서 사용하지 않습니다.
 */

#if 0  // 미사용 코드 시작

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

#endif  // 미사용 코드 끝
