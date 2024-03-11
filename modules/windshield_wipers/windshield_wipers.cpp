//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "car_system.h"

#include "user_interface.h"
#include "engine.h"

//=====[Declaration of private defines]========================================

#define MODE_OFF 0.00
#define MODE_LO 0.25
#define MODE_INT 0.5
#define MODE_HI 0.75

#define INT_DELAY_3 0.33
#define INT_DELAY_5 0.66
#define INT_DELAY_8 1

#define DELAY_3_MS 226
#define DELAY_5_MS 526
#define DELAY_8_MS 726

#define DUTY_MIN 0.055
#define DUTY_MAX 0.088
#define PERIOD 0.02

#define INCREMENT 20 //amount of increments the low state cycles through
#define DELAY_TIME_MS 300 //amount of time it takes for the low mode to sweep one way

//=====[Declaration of private data types]=====================================

typedef enum {
   WIPE,
   REST,
   INT_DELAY
} windshieldWiperState_t;

//=====[Declaration and initialization of public global objects]===============

AnalogIn wiperModePotentiometer(A0);
AnalogIn intSettingPotentiometer(A1);
PwmOut wiperServo(PF_9);

int wiperMode = 0;
int wiperDelay = 0;
int accumulatedIntTimeAlarm = 0;

float cycleLength = (DUTY_MAX-DUTY_MIN)/INCREMENT;
int delayTime = DELAY_TIME_MS/INCREMENT;

windshieldWiperState_t windshieldWiperState = REST;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

float wiperModePotentiometerReading = 0.0;
float wiperIntSettingPotentiometerReading = 0.0;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static void updateWiperMode();
static void updateIntSetting();
static void cycleWipers();
static void wipe();

//=====[Implementations of public functions]===================================

void windshieldWipersInit(){
    wiperServo.period(PERIOD);
    wiperServo.write(DUTY_MAX);
    updateWiperMode();
    updateIntSetting();
}

void windshieldWipersUpdate(){
    if (getEngineState()){
        updateWiperMode();
        updateIntSetting();
        cycleWipers();
    }
}

void servoUpdate(float dutyCycle){
    wiperServo.write(dutyCycle);
}

int getWiperMode(){
    return wiperMode;
}

int getWiperIntSetting(){
    return wiperDelay;
}
//=====[Implementations of private functions]==================================

void updateWiperMode(){
    wiperModePotentiometerReading = wiperModePotentiometer.read();
    if(wiperModePotentiometerReading < MODE_LO){ 
        wiperMode = 0;
    }
    
    else if(wiperModePotentiometerReading >= MODE_LO && wiperModePotentiometerReading < MODE_INT){
        wiperMode = 1;
    }

    else if(wiperModePotentiometerReading >= MODE_INT && wiperModePotentiometerReading < MODE_HI){
        wiperMode = 2;
    }

    else if(wiperModePotentiometerReading >= MODE_HI){
        wiperMode = 3;
    }
}

void updateIntSetting(){
    wiperIntSettingPotentiometerReading = intSettingPotentiometer.read();
    if(wiperIntSettingPotentiometerReading < INT_DELAY_3){
        wiperDelay = 0;
    }

    else if(wiperIntSettingPotentiometerReading >= INT_DELAY_3 && wiperIntSettingPotentiometerReading < INT_DELAY_5){
        wiperDelay = 1;
    }

    else if (wiperIntSettingPotentiometerReading >= INT_DELAY_5 && wiperIntSettingPotentiometerReading < 1) {
        wiperDelay = 2;
    }
}

static void cycleWipers(){ //FSM that implements cycling the wipers 

   switch(windshieldWiperState){
        case REST :
            switch(wiperMode){
                case 0 :

                break; 

                case 1 : case 2 : case 3 :
                
                windshieldWiperState = WIPE; 
                break;
           }
        break;

        case WIPE :
            switch(wiperMode){
                case 1 : 
                
                windshieldWiperState = REST; 
                break;  
                
                case 2 :

                windshieldWiperState = INT_DELAY; 
                break;

                case 3 :
                    
                    wiperServo.write(DUTY_MIN);
                    delay(350);
                    wiperServo.write(DUTY_MAX);
                    delay(350);
                    windshieldWiperState = REST;
                break;
            }
        break;
    
        case INT_DELAY : //implements the wait time in the inctermittent mode
            switch(wiperDelay){
                case 0 :  
                if (accumulatedIntTimeAlarm >= DELAY_3_MS){
                    wipe();
                    accumulatedIntTimeAlarm = 0;
                }
                else{
                    accumulatedIntTimeAlarm = accumulatedIntTimeAlarm + SYSTEM_TIME_INCREMENT_MS;
                }
                break;
                
                case 1 : 
                if (accumulatedIntTimeAlarm >= DELAY_5_MS){
                    wipe();
                    accumulatedIntTimeAlarm = 0;
                }
                else{
                    accumulatedIntTimeAlarm = accumulatedIntTimeAlarm + SYSTEM_TIME_INCREMENT_MS;
                }
                break;
                
                case 2 :  
                if (accumulatedIntTimeAlarm >= DELAY_8_MS){
                    wipe();
                    accumulatedIntTimeAlarm = 0;
                }
                else{
                    accumulatedIntTimeAlarm = accumulatedIntTimeAlarm + SYSTEM_TIME_INCREMENT_MS;
                }
                break;
            }
            windshieldWiperState = REST;
        break;
    }
}


static void wipe(){
    float temp;

    //Upper bounds are defined as greater than or equal to in each for loop to account 
    //unintended behavior where stepper motor does not return fully to level setting during this wipe cycle.
    for(int i = 0; i <= INCREMENT; i++){
        temp = DUTY_MAX - i*cycleLength;
        servoUpdate(temp);
        delay(delayTime);
    }

    for(int i = 0; i <= INCREMENT; i++){
        temp = DUTY_MIN + i*cycleLength;
        servoUpdate(temp);
        delay(delayTime);
    }
}