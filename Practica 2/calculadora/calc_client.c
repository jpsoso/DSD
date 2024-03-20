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
	printf("\n\n========== CALCULATOR ==========");
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
		
		case 'q':
			printf("[sqrt(%f)]", Operation.operator2);
						
		default:
			break;
		}
	}
}

void printVectorialOperation (struct operationVector Operator)
{
	if (!strcmp(&Operator.operator,"p"))
	{
		printf("%f · [", Operator.vec1[0]);

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
		!strcmp(&Operation.operator, "/") ||
		!strcmp(&Operation.operator, "x") ||
		!strcmp(&Operation.operator, "^") ||
		!strcmp(&Operation.operator, "s") ||
		!strcmp(&Operation.operator, "c") ||
		!strcmp(&Operation.operator, "t") ||
		!strcmp(&Operation.operator, "q") ||
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
		!strcmp(&Operation.operator, "p") ||
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
		printf("\n¿Qué operación desea realizar?\nOperaciones disponibles \n[+ - * / ] [eleva ^] [sqrt q] [sen, s] [cos, c] [tan, t] [ln l]\n-> ");
		scanf("%s", &Operation.operator);

		if (correctOperator(Operation)) 
		{
			if (!strcmp(&Operation.operator, "s") ||
				!strcmp(&Operation.operator, "c") ||
				!strcmp(&Operation.operator, "t") ||
				!strcmp(&Operation.operator, "q") ||
				!strcmp(&Operation.operator, "l"))
				{
					printf("\nIntroduzca el operando -> ");
					scanf("%lf", &Operation.operator2);
				} 
				else
				{
					printf("Introduzca el operando de la izquierda -> ");
					scanf("%lf", &Operation.operator1);

					printf("\nIntroduzca el operando de la derecha -> ");
					scanf("%lf", &Operation.operator2);
				}
			
				printf("\nSu operación: ");
				printSimpleOperation(Operation);

			if (!(Operation.operator == '/' && Operation.operator2 == 0))
			{
				printf("\n¿Es ésta la operación que desea realizar? [Y/n] ");
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
		printf("\n¿Qué operación desea realizar?\nOperaciones disponibles: [+ - p x] -> ");
		scanf("%s", &Operation.operator);

		if (correctVectorialOperator(Operation))
		{
			if (!strcmp(&Operation.operator, "p"))
			{
				printf("Introduzca el escalar -> ");
				scanf("%lf", &Operation.vec1[0]);

				printf("Introduzca el vector\n");
				for (int i = 0; i < 3; ++i)
				{
					printf("vector2[%i]: ", i);
					scanf("%lf", &Operation.vec2[i]);
				}
			}
			else
			{
				printf("Introduzca el vector de la izquierda\n");
				for (int i = 0; i < 3; ++i)
				{
					printf("vector1[%i]: ", i);
					scanf("%lf", &Operation.vec1[i]);

				}

				printf("Introduzca el vector de la derecha\n");
				for (int i = 0; i < 3; ++i)
				{
					printf("vector2[%i]: ", i);
					scanf("%lf", &Operation.vec2[i]);

				}				
			}
			printf("\nSu operación: ");
			printVectorialOperation(Operation);
			printf("\n¿Es ésta la operación que desea realizar? [Y/n] ");
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
			printf("Operación no válida");
		}
	} while (!ok);
	return Operation;
}

void
calculator_1(char *host)
{
	CLIENT *clnt;
	Result  *result_1;
	operation operate_1_arg1;
	Result  *result_2;
	operationVector operate_vector_1_arg1;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULATOR, OPERATION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	int option = 0;

	do
	{
		printMainMenu();
		scanf("%i", &option);

		if (option == 1)
		{
			operate_1_arg1 = interactiveLoadSimpleOperation();
			result_1 = operate_1(operate_1_arg1, clnt);
			if (result_1 == (Result *) NULL) {
				clnt_perror (clnt, "call failed");
			}
			printf("Resultado: %f\n", result_1->resultado);
		}
		else if (option == 2)
		{
			operate_vector_1_arg1 = interactiveLoadVectorialOperation();
			result_2 = operate_vector_1(operate_vector_1_arg1, clnt);
			if (result_2 == (Result *) NULL) {
				clnt_perror (clnt, "call failed");
			}
			printf("Resultado: [");
			for (int i = 0; i < 3; i++)
			{
				printf("%f ", result_2->vec[i]);
			}
			printf("]\n");

		}
	} while (option < 3);


#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	calculator_1 (host);
exit (0);
}
