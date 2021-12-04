/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    KL25Z-Controle.cpp
 * @brief   Application entry point.
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "arm_math.h" //Operações DSP
#include "Control.h" //API principal para aplicações Controle
#include "Interrupts.h"
#include <Control_ADC.h>
#include "Control_DAC.h"
#include "Control_PWM.h"
#include "Matrix.h"
#include <vector>
/* TODO: insert other definitions and declarations here. */

//DEBUG PIN -> PTC9
#define DEBUG_PIN_TOGGLE() \
    GPIO_TogglePinsOutput(BOARD_INITPINS_DEBUG_PIN_GPIO, 1U << BOARD_INITPINS_DEBUG_PIN_PIN)

/*
 * @brief   Application entry point.
 */




void CtrlLaw();

int main(void) {


  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    //Control::delay(1000000);


    Control::setSamplingFrequency(100); //Seta frequência da execução a 100 Hz
    Control::setControlLawHandle(CtrlLaw); //Função a ser executada na frequência determinada
    Control::start(); //Inicia

    //Teste da API pro DAC
    Control::DAC::Init();

    //Teste da API pro ADC
    Control::ADC PTC1(15); //Canal 15 do ADC Ativado
    Control::ADC PTC2(11); //Canal 11 do ADC Ativado


    //Teste da API do PWM
    Control::PWM::setFrequency(10000); //Seta Frequencia
    Control::PWM PWM0(1);

    PWM0.setDuty(50);

    //Teste de operação Matricial
    float A[] = {1,2,3,4};
    Matrix MA(2,2,A);
    Matrix MB(2,2);
    MB.Inverse(MA, MB); // Inverte MA e coloca resultado em MB
    MB.Print(); //Printa na USB o resultado


    uint32_t adcval1,adcval2;


    while(1) { //Loop infinito

    	LED_RED_TOGGLE(); //Pisca LED Vermelho
    	LED_BLUE_TOGGLE(); //Pisca LED Azul
    	LED_GREEN_TOGGLE(); //Pisca LED Verde

    	Control::delay(1000000); //Delay
    	adcval1 = PTC1.getConversion(); //lê ADC
    	adcval2 = PTC2.getConversion(); // lê ADC
    	CONTROLE_PRINT("PTC1 : %d PTC2 : %d \r\n",adcval1,adcval2); // Printa valores ADC

}

}


int k = 0;
bool Up = true;
bool init = false;

//Definição da Lei de controle
void CtrlLaw(){

//Static para ser construído apenas uma vez
static Control::PWM PWM0(0); //Define PWM canal 0

	LED_BLUE_TOGGLE(); //PISCA LED AZUL
	DEBUG_PIN_TOGGLE(); //PISCA DEBUG PIN
	if(Up){
		k++;
		//PWM1.setDuty(10);
		if(k==101)
			Up = false;

	} else { //Down
		k--;
		if(k==-1)
			Up = true;

	}

	PWM0.setDuty(k); // Seta Duty Cycle
	if(k>0)
	Control::DAC::SetValue(k*40); //seta o ADC

}




