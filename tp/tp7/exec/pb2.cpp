#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include "memoire_24.cpp"
#include <avr/eeprom.h>
#include "motor.h"
#include "debug.h"
#include "usart.h"
#include "LED.h"
#include "timer.h"

int main()
{
    Motor motor(FORWARD, FORWARD, FIFTY, FIFTY);
    //moteur.PWM();
    Led nut(&PORTA, &DDRA, PA0, PA1);

    // Usart transmit;
    // timer timer;
    for (uint8_t i = 0; i < 20; i++)
    {
        DEBUG_PRINT(DataType::UNIQUE_INT, i, {});
        DEBUG_PRINT(DataType::UNIQUE_CHAR, '\n', {});
        DEBUG_PRINT(DataType::CHAR_LIST, i, "Bonjour a tous");
    }
    return 0;
}