
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> 

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#define Num 50
#define TAM_add 4 
#define TAM_val 2 
#define TAM_num 2 
#define TAM_num16 16 
#define Num_Bytes 18

#define EEPROM 0x50//EEPROM_DEVICE_ADDRESS
    
enum casos_Maq{
    Caso_NUM,
    Caso_W_BS,
    Caso_R_BS,
    Caso_W_B,
    Caso_W_S,
    Caso_R_B,
    Caso_R_S,
    Caso_coma,
    Caso_val,
    Caso_num,
    Caso_num16,
    Caso_saltodelinea,
    Caso_saltodelinea2
};


typedef struct Vect_RE Vect_RE;
struct Vect_RE
{
    uint8_t Dato;
    enum casos_Maq caso;
    char Comando;
    char i;
    char dir_add[TAM_add];
    char val[TAM_val];
    char num[TAM_num];
    char num16[TAM_num16];
    char RESET;
    char iniciar;
};
    
void Maquina_RE(Vect_RE *dsp);

void Funcion_RB(Vect_RE *dsp);

void Funcion_WB(Vect_RE *dsp);

void Funcion_RS(Vect_RE *dsp);

void Funcion_WS(Vect_RE *dsp);

//char ConfigPostcaler(float);

//char ConfigCont(float, char);
    
    
    
    
    
    
    
    
    
    
    
    

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */
