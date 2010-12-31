/*
 * pgsql_interaction.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright          Open Source Development Lab, Inc.
 * History: 
 * Aug-2003 Created by Satoshi Nagayasu & Hideyuki Kawashima &
 *                    Sachi Osawa & Hirokazu Kondo & Satoru Satake
 *
 * $Id$
 */

#include <string.h>
#include <stdarg.h>
#include <pthread.h>

#include <libpq_interaction.h>

pthread_mutex_t db_source_mutex = PTHREAD_MUTEX_INITIALIZER;

char servername[32]="localhost";
char dbname[32]="DBT1";
/* use default port */
char dbport[32]="5432";
char username[32]="pgsql";
char authentication[32]="pgsql";

int _db_connect(struct db_context_t *dbc)
{
	const char *conninfo;
	char tmp[256];
	/* Allocate connection handles. */
	pthread_mutex_lock(&db_source_mutex);

//	dbc->conn = PQsetdbLogin(servername, dbport, NULL, NULL, dbname,
//					 username, authentication);
	sprintf(tmp, "host = %s dbname = %s port = %s", servername, dbname, dbport);
	conninfo = tmp;
	//dbc->conn = PQsetdb(servername, "5432", NULL, NULL, "DBT1");
	dbc->conn = PQconnectdb(conninfo);

	if ( PQstatus(dbc->conn)==CONNECTION_BAD )
	{
		pgsql_error(dbc->conn);
		fprintf(stderr, "connect failed.\n");
		PQfinish(dbc->conn);
		return ERROR;
	}

	fprintf(stderr, "connection established.\n");

	pthread_mutex_unlock(&db_source_mutex);

	return OK;
}

/*
 * Disconnect from the database and free the connection handle.
 * Note that we create the environment handle in odbc_connect() but
 * we don't touch it here.
 */
int
_db_disconnect(struct db_context_t *dbc)
{
	pthread_mutex_lock(&db_source_mutex);

	PQfinish(dbc->conn);

	pthread_mutex_unlock(&db_source_mutex);
	return OK;
}

/* Print out all errors messages generated to the error log file. */
int
pgsql_error(PGconn *conn)
{
	char msg[1024];

	snprintf(msg, sizeof(msg), "(backendPID=%d) %s",
			 PQbackendPID(conn), PQerrorMessage(conn));

	LOG_ERROR_MESSAGE(msg);

	return OK;
}

int
_db_init(const char *shost, const char *port, const char *instance, const char *uname, const char *auth)
{
	/* Set the database connect string, username and password. */
	if (shost != NULL) { strcpy(servername, shost); }
	if (port != NULL) { strcpy(dbport, port); }
	if (instance != NULL) { strcpy(dbname, instance); }
	if (uname != NULL) { strcpy(username, uname); }
	if (auth != NULL) { strcpy(authentication, auth); }

	return OK;
}

PGresult *
pgsql_execute(PGconn *con, const char *stmt, ...)
{
	va_list ap;
	char buf[10240];
	int len;

//	fprintf(stderr, "STMT: %s\n", stmt);

	va_start(ap, stmt);
	len = vsnprintf(buf, sizeof(buf), stmt, ap);
	va_end(ap);

	if ( len>=sizeof(buf) )
	{
		LOG_ERROR_MESSAGE("ERROR: query buffer overflow.\n");
		return NULL;
	}
	else if ( len < 0 )
	{
		LOG_ERROR_MESSAGE("ERROR: vsnprintf() failed.\n");
		return NULL;
	}

	//fprintf(stderr, "=== QUERY ===\n%s\n", buf);

	return PQexec(con, buf);
}

int commit_transaction(struct db_context_t *dbc)
{
	PGresult *res;

	res = PQexec(dbc->conn, "COMMIT");
	if ( PQresultStatus(res)!=PGRES_COMMAND_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}

	PQclear(res);

	return OK;
}

int rollback_transaction(struct db_context_t *dbc)
{
	PGresult *res;

	res = PQexec(dbc->conn, "ROLLBACK");
	if ( PQresultStatus(res)!=PGRES_COMMAND_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}

	PQclear(res);
	return OK;
}
