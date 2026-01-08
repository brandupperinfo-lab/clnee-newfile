/*
 * [미사용 코드 - 주석 처리]
 * 이 파일은 EdgeInputController 관련 코드로,
 * 현재 프로젝트에서는 NthInputController만 사용하므로 이 코드는 사용하지 않습니다.
 */

#if 0  // 미사용 코드 시작

#include "EdgeInputController.h"

void ACIO_EdgeInputController_SetConfig(EdgeInputController_HandleTypeDef* handle, EdgeInputController_ConfigTypeDef* config) {
    handle->_Config = *config;
}

void ACIO_EdgeInputController_SetCallback(EdgeInputController_HandleTypeDef* handle, EdgeInputController_CallbackTypeDef* callback) {
    handle->_Callback = *callback;
}

void ACIO_EdgeInputController_Init(EdgeInputController_HandleTypeDef* handle) {
    handle->state = ACIO_INIT;
}

void ACIO_EdgeInputController_Update(EdgeInputController_HandleTypeDef* handle) {
    switch(handle->state) {
        case ACIO_INIT:
        if(handle->_Config.hli->get_state() == ACIO_INPUTSTATE_PRESSED) {
            handle->state = ACIO_LOW;
        }
        else {
            handle->state = ACIO_HIGH;
        }
        break;

        case ACIO_HIGH:
        if(handle->_Config.hli->get_state() == ACIO_INPUTSTATE_PRESSED) {
            handle->_Callback.pressed();
            if(handle->_Config.debounce_tick == 0) {
                handle->state = ACIO_LOW;
            }
            else {
                handle->state = ACIO_FALLING_DEBOUNCE;
                handle->_tick = handle->_Config.debounce_tick - 1;
            }
        }
        break;

        // case ACIO_FALLING:
        // break;

        case ACIO_FALLING_DEBOUNCE:
        if(handle->_tick == 0) {
            handle->state = ACIO_LOW;
        }
        else {
            --(handle->_tick);
        }
        break;

        case ACIO_LOW:
        if(handle->_Config.hli->get_state() == ACIO_INPUTSTATE_RELEASED) {
            handle->_Callback.released();
            if(handle->_Config.debounce_tick == 0) {
                handle->state = ACIO_HIGH;
            }
            else {
                handle->state = ACIO_RISING_DEBOUNCE;
                handle->_tick = handle->_Config.debounce_tick - 1;
            }
        }
        break;

        // case ACIO_RISING:
        // break;

        case ACIO_RISING_DEBOUNCE:
        if(handle->_tick == 0) {
            handle->state = ACIO_HIGH;
        }
        else {
            --(handle->_tick);
        }
        break;

        default:
        break;
    }
}

#endif  // 미사용 코드 끝
