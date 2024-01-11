/*
* Nom du fichier: ButtonInterruption.cpp
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58
* Date: 26 octobre 2022
* Description: Definition des methodes de la classe ButtonInteruption declaree dans le fichier ButtonInterruption.h
*/
# include <ButtonInterruption.h>
ButtonInteruption::ButtonInteruption(intConfig intx, Edge edge) 
{
    cli();
    switch (intx)
    {
        case int0:
            EIMSK |= (1 << INT0);
            break;

        case int1:
            EIMSK |= (1 << INT1);
            break;

        case int2:
            EIMSK |= (1 << INT2);
            break;

        default:
            break;
    }
    
    switch (edge)
    {
        case Edge::Low:
            break;

        case Edge::Any:
            EICRA |= (1 << ISC00);
            break;

        case Edge::Falling:
            EICRA |= (1 << ISC01);
            break;

        case Edge::Rising:
            EICRA |= (1 << ISC01) | (1 << ISC00);
            break;

        default:
            break;
    }
    sei();
}
