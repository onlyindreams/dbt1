/*
 * odbc_interaction_home.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 18 february 2002
 */

#ifndef _ODBC_INTERACTION_HOME_H_
#define _ODBC_INTERACTION_HOME_H_

#ifdef PHASE1
#include "eu.h"
#endif

#ifdef PHASE2
#include "app_interaction.h"
#endif /* PHASE2 */

#define STMT_HOME "CALL HOME(?,?,?,?,  ?,?,?,?,?,?,?,?,?,?)"

#ifdef PHASE1
int copy_in_home(struct eu_context_t *euc, union odbc_data_t *odbcd);
int copy_out_home(struct eu_context_t *euc, union odbc_data_t *odbcd);
#endif /* PHASE1 */

int execute_home(struct odbc_context_t *odbcc, union odbc_data_t *odbcd);

#endif /* _ODBC_INTERACTION_HOME_H_ */
