#include <avr/eeprom.h>
#include "debug.h"

int main()
{
    for (uint8_t i = 0; i < 20; i++)
    {
        DEBUG_PRINT(DataType::UNIQUE_INT, i, {});
        DEBUG_PRINT(DataType::UNIQUE_CHAR, '\n', {});
        DEBUG_PRINT(DataType::CHAR_LIST, i, "Bonjour a tous");
    }
    return 0;
}