#pragma once

#include "main.h"

void ACIO_Init();
void ACIO_Update();

ACIO_InputState ACIO_Read_Button();

void ACIO_Button_Click_Callback(unsigned char nth);
void ACIO_Button_Long_Callback(unsigned char nth, unsigned short iter);
void ACIO_Button_After_Release_Callback(unsigned char nth, unsigned short iter);
