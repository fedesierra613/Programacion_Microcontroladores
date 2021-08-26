#if !defined(DISPLAYS_H)
#define DISPLAYS_H
#ifdef __cplusplus
extern "C" {
#endif

#define D1E 1
#define D1A 2
#define D2E 3
#define D2A 4
#define D3E 5
#define D3A 6

typedef struct Ds_Display Ds_Display;
struct Ds_Display
{
	char estados; //6 estados, dos por cada 7 segmentos
    
//Numero de cada 7 segmentos
    char D1;
    char D2;
    char D3;
//Tiempos de cada estado, encendido o apagado  
    char tiempoEncendido;
    char tiempoApagado;

    char tempE;
    char tempA;
};

// funcion para inicializar estructura de display
void Ds_Iniciar_displays(Ds_Display *dsp, char d1, char d2, char d3, char tE, char tA);

//funciones para  procesar display
void Ds_Procese_displays (Ds_Display *dsp);


/* 
    PRENDE LOS TRANSISTORES (PUERTOS RB0, RB3 Y RB4)

    La funcion Ds_Encienda_Disp
    enciende el display de acuerdo al numero que le ingrese

    si le entra [1-3] enciende el respectivo display
    si le entra otro numero apaga todos
*/
void Ds_Encienda_Disp(char dispNum);


/*
    PRENDE CADA SEGMENTO DE CADA 7 SEGEMENTOS (PUERTOS RA0, RA1, RA2, RA3, RA4, RA6, RA7)
    La funcion BCD
    convierte el decimal a BCD y lo traduce a la configuracion del hardware actual
*/
void Ds_BCD(char segmento);


/*
     La funcion Ds_Mostrar_en_display le entran los 3 digitos que quiero mostrar en el display

*/
void Ds_Mostrar_en_display(Ds_Display *dsp, char d1, char d2, char d3);


/*
     convertir en decimal unidades, aca se importa el numero del ADC, de 1 a 1024 
*/
void Ds_Convertir_en_uni_deci_centi(Ds_Display *dsp,uint16_t voltaje);

uint16_t Ds_Conversor_ADC (uint16_t ADC_OUT);



#ifdef __cplusplus
} // extern "C"
#endif
#endif

