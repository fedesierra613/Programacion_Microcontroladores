#ifndef FUNCIONES_H
#define FUNCIONES_H


#define FIR1 1
#define FIR2 2
#define FIR3 3
#define IIR 4

#define N 3

/*INICIAN FUNCIONES DE EJEMPLO FILTROS FIR*/

long filtrarFIR1(int in);
long filtrarFIR2(int in);
long filtrarFIR3(int in);

/*Parametros del filtro IIR*/

typedef struct coef_iir_2_ord {// este va a ser el nombre de la estructura
  float num[N]; // ponga aquí su numerador
  float den[N]; // ponga aquí su denominador
  float w[N];
  float gan[N];
  float num2[N]; // ponga aquí su numerador
  float den2[N]; // ponga aquí su denominador
  float w2[N];
} coef_iir_2_ord;// este va a ser el nombre del typedef

void inicializar_iir_2_ord(float*num, float*den, float*w, float *num2, float *den2, float *w2, float *gan, coef_iir_2_ord* ir);

float filtrarIIR(float in,coef_iir_2_ord* ir);

long filtrarFIR3_Optimizado(int in);

float filtrarIIRFormula2_a(float in, coef_iir_2_ord* ir);

float filtrarIIRFormula2_b(float in, coef_iir_2_ord* ir);







#endif


/***
 *                 _      <-. (`-')_ 
 *       <-.      (_)        \( OO) )
 *    (`-')-----. ,-(`-') ,--./ ,--/ 
 *    (OO|(_\---' | ( OO) |   \ |  | 
 *     / |  '--.  |  |  ) |  . '|  |)
 *     \_)  .--' (|  |_/  |  |\    | 
 *      `|  |_)   |  |'-> |  | \   | 
 *       `--'     `--'    `--'  `--' 
 */
