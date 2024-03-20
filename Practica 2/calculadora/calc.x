/*
 * calc.x : Protocolo de cálculo de operaciones con operandos simples y complejos 
 */

#define MAX 3

struct operation 
{
  double operator1;
  double operator2;
  char operator;
};

struct operationVector
{
	double vec1[MAX];
	double vec2[MAX];
	char operator;
};

struct Result
{
	double vec[MAX];
  double resultado;
};

union operation_res switch (int errnum) 
{
  case 0:
    Result result;  /* sin error: resultado de la operación*/
  default:
    void;          /* con error: nada                   */
};

program CALCULATOR 
{
  version OPERATION
  {
    Result OPERATE (operation) = 1;
    Result OPERATE_VECTOR (operationVector) = 2;
  } = 1;
} = 0x20000001;

