/*
 * odbc_interaction_admin_confirm.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 1 march 2002
 */

#ifndef _ODBC_INTERACTION_ADMIN_CONFIRM_H_
#define _ODBC_INTERACTION_ADMIN_CONFIRM_H_

#ifdef PHASE1
#include <eu.h>
#endif /* PHASE1 */

#ifdef PHASE2
#include "app_interaction.h"
#endif /* PHASE2 */

#define STMT_ADMIN_CONFIRM \
	"CALL admin_confirm(?, ?, ?, ?, ?, ?, ?, ?, " \
	"?, ?, ?, ?, ?, ?, ?, ?)"

#ifdef PHASE1
int copy_in_admin_confirm(struct eu_context_t *euc, union odbc_data_t *odbcd);
int copy_out_admin_confirm(struct eu_context_t *euc, union odbc_data_t *odbcd);
#endif /* PHASE1 */

int execute_admin_confirm(struct odbc_context_t *odbcc,
	union odbc_data_t *odbcd);

#endif /* _ODBC_INTERACTION_ADMIN_CONFIRM_H_ */
