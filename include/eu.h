/*
 * eu.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 30 january 2002
 */

#ifndef _EU_H_
#define _EU_H_

#include <semaphore.h>

#include <odbc_interaction.h>

#include <common.h>

#define MIX_SHOPPING 0
#define MIX_BROWSING 1
#define MIX_ORDERING 2

#ifdef REALTIME_STATS
#define STAT_INTERVAL 30
#endif

struct eu_context_t
{
#ifdef PHASE1
	struct odbc_context_t odbcc;
	union odbc_data_t odbcd;
#ifdef SEARCH_RESULTS_CACHE
	int cache_s;
#endif
#endif /* PHASE1 */

#ifdef PHASE2
	int s;
#endif /* PHASE2 */

	int interaction; /* Current interaction. */
	int previous_interaction; /* The previous interaction. */
	int previous_search_interaction;
	/* indicate if it is the first interaction so that 'prepare_home' can
	 * decide if a new c_id need to be generated
	 */
	int first_interaction; 

	long long c_id;
	long long sc_id;

	struct admin_confirm_t admin_confirm_data;
	struct admin_request_t admin_request_data;
	struct best_sellers_t best_sellers_data;
	struct buy_confirm_t buy_confirm_data;
	struct buy_request_t buy_request_data;
	struct home_t home_data;
	struct new_products_t new_products_data;
	struct product_detail_t product_detail_data;
	struct order_display_t order_display_data;
	struct order_inquiry_t order_inquiry_data;
	struct search_request_t search_request_data;
	struct search_results_t search_results_data;
	struct shopping_cart_t shopping_cart_data;
};

/* Prototypes */

#ifdef PHASE1
#ifdef SEARCH_RESULTS_CACHE
int init_eus(char *sname, char *uname, char *auth, int eus,
	int interaction_mix, int rampuprate, int duration, double tt_mean,
	int item_scale, char *host, int port);
#else
int init_eus(char *sname, char *uname, char *auth, int eus,
	int interaction_mix, int ramptuprate, int duration, double tt_mean,
	int item_scale);
#endif
#endif /* PHASE1 */

#ifdef PHASE2
int init_eus(char *sname, int port, int eus,
	int interaction_mix, int ramptuprate, int duration, double tt_mean,
	int item_scale);
#endif /* PHASE2 */
int mark_logs(char *mark);

extern int customers;
extern sem_t running_eu_count;
extern sem_t running_interactions[INTERACTION_TOTAL];
extern int altered;

#endif /* _EU_H_ */
