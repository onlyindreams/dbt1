/*
 * odbc_interaction_search_request.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 28 february 2002
 */

#ifndef _ODBC_INTERACTION_SEARCH_REQUEST_H_
#define _ODBC_INTERACTION_SEARCH_REQUEST_H_

#ifdef PHASE1
#include <eu.h>
#endif /* PHASE1 */

#ifdef PHASE2
#include "app_interaction.h"
#endif /* PHASE2 */

#define STMT_SEARCH_REQUEST \
	"CALL GetPromoImages(?, " \
	"?, ?, ?, ?, ?, " \
	"?, ?, ?, ?, ?)"

#ifdef PHASE1
int copy_out_search_request(struct eu_context_t *euc, union odbc_data_t *odbcd);
#endif /* PHASE1 */

int execute_search_request(struct odbc_context_t *odbcc,
	union odbc_data_t *odbcd);

#endif /* _ODBC_INTERACTION_SEARCH_REQUEST_H_ */
