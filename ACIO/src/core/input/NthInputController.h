#pragma once

#include "ACIO.h"

typedef struct {
    LogicInput_HandleTypeDef* hli;
    unsigned char max_nth;
    unsigned char debounce_tick;
    unsigned short event_interval_tick;
} NthInputController_ConfigTypeDef;

typedef struct {
    void (* nth_clicked)(unsigned char);
    void (* nth_long_pressed)(unsigned char, unsigned short);
    void (* nth_after_released)(unsigned char, unsigned short);
} NthInputController_CallbackTypeDef;

typedef struct {
    NthInputController_ConfigTypeDef _Config;
    NthInputController_CallbackTypeDef _Callback;

    unsigned char _nth;
    unsigned char _tick;
    unsigned short _ev_intv;
    unsigned short _iter;
    ACIO_State state;
} NthInputController_HandleTypeDef;

void ACIO_NthInputController_SetConfig(NthInputController_HandleTypeDef* handle, NthInputController_ConfigTypeDef* config);
void ACIO_NthInputController_SetCallback(NthInputController_HandleTypeDef* handle, NthInputController_CallbackTypeDef* callback);
void ACIO_NthInputController_Init(NthInputController_HandleTypeDef* handle);
void ACIO_NthInputController_Update(NthInputController_HandleTypeDef* handle);
