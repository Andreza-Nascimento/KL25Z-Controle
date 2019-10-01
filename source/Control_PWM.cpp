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

	tpm_chnl_pwm_signal_param_t Param;

	Param.chnlNumber = (tpm_chnl_t)Chnl;
	Param.level = kTPM_HighTrue;
	Param.dutyCyclePercent =0;

	ParamList[N_Channels] = Param;

	N_Channels++;


    if(N_Channels==1){
    TPM_GetDefaultConfig(&Config);
	TPM_Init(TPM0, &Config);
	TPM_StartTimer(TPM0, kTPM_SystemClock);
    }

    //Atualiza sempre que adcionarmos um canal;
    TPM_SetupPwm(TPM0, ParamList, N_Channels, kTPM_CenterAlignedPwm, Control::PWM::Frequency, CLOCK_GetPllFllSelClkFreq());




}

void Control::PWM::setDuty(uint32_t duty){
	//TPM_UpdatePwmDutycycle(TPM0, Param.chnlNumber, kTPM_CenterAlignedPwm, duty);
}

void Control::PWM::setFrequency(uint32_t Frequency){

	//Fazer testes de divisão pra ver se encaixa no modulador
	TPM_SetupPwm(TPM0, ParamList, N_Channels, kTPM_CenterAlignedPwm, Frequency, CLOCK_GetPllFllSelClkFreq());
	Control::PWM::Frequency = Frequency;

}


Control::PWM::~PWM() {
	// TODO Auto-generated destructor stub
}

tpm_config_t Control::PWM::Config;
uint8_t Control::PWM::N_Channels = 0;
tpm_chnl_pwm_signal_param_t Control::PWM::ParamList[8];
uint32_t Control::PWM::Frequency = 20000; //Padrao

