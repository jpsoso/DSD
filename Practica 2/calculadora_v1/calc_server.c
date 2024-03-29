/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calc.h"

float *
operate_1_svc(operation arg1,  struct svc_req *rqstp)
{
	static float  result;

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

	default:
		break;
	}

	return &result;
}
