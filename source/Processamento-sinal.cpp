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
    Control::DAC::Init();
    Control::ADC Sinal(11); //Sinal Analógico

    arm_rfft_instance_q15 Instancia_RealFFT;

    //Inicialização da FFT
    arm_rfft_init_q15(&Instancia_RealFFT,
                      128,
                      0,
                      1);

    uint32_t i;
    uint16_t sinal_tempo, sinal_frequencia, mag_frequencia;
    
    while(1) { //Loop infinito
      sinal_tempo = Sinal.getConversion(); //Sinal digital
      
      arm_rfft_q15(&Instancia_RealFFT,
                  (q15_t *)sinal_tempo,
                  (q15_t *)sinal_frequencia);
      
      for(i=0,i<256,i++) {
        sinal_frequencia[i]<<=6;
      }

      arm_cmplx_mag_q15((q15_t *)sinal_frequencia,
                        (q15_t *)mag_frequencia;
                        128);

  }

}



