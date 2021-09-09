# 1 "nuestrostimers.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC12-16F1xxx_DFP/1.2.63/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "nuestrostimers.c" 2
# 1 "./nuestrostimers.h" 1







typedef struct Tm_Periodico Tm_Periodico;



struct Tm_Periodico
{
 unsigned int contador;
    unsigned int periodo;
 unsigned long timeout;
 unsigned char banderas;
};


void Tm_Procese_tiempo (Tm_Periodico *ctp);



void Tm_Inicie_periodico (Tm_Periodico *ctp,unsigned int periodo);
char Tm_Hubo_periodico (Tm_Periodico *ctp);
void Tm_Baje_periodico (Tm_Periodico *ctp);
void Tm_Termine_periodico (Tm_Periodico *ctp);


void Tm_Inicie_timeout (Tm_Periodico *ctp,unsigned int tiempo);
char Tm_Hubo_timeout (Tm_Periodico *ctp);
void Tm_Baje_timeout (Tm_Periodico *ctp);
# 1 "nuestrostimers.c" 2
# 11 "nuestrostimers.c"
void Tm_Inicie_periodico (Tm_Periodico *ctp,unsigned int periodo)
{
 ctp->banderas |= 0x01U;
 ctp->banderas &= ~0x02U;
 ctp->contador = ctp->periodo = periodo;
}
void Tm_Procese_tiempo (Tm_Periodico *ctp)
{


 if (ctp->banderas & 0x01U)
 {
  --(ctp->contador);
  if ( !(ctp->contador) )
  {
   ctp->banderas |= 0x02U;
   ctp->contador = ctp-> periodo;
  }
 }
 if ((ctp->timeout))
  ctp->timeout=ctp->timeout-1;
}



char Tm_Hubo_periodico (Tm_Periodico *ctp)
{
 return (ctp->banderas & 0x02U);
}



void Tm_Baje_periodico (Tm_Periodico *ctp)
{
 ctp->banderas &= ~0x02U;
}


void Tm_Termine_periodico (Tm_Periodico *ctp)
{
 ctp->banderas &= ~0x01U;
}


char Tm_Hubo_timeout (Tm_Periodico *ctp)
{
 if((ctp->timeout == 0) && (ctp->banderas &= 0x01U))
 {
 ctp->banderas &=~0x01U;
 ctp->banderas &= 0x04U;
 return 1;
 }
 else
 {
 return 0;
 }
}
void Tm_Inicie_timeout (Tm_Periodico *ctp,unsigned int tiempo)
{


 ctp->banderas |=0x01U;
 ctp->banderas &= ~0x04U;
 ctp->timeout = tiempo;
}




void Tm_Baje_timeout (Tm_Periodico *ctp)
{
 ctp->banderas &= ~0x04U;
 ctp->banderas &=~0x01U;
}
