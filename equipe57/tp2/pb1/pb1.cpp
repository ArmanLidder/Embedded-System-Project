/*
* Nom: pb1
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Equipe #57
* Description du programme: Ceci est un programme de type machine a etats. La lumiere est initiallement eteinte et
apres avoir appuye et relache le bouton 3 fois de suite, la DEL tourne vert pendant 2 secondes et par la suite, on revient
a l'etat initiale.

Nous avons utilise le port B pour la DEL en mode sortie (0x03) sur les deux premieres pins et le bouton est relie au port D, qui est donc mis en mode entree (0x00). Nous manipulons
les 2 derniers bits du port B pour changer les couleurs (01) ou (10).

Voici la table d'etats :
+--------------+-------------+---------------+-----------------------------+
|     État     |   Entrées   | Prochain État |           Sorties           |
+--------------+-------------+---------------+-----------------------------+
| INIT         | PRESSED     | FIRST_PRESS   | DEL OFF                     |
| INIT         | NOT PRESSED | INIT          | DEL OFF                     |
| FIRST_PRESS  | PRESSED     | SECOND_PRESS  | DEL OFF                     |
| FIRST_PRESS  | NOT PRESSED | FIRST_PRESS   | DEL OFF                     |
| SECOND_PRESS | PRESSED     | THIRD_PRESS   | DEL OFF                     |
| SECOND_PRESS | NOT PRESSED | SECOND_PRESS  | DEL OFF                     |
| THIRD_PRESS  | PRESSED     | INIT          | DEL GREEN 2SECONDS THEN OFF |
| THIRD_PRESS  | NOT PRESSED | THIRD_PRESS   | DEL OFF                     |
+--------------+-------------+---------------+-----------------------------+
*/

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

const uint8_t DELAY_10MS = 10;
const int16_t DELAY_TWOSEC = 2000;
const uint8_t DDRB_PIN_CONFIG = 0x03;
const uint8_t DDRD_PIN_CONFIG = 0x00;

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

void waitForRelease()
{
    while (true)
    {
        if (!isDebounced())
            break;
    }
}

void setLedGreen()
{
    PORTB &= ~(_BV(PB0));
    PORTB |= _BV(PB1);
}

void setLedOff()
{
    PORTB &= ~((_BV(PB2)) - PB1);
}

enum buttonPressed
{
    BUTTON_NOT_PRESSED,
    BUTTON_FIRST_PRESS,
    BUTTON_SECOND_PRESS,
    BUTTON_THIRD_PRESS
};

void beginStateMachine()
{
    buttonPressed currentState = BUTTON_NOT_PRESSED;
    while (true)
    {
        switch (currentState)
        {
        case BUTTON_NOT_PRESSED:
            setLedOff();
            if (isDebounced())
            {
                currentState = BUTTON_FIRST_PRESS;
                waitForRelease();
            }
            break;
        case BUTTON_FIRST_PRESS:
            if (isDebounced())
            {
                currentState = BUTTON_SECOND_PRESS;
                waitForRelease();
            }
            break;
        case BUTTON_SECOND_PRESS:
            if (isDebounced())
            {
                currentState = BUTTON_THIRD_PRESS;
                waitForRelease();
            }
            break;
        case BUTTON_THIRD_PRESS:
            setLedGreen();
            _delay_ms(DELAY_TWOSEC);
            currentState = BUTTON_NOT_PRESSED;
            break;
        }
    }
}

int main()
{
    DDRB = DDRB_PIN_CONFIG;
    DDRD = DDRD_PIN_CONFIG;
    beginStateMachine();
    return 0;
}