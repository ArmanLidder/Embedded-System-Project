#include "targetSVisitor.h"
uint16_t timeForOne = eightSecond;
// ISR(TIMER1_COMPA_vect)
// {
//     TCNT1 = 0;
//     timerDone = true;
// }
void updateLine(uint8_t &line)
{
    line = PINA & (~(1 << PA0)) & (~(1 << PA6)) & (~(1 << PA7));
}
void followLineS(Motor &motor, uint8_t &line)
{
    switch (line)
    {
    case U1:
        motor.setRightMotorPower(FOURTY);
        motor.setLeftMotorPower(ZERO);
        while (true)
        {
            updateLine(line);
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
            updateLine(line);
            if (line == U3)
                break;
        }
        break;
    case U4_U5:
    case U4:
        /* turn right */
        motor.setLeftMotorPower(FIFTY);
        break;
    case U3:
        motor.setLeftMotorPower(FOURTY);
        motor.setRightMotorPower(FOURTY);
        break;
    default:
        break;
    }
}
void parking(Motor &motor, uint8_t &line)
{
    motor.setLeftMotorPower(FIFTY);
    motor.setRightMotorPower(FIFTY);
    motor.setLeftMotorDirection(BACKWARD);
    motor.setRightMotorDirection(BACKWARD);
    _delay_ms(2000);
    motor.setRightMotorPower(ZERO);
    do
    {
        updateLine(line);
    } while (line != U1);
    motor.setLeftMotorPower(ZERO);
    motor.setRightMotorPower(FIFTY);
    do
    {
        updateLine(line);
    } while (line != U1_U2_U3_U4_U5 && line != U1_U2_U3_U4 && line != U1_U2_U3);
    motor.stop();
    motor.setRightMotorDirection(FORWARD);
    motor.setRightMotorPower(FOURTY);
    _delay_ms(1625);
    motor.stop();
    motor.setLeftMotorDirection(BACKWARD);
    motor.setRightMotorDirection(BACKWARD);
    motor.setLeftMotorPower(FIFTY);
    motor.setRightMotorPower(FIFTY);
    _delay_ms(2000);
    motor.stop();
}
void commeBackOnLine(Motor &motor, uint8_t &line)
{
    motor.stop();
    _delay_ms(20);
    motor.setLeftMotorPower(FIFTY);
    motor.setRightMotorPower(ZERO);
    do
    {
        updateLine(line);
    } while (line == NOTHING);
    motor.setLeftMotorPower(FIFTY);
    motor.setRightMotorPower(FIFTY);
}
void followLineStraight(Motor &motor, uint8_t &line, Timer &counter)
{
    commeBackOnLine(motor, line);
    counter.initDefault(fiveSecond);
    timerDone = false;
    while (!timerDone)
    {
        followLineS(motor, line);
        updateLine(line);
    }
    counter.stopTimer();
    timerDone = false;
    while (true)
    {
        followLineS(motor, line);
        updateLine(line);
        if (line == NOTHING)
        {
            _delay_ms(250);
            updateLine(line);
            if (line == NOTHING)
                break;
        }
    }
    parking(motor, line);
}
void turnLeftZigZag(Motor &motor, Timer &counter, uint8_t &line)
{
    updateLine(line);
    motor.setRightMotorPower(FIFTY);
    motor.setLeftMotorPower(ZERO);
    updateLine(line);
    while (line != U5)
        updateLine(line);
    while (line == U5)
        updateLine(line);
    counter.initDefault(timeForOne);
    timerDone = false;
    while (line != U1 and !timerDone)
    {
        line = PINA;
        line &= (~(1 << PA0)) & (~(1 << PA6)) & (~(1 << PA7));
    }
    timeForOne = 3000 + (uint16_t)TCNT1;
    counter.stopTimer();
    if (timerDone)
    {
        followLineStraight(motor, line, counter);
    }
}
void turnRightZigzag(Motor &motor, uint8_t &line)
{
    updateLine(line);
    motor.setLeftMotorPower(FIFTY);
    motor.setRightMotorPower(ZERO);
    updateLine(line);
    while (line != U1)
        updateLine(line);
    while (line == U1)
        updateLine(line);
    while (line != U5)
        updateLine(line);
}
void followLineZigzag(Motor &motor, Timer &counter, uint8_t &line)
{
    motor.setRightMotorPower(FIFTY);
    motor.setLeftMotorPower(FIFTY);
    switch (line)
    {
    case U1:
        turnRightZigzag(motor, line);
        break;
    case U5:
        turnLeftZigZag(motor, counter, line);
        break;
    default:
        motor.setLeftMotorDirection(FORWARD);
        motor.setRightMotorDirection(FORWARD);
        break;
    }
}
void searchU1(Motor &motor, uint8_t &line)
{
    motor.setRightMotorPower(ZERO);
    motor.setLeftMotorPower(FIFTY);
    updateLine(line);
    while (line != U1)
    {
        updateLine(line);
    }
}
void targetSVisitor(Motor &motor, Timer &counter, uint8_t &line)
{
    counter.initDefault(sevenSecond);
    updateLine(line);
    timerDone = false;
    while (!timerDone)
    {
        followLineS(motor, line);
        updateLine(line);
    }
    counter.stopTimer();
    timerDone = false;
    motor.stop();
    _delay_ms(1000);
    searchU1(motor, line);
    motor.stop();
    updateLine(line);
    while (true)
    {
        updateLine(line);
        followLineZigzag(motor, counter, line);
        if (line == NOTHING)
            break;
    }
    motor.stop();
}
void followRouteS()
{
    Motor motor(FORWARD, FORWARD, FIFTY, FIFTY);
    Timer counter;
    uint8_t line;
    targetSVisitor(motor, counter, line);
}