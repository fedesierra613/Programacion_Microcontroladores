#include "displays.h"


void Ds_Iniciar_displays(Ds_Display *dsp, char d1, char d2, char d3, char tE, char tA){
    dsp->estados=D1E;
    dsp->D1=8;
    dsp->D2=8;
    dsp->D3=8;
    dsp->tiempoEncendido=tE;
    dsp->tiempoApagado=tA;
    dsp->tempE=tE;
    dsp->tempA=tA;
}
/*
void Ds_Encienda_Disp(char dispNum);

void Ds_BCD(char )
*/

void Ds_Procese_displays (Ds_Display *dsp){

    switch ( dsp->estados )
{
    // declarations
    // . . .
    case D1E:
        --(dsp->tempE);
        if(!(dsp->tempE)){
            dsp->estados =D1A;
            dsp->tempA=dsp->tiempoApagado;
        }
        /*funcion que haga el manejo de los LEDS
        apagar transistores 2 y 3
        y prender los transistores de acuerdo al numero
        */
        //acá va la función
        Ds_Encienda_Disp(1);
        Ds_BCD(dsp->D1);

        break;

    case D1A:
        --(dsp->tempA);
        if(!(dsp->tempA)){
            dsp->estados =D2E;
            dsp->tempE=dsp->tiempoEncendido;
        }
        /*funcion que haga el manejo de los LEDS
        apagar transistores 1 2 y 3
        */
        Ds_Encienda_Disp(0);
    break;

    case D2E:
        --(dsp->tempE);
        if(!(dsp->tempE)){
            dsp->estados =D2A;
            dsp->tempA=dsp->tiempoApagado;
        }
        /*funcion que haga el manejo de los LEDS
        apagar transistores 2 y 3
        y prender los transistores de acuerdo al numero
        */
        //acá va la función
        Ds_Encienda_Disp(2); 
        Ds_BCD(dsp->D2);
    break;

    case D2A:
        --(dsp->tempA);
        if(!(dsp->tempA)){
            dsp->estados =D3E;
            dsp->tempE=dsp->tiempoEncendido;
        }
        /*funcion que haga el manejo de los LEDS
        apagar transistores 1 2 y 3
        */
        Ds_Encienda_Disp(0);
    break;

    case D3E:
        --(dsp->tempE);
        if(!(dsp->tempE)){
            dsp->estados =D3A;
            dsp->tempA=dsp->tiempoApagado;
        }
        /*funcion que haga el manejo de los LEDS
        apagar transistores 2 y 3
        y prender los transistores de acuerdo al numero
        */
        //acá va la función
        Ds_Encienda_Disp(3);
        Ds_BCD(dsp->D3);
    break;

    case D3A:
        --(dsp->tempA);
        if(!(dsp->tempA)){
            dsp->estados =D1E;
            dsp->tempE=dsp->tiempoEncendido;
        }
        /*funcion que haga el manejo de los LEDS
        apagar transistores 1 2 y 3
        */
        Ds_Encienda_Disp(0);
    break;

    default:
        // a este no deberia llegar nunca
        while(1){
        /*prendo un LED que me marca el error*/
        }
}




}




