/*
 * calc.x : Protocolo de cálculo de operaciones con operandos simples y complejos 
 */

const MAX = 3;

struct operation 
{
  float operator1;
  float operator2;
  char operator;
};

struct vec_operation
{
  float vec1[MAX];
  float vec2[MAX];
  char *operator;
};

struct vec_result
{
  float vec[MAX];
};

program CALCULATOR 
{
  version SIMPLEOPERATION
  {
    float OPERATE (operation) = 1;
  } = 1;

  version SIMP_VEC_OPERATION
  {
    float OPERATE (operation) = 1;
    vec_result OPERATE_VECTOR (vec_operation) = 2;
  } = 2;

} = 0x20000001;

