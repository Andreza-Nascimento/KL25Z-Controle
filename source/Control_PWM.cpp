/*
 * ControlPWM.cpp
 *
 *  Created on: 16 de set de 2019
 *      Author: marcus
 */

#include <Control_PWM.h>


// A frequencia deverá estar dentro de uma faixa de tolerância pro divisor de frequencia

Control::PWM::PWM(uint32_t Chnl, uint32_t Frequency) {
	// TODO Auto-generated constructor stub
	//TPM_Init(base, config)

	TPM_GetDefaultConfig(&Config);
	//Config.enableDebugMode = true;
	//Config.prescale = kTPM_Prescale_Divide_32;

    Param.chnlNumber = (tpm_chnl_t)Chnl;
    Param.level = kTPM_HighTrue;
    Param.dutyCyclePercent =0;

	TPM_Init(TPM0, &Config);

	TPM_SetupPwm(TPM0, &Param, 1U, kTPM_CenterAlignedPwm, Frequency, CLOCK_GetFreq(kCLOCK_PllFllSelClk));

	TPM_StartTimer(TPM0, kTPM_SystemClock);

}

void Control::PWM::setDuty(uint32_t duty){
	TPM_UpdatePwmDutycycle(TPM0, Param.chnlNumber, kTPM_CenterAlignedPwm, duty);
}


Control::PWM::~PWM() {
	// TODO Auto-generated destructor stub
}

tpm_config_t Control::PWM::Config;


