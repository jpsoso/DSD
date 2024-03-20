/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calc.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void printMainMenu()
{
	printf("========== CALCULATOR ==========");
	printf("\n[OPCIÓN 1] Operaciones normales");
	printf("\n[OPCIÓN 2] Operaciones con vectores");
	printf("\n[OPCIÓN 3] SALIR");
	printf("\n¿Qué desea realizar? -> ");
}

void printSimpleOperation(struct operation Operation)
{
	if (!strcmp(&Operation.operator, "+") ||
		!strcmp(&Operation.operator, "-") ||
		!strcmp(&Operation.operator, "*") ||
		!strcmp(&Operation.operator, "x") ||
		!strcmp(&Operation.operator, "^") ||
		!strcmp(&Operation.operator, "/"))
	{
		printf("[ %f %s %f ]", Operation.operator1, &Operation.operator, Operation.operator2);
	}
	else
	{
		switch (Operation.operator)
		{
		case 's':
			printf("[sen(%f)]", Operation.operator2);
			break;

		case 'c':
			printf("[cos(%f)]", Operation.operator2);
			break;

		case 't':
			printf("[tan(%f)]", Operation.operator2);
			break;

		case 'l':
			printf("[ln(%f)]", Operation.operator2);
			break;
						
		default:
			break;
		}
	}
}

void printVectorialOperation (struct operationVector Operator)
{
	if (Operator.operator == '·')
	{
		printf("[");
		for (int i = 0; i < 3; ++i)
		{
			printf("%f ", Operator.vec1[i]);
		}
		printf("] · [");

		for (int i = 0; i < 3; ++i)
		{
			printf("%f ", Operator.vec2[i]);
		}
		printf("]");
	}
	else
	{
		printf("[");
		for (int i = 0; i < 3; ++i)
		{
			printf("%f ", Operator.vec1[i]);
		}
		printf("] %c [", Operator.operator);

		for (int i = 0; i < 3; ++i)
		{
			printf("%f ", Operator.vec2[i]);
		}
		printf("]");		
	}
}

bool correctOperator(struct operation Operation)
{
	bool toReturn = true;

	if (!strcmp(&Operation.operator, "+") ||
		!strcmp(&Operation.operator, "-") ||
		!strcmp(&Operation.operator, "*") ||
		!strcmp(&Operation.operator, "x") ||
		!strcmp(&Operation.operator, "^") ||
		!strcmp(&Operation.operator, "s") ||
		!strcmp(&Operation.operator, "c") ||
		!strcmp(&Operation.operator, "t") ||
		!strcmp(&Operation.operator, "l"))
	{
		toReturn = true;
	}
	else
	{
		toReturn = false;
	}

	return toReturn;
}

bool correctVectorialOperator(struct operationVector Operation)
{
	bool toReturn = true;

	if (!strcmp(&Operation.operator, "+") ||
		!strcmp(&Operation.operator, "-") ||
		!strcmp(&Operation.operator, "·") ||
		!strcmp(&Operation.operator, "x"))
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
		printf("\n¿Qué operación desea realizar?\nOperaciones disponibles \n[+ - * /] [sen, s] [cos, c] [tan, t] [ln l]\n-> ");
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

struct operationVector interactiveLoadVectorialOperation()
{
	struct operationVector Operation;
	bool ok = false;
	char *answer;

	do
	{
		printf("\n¿Qué operación desea realizar?\nOperaciones disponibles: [+ - · x] -> ");
		scanf("%f", &Operation.operator);

		if (correctVectorialOperator(Operation))
		{
			if (Operation.operator == '·')
			{
				printf("Introduzca el escalar ->\n");
				scanf("%f", Operation.vec1[0]);

				printf("Introduzca el vector\n");
				for (int i = 0; i < 3; ++i)
				{
					printf("vector2[%i]: ", i);
					scanf("%f", Operation.vec2[i]);
				}
			}
			else
			{
				printf("Introduzca el vector de la izquierda\n");
				for (int i = 0; i < 3; ++i)
				{
					printf("vector1[%i]: ", i);
					scanf("%f", Operation.vec1[i]);

				}

				printf("Introduzca el vector de la derecha\n");
				for (int i = 0; i < 3; ++i)
				{
					printf("vector2[%i]: ", i);
					scanf("%f", Operation.vec2[i]);

				}				
			}
			printf("\nSu operación: ");
			printVectorialOperation(Operation);
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
			printf("Operación inválida");
		}
	} while (!ok);

	return Operation;
}

void calculator_1(char *host)
{
	CLIENT *clnt;
	float *result_1;
	operation operate_1_arg1;
	resultVect *result_2;
	operationVector operate_vector_1_arg1;

#ifndef DEBUG
	clnt = clnt_create(host, CALCULATOR, VEC_OPERATION, "udp");
	if (clnt == NULL)
	{
		clnt_pcreateerror(host);
		exit(1);
	}
#endif /* DEBUG */
	bool exit = false;
	int option = 0;
	do
	{
		printMainMenu();
		scanf("%i", &option);

		if (option == 1) // Operación simple
		{
			operate_1_arg1 = interactiveLoadSimpleOperation();
			printf("%f %f %c ", operate_1_arg1.operator1, operate_1_arg1.operator2, operate_1_arg1.operator);

			result_1 = operate_1(operate_1_arg1, clnt);
			if (result_1 == (float *)NULL)
			{
				clnt_perror(clnt, "call failed");
			}

			printf("Resultado: %f\n\n", result_1); // Impresión resultado
		}
		else if (option == 2) // Operación vectorial
		{
			operate_vector_1_arg1 = interactiveLoadVectorialOperation();
			result_2 = operate_vector_1(operate_vector_1_arg1, clnt);
			if (result_2 == (resultVect *)NULL)
			{
				clnt_perror(clnt, "call failed");
			}

			if (operate_vector_1_arg1.operator == '·') // Impresión resultado
			{
				printf("Resultado: %f\n\n", result_2->vec[0]);
			}
			else
			{
				printf("Resultado [");
				for (int i = 0; i < 3; ++i)
				{
					printf("%f ", result_2->vec[i]);
				}
				printf("]\n\n");
			}
		}
	} while (option == 1 || option == 2);


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
