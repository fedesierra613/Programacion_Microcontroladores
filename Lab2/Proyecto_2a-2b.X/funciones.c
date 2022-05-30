#include "funciones.h"


//Filtrar FIR2 - 7
#define COR 8
#define BL 12
const int B[BL] = {
     -4,    5,   16,   28,   38,   44,   44,   38,   28,   16,    5,   -4
};
/**/
/*
//Filtrar FIR3 - 7
#define COR 8
#define BL 18
const int B[BL] = {
    -10,    0,   12,    8,  -10,  -22,    0,   52,   98,   98,   52,    0,
    -22,  -10,    8,   12,    0,  -10
};
*/
/*
//Filtrar FIR3 - 8
#define COR 8
#define BL 18
const int B[BL] = {
     -9,    0,   12,    9,  -11,  -22,    0,   52,   97,   97,   52,    0,
    -22,  -11,    9,   12,    0,   -9
};
*/
/*
//Filtrar FIR4 - 9
#define COR 15
#define BL 31
const int B[BL] = {
     -768,      0,    768,      0,  -1024,      0,   1152,      0,  -1536,
        0,   2176,      0,  -3584,      0,  10624,  16768,  10624,      0,
    -3584,      0,   2176,      0,  -1536,      0,   1152,      0,  -1024,
        0,    768,      0,   -768
};
*/
/*
//Filtrar FIR4 - 10
#define COR 15
#define BL 31
const int B[BL] = {
     -704,      0,    832,      0,   -960,      0,   1152,      0,  -1536,
        0,   2112,      0,  -3520,      0,  10624,  16704,  10624,      0,
    -3520,      0,   2112,      0,  -1536,      0,   1152,      0,   -960,
        0,    832,      0,   -704
};
*/
/*
#define BL 8
const int B[BL] = {
     17,   29,   39,   44,   44,   39,   29,   17
};
*/
/*Inicio de variables volatiles para pasar datos entre funciones*/
volatile int x[BL];
volatile int k=0;

long filtrarFIR1(int in)
{
  long i = 1;
  x[k] = (long)in;
  long y = 0;
  for (i = 1; i <= BL; i++) // NOTA, DEBE INICIAR EN 1. EJERCICIO: haga una prueba de escritorio con una respuesta impulso y compruebe...
  {
    y += (long)B[i - 1] * (long)x[(i + k) % BL]; // verifique que para su filtro no exista overflow.
  }

  k = (k + 1) % BL;
  return y >> COR; //si no es multiplo de 2^n divida por el factor de normalizaci贸n adecuado a su filtro.
}

long filtrarFIR2(int in)
{
  int i = 0;
  x[k] = in;
  int inx = k;
  long y = 0;
  for (i = 0; i < BL; ++i) {
    y += (long)x[inx] * (long)B[i];// verifique que para su filtro no exista overflow.
    inx = inx != 0 ? inx - 1 : BL - 1;
  }
  k++;
  k = (k >= BL) ? 0 : k;
  return y >> 8; //si no es multiplo de 2^n divida por el factor de normalizaci贸n adecuado a su filtro.

}

long filtrarFIR3(int in)
{
  int i = 0;
  x[k] = in;
  int inx = k;
  char *apuntadorcoef = &B[0];
  int *apuntadorarrc = &x[inx];
  // mucho cuidado con el tama帽o de los apuntadores DEBE COINCIDIR CON EL DEL ARREGLO o no va a funcionar.
  
  long y = 0;
  for (i = 0; i < BL; ++i) {
    y += (long)(*apuntadorarrc) * (long)(*apuntadorcoef);// verifique que para su filtro no exista overflow.
    apuntadorcoef++;
    if (inx != 0) {
      apuntadorarrc--;
      inx--;
    }
    else {
      apuntadorarrc = &x[BL - 1];
      inx = BL - 1;
    }
  }
  k++;
  k = (k >= BL) ? 0 : k;
  return y >> 8; //si no es multiplo de 2^n divida por el factor de normalizaci贸n adecuado a su filtro.
}


/*Funciones del filtro IIR*/

void inicializar_iir_2_ord(float*num, float*den, float*w, float *num2, float *den2, float *w2, float *gan, coef_iir_2_ord* ir)
{
  for (int i = 0; i < 3; i++) {
    ir->num[i] = num[i];
    ir->den[i] = den[i];
    ir->w[i] = w[i];
    ir->num2[i] = num2[i];
    ir->den2[i] = den2[i];
    ir->w2[i] = w2[i];
    ir->gan[i] = gan[i];
  }
}

