#include "ButtonInterruption.h"
#include "LED.h"
#include <util/delay.h>
#include "motor.h"

volatile int currentState = 0;

void beginStateMachine()
{
    while (true)
    {   
        Led led(&PORTB, &DDRB, PB0, PB1);
        switch (currentState)
        {
        case 0:
            led.setLedRed();
            break;
        case 1:
            led.setLedAmbreOnce();
            break;
        case 2:
            led.setLedGreen();
            break;
        case 3:
            led.setLedRed();
            break;
        case 4:
            led.setLedOff();
            break;
        case 5:
            led.setLedGreen();
            break;
        case 6:
            currentState = 0;
            break;
        }
    }
}

ISR(INT0_vect)
{
    _delay_ms(30);
    currentState += 1;
    EIFR |= (1 << INTF0);
}

int main()
{
    Motor motor(FORWARD, FORWARD, FIFTY, FIFTY);
    _delay_ms(3000);
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(ZERO);
    
    _delay_ms(3000);
    //motor.setLeftMotorDirection(BACKWARD);
    motor.setRightMotorDirection(BACKWARD);
    _delay_ms(3000);

    motor.setRightMotorPower(FIFTY);
    //motor.setLeftMotorPower(FIFTY);
    ButtonInteruption button (int0,Any);
    beginStateMachine();
}