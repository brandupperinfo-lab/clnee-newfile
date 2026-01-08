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
