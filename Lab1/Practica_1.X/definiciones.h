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



#ifdef __cplusplus
} // extern "C"
#endif
#endif