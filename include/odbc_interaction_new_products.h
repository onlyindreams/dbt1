/*
 * odbc_interaction_new_products.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 21 february 2002
 */

#ifndef _ODBC_INTERACTION_NEW_PRODUCTS_H_
#define _ODBC_INTERACTION_NEW_PRODUCTS_H_

#include <odbc_interaction.h>

#define STMT_NEW_PRODUCTS \
	"CALL new_products(?, ?, " \
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

int execute_new_products(struct db_context_t *odbcc,
	struct new_products_t *data);

#endif /* _ODBC_INTERACTION_NEW_PRODUCTS_H_ */
