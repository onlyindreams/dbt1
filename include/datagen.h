/*
 * datagen.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 11 january 2002
 */

#define DELIMITER ','

void gen_addresses(int ebs);
void gen_authors(int items);
void gen_customers(int ebs);
void gen_items(int items);
void gen_orders(int ebs, int items);
