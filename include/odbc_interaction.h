/*
 * odbc_interaction.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */

#ifndef _ODBC_INTERACTION_H_
#define _ODBC_INTERACTION_H_

/* comment the next line out if unixODBC is used */
#include <WINDOWS.H>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

#include <common.h>
#include <interaction_data.h>

#define LOG_ODBC_ERROR(type, handle) odbc_error(__FILE__, __LINE__, type, handle)

struct db_context_t
{
	SQLHDBC hdbc;
	SQLHSTMT hstmt;
};

/* Prototypes */
int odbc_connect(struct db_context_t *odbcc);
int odbc_disconnect(struct db_context_t *odbcc);
int odbc_error(char *filename, int line, SQLSMALLINT handle_type,
	SQLHANDLE handle);
int odbc_init(char *sname, char *uname, char *auth);

#endif /* _ODBC_INTERACTION_H_ */
