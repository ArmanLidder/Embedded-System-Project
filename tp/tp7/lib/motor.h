/*
* Nom du fichier: motor.h
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58
* Date: 26 octobre 2022
* Description: Declaration de la classe Motor et de ses methodes
*/

#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>

const uint8_t FORWARD = 0;
const uint8_t BACKWARD = 1;
const uint8_t ZERO = 255;
const uint8_t TWENTY_FIVE = 192;
const uint8_t FIFTY = 128;
const uint8_t SEVENTY_FIVE = 64;
const uint8_t HUNDRED = 0;

class Motor
{
public:
    Motor(uint8_t leftMotorDirection = FORWARD, uint8_t rightMotorDirection = FORWARD,
           uint8_t leftMotorPower = ZERO, uint8_t rightMotorPower = ZERO);
    void setLeftMotorDirection(uint8_t directionMotor);
    void setRightMotorDirection(uint8_t directionMotor);
    void setLeftMotorPower(uint8_t puissanceMotor);
    void setRightMotorPower(uint8_t puissanceMotor);

private:
    uint8_t leftMotorDirection_;
    uint8_t rightMotorDirection_;
    uint8_t leftMotorPower_;
    uint8_t rightMotorPower_;
    void configurePWMPort() { DDRB |= (1 << DDB3) | (1 << DDB4); }
    void changeLeftMotorDirection(uint8_t direction);
    void changeRightMotorDirection(uint8_t direction);
    void PWM();
};