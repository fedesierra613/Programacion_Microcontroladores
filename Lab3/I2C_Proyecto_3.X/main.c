
#include "mcc_generated_files/mcc.h"
#include "Maquina_RX.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mcc_generated_files/examples/i2c_simple_example.h"

#define TMR0_H 0x50

volatile uint8_t Lectura_Rx = 0;
volatile char Serial_Rx_flag = 0;

void Interrupcion_Rx_Serial(void){
    EUSART1_Receive_ISR();
    Lectura_Rx = EUSART1_Read();
    Serial_Rx_flag = 1;
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    //Interrupcion_Rx_Serial
    EUSART1_SetRxInterruptHandler(Interrupcion_Rx_Serial);
    //Variables e inicializacion
    Vect_RE MiVector;    
    MiVector.caso = Caso_NUM;
    MiVector.iniciar = 0;
    MiVector.RESET = 0;
    IO_RD0_SetLow();
    while (1)
    {
        if(TMR0_HasOverflowOccured() && MiVector.RESET == 1){
            MiVector.RESET = 0;
            PIR0bits.TMR0IF = 0;
            MiVector.caso = Caso_NUM;
            TMR0_WriteTimer(0);
            TMR0_Reload(TMR0_H);
            IO_RD0_Toggle();
            printf("ERR_Timer\n\r");
        }
        if(Serial_Rx_flag){
            PIR0bits.TMR0IF = 0;
            TMR0_WriteTimer(0);
            TMR0_Reload(TMR0_H);
            Serial_Rx_flag = 0;
            MiVector.Dato = Lectura_Rx;
            Maquina_RE(&MiVector);
        }
        if((MiVector.Comando == 1) && (MiVector.iniciar == 1)){//Funcion RB
            MiVector.Comando = 0;
            MiVector.iniciar = 0;
            //printf("Estoy en comando RB \n\r");
            Funcion_RB(&MiVector);
        }
        if((MiVector.Comando == 2) && (MiVector.iniciar == 1)){//Funcion WB
            MiVector.Comando = 0;
            MiVector.iniciar = 0;
            //printf("Estoy en comando WB \n\r");
            Funcion_WB(&MiVector);
        }
        if((MiVector.Comando == 3) && (MiVector.iniciar == 1)){//Funcion RS
            MiVector.Comando = 0;
            MiVector.iniciar = 0;
            //printf("Estoy en comando RS \n\r");
            Funcion_RS(&MiVector);
        }
        if((MiVector.Comando == 4) && (MiVector.iniciar == 1)){//Funcion WS
            MiVector.Comando = 0;
            MiVector.iniciar = 0;
            Funcion_WS(&MiVector);
        }
    }
}
/**
 End of File
*/