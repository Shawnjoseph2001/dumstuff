#ifndef VALVECLASSES_H
#define VALVECLASSES_H

#include "ValveStates.h"
#include <Arduino.h>

// This class defines the Valve Object that will be used to represent and actuate the valves
// Run begin to set the pins

enum ValveType
{
    NormalClosed,
    NormalOpen,
};



class Valve
{

    private:
        const uint32_t valveID;                          // Valve ID number 
        const uint32_t valveNodeID;                      // NodeID the valve is controlled by
        const ValveType valveType;                  // sets the valve type, either normal closed or normal open
        const uint8_t pin;                              // Valve PWM pin for actuation
        const uint32_t fullDutyTime;                // Time PWM needs to be at full duty for actuation, in MICROS
        const uint32_t fireDelay;                   // Time to wait until actuation after fire command given, in MICROS
        ValveState state;                           // Tracks the valve state
        elapsedMicros timer;                        // timer for the valve, used for changing duty cycles, in MICROS
        const uint8_t fullDuty{255};                // full duty cycle for servo initial actuation
        const uint8_t holdDuty{};                   // partial duty cycle to hold valve in actuated state
        
        
    public:
    
    // constructor, define the valve ID here, and the pin that controls the valve, setFireDelay is only parameter that can be left blank
        Valve(uint32_t setValveID, uint32_t setValveNodeID, ValveType setValveType, uint8_t setPin, uint32_t setFullDutyTime, uint32_t setFireDelay = 0 , u_int8_t setHoldDuty = 64); 

    // a start up method, to set pins from within setup()
        void begin();

    // access functions defined in place

    // get functions, return the current value of that variable
        uint32_t getValveID(){return valveID;}
        uint32_t getValveNodeID(){return valveNodeID;}
        ValveType getValveType(){return valveType;}
        uint8_t getPin(){return pin;}
        uint32_t getFullDutyTime(){return fullDutyTime;}
        uint8_t getHoldDuty(){return holdDuty;}
        uint32_t getFireDelay(){return fireDelay;}
        ValveState getState(){return state;}
        uint32_t getTimer(){return timer;}

    // set functions, allows the setting of a variable
        void setState(ValveState newState) {state = newState; timer = 0;} //every time a state is set, the timer should reset

    // functions with executables defined in ValveClasses.cpp
        void resetTimer();              // resets timer to zero, timer increments automatically in microseconds

    // ----- THIS METHOD TO BE RUN EVERY LOOP ------
    // stateOperations will check the current state of the valve and perform any actions that need to be performed
    // for example, if the valve is commanded to open, this needs to be run so that the valve can start opening
    // and it needs to be run every loop so that once enough time has pass the 
        void stateOperations();



};

class ValveEnable
{
    private:
        const uint32_t valveEnableNodeID;
        const uint32_t valveEnablePin;
        ValveEnableState state;

    public:
        
    // constructor
        ValveEnable (uint32_t setValveEnableNodeID, uint32_t setValveEnablePin);


    // a start up method, to set pins from within setup()
        void begin();


    // get functions, return the current value of that variable
        uint32_t getValveEnableNodeID(){return valveEnableNodeID;}
        uint32_t getValveEnablePin(){return valveEnablePin;}
        ValveEnableState getState(){return state;}   
    // set functions, allows the setting of a variable
        void setState(ValveEnableState newState) {state = newState;}

    // samesies as above
        void stateOperations();

};



#endif