/* tm_interface.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 18 march 2002
 */

#include <errno.h>
#include <common.h>
#include <app_interface.h>
#include <_socket.h>
#include <app_txn_array.h>

extern struct app_txn_array app_admin_confirm_array;
extern struct app_txn_array app_admin_request_array;
extern struct app_txn_array app_best_sellers_array;
extern struct app_txn_array app_buy_confirm_array;
extern struct app_txn_array app_buy_request_array;
extern struct app_txn_array app_home_array;
extern struct app_txn_array app_new_products_array;
extern struct app_txn_array app_order_display_array;
extern struct app_txn_array app_order_inquiry_array;
extern struct app_txn_array app_product_detail_array;
extern struct app_txn_array app_search_request_array;
extern struct app_txn_array app_search_results_array;
extern struct app_txn_array app_shopping_cart_array;

int receive_transaction_packet(int s, struct QItem *TxnQItem)
{
	void *data;
	int length;
	int interaction_q_slot_id;
	int interaction;
	int rec;

	/* Receive transaction type. */
	if ( (rec=_receive(s, (void *) &interaction, sizeof(interaction))) == -1)
	{
		LOG_ERROR_MESSAGE("cannot receive interaction type");
		return W_ERROR;
	}
	if (rec==SOCKET_CLOSE) return SOCKET_CLOSE;

	TxnQItem->TxnType=interaction;
	/* Receive transaction data. */
	switch (interaction)
	{
		case ADMIN_CONFIRM:
			interaction_q_slot_id=PinSlot(&app_admin_confirm_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_admin_confirm_array.odbc_data_array[interaction_q_slot_id].admin_confirm_odbc_data.eb);
			length = sizeof(struct admin_confirm_t);
			break;
		case ADMIN_REQUEST:
			interaction_q_slot_id=PinSlot(&app_admin_request_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_admin_request_array.odbc_data_array[interaction_q_slot_id].admin_request_odbc_data.eb);
			length = sizeof(struct admin_request_t);
			break;
		case BEST_SELLERS:
			interaction_q_slot_id=PinSlot(&app_best_sellers_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_best_sellers_array.odbc_data_array[interaction_q_slot_id].best_sellers_odbc_data.eb);
			length = sizeof(struct best_sellers_t);
			break;
		case BUY_CONFIRM:
			interaction_q_slot_id=PinSlot(&app_buy_confirm_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_buy_confirm_array.odbc_data_array[interaction_q_slot_id].buy_confirm_odbc_data.eb);
			length = sizeof(struct buy_confirm_t);
			break;
		case BUY_REQUEST:
			interaction_q_slot_id=PinSlot(&app_buy_request_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_buy_request_array.odbc_data_array[interaction_q_slot_id].buy_request_odbc_data.eb);
			length = sizeof(struct buy_request_t);
			break;
		case HOME:
			interaction_q_slot_id=PinSlot(&app_home_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_home_array.odbc_data_array[interaction_q_slot_id].home_odbc_data.eb);
			length = sizeof(struct home_t);
			break; 
		case NEW_PRODUCTS:
			interaction_q_slot_id=PinSlot(&app_new_products_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_new_products_array.odbc_data_array[interaction_q_slot_id].new_products_odbc_data.eb);
			length = sizeof(struct new_products_t);
			break;
		case ORDER_DISPLAY:
			interaction_q_slot_id=PinSlot(&app_order_display_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_order_display_array.odbc_data_array[interaction_q_slot_id].order_display_odbc_data.eb);
			length = sizeof(struct order_display_t);
			break;
		case ORDER_INQUIRY:
			interaction_q_slot_id=PinSlot(&app_order_inquiry_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_order_inquiry_array.odbc_data_array[interaction_q_slot_id].order_inquiry_odbc_data.eb);
			length = sizeof(struct order_inquiry_t);
			break;
		case PRODUCT_DETAIL:
			interaction_q_slot_id=PinSlot(&app_product_detail_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_product_detail_array.odbc_data_array[interaction_q_slot_id].product_detail_odbc_data.eb);
			length = sizeof(struct product_detail_t);
			break;
		case SEARCH_REQUEST:
			interaction_q_slot_id=PinSlot(&app_search_request_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_search_request_array.odbc_data_array[interaction_q_slot_id].search_request_odbc_data.eb);
			length = sizeof(struct search_request_t);
			break;
		case SEARCH_RESULTS:
			interaction_q_slot_id=PinSlot(&app_search_results_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_search_results_array.odbc_data_array[interaction_q_slot_id].search_results_odbc_data.eb);
			length = sizeof(struct search_results_t);
			break;
		case SHOPPING_CART:
			interaction_q_slot_id=PinSlot(&app_shopping_cart_array);
			if (interaction_q_slot_id==-1)
			{
				LOG_ERROR_MESSAGE("PinSlot failed");
				return W_ERROR;
			}
			data = &(app_shopping_cart_array.odbc_data_array[interaction_q_slot_id].shopping_cart_odbc_data.eb);
			length = sizeof(struct shopping_cart_t);
			break;
	}
	TxnQItem->SlotID=interaction_q_slot_id;
	if (_receive(s, data, length) == -1)
	{
		LOG_ERROR_MESSAGE("cannot receive interaction data");
		return W_ERROR;
	}

	return W_OK;
}

