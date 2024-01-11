#include "FollowLineTrajetB.h"
#include "debug.h"
// assignation des ports
// PORT A2 IR 01
// PORT A3 IR 02
// PORT A4 IR 03
// PORT A5 IR 04
// PORT A1 IR 05
static uint8_t firstPole;
static uint8_t secondPole;
static uint8_t thirdPole;
static uint8_t turnCount = 0;
static uint8_t diamondIntersectionCount = 0;
static Timer timer;
static bool middlePoleExists = false;
static uint8_t poleCount = 0;
uint8_t conditionTimer = 0;
static Memoire24CXXX memory;
bool test = true;

// ISR(TIMER1_COMPA_vect)
// {
//     TCNT1 = 0;
//     Timer timerBInterruption;
//     timerBInterruption.stopTimer();
//     Motor motorInterruption(FORWARD, FORWARD, ZERO, ZERO);
//     adjustMotor(motorInterruption);
// }

void adjustMotor(Motor &motor)
{
    if (poleCount == 3)
        switch (secondPole)
        {
        case 0:
            antiCockwiseRotation(motor);
            break;
        case 1:
            clockwiseRotation(motor);
            break;
        }
    else
        rollback(motor);
}

uint8_t readLineBSensor()
{
    return PINA & (~(1 << PA0)) & (~(1 << PA6)) & (~(1 << PA7));
}

void adjustLeft(Motor &motor)
{
    uint8_t line;
    motor.setRightMotorPower(FOURTY);
    motor.setLeftMotorPower(ZERO);
    do
    {
        line = readLineBSensor();
    } while (line != U3);
}
void adjustRight(Motor &motor)
{
    uint8_t line;
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(FOURTY);
    do
    {
        line = readLineBSensor();
    } while (line != U3);
}
void clockwiseRotation(Motor &motor)
{
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(ZERO);
    _delay_ms(1000);
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(HUNDRED);
    _delay_ms(250);
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(ZERO);
    _delay_ms(1000);
    motor.setRightMotorPower(SEVENTY_FIVE);
    motor.setLeftMotorPower(ZERO);
    _delay_ms(400);
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(ZERO);
}
void rollback(Motor &motor)
{
    motor.stop();
    _delay_ms(1000);
    motor.setRightMotorPower(SIXTY);
    motor.setLeftMotorPower(SIXTY);
    motor.setLeftMotorDirection(BACKWARD);
    motor.setRightMotorDirection(BACKWARD);
    _delay_ms(750);
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(ZERO);
    motor.setLeftMotorDirection(FORWARD);
    motor.setRightMotorDirection(FORWARD);
    motor.setRightMotorPower(FIFTY);
    motor.setLeftMotorPower(FIFTY);
}
void antiCockwiseRotation(Motor &motor)
{
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(ZERO);
    _delay_ms(1000);
    motor.setRightMotorPower(SEVENTY_FIVE);
    motor.setLeftMotorPower(ZERO);
    _delay_ms(500);
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(ZERO);
    _delay_ms(1000);
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(HUNDRED);
    _delay_ms(300);
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(ZERO);
}

