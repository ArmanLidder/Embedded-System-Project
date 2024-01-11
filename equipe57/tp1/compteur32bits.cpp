/*
* Nom: compteur 32 bits
005 Matthew Khouzam
* Description: Ceci est un exemple simple de programme
*/

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

const uint8_t DELAI = 10;
const uint8_t nIterations = 100;

uint8_t PINDinit;
uint8_t PINDfinal;

void fonctiondelay(uint8_t nIterations)
{
  for (uint8_t i = 0; i < nIterations; i++)
  {
    _delay_ms(DELAI);
 }
}

bool checkbuttonstate()
{
  return PIND&0x04;
}

int main()
{
  DDRB = 0x03;
  PORTD = 0x00;     
  while (1)
  {
    while (1) // Partie debounce
    {

      PINDinit = PIND;
      _delay_ms(DELAI);
      PINDfinal = PIND;
      if (PINDinit == PINDfinal)
      {
        break;
      }
    }
    while (PIND & 0x04) // vert rouge ambre loop si bouton actif
    {

      PORTB = 0x02;
      if(checkbuttonstate()==0x00){break;}
      fonctiondelay(nIterations);
      if(checkbuttonstate()==0x00){break;}
      PORTB >>= 1;
      if(checkbuttonstate()==0x00){break;}
      fonctiondelay(nIterations);
      if(checkbuttonstate()==0x00){break;}
      for (int i = 0; i < 50; i++)
      {
        PORTB <<= 1;
        _delay_ms(DELAI);
        PORTB >>= 1;
        _delay_ms(DELAI);
      }
      if(checkbuttonstate()==0x00){break;}
    }
    PORTB = 0x00;
  }

  return 0;
}

