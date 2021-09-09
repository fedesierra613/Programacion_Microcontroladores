
#if !defined(TIEMPO_H)
#define TIEMPO_H
#ifdef __cplusplus
extern "C" {
#endif
//#include <stddef.h>
typedef struct Tm_Periodico Tm_Periodico;
#define TM_PER_B_ACTIVO		0x01U// nos dice si el timer está prendido
#define TM_PER_B_TC			0x02U// esta bandera nos dice si el timer se desbordó que llegó la conteo
#define TM_Out_B_TC			0x04U
struct Tm_Periodico
{
	unsigned int contador;
    unsigned int periodo; 
	unsigned long	timeout;//acá va un timeout
	unsigned char banderas; //el primer bit me dice si está activo este timer el segundo me dice si se da periodo
};

//funciones para  procesar tiempo
void Tm_Procese_tiempo (Tm_Periodico *ctp);


//funciones de tiempos periodicos para timers
void Tm_Inicie_periodico (Tm_Periodico *ctp,unsigned int periodo);
char Tm_Hubo_periodico (Tm_Periodico *ctp);
void Tm_Baje_periodico (Tm_Periodico *ctp);
void Tm_Termine_periodico (Tm_Periodico *ctp);

//funciones de timeout
void Tm_Inicie_timeout (Tm_Periodico *ctp,unsigned int tiempo);
char Tm_Hubo_timeout (Tm_Periodico *ctp);
void Tm_Baje_timeout (Tm_Periodico *ctp);
#ifdef __cplusplus
} // extern "C"
#endif
#endif
