//=====[#include guards - begin]===============================================

#ifndef _WINDSHIELD_WIPERS_H_
#define _WINDSHIELD_WIPERS_H_

//=====[Declaration of public defines]=========================================

#define DUTY_MIN 0.025
#define DUTY_MAX 0.115
#define PERIOD 0.02

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void windshieldWipersInit();
void windshieldWipersUpdate();

//=====[#include guards - end]=================================================

#endif // _WINDSHIELD_WIPERS_H_