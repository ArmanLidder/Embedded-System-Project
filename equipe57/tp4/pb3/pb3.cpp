#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const uint8_t DELAY_10MS = 10;
const uint8_t DDRB_PIN_CONFIG = 0x03;
const uint8_t DDRD_PIN_CONFIG = 0x00;

void ajustementPwm(double pourcentage)
{

    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    // OCR1B = 'modifier ici';
    // division d'horloge par 8 - implique une fréquence de PWM fixe
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << WGM10);
    TCCR1B = (1 << CS11);
    TCCR1C = 0;
    OCR1A = 255 - 510 * (pourcentage / 100) / 2;
}

int main()
{
    DDRD = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x01;
    ajustementPwm(0.00004);
    _delay_ms(2000);
    ajustementPwm(25);
    _delay_ms(2000);
    ajustementPwm(50);
    _delay_ms(2000);
    ajustementPwm(75);
    _delay_ms(2000);
    ajustementPwm(99.6);
    _delay_ms(2000);
    while (1)
    {
        ;
        ;
    }

    return 0;
}