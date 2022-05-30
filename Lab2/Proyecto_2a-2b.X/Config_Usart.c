
#include "Config_Usart.h"
#include <xc.h>
#include "mcc_generated_files/mcc.h"


char Re_Vector(Vect_RE *dsp){
    char BandDato;
    if(dsp->Lectura == '#'){
        dsp->Iniciar = 1;
        dsp->Pos = 0;
        BandDato = 0;
    }   
    if (dsp->Iniciar){
        dsp->Dato[dsp->Pos] = dsp->Lectura - '0';
        dsp->Pos++;
    }
    if(dsp->Lectura == '*'){
        dsp->Iniciar = 0;
        BandDato = 1;
    }
    return BandDato;
}



char ConfigPostcaler(float n){
    char Post = 0xF0;
    if((n<=4096)&&(n>=500)){
        Post = 0xF0;
    }
    if((n<=8192)&&(n>4096)){
        Post = 0xF1;
    }
    if((n<=12288)&&(n>8192)){
        Post = 0xF2;
    }
    if((n<=16384)&&(n>12288)){
        Post = 0xF3;
    }
    if((n<=20480)&&(n>16384)){
        Post = 0xF4;
    }
    if((n<=24576)&&(n>20480)){
        Post = 0xF5;
    }
    if((n<=28672)&&(n>24576)){
        Post = 0xF6;
    }
    if((n<=32768)&&(n>28672)){
        Post = 0xF7;
    }
    if((n<=36864)&&(n>32768)){
        Post = 0xF8;
    }
    if((n<=40960)&&(n>36864)){
        Post = 0xF9;
    }
    if((n<=45056)&&(n>40960)){
        Post = 0xFA;
    }
    if((n<=49152)&&(n>45056)){
        Post = 0xFB;
    }
    if((n<=50000)&&(n>45056)){//53248
        Post = 0xFC;
    }
    return Post;
}


char ConfigCont(float Dato, char Post){
    char contador = 0;
    if(Post == 0xF0){
        contador = Dato/16;//(Dato/16)-1
    }
    if(Post == 0xF1){
        contador = Dato/32;
    }
    if(Post == 0xF2){
        contador = Dato/48;
    }
    if(Post == 0xF3){
        contador = Dato/64;
    }
    if(Post == 0xF4){
        contador = Dato/80;
    }
    if(Post == 0xF5){
        contador = Dato/96;
    }
    if(Post == 0xF6){
        contador = Dato/112;
    }
    if(Post == 0xF7){
        contador = Dato/128;
    }
    if(Post == 0xF8){
        contador = Dato/144;
    }
    if(Post == 0xF9){
        contador = Dato/160;
    }
    if(Post == 0xFA){
        contador = Dato/176;
    }
    if(Post == 0xFB){
        contador = Dato/192;
    }
    if(Post == 0xFC){
        contador = Dato/208;
    }
    return contador;
}