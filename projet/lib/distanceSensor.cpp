#include "distanceSensor.h"
//#include "debug.h"
int distance=0;

bool isFar()
{
    return (distance >= FAR_REGION_MIN && distance <= FAR_REGION_MAX);
}

bool isClose()
{
    return (distance >= CLOSE_REGION_MIN && distance <= CLOSE_REGION_MAX);
}

int checkPoleDistance(poleDetection &pole)
{
    can distanceConverter;
    Sound detectionSound;
    //DEBUG_PRINT(DataType::CHAR_LIST, 1, "rentrer dans checkpole");
    for (int i = 0; i < 50; i++) //"Unstable output"  pour ce temps environ, selon la documentation
    {
        distance += distanceConverter.lecture(PA0) >> PA2;
        
    } // On enleve les deux dernier bits qui sont a etre neglige (On passe de 10 bits a 8 bits).
    distance = distance / 50;
    // DEBUG_PRINT(DataType::UNIQUE_INT, distance, {});
    if (isClose())
    {
        //detectionSound.play(NOTE_DS8);
        pole = POLE_DETECTED_CLOSE;
    //    DEBUG_PRINT(DataType::CHAR_LIST, 0, "POTEAU PROCHE\n");
        
    } // Note aigu
    else if (isFar())
    {
        //detectionSound.play(NOTE_B0);
        pole = POLE_DETECTED_FAR;
        
        //DEBUG_PRINT(DataType::CHAR_LIST, 0, "POTEAU LOIN\n");
    } // Note basse
    else
    {
        detectionSound.stop();
        pole = POLE_NOT_DETECTED;
    } // Rien detecte
    return distance;
}
