/*
 * Nom du fichier: usart.cpp
 * Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
 * Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
 * Equipe #57-#58
 * Date: 26 octobre 2022
 * Description: Definition des methodes de la classe Usart declaree dans le fichier usart.h
 */

#include "usart.h"
#include <stdio.h>
#include <string.h>

const uint8_t START_BIT = 0;
const uint8_t END_BIT = 0xCF;

Usart::Usart()
{
    UBRR0H = START_BIT;
    UBRR0L = END_BIT;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void Usart::initUSART()
{
    UBRR0H = START_BIT;
    UBRR0L = END_BIT;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void Usart::transmitDataUnique(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;
}

void Usart::transmitDataInt(DataType dataType, uint8_t data = 0, char text[] = {})
{
    switch (dataType)
    {
    case DataType::UNIQUE_CHAR:
        transmitDataUnique(data);
        break;
    case DataType::CHAR_LIST:
        transmitText(text);
        break;

    case DataType::UNIQUE_INT:
        transmitInt(data);
        break;
    }
}

void Usart::transmitText(char text[])
{
    char stop = '\0';

    for (uint8_t i = 0; text[i] != stop; ++i)
    {
        transmitDataUnique((uint8_t)text[i]);
    }
}

void Usart::transmitInt(uint8_t integer)
{
    char buffer[5];
    snprintf(buffer, 4, "%u", integer);
    transmitText(buffer);
    transmitDataUnique('\t');
}