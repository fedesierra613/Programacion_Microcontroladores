
#include "mcc_generated_files/mcc.h"
#include <math.h> //estan en el PATH de compilacion osea la ruta donde busca el copilador por defecto
#include "displays.h"
#include "definiciones.h" 
#include "nuestrostimers.h"

volatile uint16_t num_ADC=0;
volatile char ADC_flag = FALSE;
volatile char timer_flag = FALSE;

// funcion interrupciones para el ADC
void Interrupcion_ADC (void){
	num_ADC = ADC_GetConversionResult();
	ADC_flag = TRUE;
}

void Interrupcion_timer (void){
	timer_flag = TRUE;
}


void main(void){
    
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    uint16_t valor_ADC =0;
    uint16_t volt_ADC=0;
    uint8_t Pack[6];
    char send = FALSE;
	Ds_Display seven_seg;
	Tm_Periodico timer_1ms;
	Tm_Inicie_periodico (&timer_1ms, tiempo_cont);
	ADC_Initialize();
    ADCON0 = ADCON0 | 0b00011101;
    ADCON0 = ADCON0 & 0b10011111;
    ADCON1 = 0b11100000;
	Ds_Iniciar_displays (&seven_seg, N_1, N_2, N_3, T_On, T_Off);    
    TMR6_StartTimer();
	ADC_SetInterruptHandler(Interrupcion_ADC);
	TMR6_SetInterruptHandler(Interrupcion_timer);
	
    while (1){        
		if(timer_flag){
            timer_flag = FALSE;
            Tm_Procese_tiempo(&timer_1ms);
            Ds_Procese_displays(&seven_seg);
			} 
        
        if(Tm_Hubo_periodico(&timer_1ms)){						
				Tm_Baje_periodico(&timer_1ms); //bajo bandera
                ADC_StartConversion();                
                send = TRUE;
		}
        
        if(send && EUSART_is_tx_ready()){
        	send = FALSE;
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
        
        if(ADC_flag){//bandera activada en la interrupcion 
			ADC_flag = FALSE;
            //valor_ADC = ADC_GetConversionResult();//interrupcion 
			valor_ADC = num_ADC;
            volt_ADC = Ds_Conversor_ADC(valor_ADC);// esto se queda aqui 
            Ds_Convertir_en_uni(&seven_seg, volt_ADC);// esto se queda aqui 
        }
	};
}
