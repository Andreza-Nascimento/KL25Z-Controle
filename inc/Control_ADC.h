/*
 * ADC.h
 *
 *  Created on: 16 de set de 2019
 *      Author: marcus
 */

#ifndef CONTROL_ADC_H_
#define CONTROL_ADC_H_

#include "Control.h"
#include "fsl_adc16.h"

class Control::ADC {
public:

	/*Construtor. Entrar apenas com o número do Canal do PINO.
	 * Verificar se o pino foi inicializado pelo "MCUXpresso configuration tool". A correspondência
	 * PINO-ADC está explicita na label. Exemplo
	 * ADC0_SE15/.../PTC1 ~ Pino PTC1 corresponde ao canal "0" do ADC!
	*/


	ADC(uint32_t ChannelNumber);

	/* Leitura do canal ADC */

	uint32_t getConversion();


	~ADC();

	/* Aqui entramos com uma configuração customizada */
	static void setConfig(adc16_config_t config);




private:
	adc16_channel_config_t ChannelConfig;
	static adc16_config_t Config;
	static bool isInit;

};

#endif /* CONTROL_ADC_H_ */
