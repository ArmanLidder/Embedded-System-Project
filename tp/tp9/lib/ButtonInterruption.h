/*
* Nom du fichier: ButtonInterruption.h
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58
* Date: 26 octobre 2022
* Description: Declaration de la classe ButtonInteruption et de ses methodes
*/
#pragma once
# define F_CPU 8000000UL
# include <avr/interrupt.h>

enum  Edge {Low, Any, Falling, Rising};
enum  intConfig {int0,int1,int2};

class ButtonInteruption
{
    public:
        ButtonInteruption(intConfig intx, Edge edge);
};