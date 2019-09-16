/*
 * ControlPWM.h
 *
 *  Created on: 16 de set de 2019
 *      Author: marcus
 */

#ifndef CONTROL_PWM_H_
#define CONTROL_PWM_H_

#include "Control.h"
#include "fsl_tpm.h"
#include "pin_mux.h"

class Control::PWM {
public:
	PWM(uint32_t Chnl, uint32_t Frequency);
	virtual ~PWM();
	void setDuty(uint32_t duty);

	//implementar depois high precision mode (duty ~ contagens)

	static void setConfig(tpm_config_t Config);



private:
	tpm_chnl_pwm_signal_param_t Param;
	static tpm_config_t Config;

};

#endif /* CONTROL_PWM_H_ */
