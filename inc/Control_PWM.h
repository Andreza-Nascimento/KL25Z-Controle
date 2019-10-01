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

#include <vector>

class Control::PWM {
public:
	PWM(uint32_t Chnl);
	virtual ~PWM();

	void setDuty(uint32_t duty);

	//implementar depois high precision mode (duty ~ contagens)

	static void setConfig(tpm_config_t Config);
	static void setFrequency(uint32_t Frequency);



private:
	static uint32_t Frequency;
	static std::vector<tpm_chnl_pwm_signal_param_t> ParamList;
	static tpm_config_t Config;
	static uint8_t N_Channels;

};

#endif /* CONTROL_PWM_H_ */