int send_transaction_packet(int s, struct QItem TxnQItem)
{
	void *data;
	int length;
	int interaction;

	interaction=TxnQItem.TxnType;
	if (_send(s, &interaction, sizeof(int)) == -1)
	{
		LOG_ERROR_MESSAGE("cannot send interaction type");
		return W_ERROR;
	}
	switch (interaction)
	{
		case ADMIN_CONFIRM:
			data = &(app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb);
			length = sizeof(struct admin_confirm_t);
			break;
		case ADMIN_REQUEST:
			data = &(app_admin_request_array.odbc_data_array[TxnQItem.SlotID].admin_request_odbc_data.eb);
			length = sizeof(struct admin_request_t);
			break;
		case BEST_SELLERS:
			data = &(app_best_sellers_array.odbc_data_array[TxnQItem.SlotID].best_sellers_odbc_data.eb);
			length = sizeof(struct best_sellers_t);
			break;
		case BUY_CONFIRM:
			data = &(app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb);
			length = sizeof(struct buy_confirm_t);
			break;
		case BUY_REQUEST:
			data = &(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb);
			length = sizeof(struct buy_request_t);
			break;
		case HOME:
#ifdef DEBUG
			DEBUGMSG("thread_id%d: send pkg txntype %d, slot %d", pthread_self(), TxnQItem.TxnType, TxnQItem.SlotID);
			DEBUGMSG("thread_id%d: c_fname:%s, c_lname:%s", pthread_self(), app_home_array.odbc_data_array[TxnQItem.SlotID].home_odbc_data.eb.c_fname, app_home_array.odbc_data_array[TxnQItem.SlotID].home_odbc_data.eb.c_lname);
#endif
			data = &(app_home_array.odbc_data_array[TxnQItem.SlotID].home_odbc_data.eb);
			length = sizeof(struct home_t);
			break; 
		case NEW_PRODUCTS:
			data = &(app_new_products_array.odbc_data_array[TxnQItem.SlotID].new_products_odbc_data.eb);
			length = sizeof(struct new_products_t);
			break;
		case ORDER_DISPLAY:
			data = &(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb);
			length = sizeof(struct order_display_t);
			break;
		case ORDER_INQUIRY:
			data = &(app_order_inquiry_array.odbc_data_array[TxnQItem.SlotID].order_inquiry_odbc_data.eb);
			length = sizeof(struct order_inquiry_t);
			break;
		case PRODUCT_DETAIL:
			data = &(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb);
			length = sizeof(struct product_detail_t);
			break;
		case SEARCH_REQUEST:
			data = &(app_search_request_array.odbc_data_array[TxnQItem.SlotID].search_request_odbc_data.eb);
			length = sizeof(struct search_request_t);
			break;
		case SEARCH_RESULTS:
			data = &(app_search_results_array.odbc_data_array[TxnQItem.SlotID].search_results_odbc_data.eb);
			length = sizeof(struct search_results_t);
			break;
		case SHOPPING_CART:
			data = &(app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb);
			length = sizeof(struct shopping_cart_t);
			break;
	}
	if (_send(s, data, length) == -1)
	{
		LOG_ERROR_MESSAGE("cannot send interaction data, errno %d", errno);
		return W_ERROR;
	}

	/* free slot */
	switch (TxnQItem.TxnType)
	{
		case ADMIN_CONFIRM:
			FreeSlot(&app_admin_confirm_array, TxnQItem.SlotID);
			break;
		case ADMIN_REQUEST:
			FreeSlot(&app_admin_request_array, TxnQItem.SlotID);
			break;
		case BEST_SELLERS:
			FreeSlot(&app_best_sellers_array, TxnQItem.SlotID);
			break;
		case BUY_REQUEST:
			FreeSlot(&app_buy_request_array, TxnQItem.SlotID);
			break;
		case BUY_CONFIRM:
			FreeSlot(&app_buy_confirm_array, TxnQItem.SlotID);
			break;
		case HOME:
			FreeSlot(&app_home_array, TxnQItem.SlotID);
			break;
		case NEW_PRODUCTS:
			FreeSlot(&app_new_products_array, TxnQItem.SlotID);
			break;
		case ORDER_DISPLAY:
			FreeSlot(&app_order_display_array, TxnQItem.SlotID);
			break;
		case ORDER_INQUIRY:
			FreeSlot(&app_order_inquiry_array, TxnQItem.SlotID);
			break;
		case PRODUCT_DETAIL:
			FreeSlot(&app_product_detail_array, TxnQItem.SlotID);
			break;
		case SEARCH_REQUEST: 
			FreeSlot(&app_search_request_array, TxnQItem.SlotID);
			break;
		case SEARCH_RESULTS: 
			FreeSlot(&app_search_results_array, TxnQItem.SlotID);
			break;
		case SHOPPING_CART: 
			FreeSlot(&app_shopping_cart_array, TxnQItem.SlotID);
			break;
	}
	return W_OK;
}

