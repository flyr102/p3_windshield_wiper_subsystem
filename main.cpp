//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Defines]===============================================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn driverSeat (D7);
DigitalIn driverBelt (D6);
DigitalIn passengerSeat (D5);
DigitalIn passengerBelt (D4);
DigitalIn ignitionButton (D3);

DigitalOut ignitionLed (LED1);
DigitalOut engineLed (LED2);

DigitalInOut sirenPin(PE_10);

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration and initialization of public global variables]=============

bool alarmState = OFF;
bool ignitionState = OFF;
bool engineState = OFF;
bool driverWelcomeMessageSent = false;

//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();
void driverWelcomeUpdate();
void ignitionActivationUpdate();
void engineActivationUpdate();

//=====[Main function, the program entry point after power on or reset]========

int main(){
    inputsInit();
    outputsInit();
    while (!engineState && !alarmState)
    {
        driverWelcomeUpdate();
        ignitionActivationUpdate();
        engineActivationUpdate();
    }
}

//=====[Implementations of public functions]===================================

void inputsInit()
{
    driverSeat.mode(PullDown);
    driverBelt.mode(PullDown);
    passengerSeat.mode(PullDown);
    passengerBelt.mode(PullDown);
    ignitionButton.mode(PullDown);
    sirenPin.mode(OpenDrain);
    sirenPin.input();
}

void outputsInit() 
{
    ignitionLed = OFF;
    engineLed = OFF;
}

void driverWelcomeUpdate(){
    if (driverSeat){
        if (!driverWelcomeMessageSent) {
            uartUsb.write ("Welcome to enhanced alarm system model 218-W24\r\n", 48);
            driverWelcomeMessageSent = true;
        }
    }
    else if (!driverSeat){
        driverWelcomeMessageSent = false;
    }
}

void ignitionActivationUpdate() 
{
    if (driverSeat && driverBelt && passengerSeat && passengerBelt && !engineState){
        ignitionState = ON;
    }
    else if (!driverSeat || !driverBelt || !passengerSeat || !passengerBelt || engineState){
        ignitionState = OFF;
    }
    ignitionLed = ignitionState;
}

void engineActivationUpdate(){
    if (ignitionState && ignitionButton){
        ignitionState = OFF;
        engineState = ON;
        uartUsb.write("Engine started.\r\n", 17);
    }
    else if (!ignitionState && ignitionButton){
        sirenPin.output();                                     
        sirenPin = LOW;   
        alarmState = ON;
        uartUsb.write("Ignition inhibited\r\n", 20);
        if (driverSeat){
            uartUsb.write("Driver seat not occupied.\r\n", 27);
        }
        if (driverBelt){
            uartUsb.write("Driver seatbelt not fastened.\r\n", 31);
        }
        if (passengerSeat){
            uartUsb.write("Passenger seat not occupied.\r\n", 30);
        }
        if (passengerBelt){
            uartUsb.write("Passenger seatbelt not fastened.\r\n", 34);
        }
    }
    ignitionLed = ignitionState;
    engineLed = engineState;
}