/*
 * load_db_proc.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *		    Open Source Development Lab, Inc.
 *
 * 19 february 2002
 */

#include <stdio.h>
#include "odbc_interaction.h"
#include "common.h"
#include <sql.h>
#include <sqlext.h>

/*
 * This program loads stored procedure files that are too large to be loaded
 * by repmcli.
 */
int main(int argc, char *argv[])
{
	FILE *dbproc_file;
	SQLRETURN rc;
	SQLHSTMT hstmt;
	SQLHDBC hdbc;
	SQLHENV henv   = SQL_NULL_HENV;
	
	/* 100KB should be big enough. */
	char dbproc[102400]; 
	int i;
	char sname[32], uname[32], auth[32];

	if (argc < 5)
	{
		printf("usage: %s <servername> <uname> <password> <db_procedure_name>\n", argv[0]);
		return 1;
	}

	strcpy(sname, argv[1]);
	strcpy(uname, argv[2]);
	strcpy(auth, argv[3]);
	init_common();

	dbproc_file = fopen(argv[4], "r");
	if (!dbproc_file)
	{
		printf("cannot open %s\n", argv[4]);
		return 4;
	}
	printf("opened %s\n", argv[4]);

	i = 0;
	while ((dbproc[i] = getc(dbproc_file)) != EOF)
	{
		++i;
	}
	dbproc[i] = '\0';
	printf("read %s\n", argv[4]);

	/* allocate environment handle*/
	rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ERROR_MESSAGE("alloc env handle failed");
		return W_ERROR;
	}

	rc = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_DBC, hdbc);
		return W_ERROR;
	}

	/* Open connection to the database. */
	rc = SQLConnect(hdbc, sname, SQL_NTS,
		uname, SQL_NTS, auth, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_DBC, hdbc);
		return W_ERROR;
	}

	/* allocate statement handle*/
	rc = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, hstmt);
		return W_ERROR;
	}

	rc = SQLPrepare(hstmt, dbproc, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, hstmt);
		printf("prepare failed\n");
		return 5;
	}

	/* Load stored procedure. */
	rc = SQLExecute(hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, hstmt);
		printf("load failed\n");
		return W_ERROR;
	}
	printf("loaded %s\n", argv[4]);

	return 0;
}
