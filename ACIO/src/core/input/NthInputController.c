#include "NthInputController.h"

void ACIO_NthInputController_SetConfig(NthInputController_HandleTypeDef* handle, NthInputController_ConfigTypeDef* config) {
    handle->_Config = *config;
}

void ACIO_NthInputController_SetCallback(NthInputController_HandleTypeDef* handle, NthInputController_CallbackTypeDef* callback) {
    handle->_Callback = *callback;
}

void ACIO_NthInputController_Init(NthInputController_HandleTypeDef* handle) {
    handle->state = ACIO_IDLE;
    handle->_iter = 0;
}

void ACIO_NthInputController_Update(NthInputController_HandleTypeDef* handle) {
    switch(handle->state) {
        case ACIO_IDLE:
        if(handle->_Config.hli->get_state() == ACIO_INPUTSTATE_PRESSED) {
            handle->_nth = 1;
            handle->_tick = handle->_Config.debounce_tick;
            if(handle->_Config.debounce_tick == 0) {
                handle->state = ACIO_WAIT_FOR_RELEASE;
                handle->_ev_intv = handle->_Config.event_interval_tick;
            }
            else {
                handle->state = ACIO_FALLING_DEBOUNCE;
                handle->_tick = handle->_Config.debounce_tick - 1;
            }
        }
        break;

        case ACIO_FALLING_DEBOUNCE:
        if(handle->_tick == 0) {
            handle->state = ACIO_WAIT_FOR_RELEASE;
            handle->_ev_intv = handle->_Config.event_interval_tick;
        }
        else {
            --(handle->_tick);
        }
        break;

        case ACIO_WAIT_FOR_RELEASE:
        if(handle->_ev_intv == 0) {
            handle->state = ACIO_WAIT_FOR_AFTER_RELEASE;
            handle->_Callback.nth_long_pressed(handle->_nth, 0);
            handle->_ev_intv = handle->_Config.event_interval_tick;
            handle->_iter = 0;
        }
        else {
            if(handle->_Config.hli->get_state() == ACIO_INPUTSTATE_RELEASED) {
                if(handle->_nth == handle->_Config.max_nth) {
                    handle->_Callback.nth_clicked(handle->_nth);
                    if(handle->_Config.debounce_tick == 0) {
                        handle->state = ACIO_IDLE;
                    }
                    else {
                        handle->_tick = handle->_Config.debounce_tick - 1;
                        handle->state = ACIO_N_MAX_RISING_DEBOUNCE;
                    }
                }
                else {
                    if (handle->_Config.debounce_tick == 0) {
                        handle->state = ACIO_WAIT_FOR_PRESS;
                    } else {
                        handle->_tick = handle->_Config.debounce_tick - 1;
                        handle->state = ACIO_RISING_DEBOUNCE;
                    }
                }
            } else {
                --(handle->_ev_intv);
            }
        }
        break;

        case ACIO_WAIT_FOR_AFTER_RELEASE:
        if(handle->_Config.hli->get_state() == ACIO_INPUTSTATE_RELEASED) {
            handle->_Callback.nth_after_released(handle->_nth, handle->_iter);
            if(handle->_Config.debounce_tick == 0) {
                handle->state = ACIO_IDLE;
            }
            else {
                handle->_tick = handle->_Config.debounce_tick - 1;
                handle->state = ACIO_AFTER_RISING_DEBOUNCE;
            }
        }
        else {
        	if(handle->_ev_intv == 0) {
                handle->_Callback.nth_long_pressed(handle->_nth, ++(handle->_iter));
                handle->_ev_intv = handle->_Config.event_interval_tick;
        	}
        	else {
        		--(handle->_ev_intv);
        	}
        }
        break;

        case ACIO_AFTER_RISING_DEBOUNCE:
        if(handle->_tick == 0) {
            handle->state = ACIO_IDLE;
        }
        else {
            --(handle->_tick);
        }
        break;

        case ACIO_RISING_DEBOUNCE:
        if(handle->_tick == 0) {
            handle->state = ACIO_WAIT_FOR_PRESS;
            handle->_ev_intv = handle->_Config.event_interval_tick;
        }
        else {
            --(handle->_tick);
        }
        break;

        case ACIO_WAIT_FOR_PRESS:
        if(handle->_Config.hli->get_state() == ACIO_INPUTSTATE_PRESSED) {
            if(handle->_Config.debounce_tick == 0) {
                handle->state = ACIO_WAIT_FOR_RELEASE;
            }
            else {
                handle->_tick = handle->_Config.debounce_tick - 1;
                handle->state = ACIO_FALLING_DEBOUNCE;
                ++(handle->_nth);
            }
        }
        else if(handle->_ev_intv == 0) {
            handle->_Callback.nth_clicked(handle->_nth);
            handle->state = ACIO_IDLE;
        }
        else {
            --(handle->_ev_intv);
        }
        break;

        case ACIO_N_MAX_RISING_DEBOUNCE:
        if(handle->_tick == 0) {
            handle->state = ACIO_IDLE;
        }
        else {
            --(handle->_tick);
        }
        break;

        default:
        break;
    }
}
