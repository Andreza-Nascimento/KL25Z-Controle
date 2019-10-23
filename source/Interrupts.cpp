/*
 * Interrupts.cpp
 *
 *  Created on: 13 de set de 2019
 *      Author: marcus
 */

#include "inc/Interrupts.h"

#if defined (__cplusplus)
extern "C" {
#endif

void PIT_DriverIRQHandler(){

	if(PIT_GetStatusFlags(PIT, kPIT_Chnl_0)){
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	Control::runControl();
	}

}




#if defined (__cplusplus)
} // extern "C"
#endif