void followLineB(Motor &motor, uint8_t &captorLed, uint8_t &statusB, bool &isRunningB)
{
    uint8_t line;
    switch (captorLed)
    {
    case U1:
        _delay_ms(20);
        line = readLineBSensor();
        if (line == U1)
        {
            motor.setRightMotorPower(FOURTY);
            motor.setLeftMotorPower(ZERO);
            while (true)
            {
                line = readLineASensor();
                if (line == U3)
                    break;
            }
        }
        break;
    case U1_U2:
    case U2:
        /* turn left */
        motor.setRightMotorPower(FIFTY);
        break;
    case U5:
        _delay_ms(20);
        line = readLineBSensor();
        if (line == U5)
        {
            motor.setLeftMotorPower(FOURTY);
            motor.setRightMotorPower(ZERO);
            while (true)
            {
                line = readLineASensor();
                if (line == U3)
                    break;
            }
        }
        break;
    case U4_U5:
    case U4:
        /* turn right */
        motor.setLeftMotorPower(SIXTY);
        break;
    case U3:
        motor.setLeftMotorPower(FOURTY);
        motor.setRightMotorPower(FOURTY);
        break;
    case U1_U2_U3_U4:
    case U1_U2_U3:
        if (turnCount < 4)
        {
            motor.setLeftMotorPower(ZERO);
            motor.setRightMotorPower(ZERO);
            _delay_ms(1000);
            motor.setLeftMotorPower(SEVENTY_FIVE);
            motor.setRightMotorPower(SEVENTY_FIVE);
            _delay_ms(350);
            motor.setRightMotorPower(FIFTY);
            motor.setLeftMotorPower(ZERO);
            do
            {
                line = readLineBSensor();
            } while (line != U3);
            turnCount++;
        }
        break;
    case U2_U3_U4_U5:
    case U3_U4_U5:
        if (turnCount < 4)
        {
            motor.setLeftMotorPower(ZERO);
            motor.setRightMotorPower(ZERO);
            _delay_ms(1000);
            motor.setLeftMotorPower(SEVENTY_FIVE);
            motor.setRightMotorPower(SEVENTY_FIVE);
            _delay_ms(350);
            motor.setLeftMotorPower(FIFTY);
            motor.setRightMotorPower(ZERO);
            do
            {
                line = readLineBSensor();
                // DEBUG_PRINT(DataType::UNIQUE_INT, line, "");
            } while (line != U3);
            turnCount++;
        }
        break;
    case U1_U2_U3_U4_U5:
        if (statusB == 0)
        {
            _delay_ms(750);
            statusB++;
            break;
        }
        else if (statusB != 0)
        {
            motor.setLeftMotorPower(ZERO);
            motor.setRightMotorPower(ZERO);
            isRunningB = false;
            test = false;
        }
        break;
    default:
        break;
    }
}
void followLineBT(Motor &motor, uint8_t &captorLed, uint8_t &statusB, bool &isRunningB)
{

    if ((diamondIntersectionCount == 2) && (conditionTimer == 0))
    {
        timer.initDefault(twoAndHalfSecond);
        conditionTimer++;
    }
    uint8_t line;
    switch (captorLed)
    {
    case U1:
        motor.setRightMotorPower(FOURTY);
        motor.setLeftMotorPower(ZERO);
        while (true)
        {
            line = readLineASensor();
            if (line == U3)
                break;
        }
        break;
    case U1_U2:
    case U2:
        /* turn left */
        motor.setRightMotorPower(FIFTY);
        break;
    case U5:
        motor.setLeftMotorPower(FOURTY);
        motor.setRightMotorPower(ZERO);
        while (true)
        {
            line = readLineASensor();
            if (line == U3)
                break;
        }
        break;
    case U4_U5:
    case U4:
        /* turn right */
        motor.setLeftMotorPower(SIXTY);
        break;
    case U3:
        motor.setLeftMotorPower(FOURTY);
        motor.setRightMotorPower(FOURTY);
        break;
    // case U1_U5:
    // case U2_U4:
    // case U1_U4:
    // case U2_U5:
    case U1_U2_U3:
    case U2_U3_U4:
    case U3_U4_U5:
        motor.setLeftMotorPower(ZERO);
        motor.setRightMotorPower(ZERO);
        _delay_ms(2000);
        motor.setLeftMotorPower(SEVENTY_FIVE);
        motor.setRightMotorPower(SEVENTY_FIVE);
        _delay_ms(500);
        switch (diamondIntersectionCount)
        {
        case 0:
        case 1:
            if (thirdPole == 1)
                adjustLeft(motor);
            else
                adjustRight(motor);
            break;
        case 2:
        case 3:
            if (firstPole == 1)
                adjustLeft(motor);
            else
                adjustRight(motor);
            break;
        }
        motor.setLeftMotorPower(SIXTY);
        motor.setRightMotorPower(SIXTY);
        diamondIntersectionCount++;
    }
}
void followRouteB()
{
    // DDRB &= ((1 << DDB0) & (1 << DDB1));
    DDRA &= (~(1 << DDA1)) & (~(1 << DDA2)) & (~(1 << DDA3)) & (~(1 << DDA4)) & (~(1 << DDA5));
    uint8_t line = PINA;
    uint8_t statusB = 0;
    bool isRunningB = true;
    Memoire24CXXX memory;
    memory.lecture(0x0001, &poleCount);
    memory.lecture(0x0002, &firstPole);
    if (poleCount == 3)
    {
        memory.lecture(0x0003, &secondPole);
        memory.lecture(0x0004, &thirdPole);
        middlePoleExists = true;
    }
    else
        memory.lecture(0x0003, &thirdPole);
    Motor motor(FORWARD, FORWARD, SIXTY, SIXTY);
    line = U1_U2_U3_U4_U5;
    followLineB(motor, line, statusB, isRunningB);
    while (test)
    {
        line = readLineBSensor();
        if (turnCount == 2 && diamondIntersectionCount != 4)
            followLineBT(motor, line, statusB, isRunningB);
        else
            followLineB(motor, line, statusB, isRunningB);
    }
}