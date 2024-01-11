/*
* Nom du fichier: Interpretor.h
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58
* Date: 7 novembre 2022
* Description: La classe interpreteur permet de lire les instructions contenues dans
*              memoire EEPROM externe et de les executer.
*/

#pragma once
#include "LED.h"
#include "motor.h"
#include "memoire_24.h"
#include "debug.h"
#include "Sound.h"

static const uint8_t LOW_NOTE  = 44;
static const uint8_t HIGH_NOTE = 82;

enum Instruction
{
    dbt = 0x01,
    att = 0x02,
    dal = 0x44,
    det = 0x45,
    sgo = 0x48,
    sar = 0x09,
    mar = 0x61 || 0x60,
    mav = 0x62,
    mre = 0x63,
    trd = 0x64,
    trg = 0x65,
    dbc = 0xC0,
    fbc = 0xC1,
    fin = 0xFF
};

class Interpretor
{
    
public:
    Interpretor();
};