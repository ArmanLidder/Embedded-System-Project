/*
* Nom du fichier: Interpretor.cpp
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58
* Date: 7 novembre 2022
* Description: Implementation de la classe interpretor.
*/

#pragma once
#include "Interpretor.h"

Interpretor::Interpretor()
{
        uint8_t  operand;
        uint8_t  instruction;
        uint16_t lCounter;
        uint16_t lAddress;
        uint16_t fileSize;
        uint16_t pCounter = 0x0000;
        
        bool isRunning    = false;
        bool isStarting   = false;

        Usart         usart;
        Motor         motor;
        Sound         sound;
        Memoire24CXXX memoire;
        Led           led(&PORTB, &DDRB, PB0, PB1);
        
        // Lecture des 2 premiers octets pour determiner la 
        // taille du fichier
        memoire.lecture(pCounter, &instruction);
        pCounter++;
        fileSize = instruction;

        memoire.lecture(pCounter, &instruction);
        pCounter++;
        fileSize = fileSize << 8;
        fileSize |= instruction;

        // Detection de l'instruction DBT => Debut
        while (!(isRunning))
        {
            memoire.lecture(pCounter, &instruction);
            pCounter++;
            memoire.lecture(pCounter, &operand);
            pCounter++;
            
            isStarting = (instruction == dbt);
            if (isStarting)
                isRunning = true;
        }

        // Une fois DBT detecte, lecture et implementation
        // des prochaines instructions
        while (isRunning)
        {
            memoire.lecture(pCounter, &instruction);
            pCounter++;
            memoire.lecture(pCounter, &operand);
            pCounter++;

            switch (instruction)
            {
            case Instruction::att:
                for (uint16_t i = 0; i < operand; i++)
                    _delay_ms(25);
                break;

            case Instruction::dal:
                switch (operand)
                {
                case 1:
                    led.setLedGreen();
                    break;
                case 2:
                    led.setLedRed();
                    break;
                }
                break;

            case Instruction::det:
                led.setLedOff();
                break;

            case Instruction::sgo:
                if (LOW_NOTE < operand && operand < HIGH_NOTE)
                    sound.play(operand);
                else if (operand == 0)
                    sound.playGodfather();
                break;

            case Instruction::sar:
                sound.stop();
                break;

            case Instruction::mar:
                motor.setLeftMotorPower(ZERO);
                motor.setRightMotorPower(ZERO);
                break;

            case Instruction::mav:
                motor.setLeftMotorDirection(FORWARD);  // (OPT 57) Pour robot => FORWARD
                motor.setRightMotorDirection(FORWARD); // (OPT 57) Pour robot => FORWARD
                motor.setRightMotorPower(operand);
                motor.setLeftMotorPower(operand);
                break;

            case Instruction::mre:
                motor.setLeftMotorDirection(BACKWARD);  // (OPT 57) Pour robot 58 => FORWARD
                motor.setRightMotorDirection(BACKWARD); // (OPT 57) Pour robot 58 => FORWARD
                motor.setRightMotorPower(operand);
                motor.setLeftMotorPower(operand);
                break;

            case Instruction::trd:
                motor.setLeftMotorDirection(FORWARD);
                motor.setRightMotorDirection(BACKWARD);
                motor.setLeftMotorPower(HUNDRED);
                motor.setRightMotorPower(HUNDRED);
                _delay_ms(400);
                motor.setLeftMotorPower(ZERO);
                motor.setRightMotorPower(ZERO);
                break;

            case Instruction::trg:
                motor.setLeftMotorDirection(BACKWARD);
                motor.setRightMotorDirection(FORWARD);
                motor.setLeftMotorPower(HUNDRED);
                motor.setRightMotorPower(HUNDRED);
                _delay_ms(400);
                motor.setLeftMotorPower(ZERO);
                motor.setRightMotorPower(ZERO);
                break;

            case Instruction::dbc:
                lAddress = pCounter;
                lCounter = operand;
                break;

            case Instruction::fbc:
                if (!(lCounter == 0))
                {
                    pCounter = lAddress;
                    lCounter--;
                }
                break;

            case Instruction::fin:
                motor.setLeftMotorPower(ZERO);
                motor.setRightMotorPower(ZERO);
                led.setLedOff();
                sound.stop();
                isRunning = false;
                break;
            }
        }
}
