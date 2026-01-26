/*
 * [미사용 코드 - 주석 처리]
 * 이 파일은 USB 키보드/조이스틱 리포트 관련 코드로,
 * 현재 프로젝트(초음파 세척기/UV 살균기)에서 사용하지 않습니다.
 */

#if 0  // 미사용 코드 시작

#include "usb_report.h"


void NKRO_Press_Modifier(NKRO_ReportTypeDef *report, Keyboard_Modifier modifier) {
	report->modifier |= modifier;
}

void NKRO_Release_Modifier(NKRO_ReportTypeDef *report, Keyboard_Modifier modifier) {
	report->modifier &= ~modifier;
}

void NKRO_Press_Key(NKRO_ReportTypeDef *report, NKRO_Key nkro_key) {
	report->key[nkro_key.byte_offset] |= nkro_key.bitmask;
}

void NKRO_Release_Key(NKRO_ReportTypeDef *report, NKRO_Key nkro_key) {
	report->key[nkro_key.byte_offset] &= ~nkro_key.bitmask;
}

void KONAMI_Joystick_Press_Button(KONAMI_Joystick_ReportTypeDef *report, uint8_t button) {
	report->button |= ((uint16_t)0x01 << button);
}

void KONAMI_Joystick_Release_Button(KONAMI_Joystick_ReportTypeDef *report, uint8_t button) {
	report->button &= ~((uint16_t)0x01 << button);
}

#endif  // 미사용 코드 끝
