/*
 * [미사용 코드 - 주석 처리]
 * 이 파일은 EdgeInputController 관련 코드로,
 * 현재 프로젝트에서는 NthInputController만 사용하므로 이 코드는 사용하지 않습니다.
 */

#if 0  // 미사용 코드 시작

#pragma once

#include "ACIO.h"

typedef struct {
    LogicInput_HandleTypeDef* hli;
    unsigned char debounce_tick;
} EdgeInputController_ConfigTypeDef;

typedef struct {
    void (* released)();
    void (* pressed)();
} EdgeInputController_CallbackTypeDef;

typedef struct {
    EdgeInputController_ConfigTypeDef _Config;
    EdgeInputController_CallbackTypeDef _Callback;

    unsigned char _tick;
    ACIO_State state;
} EdgeInputController_HandleTypeDef;

void ACIO_EdgeInputController_SetConfig(EdgeInputController_HandleTypeDef* handle, EdgeInputController_ConfigTypeDef* config);
void ACIO_EdgeInputController_SetCallback(EdgeInputController_HandleTypeDef* handle, EdgeInputController_CallbackTypeDef* callback);
void ACIO_EdgeInputController_Init(EdgeInputController_HandleTypeDef* handle);
void ACIO_EdgeInputController_Update(EdgeInputController_HandleTypeDef* handle);

#endif  // 미사용 코드 끝
