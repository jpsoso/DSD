/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calc.h"


void
calculator_1(char *host)
{
	CLIENT *clnt;
	float  *result_1;
	operation operate_1_arg1;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULATOR, SIMPLEOPERATION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = operate_1(operate_1_arg1, clnt);
	if (result_1 == (float *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


void printVector(float vector[])
{
	printf("(%d, %d, %d)", vector[0], vector[1], vector[2]);
}

void
calculator_2(char *host)
{
	CLIENT *clnt;
	float  *result_1;
	operation operate_2_arg1;
	vec_result  *result_2;
	vec_operation operate_vector_2_arg1;

	operate_vector_2_arg1.vec1[0] = 1;
	operate_vector_2_arg1.vec1[1] = 1;
	operate_vector_2_arg1.vec1[2] = 1;

	operate_vector_2_arg1.vec2[0] = 1;
	operate_vector_2_arg1.vec2[1] = 1;
	operate_vector_2_arg1.vec2[2] = 1;


#ifndef	DEBUG
	clnt = clnt_create (host, CALCULATOR, SIMP_VEC_OPERATION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

/* 	result_1 = operate_2(operate_2_arg1, clnt);
	if (result_1 == (float *) NULL) {
		clnt_perror (clnt, "call failed");
	} */
	result_2 = operate_vector_2(operate_vector_2_arg1, clnt);
	if (result_2 == (vec_result *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	printVector(&result_2);

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
	// calculator_1 (host);
	calculator_2 (host);
exit (0);
}