/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calc.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void printSimpleOperation(struct operation Operation)
{
	printf("[ %f %s %f ]", Operation.operator1, &Operation.operator, Operation.operator2);
}

bool correctOperator(struct operation Operation)
{
	bool toReturn = true;

	if (!strcmp(&Operation.operator, "+") ||
		!strcmp(&Operation.operator, "-") ||
		!strcmp(&Operation.operator, "*") ||
		!strcmp(&Operation.operator, "x") ||
		!strcmp(&Operation.operator, "/"))
	{
		toReturn = true;
	}
	else
	{
		toReturn = false;
	}

	return toReturn;
}

struct operation interactiveLoadSimpleOperation()
{
	struct operation Operation;
	bool ok = false;
	char *answer;

	do
	{
		printf("*---- CALCULADORA ----*\nIntroduzca el operando de la izquierda -> ");
		scanf("%f", &Operation.operator1);
		printf("\n¿Qué operación desea realizar?\nOperaciones disponibles [+ - * /]-> ");
		scanf("%s", &Operation.operator);
		printf("\nIntroduzca el operando de la derecha -> ");
		scanf("%f", &Operation.operator2);
		printf("\nSu operación: ");
		printSimpleOperation(Operation);
		if (Operation.operator2 != 0 && correctOperator(Operation))
		{
			printf("\n¿Es esta la operación que desea realizar? [Y/n] ");
			scanf("%s", &answer);
			if (!strcmp(&answer, "Y") || !strcmp(&answer, "y"))
			{
				ok = true;
			}
			else
			{
				ok = false;
			}
		}
		else
		{
			printf("\nError: Operación no válida\n\n");
		}
	} while (!ok);

	return Operation;
}

void calculator_1(char *host)
{
	CLIENT *clnt;
	float *result_1;
	operation operate_1_arg1;

	// Ponemos los argumentos de la operación
	operate_1_arg1 = interactiveLoadSimpleOperation();

#ifndef DEBUG
	clnt = clnt_create(host, CALCULATOR, SIMPLEOPERATION, "udp");
	if (clnt == NULL)
	{
		clnt_pcreateerror(host);
		exit(1);
	}
#endif /* DEBUG */

	result_1 = operate_1(operate_1_arg1, clnt);
	if (result_1 == (float *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}

	// Imprimimos por pantalla el resultado
	printf("El resultado es: %f\n", *result_1);

#ifndef DEBUG
	clnt_destroy(clnt);
#endif /* DEBUG */
}

int main(int argc, char *argv[])
{
	char *host;

	if (argc < 2)
	{
		printf("usage: %s server_host\n", argv[0]);
		exit(1);
	}
	host = argv[1];
	calculator_1(host);
	exit(0);
}
