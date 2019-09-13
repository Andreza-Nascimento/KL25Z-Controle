/*
 * Control.h
 *
 *  Created on: 13 de set de 2019
 *      Author: marcus
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "fsl_debug_console.h"
#include "fsl_pit.h"
#include "fsl_adc16.h"

// Implementar :
// Setar Amostragem
// Setar ADC
// Setar DAC
// Setar PWM
// Falar com Matlab
// HIL ?


#define CONTROLE_PRINT PRINTF
#define PIT_CANAL_0 kPIT_Chnl_0
#define PIT_CANAL_1 kPIT_Chnl_1
#define PIT_CANAL_2 kPIT_Chnl_2
#define PIT_CANAL_3 kPIT_Chnl_3


typedef void (*FunPt)();

class Control {
public:

	class ADC {
	public:
		ADC(uint32_t ChannelNumber){
			ChannelConfig.channelNumber = ChannelNumber;
			ChannelConfig.enableInterruptOnConversionCompleted = false;
			ChannelConfig.enableDifferentialConversion = false;
		};


		uint32_t getConversion();
		~ADC(){};

	private:
		adc16_channel_config_t ChannelConfig;

	};

	static void setSamplingFrequency(float Hz);
	static void setSamplingTime(float Ts);
	static void start();
	static void stop();
	static void runControl();
	static bool getControlStatus();
	static void setControlLawHandle(FunPt callback);

	//Blocking!
	static void delay(uint32_t usec);



private:
	Control();
	virtual ~Control();
	static bool isRunning;
	static FunPt ControlHandle;


};


#endif /* CONTROL_H_ */
