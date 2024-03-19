/*
 * calc.x : Protocolo de cálculo de operaciones con operandos simples y complejos 
 */

struct operation 
{
  float operator1;
  float operator2;
  char operator;
};

union operation_res switch (int errnum) 
{
  case 0:
    float result;  /* sin error: resultado de la operación*/
  default:
    void;          /* con error: nada                   */
};

program CALCULATOR 
{
  version SIMPLEOPERATION
  {
    float OPERATE (operation) = 1;
  } = 1;
} = 0x20000001;

