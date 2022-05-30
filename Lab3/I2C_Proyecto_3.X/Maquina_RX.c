
#include "mcc_generated_files/mcc.h"
#include "Maquina_RX.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mcc_generated_files/examples/i2c_simple_example.h"



void Maquina_RE(Vect_RE *dsp){
    switch (dsp->caso){
        //Dato de entrada W o R
        case Caso_NUM:
            dsp->RESET = 1;
            if(dsp->Dato == 'W'){
                dsp->caso = Caso_W_BS;
            }else if(dsp->Dato == 'R'){
                dsp->caso = Caso_R_BS;
            }else{
                dsp->RESET = 0;
                printf("ERR1\n\r");
            }
        break;
        
        case Caso_W_BS:
            if(dsp->Dato == 'B'){
                dsp->i = 0;
                dsp->Comando = 2;
                dsp->caso = Caso_W_B;//Comando 1 - 2
            }else if(dsp->Dato == 'S'){
                dsp->i = 0;
                dsp->Comando = 4;
                dsp->caso = Caso_W_S;//Comando 2 - 4
            }else{
                dsp->caso = Caso_NUM;
                dsp->RESET = 0;
                printf("ERR2\n\r");
            }
        break;
        
        case Caso_R_BS:
            if(dsp->Dato == 'B'){
                dsp->i = 0;
                dsp->Comando = 1;
                dsp->caso = Caso_R_B;//Comando 3 - 1
            }else if(dsp->Dato == 'S'){
                dsp->i = 0;
                dsp->Comando = 3;
                dsp->caso = Caso_R_S;//Comando 4 - 3
            }else{
                dsp->caso = Caso_NUM;
                dsp->RESET = 0;
                printf("ERR3\n\r");
            }
        break;
        //fin configuracion y eleccion de los 4 comandos
        
        //Toma del dato ADD Comando RB
        case Caso_R_B:
            if((dsp->Dato<=57)&&(dsp->Dato>=48)){
                dsp->dir_add[dsp->i] = dsp->Dato - '0';
            }else if((dsp->Dato<=70)&&(dsp->Dato>=65)){
                dsp->dir_add[dsp->i] = dsp->Dato - '7';
            }else{
                dsp->caso = Caso_NUM;
                dsp->RESET = 0;
                printf("ERR4\n\r");
                break;
            }
            dsp->i++;
            if(dsp->i>=4){
                dsp->i = 0;
                dsp->caso = Caso_saltodelinea;
            }
        break;
        
        //Comando WB
        case Caso_W_B:
            if((dsp->Dato<=57)&&(dsp->Dato>=48)){
                dsp->dir_add[dsp->i] = dsp->Dato - '0';
            }else if((dsp->Dato<=70)&&(dsp->Dato>=65)){
                dsp->dir_add[dsp->i] = dsp->Dato - '7';
            }else{
                dsp->caso = Caso_NUM;
                dsp->RESET = 0;
                printf("ERR5\n\r");
                break;
            }
            dsp->i++;
            if(dsp->i>=4){
                dsp->i = 0;
                dsp->caso = Caso_coma;
            }
        break;
        
        //Comando RS
        case Caso_R_S:
            if((dsp->Dato<=57)&&(dsp->Dato>=48)){
                dsp->dir_add[dsp->i] = dsp->Dato - '0';
            }else if((dsp->Dato<=70)&&(dsp->Dato>=65)){
                dsp->dir_add[dsp->i] = dsp->Dato - '7';
            }else{
                dsp->caso = Caso_NUM;
                dsp->RESET = 0;
                printf("ERR6\n\r");
                break;
            }
            dsp->i++;
            if(dsp->i>=4){
                dsp->i = 0;
                dsp->caso = Caso_coma;
            }
        break;
        
        //Comando WS
        case Caso_W_S:
            if((dsp->Dato<=57)&&(dsp->Dato>=48)){
                dsp->dir_add[dsp->i] = dsp->Dato - '0';
            }else if((dsp->Dato<=70)&&(dsp->Dato>=65)){
                dsp->dir_add[dsp->i] = dsp->Dato - '7';
            }else{
                dsp->caso = Caso_NUM;
                dsp->RESET = 0;
                printf("ERR7\n\r");
                break;
            }
            dsp->i++;
            if(dsp->i>=4){
                dsp->i = 0;
                dsp->caso = Caso_coma;
            }
        break;
        
        //Caso coma
        case Caso_coma:
            if(dsp->Dato == ','){
                if(dsp->Comando == 2){
                    dsp->caso = Caso_val;
                }else if(dsp->Comando == 3){
                    dsp->caso = Caso_num;
                }else if(dsp->Comando == 4){
                    dsp->caso = Caso_num16;
                }
            }else{
                dsp->caso = Caso_NUM;
                dsp->RESET = 0;
                printf("ERR8\n\r");
                break;
            }
        break;
        
        //Escritura de un byte en hex ascii (val) 
        case Caso_val:
            if((dsp->Dato<=57)&&(dsp->Dato>=48)){
                dsp->val[dsp->i] = dsp->Dato - '0';
            }else if((dsp->Dato<=70)&&(dsp->Dato>=65)){
                dsp->val[dsp->i] = dsp->Dato - '7';
            }else{
                dsp->caso = Caso_NUM;
                dsp->RESET = 0;
                printf("ERR9\n\r");
                break;
            }
            dsp->i++;
            if(dsp->i>=2){
                dsp->i = 0;
                dsp->caso = Caso_saltodelinea;
            }
        break;
        
        case Caso_num:
            if((dsp->Dato<=57)&&(dsp->Dato>=48)){
                dsp->num[dsp->i] = dsp->Dato - '0';
            }else if((dsp->Dato<=70)&&(dsp->Dato>=65)){
                dsp->num[dsp->i] = dsp->Dato - '7';
            }else{
                dsp->caso = Caso_NUM;
                dsp->RESET = 0;
                printf("ERR10\n\r");
                break;
            }
            dsp->i++;
            if(dsp->i>=2){
                dsp->i = 0;
                dsp->caso = Caso_saltodelinea;
            }
        break;
        
        case Caso_num16:
            if((dsp->Dato<=57)&&(dsp->Dato>=48)){
                dsp->num16[dsp->i] = dsp->Dato - '0';
            }else if((dsp->Dato<=70)&&(dsp->Dato>=65)){
                dsp->num16[dsp->i] = dsp->Dato - '7';
            }else{
                dsp->caso = Caso_NUM;
                dsp->RESET = 0;
                printf("ERR11\n\r");
                break;
            }
            dsp->i++;
            if((dsp->i)%2 == 0){
                dsp->caso = Caso_coma;
            }
            if((dsp->i)>=32){
                dsp->i = 0;
                dsp->caso = Caso_saltodelinea;
            }
        break;
        
        //Caso salto de linea
        case Caso_saltodelinea:
            if(dsp->Dato == 10){
                dsp->iniciar = 1;
                dsp->RESET = 0;
                dsp->caso = Caso_NUM;
            }else{
                dsp->caso = Caso_NUM;
                dsp->RESET = 0;
                printf("ERR12\n\r");
                break;
            }
        break;
    }
}

