//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Defines]===============================================================

//=====[Declaration and initialization of public global objects]===============
DigitalIn driverSeat (D7);
DigitalIn driverBelt (D6);
DigitalIn passengerSeat (D5);
DigitalIn passengerBelt (D4);
DigitalIn ignition (D3);

DigitalOut alarmBuzzer (D2);
DigitalOut ignitionLed (LED1);
DigitalOut engineLed (LED2);

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration and initialization of public global variables]=============

//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();

//=====[Main function, the program entry point after power on or reset]========

int main(){
    while (true)
    {

    }
}

//=====[Implementations of public functions]===================================

void inputsInit()
{
    driverSeat.mode(PullDown);
    driverBelt.mode(PullDown);
    passengerSeat.mode(PullDown);
    passengerBelt.mode(PullDown);
    ignition.mode(PullDown);
}

void outputsInit()
{
    alarmBuzzer = OFF;
    ignitionLed = OFF;
    engineLed = OFF;
}


