/*
* Nom: pb2
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Equipe #57
* Description du programme:
Si la lumière est basse (en cachant la photorésistance), la DEL prendra la couleur verte.
Si la lumière est à un bon niveau (lumière ambiante), la DEL tournera à l'ambré.
Si la lumière est trop forte (photorésistance sous une lampe de poche), la DEL devient rouge.

Nous avons utilise le port B pour la DEL en mode sortie (0x03) sur les deux premieres pins et nous convertissons la tension analogique en numerique, 
qui necessite le PINA0 en mode entree (0x00). Nous manipulonsles 2 derniers bits du port B pour changer les couleurs 
(01) ou (10).
*/
#define F_CPU 8000000UL
#include "can.h"
#include <util/delay.h>
#include <avr/io.h>

const uint8_t SET_COLOR_10_MS = 10;
const uint8_t DARK_REGION_MIN = 0;
const uint8_t DARK_REGION_MAX = 100;
const uint8_t BRIGHT_REGION_MIN = 240;
const uint8_t BRIGHT_REGION_MAX = 255;
uint16_t lightLevel;

void setLedRed()
{
    PORTB &= ~(_BV(PB1));
    PORTB |= _BV(PB0);
}

void setLedGreen()
{
    PORTB &= ~(_BV(PB0));
    PORTB |= _BV(PB1);
}

void setLedAmbre()
{
    setLedRed();
    _delay_ms(SET_COLOR_10_MS);
    setLedGreen();
    _delay_ms(SET_COLOR_10_MS);
}

void initialisation()
{
    DDRB |= _BV(PB0);
    DDRB |= _BV(PB1);
    DDRA &= ~(_BV(PD2));
}

bool isDark()
{
    return (lightLevel >= DARK_REGION_MIN && lightLevel < DARK_REGION_MAX);
}

bool isBrightLight()
{
    return (lightLevel >=BRIGHT_REGION_MIN && lightLevel <=BRIGHT_REGION_MAX);
}

void runProgram()
{
    while (true)
    {
        can analogConverter;
        lightLevel = analogConverter.lecture(PA0) >> PA2; //On enleve les deux dernier bits qui sont a etre neglige (On passe de 10 bits a 8 bits).
        if (isDark())
            setLedGreen();
        else if(isBrightLight()) 
            setLedRed();
        else
            setLedAmbre();
    }
}

int main()
{
    initialisation();
    runProgram(); //Note : la lumiere est rouge seulement si vous utilisez un flash-light
    return 0;
}
