/*
 * ControlDAC.h
 *
 *  Created on: 16 de set de 2019
 *      Author: marcus
 */

#ifndef CONTROL_DAC_H_
#define CONTROL_DAC_H_

#include "Control.h"
#include "fsl_dac.h"

class Control::DAC {



public:
	static void SetValue(uint16_t dacValue);
	static void SetVoltage(float volts);
	static void Init();

private:
	DAC();
	virtual ~DAC();
	static dac_config_t DAC_CONFIG;


};

#endif /* CONTROL_DAC_H_ */
