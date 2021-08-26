#if !defined(DEFINICIONES_H)
#define DEFINICIONES_H
#ifdef __cplusplus
extern "C" {
#endif

#define SI 1
#define NO 0
#define UNSEGUNDO 250
#define DISPLAYENCENDIDO 9
#define DISPLAYAPAGADO 1
#define CONTEOSTIMERS1 1000

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define SET_BIT(p,n) ((p) |= (1 << (n)))
#define CLR_BIT(p,n) ((p) &= ~((1) << (n)))

#define T_On 4
#define T_Off 1
#define Valor_Inicial0 4
#define Valor_Inicial1 5
#define Valor_Inicial2 6
#define Zero 0
//#define uint16_t ADC_Value 

#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6

#ifdef __cplusplus
} // extern "C"
#endif
#endif