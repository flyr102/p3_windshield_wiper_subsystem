//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "car_system.h"

#include "user_interface.h"
#include "ignition.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn potentiometer(A0);

PwmOut servo(PF_9);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

float potentiometerReading = 0.0;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================



//=====[Implementations of private functions]==================================
