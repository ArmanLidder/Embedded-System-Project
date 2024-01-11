/*
 * Nom du fichier: usart.cpp
 * Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
 * Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
 * Equipe #57-#58
 * Date: 26 octobre 2022
 * Description: Definition des methodes de la classe Usart declaree dans le fichier usart.h
 */

/*
    To transmit data from PC to External memory
    Usart transmition;                          Create a Usart instance 
    transmition.transmitExternalMem();          Transmit from PC to external Mem
    serieViaUSB -e -f "file_name"               Transmit from PC to internal memory with
    getInstructionNumber                        iterate on the number of instructions    
    readExtarnalMem(a 8 bit pointer)            Read external mem 
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

void Usart::readExtarnalMem(uint16_t address, uint8_t* externalMemData){
    int resultat = memory.lecture(address, externalMemData);
    _delay_ms(6);
}

uint16_t Usart::getInstructionNumber(){
    uint16_t instructionNumber;
    uint8_t size0;
    uint8_t size1;
    readExtarnalMem((uint16_t)0x0000, &size0);
    readExtarnalMem((uint16_t)0x0001, &size1);
    instructionNumber = (uint16_t)size0;
    instructionNumber = instructionNumber << 8;
    instructionNumber |= (uint16_t)size1;
    return instructionNumber;
}

uint8_t Usart::USARTReceive(void)
{
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}

void Usart::transmitExternalMem()
{
    uint8_t size1, size2;
    uint16_t instructionNumber;
    size1 = USARTReceive();
    instructionNumber = (uint16_t)size1;
    int resultat = memory.ecriture(0x0000, size1);
    _delay_ms(6);
    instructionNumber = instructionNumber << 8;

    size2 = USARTReceive();
    resultat = memory.ecriture(0x0001, size2);
    _delay_ms(6);
    instructionNumber |= (uint16_t)size2;
    

    for (uint16_t i = 2; i < instructionNumber; i++)
    {
        int resultat = memory.ecriture(0x0000 + i, USARTReceive());
        _delay_ms(6);
    }
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