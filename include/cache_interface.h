/* app_interface.h 
 * appServer interface for sending/receiving packet to/from eb
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */
#ifndef _CACHE_INTERFACE_H
#define _CACHE_INTERFACE_H_
#include <errno.h>
#include <common.h>
#include <_socket.h>
#include <odbc_interaction.h>

int receive_search_results_request(int s, struct search_results_t *search_results_request);
int send_search_results_response(int s,  struct search_results_t *search_results_response);
#endif
