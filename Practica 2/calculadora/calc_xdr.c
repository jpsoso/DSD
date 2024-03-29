/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "calc.h"

bool_t
xdr_operation (XDR *xdrs, operation *objp)
{
	register int32_t *buf;

	 if (!xdr_double (xdrs, &objp->operator1))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->operator2))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->operator))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_operationVector (XDR *xdrs, operationVector *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->vec1, 3,
		sizeof (double), (xdrproc_t) xdr_double))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->vec2, 3,
		sizeof (double), (xdrproc_t) xdr_double))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->operator))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Result (XDR *xdrs, Result *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->vec, 3,
		sizeof (double), (xdrproc_t) xdr_double))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->resultado))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_operation_res (XDR *xdrs, operation_res *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->errnum))
		 return FALSE;
	switch (objp->errnum) {
	case 0:
		 if (!xdr_Result (xdrs, &objp->operation_res_u.result))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}
