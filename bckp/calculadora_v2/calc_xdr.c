/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "calc.h"

bool_t
xdr_operation (XDR *xdrs, operation *objp)
{
	register int32_t *buf;

	 if (!xdr_float (xdrs, &objp->operator1))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->operator2))
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
		sizeof (float), (xdrproc_t) xdr_float))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->vec2, 3,
		sizeof (float), (xdrproc_t) xdr_float))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->operator))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_resultVect (XDR *xdrs, resultVect *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->vec, 3,
		sizeof (float), (xdrproc_t) xdr_float))
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
		 if (!xdr_resultVect (xdrs, &objp->operation_res_u.result))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}
