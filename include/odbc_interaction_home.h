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

#include <odbc_interaction.h>

#define STMT_HOME "CALL HOME(?,?,?,?,  ?,?,?,?,?,?,?,?,?,?)"

int execute_home(struct db_context_t *odbcc, struct home_t *data);

#endif /* _ODBC_INTERACTION_HOME_H_ */
