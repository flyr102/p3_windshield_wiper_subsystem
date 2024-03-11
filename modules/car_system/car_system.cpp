//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "car_system.h"

#include "user_interface.h"
#include "windshield_wipers.h"
#include "engine.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void carSystemInit()
{
    engineInit();
    windshieldWipersInit();
    userInterfaceInit();
}

void carSystemUpdate()
{
    engineUpdate();
    windshieldWipersUpdate();
    userInterfaceUpdate();

    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
