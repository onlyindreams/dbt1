/*
 * odbc_interaction_best_sellers.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 26 february 2002
 */

#ifndef _ODBC_INTERACTION_BEST_SELLERS_H_
#define _ODBC_INTERACTION_BEST_SELLERS_H_

#include "odbc_interaction.h"
#ifdef PHASE1
#include "eu.h"
#endif /* PHASE1 */

#define STMT_BEST_SELLERS \
	"CALL best_sellers(?, ?, " \
	"?, ?, ?, ?, ?, "\
	"?, ?, ?, ?, ?, "\
	"?, "\
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?, " \
	"?, ?, ?, ?)"

#ifdef PHASE1
int copy_in_best_sellers(struct eu_context_t *euc, union odbc_data_t *odbcd);
int copy_out_best_sellers(struct eu_context_t *euc, union odbc_data_t *odbcd);
#endif /* PHASE1 */

int execute_best_sellers(struct odbc_context_t *odbcc,
	union odbc_data_t *odbcd);

#endif /* _ODBC_INTERACTION_BEST_SELLERS_H_ */
