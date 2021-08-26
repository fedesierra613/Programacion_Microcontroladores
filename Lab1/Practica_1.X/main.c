/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1827
        Driver Version    :  2.00
 */

#include "mcc_generated_files/mcc.h"
#include <math.h> //estan en el PATH de compilacion osea la ruta donde busca el copilador por defecto
#include "displays.h"
#include "definiciones.h" 
#include "nuestrostimers.h"




uint16_t valor_ADC = 0;
adc_channel_t AN1_Channel;
uint16_t volt_ADC = 0;
uint8_t Pack[6];


void main(void){
  
	SYSTEM_Initialize();
	Ds_Display seven_seg;
	Tm_Periodico timer_1ms;
    Tm_Periodico timer_1000ms;
	Tm_Inicie_periodico (&timer_1ms, 1000);
	ADC_SelectChannel (AN1_Channel);
	Tm_Periodico My_ADC_1000ms;
	Tm_Inicie_periodico (&timer_1000ms, 1000);
	ADC_Initialize();
	Ds_Iniciar_displays (&seven_seg, Valor_Inicial0, Valor_Inicial1, Valor_Inicial2, T_On, T_Off);
    TMR6_StartTimer();

    

	while (1){
        
		if(TMR6_HasOverflowOccured()){
			Tm_Procese_tiempo(&timer_1ms);
            Ds_Procese_displays(&seven_seg);
		}
        
    if(Tm_Hubo_periodico(&timer_1ms)){						
		Tm_Baje_periodico(&timer_1ms); //bajo bandera
        ADC_StartConversion();
                
        if(EUSART_is_tx_ready()){
            Pack[0]=(seven_seg.D3 + '0');
            Pack[1]=(',');   
            Pack[2]=(seven_seg.D2 + '0');
            Pack[3]=(seven_seg.D1 + '0');
            Pack[5]=0x0D;
            Pack[4]= '\n';
            EUSART_Write(Pack[0]);
            EUSART_Write(Pack[1]);
            EUSART_Write(Pack[2]);
            EUSART_Write(Pack[3]); 
            EUSART_Write(Pack[4]);
            EUSART_Write(Pack[5]);
        }      
    }

		if(ADC_IsConversionDone()){
            valor_ADC = ADC_GetConversionResult();
			volt_ADC = Ds_Conversor_ADC(valor_ADC);
			Ds_Convertir_en_uni_deci_centi(&seven_seg, volt_ADC);
		}
	}
}