#pragma once

#include "ACIO.h"

typedef struct {
    ACIO_InputState (*get_state)();
} LogicInput_HandleTypeDef;
