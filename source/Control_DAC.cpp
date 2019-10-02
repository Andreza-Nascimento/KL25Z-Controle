/*
 * ControlDAC.cpp
 *
 *  Created on: 16 de set de 2019
 *      Author: marcus
 */

#include <Control_DAC.h>

Control::DAC::DAC() {
	// TODO Auto-generated constructor stub

	//ADC (TORNAR CONFIGURAVEL PRO USUARIO? )

}

void Control::DAC::Init(){
	DAC_CONFIG.enableLowPowerMode = false;
	DAC_CONFIG.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2; //Ver qua eh
	DAC_Init(DAC0, &DAC_CONFIG);
	DAC_Enable(DAC0, true);
    DAC_SetBufferReadPointer(DAC0, 0U);
}



Control::DAC::~DAC() {
	// TODO Auto-generated destructor stub
}

//valor 12-bits (entre 0 e 4096)
void Control::DAC::SetValue(uint16_t dacValue){
	DAC_SetBufferValue(DAC0, 0U, dacValue);

}

//Valor entre 0 e 3.3V
void Control::DAC::SetVoltage(float volts){
	uint16_t dacValue = (volts*4096.0f)/3.31f;
	DAC_SetBufferValue(DAC0, 0U, dacValue);

}

dac_config_t Control::DAC::DAC_CONFIG;
