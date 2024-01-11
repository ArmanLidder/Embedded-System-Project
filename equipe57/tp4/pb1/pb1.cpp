#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
const uint8_t DELAY_10MS = 10;
const uint8_t DDRB_PIN_CONFIG = 0x03;
const uint8_t DDRD_PIN_CONFIG = 0x00;
volatile int currentState = 0;
bool isPressed()
{
    return (PIND & _BV(PB2)) == _BV(PB2);
}
bool isDebounced()
{
    if (isPressed())
    {
        _delay_ms(DELAY_10MS);
        return isPressed();
    }
    return false;
}
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
    _delay_ms(DELAY_10MS);
    setLedGreen();
    _delay_ms(DELAY_10MS);
}
void setLedOff()
{
    PORTB &= ~((_BV(PB2)) - PB1);
}
void beginStateMachine()
{
    while (true)
    {
        switch (currentState)
        {
        case 0:
            setLedRed();
            break;
        case 1:
            setLedAmbre();
            break;
        case 2:
            setLedGreen();
            break;
        case 3:
            setLedRed();
            break;
        case 4:
            setLedOff();
            break;
        case 5:
            setLedGreen();
            break;
        case 6:
            currentState = 0;
            break;
        }
    }
}
// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR(INT0_vect)
{
    _delay_ms(30);
    currentState += 1;
    EIFR |= (1 << INTF0);
}
void initialisation(void)
{
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRB = 0x03;
    DDRD = 0x00;
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC00);
    // sei permet de recevoir à nouveau des interruptions.
    sei();
}
int main()
{
    initialisation();
    beginStateMachine();
    return 0;
}