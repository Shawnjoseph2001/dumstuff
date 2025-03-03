#include "ValveClass.h"
#include "ValveStates.h"
#include <Arduino.h>



Valve::Valve(uint32_t setValveID, uint32_t setValveNodeID, ValveType setValveType, uint8_t setPin, uint32_t setFullDutyTime, uint32_t setFireDelay, uint8_t setHoldDuty)
                : valveID{setValveID}, valveNodeID{setValveNodeID}, valveType{setValveType}, pin{setPin}, fullDutyTime{setFullDutyTime}, fireDelay{setFireDelay}, holdDuty{setHoldDuty}
{
    switch (valveType)
    {
        case NormalClosed:
            state = ValveState::Closed;
            break;
        case NormalOpen:
            state = ValveState::Open;
            break;
        default:
            state = ValveState::Closed;
            break;
    }
    timer = 0;
    
}

ValveEnable::ValveEnable(uint32_t setValveEnablePin, uint32_t setValveEnableNodeID)
                : valveEnablePin{setValveEnablePin}, valveEnableNodeID{setValveEnableNodeID}
{
    
}

void Valve::begin()
{
    pinMode(pin, OUTPUT);
    analogWrite(pin, 0);
}

void ValveEnable::begin()
{
    pinMode(valveEnablePin, OUTPUT);
    digitalWrite(valveEnablePin, 0);
}

void Valve::resetTimer()
{
    timer = 0;
}

void Valve::stateOperations()
{


    switch (state)
    {
    // if a valve has been commanded to fire, it will start actuation after appropriate delay, normal closed actuate open, normal open actuate closed
    // every state change should reset the timer
    case ValveState::FireCommanded:
        if(timer >= fireDelay)
        {
            switch (valveType)
            {
                case NormalClosed:
                    state = ValveState::OpenCommanded;
                    timer = 0;
                    break;
                case NormalOpen:
                    state = ValveState::CloseCommanded;
                    timer = 0;
                    break;
                default:
                    break;
            }
        }
        break;

    // if a valve is commanded open, if its normal closed it needs to fully actuate, if normal open it needs to drop power to zero
    case ValveState::OpenCommanded:
        switch (valveType)
        {
            case NormalClosed:
                analogWrite(pin, fullDuty);
                timer = 0;
                state = ValveState::OpenProcess;
                //Serial.print("NC OpenCommanded: ");
                //Serial.println(valveID);
                break;
            case NormalOpen:
                analogWrite(pin, 0);
                timer = 0;
                state = ValveState::Open;
                //Serial.print("NO OpenCommanded: ");
                //Serial.println(valveID);                
                break;
            default:
                break;
        }
        break;

    // if a valve is commanded closed, a normal closed removes power, normal open starts activation sequence
    case ValveState::CloseCommanded:
        switch (valveType)
        {
            case NormalClosed:
                analogWrite(pin, 0);
                timer = 0;
                state = ValveState::Closed;
                break;
            case NormalOpen:
                analogWrite(pin, fullDuty);
                timer = 0;
                state = ValveState::CloseProcess;
                break;
        }
        break;

    // if a valve is in OpenProcess, check if the fullDutyTime has passed. If it has, cycle down to hold duty
    case ValveState::OpenProcess:
        if(timer >= fullDutyTime)
        {
            analogWrite(pin, holdDuty);
            timer = 0;
            state = ValveState::Open;
        }
        break;

    // if a valve is in CloseProcess, check if the fullDutyTime has passed. If it has, cycle down to hold duty
    case ValveState::CloseProcess:
        if(timer >= fullDutyTime)
        {
            analogWrite(pin, holdDuty);
            timer = 0;
            state = ValveState::Closed;
        }
        break;
    case ValveState::Closed:
        switch (valveType)
        {
            case NormalClosed:
                analogWrite(pin, 0);
                break;
            default:
                break;
        }
    
    // All other states require no action
    default:
        break;
    }
}

void ValveEnable::stateOperations()
{
    switch (state)
    {
    
        case ValveEnableState::On:
            {
            digitalWrite(valveEnablePin, 1);
            }
        case ValveEnableState::Off:
            {
            digitalWrite(valveEnablePin, 0);
            }
    default:
        break;
    
    }
}