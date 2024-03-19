/*
 * calc.x : Protocolo de cálculo de operaciones con operandos simples y complejos 
 */


#define MAX 3

struct operation 
{
  float operator1;
  float operator2;
  char operator;
};

struct operationVector
{
	float vec1[MAX];
	float vec2[MAX];
	char operator;
};

struct resultVect
{
	float vec[MAX];
};

union operation_res switch (int errnum)
{
case 0:
	resultVect result;
default:
	void;
};

program CALCULATOR
{
	version VEC_OPERATION
	{
		float OPERATE (operation) = 1;
    resultVect OPERATE_VECTOR (operationVector) = 2;
	}	= 1;
} = 0x20000001;


