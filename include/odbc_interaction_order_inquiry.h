/*
 * odbc_interaction_order_inquiry.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */

#ifndef _ODBC_INTERACTION_ORDER_INQUIRY_H 
#define _ODBC_INTERACTION_ORDER_INQUIRY_H

#ifdef PHASE1
#include <eu.h>
#endif /* PHASE1 */

#ifdef PHASE2
#include "app_interaction.h"
#endif /* PHASE2 */

#define STMT_ORDER_INQUIRY "CALL order_inquiry(?,?)"

#ifdef PHASE1
int copy_in_order_inquiry(struct eu_context_t *euc, union odbc_data_t *odbcd);
int copy_out_order_inquiry(struct eu_context_t *euc, union odbc_data_t *odbcd);
#endif /* PHASE1 */

int execute_order_inquiry(struct odbc_context_t *odbcc,
	union odbc_data_t *odbcd);

#endif /* _ODBC_INTERACTION_ORDER_INQUIRY_H */
