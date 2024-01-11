/*
* Nom du fichier: Sound.h
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58
* Date: 7 novembre 2022
* Description: Classe Sound permettant l'utilisation du haut-parleur piezoelectrique.
*              Au niveau materiel, les broches 6 et 7 sont configure en sortie et doivent
*              etre reliees au cable de l'haut-parleur. De plus, le signal PWM emettant les 
*              differentes frequences sonores est emis par le timer 2. Sa configuration est 
*              suivantes: impulsion emise par OC2A, mode CTC et prescalor a 256.
*/

#define F_CPU 8000000UL
#define PRESCALED_F_CPU 31250 // F_CPU/PRESCALOR(256)

#pragma once
#include <avr/io.h>
#include "Godfather.h"
#include <util/delay.h>

class Sound
{
public:

    Sound();
    
    void play(uint8_t note);
    void stop();
    void playGodfather();

protected:

    uint16_t setOCR2A(uint16_t frequency);
    void     timer2Config();
};