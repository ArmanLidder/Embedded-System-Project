/*
* Nom du fichier: debug.h
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58
* Date: 26 octobre 2022
* Description: Permet le deboguage en utilisation la transmission RS232
*/

#pragma once

#include "usart.h"
#ifdef DEBUG
Usart transmit;
#define DEBUG_PRINT(datatype, data, data2) transmit.transmitDataInt(datatype, data, data2)

#else
#define DEBUG_PRINT(datatype, data, data2) \
    do                                     \
    {                                      \
    } while (0)
#endif
