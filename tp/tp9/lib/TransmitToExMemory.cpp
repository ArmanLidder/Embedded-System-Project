/*
* Nom du fichier: TransmitToExMemory.h
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58
* Date: 7 novembre 2022
* Description: Implementation du constructeur de la classe
*/

#pragma once
#include "TransmitToExMemory.h"

TransmitToExMemory::TransmitToExMemory()
{
    Usart usart;
    Led  led(&PORTB, &DDRB, PB0, PB1);
    led.setLedRed(); // Symbolize that we are waiting for data
    usart.transmitExternalMem();
    led.setLedGreen(); // Symbolize that data has been transferred
    _delay_ms(2000);
    led.setLedOff();
}