/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CALC_H_RPCGEN
#define _CALC_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct operation {
	float operator1;
	float operator2;
	char operator;
};
typedef struct operation operation;

struct operationVector {
	float vec1[3];
	float vec2[3];
	char operator;
};
typedef struct operationVector operationVector;

struct resultVect {
	float vec[3];
};
typedef struct resultVect resultVect;

struct operation_res {
	int errnum;
	union {
		resultVect result;
	} operation_res_u;
};
typedef struct operation_res operation_res;

#define CALCULATOR 0x20000001
#define VEC_OPERATION 1

#if defined(__STDC__) || defined(__cplusplus)
#define OPERATE 1
extern  float * operate_1(operation , CLIENT *);
extern  float * operate_1_svc(operation , struct svc_req *);
#define OPERATE_VECTOR 2
extern  resultVect * operate_vector_1(operationVector , CLIENT *);
extern  resultVect * operate_vector_1_svc(operationVector , struct svc_req *);
extern int calculator_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define OPERATE 1
extern  float * operate_1();
extern  float * operate_1_svc();
#define OPERATE_VECTOR 2
extern  resultVect * operate_vector_1();
extern  resultVect * operate_vector_1_svc();
extern int calculator_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_operation (XDR *, operation*);
extern  bool_t xdr_operationVector (XDR *, operationVector*);
extern  bool_t xdr_resultVect (XDR *, resultVect*);
extern  bool_t xdr_operation_res (XDR *, operation_res*);

#else /* K&R C */
extern bool_t xdr_operation ();
extern bool_t xdr_operationVector ();
extern bool_t xdr_resultVect ();
extern bool_t xdr_operation_res ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CALC_H_RPCGEN */
