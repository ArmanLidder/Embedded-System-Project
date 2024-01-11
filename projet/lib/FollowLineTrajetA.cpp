
#include "FollowLineTrajetA.h"
//#include "debug.h"
// assignation des ports
// PORT A2 IR 01
// PORT A3 IR 02
// PORT Amak IR 03
// PORT A5 IR 04
// PORT A1 IR 05

static const uint8_t DEPARTURE = 0;
static const uint8_t ARRIVAL = 1;
static const uint8_t POLE_DETECTION_DEBOUNCE = 80;
static const uint16_t TEMP_FOLLOWLINE_DELAY = 1750;
static uint16_t poleCount =2;
static uint8_t statusA = 0;
uint8_t lineA = 0;
static bool isRunning = true;
static Memoire24CXXX memory;
static Sound son;

uint8_t readLineASensor()
{
    return PINA & (~(1 << PA0)) & (~(1 << PA6)) & (~(1 << PA7));
}
void followLineA(Motor &motor, uint8_t &captorLed, uint8_t &statusA, bool &isRunning)
{
    uint8_t lineA;
    switch (captorLed)
    {
    case U1:
        motor.setRightMotorPower(FIFTY);
        motor.setLeftMotorPower(ZERO);
        while (true)
        {
            lineA = readLineASensor();
            if (lineA == U3)
                break;
        }
        break;
    case U1_U2:
    case U2:
        /* turn left */
        motor.setRightMotorPower(SIXTY);
        break;
    case U5:
        motor.setLeftMotorPower(FIFTY);
        motor.setRightMotorPower(ZERO);
        while (true)
        {
            lineA = readLineASensor();
            if (lineA == U3)
                break;
        }
        break;
    case U4_U5:
    case U4:
        /* turn right */
        motor.setLeftMotorPower(SEVENTY_FIVE);
        break;
    case U3:
        motor.setLeftMotorPower(FIFTY);
        motor.setRightMotorPower(FIFTY);
        break;
    case U1_U2_U3_U4_U5:
        if (statusA == ARRIVAL)
        {
            motor.setLeftMotorPower(ZERO);
            motor.setRightMotorPower(ZERO);
            memory.ecriture(0x0001, poleCount-2);
            _delay_ms(10);
            isRunning = false;
        }
        else if (statusA == DEPARTURE)
        {
            _delay_ms(750);
            statusA++;
            break;
        }
        break;
    default:
        break;
    }
}
void followLineATemporarily(Motor &motor)
{
    for (uint16_t i = 0; i < TEMP_FOLLOWLINE_DELAY; i++)
    {
        lineA = readLineASensor();
        followLineA(motor, lineA, statusA, isRunning);
        _delay_ms(1);
    }
}
void followRouteA()
{
    DDRA &= (~(1 << DDA1)) & (~(1 << DDA2)) & (~(1 << DDA3)) & (~(1 << DDA4)) & (~(1 << DDA5));
    Sound detectionSound;
    Motor motor(FORWARD, FORWARD, SIXTY, SIXTY);
    while (isRunning)
    {
        poleDetection poleState = POLE_NOT_DETECTED;
        lineA = readLineASensor();
        followLineA(motor, lineA, statusA, isRunning);
        checkPoleDistance(poleState);
        if (poleState == POLE_DETECTED_FAR || poleState == POLE_DETECTED_CLOSE)
        {
            _delay_ms(POLE_DETECTION_DEBOUNCE);
            checkPoleDistance(poleState);
            if (poleState == POLE_DETECTED_FAR || poleState == POLE_DETECTED_CLOSE)
            {
                switch (poleState)
                {
                case POLE_DETECTED_FAR:
                    detectionSound.play(NOTE_B0);
                    memory.ecriture(poleCount, 1);
                    _delay_ms(10);
                    //DEBUG_PRINT(DataType::CHAR_LIST, 1, "far");
                    break;
                case POLE_DETECTED_CLOSE:
                    detectionSound.play(NOTE_DS8);
                    memory.ecriture(poleCount, 0);
                    _delay_ms(10);
                    //DEBUG_PRINT(DataType::CHAR_LIST, 1, "close");
                    break;
                default:
                    break;
                }
                poleCount++;
                motor.pause();
                detectionSound.stop();
                followLineATemporarily(motor);
            }
        }
    }
}