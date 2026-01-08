#pragma once

#include "ACIO.h"
#include "../input/InputState.h"

__attribute__((unused)) static ACIO_InputState ACIO_Callback_Null_InputState_void() {
    return ACIO_INPUTSTATE_RELEASED;
}

__attribute__((unused)) static void ACIO_Callback_Null_void_void() {
    return;
}

__attribute__((unused)) static void ACIO_Callback_Null_void_uchar(unsigned char n) {
	(void)n;
    return;
}

__attribute__((unused)) static void ACIO_Callback_Null_void_uchar_ushort(unsigned char n, unsigned short m) {
	(void)n;
	(void)m;
    return;
}
