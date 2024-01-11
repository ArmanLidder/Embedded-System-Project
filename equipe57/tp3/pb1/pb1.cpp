/*
* Nom: pb1
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Equipe #57
* Description du programme: 
*/

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

const uint8_t DELAY_1US = 10;
const uint8_t DELAY_1MS = 1;
const uint8_t DDRB_PIN_CONFIG = 0x03;
const uint8_t DDRD_PIN_CONFIG = 0x00;
const uint16_t FREQUENCY_1KHZ = 1000;


bool isPressed()
{
    return (PIND & _BV(PB2)) == _BV(PB2);
}

bool isDebounced()
{
    if (isPressed())
    {
        _delay_ms(DELAY_1MS);
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

void setLedOff()
{
    PORTB &= ~((_BV(PB2))-PB1);
}

void PWM()
{
    while (isDebounced())
    {
    int b = 1000;
    int a = b;
    int c = b-a;
        for (int k = 0; k < 500; k++)
        {
            for (int i = 0; i < a; i++)
            {
                setLedGreen();
                _delay_loop_1(DELAY_1US);
            }
            for (int j = 0; j < c; j++)
            {
                setLedOff();
                _delay_loop_1(DELAY_1US);
            }
            a -= 2;
            c += 2;
        }
    }
}


int main()
{
  DDRB = DDRB_PIN_CONFIG;
  PORTD = DDRD_PIN_CONFIG;     
  while (true)
  {
    PWM();
  }
  return 0;
}