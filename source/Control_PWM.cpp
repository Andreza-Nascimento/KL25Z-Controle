/*
 * ControlPWM.cpp
 *
 *  Created on: 16 de set de 2019
 *      Author: marcus
 */

#include <Control_PWM.h>



// Parâmetro -> Canal PWM do TPM0 (Não é o pino!)
Control::PWM::PWM(uint32_t Chnl) {
	// TODO Auto-generated constructor stub

	tpm_chnl_pwm_signal_param_t Param;

	Param.chnlNumber = (tpm_chnl_t)Chnl;
	Param.level = kTPM_HighTrue;
	Param.dutyCyclePercent = 0;

	ParamList[N_Channels] = Param;

	Chn = N_Channels; //Esse Chn é do software, não hardware!

	N_Channels++;


    if(N_Channels==1){
    TPM_GetDefaultConfig(&Config);
    Config.enableDebugMode = true;
	TPM_Init(TPM0, &Config);
	TPM_StartTimer(TPM0, kTPM_SystemClock);
    }

    //Atualiza sempre que adcionarmos um canal;
    TPM_SetupPwm(TPM0, ParamList, N_Channels, kTPM_EdgeAlignedPwm, Control::PWM::Frequency, CLOCK_GetPllFllSelClkFreq());

}

//Algumas vezes não funciona. Revisar.
void Control::PWM::setDuty(uint32_t duty){
	ParamList[Chn].dutyCyclePercent = duty;
//	TPM_UpdateChnlEdgeLevelSelect(TPM0, ParamList[Chn].chnlNumber, 0U);
	TPM_UpdatePwmDutycycle(TPM0, ParamList[Chn].chnlNumber, kTPM_EdgeAlignedPwm, duty);
//	TPM_UpdateChnlEdgeLevelSelect(TPM0, ParamList[Chn].chnlNumber, kTPM_HighTrue);
}


// 1k ~ 100k OK!
void Control::PWM::setFrequency(uint32_t Frequency){

	//TODO : Fazer testes pra ver se encaixa na portadora.
	Control::PWM::Frequency = Frequency;

	if(N_Channels){
	TPM_StopTimer(TPM0);
	TPM_StartTimer(TPM0, kTPM_SystemClock);
	TPM_SetupPwm(TPM0, ParamList, N_Channels, kTPM_EdgeAlignedPwm, Control::PWM::Frequency, CLOCK_GetPllFllSelClkFreq());
	}

}


Control::PWM::~PWM() {
	// TODO Auto-generated destructor stub
	N_Channels--;
	//TPM_SetupPwm(TPM0, ParamList, N_Channels, kTPM_EdgeAlignedPwm, Control::PWM::Frequency, CLOCK_GetPllFllSelClkFreq());
}

tpm_config_t Control::PWM::Config;
uint8_t Control::PWM::N_Channels = 0;
tpm_chnl_pwm_signal_param_t Control::PWM::ParamList[8];
uint32_t Control::PWM::Frequency = 1000; //Padrão

