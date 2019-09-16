/*
 * ADC.cpp
 *
 *  Created on: 16 de set de 2019
 *      Author: marcus
 */

#include "Control_ADC.h"

Control::ADC::ADC(uint32_t ChannelNumber) {
	// TODO Auto-generated constructor stub
	ChannelConfig.channelNumber = ChannelNumber;
	ChannelConfig.enableInterruptOnConversionCompleted = false;
	ChannelConfig.enableDifferentialConversion = false;

	//ADC16_Deinit(ADC0); //Necessário ?

	//ADC (TORNAR CONFIGURAVEL PRO USUARIO? )
	Config.resolution = kADC16_Resolution16Bit; //16 bits
	Config.clockDivider = kADC16_ClockDivider1;
	Config.clockSource = kADC16_ClockSourceAlt0; //BUS CLOCK (24MHZ Default)
	Config.enableContinuousConversion = true;
	Config.enableHighSpeed = false;
	Config.longSampleMode = kADC16_LongSampleDisabled;
	ADC16_Init(ADC0, &Config);
	ADC16_DoAutoCalibration(ADC0); //Útil ?
}

// ADC METHODS

uint32_t Control::ADC::getConversion(){
	//while(ADC16_SetChannelConfig(ADC0, kADC16_ChannelMuxA, ChannelConfig))
	ADC16_SetChannelConfig(ADC0, kADC16_ChannelMuxA, &ChannelConfig);
    while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, kADC16_ChannelMuxA)))
    {}

	return ADC16_GetChannelConversionValue(ADC0, kADC16_ChannelMuxA);
}

Control::ADC::~ADC() {
	// TODO Auto-generated destructor stub

}



void Control::ADC::setConfig(adc16_config_t config){
	Config = config;
	ADC16_Deinit(ADC0);
	ADC16_Init(ADC0, &Config);
}


adc16_config_t Control::ADC::Config;
bool Control::ADC::isInit = false;