/*ver la ayuda de matlab de dfilt.df2 para ver la estructura implementada en este filtro*/
float filtrarIIR(float in, coef_iir_2_ord* ir) {
  float y;
  /*Ecuacion implementada:
  w0=a0*x-a1*w1-a2*w2 donde x es la entrada  a denota a los denominadores notese que a0 es siempre 1 por lo que da lo mismo quitarlo
  y =b0*w0+b1*w1+b2*w2
  w2=w1
  w1=w0
  */
  ir->w[0] = (ir->den[0] * in) - (ir->den[1] * ir->w[1]) - (ir->den[2] * ir->w[2]); // OJO QUE EL MENOS YA ESTA EN LA ECUACION ver en  la ayuda de filterDesign en "show filter structure" si esta es o no la ecuaci贸n que implementan en ese software
  y = ((ir->num[0] * ir->w[0]) + (ir->num[1] * ir->w[1]) + (ir->num[2] * ir->w[2]));
  ir->w[2] = ir->w[1];//debe ser primero este
  ir->w[1] = ir->w[0];// y luego este para no sobreescribir
  return y;
}


/***
                   _      <-. (`-')_
         <-.      (_)        \( OO) )
      (`-')-----. ,-(`-') ,--./ ,--/
      (OO|(_\---' | ( OO) |   \ |  |
       / |  '--.  |  |  ) |  . '|  |)
       \_)  .--' (|  |_/  |  |\    |
        `|  |_)   |  |'-> |  | \   |
         `--'     `--'    `--'  `--'
*/
long filtrarFIR3_Optimizado(int in) //Implementaci髇 de FIR3 con la mitad de los coeficientes
{
  int i = 0;  //Variable que recorre posiciones del vector de salida
  x[k] = in; //Se馻l de entrada asignada al vector X0
  int inx = k; //Inicializa posiciones de vector de se馻l de entrada
  char *apuntadorcoef = &B[0]; //Apuntador a vector de coeficientes de FIR
  int *apuntadorarrc = &x[inx]; //Apuntador de la posici髇 inicial de se馻l
  int *apuntadoroffset = inx; //Apuntador de la posici髇 de offset del vector de la se馻l
  // mucho cuidado con el tama駉 de los apuntadores DEBE COINCIDIR CON EL DEL ARREGLO o no va a funcionar.
  long buffer[BL]; //Registro de corrimiento 
  for ( i = BL-1; i > 0; i = i-1 ){
    buffer[i] = buffer[i-1];
  }
  buffer[0] = in;
  long y = 0;
  for (i = 0; i < (BL/2); i++)
  {
    y += ((long)(*apuntadorcoef) * ((long)(*apuntadorarrc) + (long)(buffer[BL-i-1]))); // verifique que para su filtro no exista overflow.
    apuntadorcoef++;
    if (inx != 0)
    {
      apuntadorarrc--;
      apuntadoroffset++;
      inx--;
    }
    else
    {
      apuntadorarrc = &x[BL - 1];
      apuntadoroffset = &x[0];
      inx = (BL/2) ;
    }
  }
  k++;
  k = (k >= BL) ? 0 : k;

  //Verificaci髇 de si el vector es par o impar
  if((BL%2) == 0) //Si es par se retorna la salida
  {
    return y>>8; //si no es multiplo de 2^n divida por el factor de normalizaci髇 adecuado a su filtro.
  }
  else //Si es impar se le suma a la salida (y) el factor faltante de la mitad y se retorna su valor
  {
    y += ((long)B[(BL/2)+1]) * ((long)x[(BL/2)+1]); // Se obtiene el valor de la mitad del vector que esta solito :c
    return y>>8; //si no es multiplo de 2^n divida por el factor de normalizaci髇 adecuado a su filtro.
  }
}


float filtrarIIRFormula2_a(float in, coef_iir_2_ord* ir){
    float y;
    ir->w[0] = ((ir->gan[0] * in) - (ir->den[1] * ir->w[1]) - (ir->den[2] * ir->w[2]))/(1/ir->den[0]); // OJO QUE EL MENOS YA ESTA EN LA ECUACION ver en  la ayuda de filterDesign en "show filter structure" si esta es o no la ecuaci贸n que implementan en ese software
    y = ((ir->num[0] * ir->w[0]) + (ir->num[1] * ir->w[1]) + (ir->num[2] * ir->w[2]));
    ir->w[2] = ir->w[1];//debe ser primero este
    ir->w[1] = ir->w[0];// y luego este para no sobreescribir
    return y;
}

float filtrarIIRFormula2_b(float in, coef_iir_2_ord* ir){
    float y;
    ir->w2[0] = ((ir->gan[1] * in) - (ir->den2[1] * ir->w2[1]) - (ir->den2[2] * ir->w2[2]))/(1/ir->den2[0]); // OJO QUE EL MENOS YA ESTA EN LA ECUACION ver en  la ayuda de filterDesign en "show filter structure" si esta es o no la ecuaci贸n que implementan en ese software
    y = ((ir->num2[0] * ir->w2[0]) + (ir->num2[1] * ir->w2[1]) + (ir->num2[2] * ir->w2[2]));
    ir->w2[2] = ir->w2[1];//debe ser primero este
    ir->w2[1] = ir->w2[0];// y luego este para no sobreescribir
    return y;
}