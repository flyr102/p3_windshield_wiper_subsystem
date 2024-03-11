//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "car_system.h"

#include "user_interface.h"
#include "engine.h"
#include "ignition.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

typedef enum {
   WAIT,
   BUTTON_PRESSED,
   BUTTON_RELEASED
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn driverSeatSensor (D10);
DigitalIn ignitionButton (BUTTON1);

DigitalOut ignitionLed (LED1);

bool ignitionState = OFF;

buttonState_t driverSeatSensorState;
buttonState_t ignitionButtonState;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static bool driverSeatSensorUpdate();
static bool ignitionButtonUpdate();
void sensorScan();

//=====[Implementations of public functions]===================================

void ignitionInit(){
    ignitionButton.mode(PullDown);
    driverSeatSensor.mode(PullDown);
}

void ignitionUpdate(){
    sensorScan();
}

bool getIgnitionState(){
    return ignitionState;
}

bool getIgnitionButtonUpdate(){
    return ignitionButtonUpdate();
}

//=====[Implementations of private functions]==================================

void sensorScan(){
    if (driverSeatSensorUpdate() && !getEngineState()){
        ignitionState = ON;
    }
    else if (!driverSeatSensorUpdate() || getEngineState()){
        ignitionState = OFF;
    }
    ignitionLed = ignitionState;
}

static bool driverSeatSensorUpdate(){

   switch(driverSeatSensorState){
       case WAIT :
           if(driverSeatSensor){
               driverSeatSensorState = BUTTON_PRESSED;
               return true;
           }
       break;

       case BUTTON_PRESSED :
           if(!driverSeatSensor){
               driverSeatSensorState = BUTTON_RELEASED;
           }
           return true;
       break;
    
       case BUTTON_RELEASED :
           driverSeatSensorState = WAIT;
       break;
   }
   return false;
}

static bool ignitionButtonUpdate(){ 

   switch(ignitionButtonState){
       case WAIT :
           if(ignitionButton){
               ignitionButtonState = BUTTON_PRESSED;
           }
       break;

       case BUTTON_PRESSED :
           if(!ignitionButton){
               ignitionButtonState = BUTTON_RELEASED;
           }
       break;
    
       case BUTTON_RELEASED :
           ignitionButtonState = WAIT;
           return true;
       break;
   }
   return false;
}