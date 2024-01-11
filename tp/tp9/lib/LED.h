/*
 * Nom du fichier: LED.h
 * Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
 * Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
 * Equipe #57-#58
 * Date: 26 octobre 2022
 * Description: Declaration de la classe LED et de ses methodes
 */

#pragma once
#include <avr/io.h>

class Led
{
private:
    volatile uint8_t *port_ = nullptr;
    volatile uint8_t *ddrx_ = nullptr;
    int pinOne_;
    int pinTwo_;

public:
    Led(volatile uint8_t *port, volatile uint8_t *ddrx, int pinOne, int pinTwo);
    void setLedOff();
    void setLedGreen();
    void setLedRed();
    void setLedAmbreOnce();
    void setLedAmbreLoop(uint16_t loopTime);
};
