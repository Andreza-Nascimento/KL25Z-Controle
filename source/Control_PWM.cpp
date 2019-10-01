/*
 * ControlPWM.cpp
 *
 *  Created on: 16 de set de 2019
 *      Author: marcus
 */

#include <Control_PWM.h>


// A frequencia deverá estar dentro de uma faixa de tolerância pro divisor de frequencia

Control::PWM::PWM(uint32_t Chnl) {
	// TODO Auto-generated constructor stub
	//TPM_Init(base, config)


	//Config.enableDebugMode = true;
	//Config.prescale = kTPM_Prescale_Divide_32;
	N_Channels++;
	//ParamList = realloc(ParamList,N_Channels*sizeof(tpm_chnl_pwm_signal_param_t))

	ParamList[N_Channels-1].chnlNumber = (tpm_chnl_t)Chnl;
	ParamList[N_Channels-1].level = kTPM_HighTrue;
	ParamList[N_Channels-1].dutyCyclePercent =0;


    if(N_Channels==1){
    TPM_GetDefaultConfig(&Config);
	TPM_Init(TPM0, &Config);
	TPM_StartTimer(TPM0, kTPM_SystemClock);
    }
    TPM_SetupPwm(TPM0, &ParamList[0], 1, kTPM_CenterAlignedPwm, Control::PWM::Frequency , CLOCK_GetPllFllSelClkFreq());



}

void Control::PWM::setDuty(uint32_t duty){
	//TPM_UpdatePwmDutycycle(TPM0, Param.chnlNumber, kTPM_CenterAlignedPwm, duty);
}

void Control::PWM::setFrequency(uint32_t Frequency){
	Control::PWM::Frequency = Frequency;
	TPM_SetupPwm(TPM0, &ParamList[0], N_Channels, kTPM_CenterAlignedPwm, Frequency, CLOCK_GetPllFllSelClkFreq())

}


Control::PWM::~PWM() {
	// TODO Auto-generated destructor stub
}

tpm_config_t Control::PWM::Config;
uint8_t Control::PWM::N_Channels = 0;
uint32_t Control::PWM::Frequency = 20000; //Padrão
std::vector<tpm_chnl_pwm_signal_param_t> Control::PWM::ParamList;

