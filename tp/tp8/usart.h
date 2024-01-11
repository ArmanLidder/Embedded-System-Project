/*
 * Nom du fichier: usart.cpp
 * Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
 * Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
 * Equipe #57-#58
 * Date: 26 octobre 2022
 * Description: Declaration de la classe Usart et de ses methodes
 */

#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
enum DataType
{
    UNIQUE_CHAR,
    CHAR_LIST,
    UNIQUE_INT
};
class Usart
{
public:
    Usart();
    void transmitDataInt(DataType dataType, uint8_t data, char text[]);
    void transmitDataUnique(uint8_t data);
    void transmitText(char text[]);
    void transmitInt(uint8_t integer);
    void initUSART();
};
