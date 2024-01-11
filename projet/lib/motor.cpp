/*
 * Nom du fichier: motor.cpp
 * Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
 * Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
 * Equipe #57-#58
 * Date: 26 octobre 2022
 * Description: Definition des methodes de la classe Motor declaree dans le fichier motor.h
 */
#include "motor.h"
Motor::Motor(uint8_t leftMotorDirection, uint8_t rightMotorDirection,
             uint8_t leftMotorPower, uint8_t rightMotorPower)
    : leftMotorDirection_(leftMotorDirection),
      rightMotorDirection_(rightMotorDirection),
      leftMotorPower_(leftMotorPower),
      rightMotorPower_(rightMotorPower)
{
    setRightMotorPower(rightMotorPower_);
    this->PWM();
}
void Motor::stop()
{
    setLeftMotorPower(ZERO);
    setRightMotorPower(ZERO);
}
void Motor::PWM()
{
    // PHYSIQUEMENT SUR LE ROBOT
    //- OC0A sur PB3 est pour controller le Motor gauche
    // PB5 direction gauche
    // PB2 direction droit
    //  -OC0B sur PB4 est pour controller le Motor droit
    cli();
    this->configurePWMPort();
    TCNT0 = 0;
    OCR0A = leftMotorPower_;
    OCR0B = rightMotorPower_;
    TCCR0A |= (1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) | (1 << COM2B0) | (1 << WGM20);
    TCCR0B |= 1 << CS11;
    // TCCR0C = 0;
    sei();
}
void Motor::setLeftMotorDirection(uint8_t directionMotor)
{
    leftMotorDirection_ = directionMotor;
    changeLeftMotorDirection(leftMotorDirection_);
}
void Motor::setRightMotorDirection(uint8_t directionMotor)
{
    rightMotorDirection_ = directionMotor;
    changeRightMotorDirection(rightMotorDirection_);
}
void Motor::setLeftMotorPower(uint8_t puissanceMotor)
{
    leftMotorPower_ = puissanceMotor;
    OCR0A = leftMotorPower_;
}
void Motor::setRightMotorPower(uint8_t puissanceMotor)
{
    if (puissanceMotor == ZERO)
        rightMotorPower_ = ZERO;
    else
        rightMotorPower_ = (puissanceMotor * 0.9);
    // rightMotorPower_ = uint8_t((puissanceMotor * 0.9) + 36);
    OCR0B = rightMotorPower_;
}
void Motor::changeLeftMotorDirection(uint8_t direction)
{
    if (direction == 0)
        PORTB &= ~(1 << PB5);
    else if (direction == 1)
        PORTB |= 1 << PB5;
}
void Motor::changeRightMotorDirection(uint8_t direction)
{
    if (direction == 0)
        PORTB &= ~(1 << PB2);
    else if (direction == 1)
        PORTB |= 1 << PB2;
}

void Motor::pause()
{
    setLeftMotorPower(ZERO);
    setRightMotorPower(ZERO);
    _delay_ms(1000);
    setLeftMotorPower(SEVENTY_FIVE);
    setRightMotorPower(SEVENTY_FIVE);
}

