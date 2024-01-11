/*
* Nom: pb2
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Equipe #57
* Description du programme: Ceci est un programme de type machine a etats. La DEL est initiallement rouge et 
apres avoir appuye le bouton, elle devient ambre. Apres avoir relache le bouton, elle devient verte. Apres l'avoir appuyer une deuxieme fois, 
elle devient rouge encore. Apres l'avoir relache, elle s'eteint. Quand on pese sur le bouton de nouveau, elle devient verte et lorsqu'on le 
relache encore, la DEL tourne rouge et on revient alors dans l'etat initial.

Nous avons utilise le port B pour la DEL en mode sortie (0x03) et le bouton est relie au port D, qui est donc mis en mode entree (0x00). Nous manipulons
les 2 derniers bits du port B pour changer les couleurs (01) ou (10).

Voici la table d'etats :
+------------------+-------------+------------------+-----------+
|       État       |   Entrées   |  Prochain État   |  Sorties  |
+------------------+-------------+------------------+-----------+
| INIT_RED_DEL     | PRESSED     | KEPT_PRESS_ONE   | DEL AMBER |
| INIT_RED_DEL     | RELEASED    | INIT_RED_DEL     | DEL RED   |
| KEPT_PRESS_ONE   | PRESSED     | KEPT_PRESS_ONE   | DEL AMBER |
| KEPT_PRESS_ONE   | RELEASED    | RELEASED_ONE     | DEL GREEN |
| RELEASED_ONE     | RELEASED    | RELEASED_ONE     | DEL GREEN |
| RELEASED_ONE     | PRESSED     | KEPT_PRESS_TWO   | DEL RED   |
| KEPT_PRESS_TWO   | PRESSED     | KEPT_PRESS_TWO   | DEL RED   |
| KEPT_PRESS_TWO   | RELEASED    | RELEASED_TWO     | DEL OFF   |
| RELEASED_TWO     | RELEASED    | RELEASED_TWO     | DEL OFF   |
| RELEASED_TWO     | PRESSED     | KEPT_PRESS_THREE | DEL GREEN |
| KEPT_PRESS_THREE | PRESSED     | KEPT_PRESS_THREE | DEL GREEN |
| KEPT_PRESS_THREE | RELEASED    | INIT_RED_DEL     | DEL RED   |
+------------------+-------------+------------------+-----------+
*/


#define F_CPU 8000000UL

#include <util/delay.h>
#include <avr/io.h>

const uint8_t DELAY_10MS = 10;
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
    PORTB &= ~((_BV(PB2))-PB1);
}

enum buttonState
{
    BUTTON_NOT_PRESSED,
    BUTTON_KEPT_PRESS_ONE,
    BUTTON_RELEASED_ONE,
    BUTTON_KEPT_PRESS_TWO,
    BUTTON_RELEASED_TWO,
    BUTTON_KEPT_PRESS_THREE
};

void beginStateMachine()
{
    buttonState currentState = BUTTON_NOT_PRESSED;
    while (true)
    {
        switch (currentState)
        {
        case BUTTON_NOT_PRESSED:
            setLedRed();
            if (isDebounced())
                currentState = BUTTON_KEPT_PRESS_ONE;
            break;

        case BUTTON_KEPT_PRESS_ONE:
            while (isDebounced())
                setLedAmbre();
            currentState = BUTTON_RELEASED_ONE;
            break;
        case BUTTON_RELEASED_ONE:
            setLedGreen();
            if (isDebounced())
                currentState = BUTTON_KEPT_PRESS_TWO;
            break;
        case BUTTON_KEPT_PRESS_TWO:
            while (isDebounced())
                setLedRed();
            currentState = BUTTON_RELEASED_TWO;
        case BUTTON_RELEASED_TWO:
            setLedOff();
            if (isDebounced())
                currentState = BUTTON_KEPT_PRESS_THREE;
            break;
        case BUTTON_KEPT_PRESS_THREE:
            while (isDebounced())
                setLedGreen();
            currentState = BUTTON_NOT_PRESSED;
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