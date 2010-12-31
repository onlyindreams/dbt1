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

/* if not on Windows, just define only W_ERROR macro. */
#ifdef WINDOWS
 #include <WINDOWS.H>
#else
 #define W_ERROR 0
#endif

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
int _db_connect(struct db_context_t *odbcc);
int _db_disconnect(struct db_context_t *odbcc);
int odbc_error(char *filename, int line, SQLSMALLINT handle_type,
	SQLHANDLE handle);
int _db_init(const char *, const char *, const char *, const char *, const char *);
int commit_transaction(struct db_context_t *dbc);
int rollback_transaction(struct db_context_t *dbc);

#endif /* _ODBC_INTERACTION_H_ */
