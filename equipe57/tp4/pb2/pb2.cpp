#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
const uint8_t DELAY_10MS = 10;
const uint8_t DDRB_PIN_CONFIG = 0x03;
const uint8_t DDRD_PIN_CONFIG = 0x00;

volatile uint8_t gMinuterieExpiree;
volatile uint8_t gBoutonPoussoir;

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

// placer le bon type de signal d'interruption
// à prendre en charge en argument

ISR(TIMER1_COMPA_vect)
{
    gMinuterieExpiree = 1;
    setLedRed();
}

ISR(INT0_vect)
{
    gBoutonPoussoir = 1;
    setLedGreen();
}

void initialisation(void)
{

    cli();

    DDRB = 0x03;
    DDRD = 0x00;

    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);

    sei();
}

void partirMinuterie(uint16_t duree)
{

    gMinuterieExpiree = 0;

    TCNT1 = 0;
    OCR1A = (65536 * duree) / 8390;

    TCCR1A |= (1 << COM1A0);                            // compare output mode A
    TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12); // prescale 1024, CTC mode
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A); // interrupt quand counter match ocr1a
}
int main()
{
    _delay_ms(10000);
    initialisation();
    setLedRed();
    _delay_ms(100);
    setLedOff();
    partirMinuterie(1000);
    do
    {
        // attendre qu'une des deux variables soit modifiée
        // par une ou l'autre des interruptions.
    } while (gMinuterieExpiree == 0 && gBoutonPoussoir == 0);
    cli ();
    return 0;
}