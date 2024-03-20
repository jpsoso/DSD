/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static float *
_operate_1 (operation  *argp, struct svc_req *rqstp)
{
	return (operate_1_svc(*argp, rqstp));
}

static resultVect *
_operate_vector_1 (operationVector  *argp, struct svc_req *rqstp)
{
	return (operate_vector_1_svc(*argp, rqstp));
}

static void
calculator_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		operation operate_1_arg;
		operationVector operate_vector_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case OPERATE:
		_xdr_argument = (xdrproc_t) xdr_operation;
		_xdr_result = (xdrproc_t) xdr_float;
		local = (char *(*)(char *, struct svc_req *)) _operate_1;
		break;

	case OPERATE_VECTOR:
		_xdr_argument = (xdrproc_t) xdr_operationVector;
		_xdr_result = (xdrproc_t) xdr_resultVect;
		local = (char *(*)(char *, struct svc_req *)) _operate_vector_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (CALCULATOR, VEC_OPERATION);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, CALCULATOR, VEC_OPERATION, calculator_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (CALCULATOR, VEC_OPERATION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, CALCULATOR, VEC_OPERATION, calculator_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (CALCULATOR, VEC_OPERATION, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
