# 1 "funciones.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-K_DFP/1.4.87/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "funciones.c" 2
# 1 "./funciones.h" 1
# 14 "./funciones.h"
long filtrarFIR1(int in);
long filtrarFIR2(int in);
long filtrarFIR3(int in);



typedef struct coef_iir_2_ord {
  float num[3];
  float den[3];
  float w[3];
  float gan[3];
  float num2[3];
  float den2[3];
  float w2[3];
} coef_iir_2_ord;

void inicializar_iir_2_ord(float*num, float*den, float*w, float *num2, float *den2, float *w2, float *gan, coef_iir_2_ord* ir);

float filtrarIIR(float in,coef_iir_2_ord* ir);

long filtrarFIR3_Optimizado(int in);

float filtrarIIRFormula2_a(float in, coef_iir_2_ord* ir);

float filtrarIIRFormula2_b(float in, coef_iir_2_ord* ir);
# 2 "funciones.c" 2





const int B[12] = {
     -4, 5, 16, 28, 38, 44, 44, 38, 28, 16, 5, -4
};
# 58 "funciones.c"
volatile int x[12];
volatile int k=0;

long filtrarFIR1(int in)
{
  long i = 1;
  x[k] = (long)in;
  long y = 0;
  for (i = 1; i <= 12; i++)
  {
    y += (long)B[i - 1] * (long)x[(i + k) % 12];
  }

  k = (k + 1) % 12;
  return y >> 8;
}

long filtrarFIR2(int in)
{
  int i = 0;
  x[k] = in;
  int inx = k;
  long y = 0;
  for (i = 0; i < 12; ++i) {
    y += (long)x[inx] * (long)B[i];
    inx = inx != 0 ? inx - 1 : 12 - 1;
  }
  k++;
  k = (k >= 12) ? 0 : k;
  return y >> 8;

}

long filtrarFIR3(int in)
{
  int i = 0;
  x[k] = in;
  int inx = k;
  char *apuntadorcoef = &B[0];
  int *apuntadorarrc = &x[inx];


  long y = 0;
  for (i = 0; i < 12; ++i) {
    y += (long)(*apuntadorarrc) * (long)(*apuntadorcoef);
    apuntadorcoef++;
    if (inx != 0) {
      apuntadorarrc--;
      inx--;
    }
    else {
      apuntadorarrc = &x[12 - 1];
      inx = 12 - 1;
    }
  }
  k++;
  k = (k >= 12) ? 0 : k;
  return y >> 8;
}




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


float filtrarIIR(float in, coef_iir_2_ord* ir) {
  float y;






  ir->w[0] = (ir->den[0] * in) - (ir->den[1] * ir->w[1]) - (ir->den[2] * ir->w[2]);
  y = ((ir->num[0] * ir->w[0]) + (ir->num[1] * ir->w[1]) + (ir->num[2] * ir->w[2]));
  ir->w[2] = ir->w[1];
  ir->w[1] = ir->w[0];
  return y;
}
# 161 "funciones.c"
long filtrarFIR3_Optimizado(int in)
{
  int i = 0;
  x[k] = in;
  int inx = k;
  char *apuntadorcoef = &B[0];
  int *apuntadorarrc = &x[inx];
  int *apuntadoroffset = inx;

  long buffer[12];
  for ( i = 12 -1; i > 0; i = i-1 ){
    buffer[i] = buffer[i-1];
  }
  buffer[0] = in;
  long y = 0;
  for (i = 0; i < (12/2); i++)
  {
    y += ((long)(*apuntadorcoef) * ((long)(*apuntadorarrc) + (long)(buffer[12 -i-1])));
    apuntadorcoef++;
    if (inx != 0)
    {
      apuntadorarrc--;
      apuntadoroffset++;
      inx--;
    }
    else
    {
      apuntadorarrc = &x[12 - 1];
      apuntadoroffset = &x[0];
      inx = (12/2) ;
    }
  }
  k++;
  k = (k >= 12) ? 0 : k;


  if((12%2) == 0)
  {
    return y>>8;
  }
  else
  {
    y += ((long)B[(12/2)+1]) * ((long)x[(12/2)+1]);
    return y>>8;
  }
}


float filtrarIIRFormula2_a(float in, coef_iir_2_ord* ir){
    float y;
    ir->w[0] = ((ir->gan[0] * in) - (ir->den[1] * ir->w[1]) - (ir->den[2] * ir->w[2]))/(1/ir->den[0]);
    y = ((ir->num[0] * ir->w[0]) + (ir->num[1] * ir->w[1]) + (ir->num[2] * ir->w[2]));
    ir->w[2] = ir->w[1];
    ir->w[1] = ir->w[0];
    return y;
}

float filtrarIIRFormula2_b(float in, coef_iir_2_ord* ir){
    float y;
    ir->w2[0] = ((ir->gan[1] * in) - (ir->den2[1] * ir->w2[1]) - (ir->den2[2] * ir->w2[2]))/(1/ir->den2[0]);
    y = ((ir->num2[0] * ir->w2[0]) + (ir->num2[1] * ir->w2[1]) + (ir->num2[2] * ir->w2[2]));
    ir->w2[2] = ir->w2[1];
    ir->w2[1] = ir->w2[0];
    return y;
}
