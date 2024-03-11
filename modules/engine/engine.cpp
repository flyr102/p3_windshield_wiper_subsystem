//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "car_system.h"

#include "user_interface.h"
#include "ignition.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

typedef enum {
   WAIT,
   BUTTON_PRESSED,
   BUTTON_RELEASED
} ignitionButtonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalOut engineLed(LED2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

bool engineState = false;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static bool engineButtonUpdate();
static void inputsInit();
static void outputsInit();

//=====[Implementations of public functions]===================================

void engineInit(){
    inputsInit();
    outputsInit();
}

void engineUpdate(){ 
    ignitionUpdate();
    if (getIgnitionState() && getIgnitionButtonUpdate()){
        engineState = true;
    }
    else if (engineState && getIgnitionButtonUpdate()){
        engineState = false;
    }
    engineLed = engineState;
}

bool getEngineState(){
    return engineState;
}

//=====[Implementations of private functions]==================================

static void inputsInit(){
    ignitionInit();
}

static void outputsInit(){
    engineLed = OFF;
}

static void engineLedUpdate(){
    engineLed = engineState;
}