void Funcion_RB(Vect_RE *dsp){
    uint8_t Enviar[2];
    uint8_t Recibir[1];
    Enviar[0] = (dsp->dir_add[0]*16) + dsp->dir_add[1];
    Enviar[1] = (dsp->dir_add[2]*16) + dsp->dir_add[3];
    i2c_writeNBytes(EEPROM,Enviar,2);
    i2c_readNBytes(EEPROM,Recibir,sizeof(Recibir));
    printf("0x%x  ",Recibir[sizeof(Recibir)]);
    printf("\n\r");
}

void Funcion_WB(Vect_RE *dsp){
    uint8_t Enviar[3];
    uint8_t Recibir[1];
    Enviar[0] = (dsp->dir_add[0]*16) + dsp->dir_add[1];
    Enviar[1] = (dsp->dir_add[2]*16) + dsp->dir_add[3];
    Enviar[3] = dsp->val[0]*16 + dsp->val[1];
    i2c_writeNBytes(EEPROM,Enviar,sizeof(Enviar));
    i2c_writeNBytes(EEPROM,Enviar,2);
    i2c_readNBytes(EEPROM,Recibir,sizeof(Recibir));
    printf("0x%x  ",Recibir[0]);
    printf("\n\r");
}

void Funcion_RS(Vect_RE *dsp){
    uint8_t Enviar[2];
    uint8_t Num_Datos;
    uint8_t Recibir[Num];
    char i;
    Enviar[0] = (dsp->dir_add[0]*16) + dsp->dir_add[1];
    Enviar[1] = (dsp->dir_add[2]*16) + dsp->dir_add[3];
    Num_Datos = (dsp->num[0]*16) + dsp->num[1];
    i2c_writeNBytes(EEPROM,Enviar,2);
    i2c_readNBytes(EEPROM,Recibir,Num_Datos);
    
    for(i=0;i<Num_Datos;i++)
    {
        printf("0x%x  ",Recibir[i]);
    }
    printf("\n\r");
}

void Funcion_WS(Vect_RE *dsp){
    uint8_t Enviar[Num_Bytes];
    char i;
    char j = 0;
    Enviar[0] = (dsp->dir_add[0]*16) + dsp->dir_add[1];
    Enviar[1] = (dsp->dir_add[2]*16) + dsp->dir_add[3];
    for(i=2;i<=Num_Bytes-1;i++){
        Enviar[i] = dsp->num16[j]*16 + dsp->num16[j+1];
        j = j + 2;
    }
    i2c_writeNBytes(EEPROM,Enviar,sizeof(Enviar));
    printf("OK_WS2\n\r");
}
