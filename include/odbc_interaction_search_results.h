/*
 * odbc_interaction_search_results.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 26 february 2002
 */

#ifndef _ODBC_INTERACTION_SEARCH_RESULTS_H_
#define _ODBC_INTERACTION_SEARCH_RESULTS_H_

#include "odbc_interaction.h"
#ifdef PHASE1
#include "eu.h"
#endif /* PHASE1 */

#define STMT_SEARCH_RESULTS_AUTHOR \
	"CALL search_results_author(?, " \
    "?, " \
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

#define STMT_SEARCH_RESULTS_SUBJECT \
	"CALL search_results_subject(?, " \
    "?, " \
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

#define STMT_SEARCH_RESULTS_TITLE \
	"CALL search_results_title(?, " \
    "?, " \
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
int copy_in_search_results(struct eu_context_t *euc, union odbc_data_t *odbcd);
int copy_out_search_results(struct eu_context_t *euc, union odbc_data_t *odbcd);
#endif /* PHASE1 */

int execute_search_results(struct odbc_context_t *odbcc, union odbc_data_t *odbcd);

#endif /* _ODBC_INTERACTION_SEARCH_RESULTS_H_ */
