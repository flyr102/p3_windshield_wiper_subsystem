//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "car_system.h"

#include "windshield_wipers.h"
#include "engine.h"
#include "display.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut incorrectCodeLed(LED3);


//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool incorrectCodeState = OFF;
static bool systemBlockedState = OFF;

static bool codeComplete = false;
static int numberOfCodeChars = 0;

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceMatrixKeypadUpdate();
static void incorrectCodeIndicatorUpdate();
static void systemBlockedIndicatorUpdate();

static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    userInterfaceDisplayUpdate();
}

//=====[Implementations of private functions]==================================


static void userInterfaceDisplayInit()
{
    displayInit();
     
    displayCharPositionWrite(0,0);
    displayStringWrite("WIPERS:");

    displayCharPositionWrite(0,1);
    displayStringWrite("                ");
}

static void userInterfaceDisplayUpdate()
{
    switch(getWiperMode()){
        case 0 : 
        displayCharPositionWrite(8,0);
        displayStringWrite("OFF"); break;
        case 1 : 
        displayCharPositionWrite(8,0);
        displayStringWrite("LOW"); break;
        case 2 :
        displayCharPositionWrite(8,0);
        displayStringWrite("INT"); break;
        case 3 :
        displayCharPositionWrite(8,0);
        displayStringWrite("ON "); break;
        default : 
        displayCharPositionWrite(0,0);
        displayStringWrite("WIPERS:"); break;
    }

    switch(getWiperIntSetting()){
        case 0 :
        displayCharPositionWrite(0,1);
        displayStringWrite("FREQ: 3 sec"); break;
        case 1 : 
        displayCharPositionWrite(0,1);
        displayStringWrite("FREQ: 5 sec"); break;
        case 2 :
        displayCharPositionWrite(0,1);
        displayStringWrite("FREQ: 8 sec"); break;
        default: 
        displayCharPositionWrite(0,1);
        displayStringWrite("                "); break;
    }
}