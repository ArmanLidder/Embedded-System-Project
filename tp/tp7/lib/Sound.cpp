/*
* Nom du fichier: Sound.cpp
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58
* Date: 7 novembre 2022
* Description: Definition des methodes de la classe Sound declaree dans le fichier Sound.h
*/

#pragma once
#include "Sound.h"

Sound::Sound()
{
    DDRD |= (1 << PD6) | (1 << PD7);
}

uint16_t Sound::setOCR2A(uint16_t frequency)
{
	return (PRESCALED_F_CPU/(2*frequency))- 1;
}

void Sound::timer2Config()
{
	TCCR2A |= (1 << COM2A0) | (1 << WGM21);
	TCCR2B |= (1 << CS22) | (1 << CS21);
}

void Sound::play(uint8_t note)
{
	uint16_t frequency = 440*pow(2,(note-69)/12); 
	Sound::timer2Config();
	Sound::setOCR2A(frequency);
}

void Sound::stop()
{
	OCR2A  = 0;
	TCCR2A = 0;
	TCCR2B = 0;
}

void Sound::playGodfather()
{
	for (uint16_t frequency: godfather)
	{
		if (frequency == REST)
			_delay_ms(100);
		else
		{
			Sound::timer2Config();
			OCR2A = Sound::setOCR2A(frequency);
			_delay_ms(300);
		}
	}
	Sound::stop();
}

