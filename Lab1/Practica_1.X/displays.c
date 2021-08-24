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

void Ds_Encienda_Disp(char dispNum){
    switch (dispNum){

        case 0:

            IO_RB0_SetLow();
            IO_RB3_SetLow();      //Apagar todos los displays 1ms
            IO_RB4_SetLow();

        break;


        case 1:

            IO_RB0_SetHigh();//Enciende display 1 9ms

        break;

        case 2:

            IO_RB3_SetHigh();//Enciende display 2
            
        break;


        case 3:

            IO_RB4_SetHigh();//Enciende display 3

        break;

}


void Ds_BCD(char segmento){
    switch (segmento){

        case 0:

            IO_RA0_SetHigh();//a Encendido
            IO_RA1_SetHigh(); //b Encendido
            IO_RA2_SetHigh(); //c Encendido
            IO_RA3_SetHigh();//d Encendido
            IO_RA4_SetHigh();//e Encendido
            IO_RA7_SetHigh();//f Encendido
            IO_RA6_SetLow();//g Apagado


        break;

        case 1:

            IO_RA0_SetLow();//a Apagado
            IO_RA1_SetHigh();//b Encendido
            IO_RA2_SetHigh();//c Encendido
            IO_RA3_SetLow();//d Apagado
            IO_RA4_SetLow();//e Apagado
            IO_RA7_SetLow();//f Apagado
            IO_RA6_SetLow();//g Apagado


        break;


        case 2:

            IO_RA0_SetHigh();//a Encendido
            IO_RA1_SetHigh();//b Encendido
            IO_RA2_SetLow();//c Apagado
            IO_RA3_SetHigh();//d Encendido
            IO_RA4_SetHigh();//e Encendido
            IO_RA7_SetLow();//f Apagado
            IO_RA6_SetHigh();//g Encendido


        break;


        case 3:

            IO_RA0_SetHigh();//a Encendido
            IO_RA1_SetHigh();//b Encendido
            IO_RA2_SetHigh();//c Encendido
            IO_RA3_SetHigh();//d Encendido
            IO_RA4_SetLow();//e Apagado
            IO_RA7_SetLow();//f Apagado
            IO_RA6_SetHigh();//g Encendido


        break;



        case 4:

            IO_RA0_SetLow();//a Apagago
            IO_RA1_SetHigh();//b Encendido
            IO_RA2_SetHigh();//c Encendido
            IO_RA3_SetLow();//d Apagado
            IO_RA4_SetLow();//e Apagado
            IO_RA7_SetHigh();//f Encendido
            IO_RA6_SetHigh();//g Encendido


        break;

        case 5:

            IO_RA0_SetHigh();//a Encendido
            IO_RA1_SetLow();//b Apagado
            IO_RA2_SetHigh();//c Encendido
            IO_RA3_SetHigh();//d Encendido
            IO_RA4_SetLow();//e Apagado
            IO_RA7_SetHigh();//f Encendido
            IO_RA6_SetHigh();//g Encendido


        break;


        case 6:

            IO_RA0_SetHigh();//a Encendido
            IO_RA1_SetLow();//b Apagado
            IO_RA2_SetHigh();//c Encendido
            IO_RA3_SetHigh();//d Encendido
            IO_RA4_SetHigh();//e Encendido
            IO_RA7_SetHigh();//f Encendido
            IO_RA6_SetHigh();//g Encendido


        break;


        case 7:

            IO_RA0_SetHigh();//a Encendido
            IO_RA1_SetHigh();//b Encendido
            IO_RA2_SetHigh();//c Encendido
            IO_RA3_SetLow();//d Apagado
            IO_RA4_SetLow();//e Apagado
            IO_RA7_SetLow();//f Apagado
            IO_RA6_SetLow();//g Apagado


        break;


        case 8:

            IO_RA0_SetHigh();//a Encendido
            IO_RA1_SetHigh();//b Encendido
            IO_RA2_SetHigh();//c Encendido
            IO_RA3_SetHigh();//d Encendido
            IO_RA4_SetHigh();//e Encendido
            IO_RA7_SetHigh();//f Encendido
            IO_RA6_SetHigh();//g Encendido


        break;


        case 9:

            IO_RA0_SetHigh();//a Encendido
            IO_RA1_SetHigh();//b Encendido
            IO_RA2_SetHigh();//c Encendido
            IO_RA3_SetHigh();//d Encendido
            IO_RA4_SetLow();//e Apagado
            IO_RA7_SetHigh();//f Encendido
            IO_RA6_SetHigh();//g Encendido


        break;

    }
}

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
            //aca va la funcion
            Ds_Encienda_Disp(1);
            Ds_BDC(dsp->D1);

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


char Ds_Convertir_en_uni_deci_centi(Ds_Display *dsp,int num){

        

}



void Ds_Mostrar_en_display(Ds_Display *dsp, char d1, char d2, char d3){


}