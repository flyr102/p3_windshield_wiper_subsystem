//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "car_system.h"

#include "user_interface.h"
#include "ignition.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

bool engineState = OFF;

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

//Modifies engine state if specifed conditions are met. Controls engineLed and siredPin.
void engineActivationUpdate(){
    if (ignitionState && ignitionButton){
        ignitionState = OFF;
        engineState = ON;
        uartUsb.write("Engine started.\r\n", 17);
    }
    else if (!ignitionState && ignitionButton){
        uartUsb.write("Ignition inhibited\r\n", 20);
        if (!driverSeatSensor){
            uartUsb.write("Driver seat not occupied.\r\n", 27);
        }
    }
    ignitionLed = ignitionState;
    engineLed = engineState;
}

//=====[Implementations of private functions]==================================
