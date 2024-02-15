//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "car_system.h"

//=====[Defines]===============================================================

//=====[Declaration of public data types]======================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration and initialization of public global variables]=============

//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();
void ignitionActivationUpdate();
void windshieldWiperCycle();

//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();
void ignitionActivationUpdate();
void engineActivationUpdate();

//=====[Main function, the program entry point after power on or reset]========

int main(){
    inputsInit();
    outputsInit();
    carSystemInit();
    while (true)
    {
        ignitionActivationUpdate();
        engineActivationUpdate();
        carSystemUpdate();
        windshieldWiperCycle();
    }
}

//=====[Implementations of public functions]===================================

//Activates Inputs Declared Above
void inputsInit()
{
    driverSeatSensor.mode(PullDown);
    ignitionButton.mode(PullDown);
}

//Activates Inputs Declared Above
void outputsInit() 
{
    ignitionLed = OFF;
    engineLed = OFF;
}

//Modifies ignition state if specified conditions are met. Controls ignitionLed.
void ignitionActivationUpdate() 
{
    if (driverSeatSensor && !engineState){
        ignitionState = ON;
    }
    else if (!driverSeatSensor || engineState){
        ignitionState = OFF;
    }
    ignitionLed = ignitionState;
}

void windshieldWiperCycle(){
    servo.period(PERIOD); // 20ms period
    servo.write(DUTY_MIN);
    while(true){
        servo.write(DUTY_MIN);
        delay(3000);
        servo.write(DUTY_MAX);
        delay(3000);
    }
}