#include "selectRoute.h"

ISR(INT1_vect)
{
    if ((currentState == 2))
        currentState = 0;
    else
        currentState++;
    EIFR |= (1 << INTF1);
}

ISR(INT0_vect)
{
    _delay_ms(30);
    isStart = true;
}

int selectRoute() {
    ButtonInteruption selection(int0, Falling); 
    ButtonInteruption confirm(int1, Falling);
    Led led(&PORTC, &DDRC, PC2, PC3);
    while (!(isStart))
    {   
        switch (currentState) {
        case 0:
            led.setLedGreen();
            break;
        case 1:
            led.setLedRed();
            break;
        case 2:
            led.setLedAmbreOnce();
            break;
        }
    }
    while(isStart) {
        switch (currentState) {
        case 0:
            for (int i = 0; i < 8; i++) {
                led.setLedGreen();
                _delay_ms(QUARTER_SECOND);
                led.setLedOff();
                _delay_ms(QUARTER_SECOND);              
            }
            return currentState;
            break;
            
        case 1:
            for (int i = 0; i < 8; i++) {
                led.setLedRed();
                _delay_ms(QUARTER_SECOND);
                led.setLedOff();
                _delay_ms(QUARTER_SECOND);
                isStart = false;
                
            }
            return currentState;
            break;
        case 2:
            for (int i = 0; i < 8; i++) {
                led.setLedAmbreLoop(QUARTER_SECOND);
                led.setLedOff();
                _delay_ms(QUARTER_SECOND);
                isStart = false;
                
            }
            return currentState;
            break;
        }
    }
    return currentState;
}