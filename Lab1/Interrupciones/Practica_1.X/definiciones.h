#if !defined(DEFINICIONES_H)
#define DEFINICIONES_H
#ifdef __cplusplus
extern "C" {
#endif

#define PI 3.1415926535f
#define SI 1
#define NO 0
#define UNSEGUNDO 250
#define DISPLAYENCENDIDO 5
#define DISPLAYAPAGADO 1
#define TRUE 1
#define FALSE 0
    
#include <stdio.h>
#include <stdint.h>
    
//typedef unsigned int16_t uint16_t;

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define SET_BIT(p,n) ((p) |= (1 << (n)))
#define CLR_BIT(p,n) ((p) &= ~((1) << (n)))
#define T_On 4
#define T_Off 1
#define N_1 1
#define N_2 1
#define N_3 1
#define Zero 0

#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6

#define tiempo_cont 1000

      
//#define Valor_Vmax 999


#ifdef __cplusplus
} // extern "C"
#endif
#endif