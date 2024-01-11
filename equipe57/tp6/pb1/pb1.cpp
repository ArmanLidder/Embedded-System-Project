/*
* Nom: pb1
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Equipe #57
* Description du programme: Ceci est un programme ou lorsque le bouton est enfoncé, un compteur qui incrémente 10 fois par seconde est activé. 
Quand le bouton est relâché ou lorsque le compteur atteint 120, la lumière clignote vert pendant 1/2 seconde. Ensuite, la carte mère ne fait rien. 
Puis, deux secondes plus tard, la lumière rouge s'allume. Elle devra clignoter (compteur / 2) fois au rythme de 2 fois par seconde. 
Ensuite, la lumière tourne au vert pendant une seconde. Finalement, elle s'éteint et le robot revient à son état original.

Nous avons utilise le port B pour la DEL en mode sortie (0x03) sur les deux premieres pins et le bouton poussoir est relie au pin D, qui est donc mis en mode 
entree (0x00). Ainsi, il y aura des interruptions lorsque nous appuyons et relachons le bouton. Nous manipulons les 2 derniers bits du port B pour changer 
les couleurs (01) ou (10). 
*/
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const uint8_t maxCount=120;
const uint16_t PERIOD = 3125; 
const uint16_t THIRTYMS = 30;
const uint16_t TWOSECONDS = 2000;
const uint16_t ONESECOND = 1000;
const uint16_t HALFSECOND = 500;
const uint16_t QUARTERSECOND = 250;

volatile bool gIsPressed;
volatile uint8_t gCounter;


ISR(TIMER1_COMPA_vect)
{
    gCounter += 1;
}

ISR(INT0_vect)
{
    _delay_ms(THIRTYMS);
    gIsPressed = !gIsPressed;
    EIFR |= (1 << INTF0);
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

void setLedOff()
{
    PORTB &= ~((_BV(PB2)) - PB1);
}

void initializationDDRB()
{
    DDRB |= _BV(PB0);
    DDRB |= _BV(PB1);
}

void initializationDDRD()
{
    DDRD &= ~(_BV(PD2));
}

void initialisation()
{

    cli();

    initializationDDRB();
    initializationDDRD();

    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);

    sei();
}

void startTimer(const uint16_t& dureeA)
{
    TCNT1 = 0;
    OCR1A = dureeA;

    TCCR1A |= (1 << COM1A0);             
    TCCR1B |= (1 << CS12) | (1 << WGM12); 
    TCCR1C = 0;     
    TIMSK1 |= (1 << OCIE1A); 
    // On a prescale 256, CTC mode. La valeur de OCR1A (const uint16_t PERIOD = 3125) a ete calculer en solvant l'equation pour nombre:
    //                              nombre / (F_CPU / PRESCALE) = DELAI, donc si on veut une interrupt chaque 0.1s, DELAI = 0.1 => nombre = 3125
}

void stopTimer()
{
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}

void countWhilePressed()
{
    while (gIsPressed && gCounter != maxCount)
    {
    }
}

void flashLedGreen()
{
    setLedGreen();
    _delay_ms(HALFSECOND);
    setLedOff();
}

void flashLedRed()
{
    uint8_t flashCount = gCounter / 2;
    for (uint8_t i = 0; i < flashCount; i++)
    {
        setLedRed();
        _delay_ms(QUARTERSECOND);
        setLedOff();
        _delay_ms(QUARTERSECOND);
    }
}

void runProgram()
{
    gIsPressed = false;
    while (true)
    {
        gCounter = 0;
        if (gIsPressed)
        {
            startTimer(PERIOD);
            countWhilePressed();
            stopTimer();
            flashLedGreen();
            _delay_ms(TWOSECONDS);
            flashLedRed();
            setLedGreen();
            _delay_ms(ONESECOND);
            setLedOff();
        }
    }
}

int main()
{
    initialisation();
    runProgram();
    return 0;
}
