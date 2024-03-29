/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calc.h"
#include <math.h>
#include <stdio.h>

float *
operate_1_svc(operation arg1,  struct svc_req *rqstp)
{
	static float  result = 0;

	switch (arg1.operator)
	{
	case '+':
		result = arg1.operator1 + arg1.operator2;
		break;

	case '-':
		result = arg1.operator1 - arg1.operator2;
		break;

	case '*' || 'x':
		result = arg1.operator1 * arg1.operator2;
		break;

	case '/':
		result = arg1.operator1 / arg1.operator2;
		break;

	case '^':
		result = pow(arg1.operator1, arg1.operator2);
		break;

	case 's':
		result = sin(arg1.operator2);
		break;

	case 'c':
		result = cos(arg1.operator2);
		break;

	case 't':
		result = tan(arg1.operator2);
		break;
	
	case 'l':
		result = log(arg1.operator2);
		break;
		
	default:
		break;
	}
	
    FILE *f;
    f = fopen("/dev/tty", "w");
    if (f == (FILE *)NULL)
    {
      result = 0;
      return (&result);
    }

    fprintf(f, "%f\n", result);
    fclose(f);

	return &result;
}

resultVect suma(operationVector operation)
{
	resultVect result;
	for (int i = 0; i < 3; ++i)
	{
		result.vec[i] = operation.vec1[i] + operation.vec2[i];
	}
	return result;
}

resultVect resta(operationVector operation)
{
	resultVect result;
	for (int i = 0; i < 3; ++i)
	{
		result.vec[i] = operation.vec1[i] - operation.vec2[i];
	}
	return result;
}

resultVect prodEscalar(operationVector operation)
{
	resultVect result;
	for (int i = 0; i < 3; ++i)
	{
		result.vec[0] += operation.vec1[i] * operation.vec2[i];
	}
	return result;
}

resultVect prodVectorial(operationVector operation)
{
	resultVect result;
	result.vec[0] = operation.vec1[1] * operation.vec2[2] - operation.vec1[2] * operation.vec2[1];
	result.vec[1] = operation.vec1[2] * operation.vec2[0] - operation.vec1[0] * operation.vec2[2];
	result.vec[2] = operation.vec1[0] * operation.vec2[1] - operation.vec1[1] * operation.vec2[0];
	return result;
}



resultVect *
operate_vector_1_svc(operationVector arg1,  struct svc_req *rqstp)
{
	static resultVect  result;

	

	return &result;
}
