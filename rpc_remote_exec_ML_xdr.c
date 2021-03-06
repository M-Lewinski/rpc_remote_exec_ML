/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "rpc_remote_exec_ML.h"

bool_t
xdr_runExecStructRequest (XDR *xdrs, runExecStructRequest *objp)
{
	register int32_t *buf;


	if (xdrs->x_op == XDR_ENCODE) {
		buf = XDR_INLINE (xdrs, 4 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->dataSize))
				 return FALSE;
			 if (!xdr_u_long (xdrs, &objp->ID))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageNR))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageType))
				 return FALSE;

		} else {
		IXDR_PUT_LONG(buf, objp->dataSize);
		IXDR_PUT_U_LONG(buf, objp->ID);
		IXDR_PUT_LONG(buf, objp->packageNR);
		IXDR_PUT_LONG(buf, objp->packageType);
		}
		 if (!xdr_string (xdrs, &objp->data, ~0))
			 return FALSE;
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		buf = XDR_INLINE (xdrs, 4 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->dataSize))
				 return FALSE;
			 if (!xdr_u_long (xdrs, &objp->ID))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageNR))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageType))
				 return FALSE;

		} else {
		objp->dataSize = IXDR_GET_LONG(buf);
		objp->ID = IXDR_GET_U_LONG(buf);
		objp->packageNR = IXDR_GET_LONG(buf);
		objp->packageType = IXDR_GET_LONG(buf);
		}
		 if (!xdr_string (xdrs, &objp->data, ~0))
			 return FALSE;
	 return TRUE;
	}

	 if (!xdr_int (xdrs, &objp->dataSize))
		 return FALSE;
	 if (!xdr_u_long (xdrs, &objp->ID))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->packageNR))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->packageType))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->data, ~0))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_runExecStructResponse (XDR *xdrs, runExecStructResponse *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->lastCorrectPackageNR))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_getExecStructRequest (XDR *xdrs, getExecStructRequest *objp)
{
	register int32_t *buf;


	if (xdrs->x_op == XDR_ENCODE) {
		buf = XDR_INLINE (xdrs, 4 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_u_long (xdrs, &objp->ID))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageNR))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageNRFromType))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageType))
				 return FALSE;
		} else {
			IXDR_PUT_U_LONG(buf, objp->ID);
			IXDR_PUT_LONG(buf, objp->packageNR);
			IXDR_PUT_LONG(buf, objp->packageNRFromType);
			IXDR_PUT_LONG(buf, objp->packageType);
		}
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		buf = XDR_INLINE (xdrs, 4 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_u_long (xdrs, &objp->ID))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageNR))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageNRFromType))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageType))
				 return FALSE;
		} else {
			objp->ID = IXDR_GET_U_LONG(buf);
			objp->packageNR = IXDR_GET_LONG(buf);
			objp->packageNRFromType = IXDR_GET_LONG(buf);
			objp->packageType = IXDR_GET_LONG(buf);
		}
	 return TRUE;
	}

	 if (!xdr_u_long (xdrs, &objp->ID))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->packageNR))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->packageNRFromType))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->packageType))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_getExecStructResponse (XDR *xdrs, getExecStructResponse *objp)
{
	register int32_t *buf;


	if (xdrs->x_op == XDR_ENCODE) {
		buf = XDR_INLINE (xdrs, 4 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->dataSize))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageNR))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageType))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->end))
				 return FALSE;

		} else {
		IXDR_PUT_LONG(buf, objp->dataSize);
		IXDR_PUT_LONG(buf, objp->packageNR);
		IXDR_PUT_LONG(buf, objp->packageType);
		IXDR_PUT_LONG(buf, objp->end);
		}
		 if (!xdr_string (xdrs, &objp->data, ~0))
			 return FALSE;
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		buf = XDR_INLINE (xdrs, 4 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->dataSize))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageNR))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->packageType))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->end))
				 return FALSE;

		} else {
		objp->dataSize = IXDR_GET_LONG(buf);
		objp->packageNR = IXDR_GET_LONG(buf);
		objp->packageType = IXDR_GET_LONG(buf);
		objp->end = IXDR_GET_LONG(buf);
		}
		 if (!xdr_string (xdrs, &objp->data, ~0))
			 return FALSE;
	 return TRUE;
	}

	 if (!xdr_int (xdrs, &objp->dataSize))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->packageNR))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->packageType))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->end))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->data, ~0))
		 return FALSE;
	return TRUE;
}
