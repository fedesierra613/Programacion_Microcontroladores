
#include "mcc_generated_files/mcc.h"
#include "Config_Usart.h"
#include "mcc_generated_files/eusart1.h"

#include "funciones.h"

#define TAM_VEC 4
#define TAM_VEC_DAC 2

#define N 3

volatile uint16_t Result_ADC = 0;
volatile char ADC_flag = 0;
volatile char Serial_Rx_flag = 0;
volatile uint8_t Lectura_Rx = 0;
volatile char ADC_Tx_Vect[TAM_VEC];

void Interrupcion_Rx_Serial(void){
    EUSART1_Receive_ISR();
    Lectura_Rx = EUSART1_Read();
    Serial_Rx_flag = 1;
}

void Interrupcion_ADC(void){
    Result_ADC = ((adc_result_t)((ADRESH << 8) + ADRESL));
    ADC_flag = 1;
}



/*
                         Main application
 */
void main(void)
{
    SYSTEM_Initialize();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    float SalidaIIR;
    
    long SalidaFIR_long;
    
    char Dato = 0;
    char Intx = 0;
    char Iniciar;
    uint16_t a;
    char Inicont = 0;
    char Postcaler;
    char AuxPost = 0;
    char Auxcont = 0;
    char Listo_enviar = 0;
    char Contador;
    float DatoRe;
    int AuxReADC;
    uint16_t DAC_IN = 0b0011000000000000;
    uint16_t Resta = 0b0000111111111111;
    uint16_t Resta_IRR = 0b1111000000000000;
    uint16_t Palabra_DAC;
    uint16_t SALIDA;
    uint8_t Vector_DAC[TAM_VEC_DAC];
    Vector_DAC[0] = 0;
    Vector_DAC[1] = 0;
    
    char ADC_Vect[TAM_VEC];
    
    ADC_Tx_Vect[0] = 0;
    ADC_Tx_Vect[1] = 0;
    ADC_Tx_Vect[2] = 0;
    ADC_Tx_Vect[3] = 0;
    
    uint8_t V_P[TAM_VEC_DAC];
    V_P[0] = 0b00110000;
    V_P[1] = 0b01010110;
    
    char PrueVect[8];
    uint8_t Lect;
    
    uint16_t AuxADC;
    
    IO_RB0_SetHigh();
    
    IO_RE0_SetHigh();
    IO_RB4_SetHigh();
        
    Vect_RE MiVector;
    coef_iir_2_ord ir;
    
    ADCC_SetADIInterruptHandler(Interrupcion_ADC);
        
    EUSART1_SetRxInterruptHandler(Interrupcion_Rx_Serial);//Interrupcion_Rx_Serial
          
    SPI1_Open(SPI1_DEFAULT);
    __delay_us(50000);
    
    
    /*; // pon
    //el filtro que se pone acá es un Butter con Fs en 100 y corte en 5Hz @ 3dB
    float num[N] = {0.02008336596190929412841796875,0.0401667319238185882568359375,0.02008336596190929412841796875}; // ponga aquí su numerador, por defecto para ejemplo un oscilador sería: {1.0, -2.0, 1.0}
    float den[N] = {1,-1.56101810932159423828125,0.641351521015167236328125}; // ponga aquí su denominador, por defecto para ejemplo                       {1,   0, -1}
    float w[N] = {0, 0, 0};// condición inicial punto intermedio,  por defecto para ejemplo                   {0, 0, 0}
    float gan[N] = {0, 0, 0};
    inicializar_iir_2_ord(num, den, w, &ir);
    */
    
    
    float num[N] = {1, 2, 1}; // ponga aquí su numerador, por defecto para ejemplo un oscilador sería: {1.0, -2.0, 1.0}
    float den[N] = {1, -0.4531195164, 0.4663255811}; // ponga aquí su denominador, por defecto para ejemplo                       {1,   0, -1}
    float w[N] = {0, 0, 0};// condición inicial punto intermedio,  por defecto para ejemplo                   {0, 0, 0}
    float num2[N] = {1, 2, 1}; // ponga aquí su numerador, por defecto para ejemplo un oscilador sería: {1.0, -2.0, 1.0}
    float den2[N] = {1, -0.3289756775, 0.06458765268}; // ponga aquí su denominador, por defecto para ejemplo                       {1,   0, -1}
    float w2[N] = {0, 0, 0};// condición inicial punto intermedio,  por defecto para ejemplo                   {0, 0, 0}
    float gan[N] = {0.2533015013, 0.1839029938, 0};
    inicializar_iir_2_ord(num, den, w, num2, den2, w2, gan, &ir);
    
    
    T2CON = 0xF1;
    T2PR = 0xC2;
    
    while (1)
    {
        if(Serial_Rx_flag){
            Serial_Rx_flag = 0;
            MiVector.Lectura = Lectura_Rx;
            Iniciar = Re_Vector(&MiVector);
        }
        
        if(Iniciar){
            Iniciar = 0;
            DatoRe = 0;
            a = 1;
            for(char i=MiVector.Pos-2;i>0;i--){
                DatoRe = DatoRe + ((uint16_t) MiVector.Dato[i]) * a;
                a=a*10;
            }
            AuxPost = 1;
        }
        
        if(AuxPost){//Ajustar Postcaler
            Postcaler = ConfigPostcaler(DatoRe);
            T2CON = Postcaler;
            AuxPost = 0;
            Auxcont = 1;
        }
        
        if(Auxcont){//Ajustar contador
            Contador = ConfigCont(DatoRe, Postcaler);
            T2PR = Contador;
            Auxcont = 0;
       }
        
        if(ADC_flag){
            ADC_flag = 0;
            IO_RB0_Toggle();
            
            SalidaFIR_long = filtrarFIR1(Result_ADC);
            
            //SalidaFIR_long = filtrarFIR2(Result_ADC);
            
            //SalidaFIR_long = filtrarFIR3(Result_ADC);
            
            //SalidaFIR_long = filtrarFIR3_Optimizado(Result_ADC);
            //SalidaFIR_long = SalidaFIR_long + 200;
            
            //SalidaIIR = filtrarIIR(Result_ADC, &ir);
            //SalidaIIR = filtrarIIRFormula2_a(Result_ADC, &ir);
            //SalidaIIR = filtrarIIRFormula2_b(SalidaIIR, &ir);
            
            SALIDA = (Resta & (int16_t)SalidaFIR_long);
            
            Palabra_DAC = (DAC_IN) + ((uint16_t)SALIDA);//Result_ADC
            Vector_DAC[1] = Palabra_DAC;
            Vector_DAC[0] = Palabra_DAC >> 8;
            IO_RE0_SetLow();
            SPI1_WriteBlock(&Vector_DAC, 2);
            __delay_us(50);
            IO_RE0_SetHigh();
            __delay_us(1);
            IO_RB4_SetLow();
            __delay_us(1);
            IO_RB4_SetHigh();
            
            AuxReADC = Result_ADC;
            ADC_Vect[3] = AuxReADC%10;
            AuxReADC = AuxReADC/10;
            ADC_Vect[2] = AuxReADC%10;
            AuxReADC = AuxReADC/10;
            ADC_Vect[1] = AuxReADC%10;
            AuxReADC = AuxReADC/10;
            ADC_Vect[0] = AuxReADC%10;
            
            AuxReADC = SalidaFIR_long;
            ADC_Tx_Vect[3] = AuxReADC%10;
            AuxReADC = AuxReADC/10;
            ADC_Tx_Vect[2] = AuxReADC%10;
            AuxReADC = AuxReADC/10;
            ADC_Tx_Vect[1] = AuxReADC%10;
            AuxReADC = AuxReADC/10;
            ADC_Tx_Vect[0] = AuxReADC%10;
            EUSART1_Write('-');
            EUSART1_Write(ADC_Vect[0] + '0');
            EUSART1_Write(ADC_Vect[1] + '0');
            EUSART1_Write(ADC_Vect[2] + '0');
            EUSART1_Write(ADC_Vect[3] + '0');
            EUSART1_Write(',');
            EUSART1_Write(ADC_Tx_Vect[0] + '0');
            EUSART1_Write(ADC_Tx_Vect[1] + '0');
            EUSART1_Write(ADC_Tx_Vect[2] + '0');
            EUSART1_Write(ADC_Tx_Vect[3] + '0');
            EUSART1_Write(0x0D);
        }
    }
}
/**
 End of File
*/