/*
 * Copyright (C) 2001-2003 FhG Fokus
 * Copyright (C) 2008 1&1 Internet AG
 *
 * This file is part of Kamailio, a free SIP server.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Kamailio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Kamailio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*! \file
 *  \brief DB_POSTGRES :: Core
 *  \ingroup db_postgres
 *  Module: \ref db_postgres
 */

/*! \defgroup db_postgres DB_POSTGRES :: the PostgreSQL driver for Kamailio
 *  \brief The Kamailio database interface to the PostgreSQL database
 *  - http://www.postgresql.org
 *
 */

#include <stdio.h>
#include "../../core/sr_module.h"
#include "../../lib/srdb1/db_con.h"
#include "../../lib/srdb1/db.h"
#include "../../lib/srdb1/db_query.h"
#include "km_dbase.h"
#include "db_postgres.h"


/*MODULE_VERSION*/

/*
 * PostgreSQL database module interface
 */

static cmd_export_t cmds[] = {
		{"db_bind_api", (cmd_function)db_postgres_bind_api, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}};


struct module_exports kam_exports = {
		"db_postgres",		  /* module name*/
		DEFAULT_DLFLAGS,	  /* dlopen flags */
		cmds,				  /* exported functions */
		0,					  /* exported parameters */
		0,					  /* exported rpc functions */
		0,					  /* exported pseudo-variables */
		0,					  /* response function*/
		km_postgres_mod_init, /* module init function */
		0,					  /* per-child init function */
		0					  /* module destroy function */
};


int km_postgres_mod_init(void)
{
	return 0;
}

int db_postgres_bind_api(db_func_t *dbb)
{
	if(dbb == NULL)
		return -1;

	memset(dbb, 0, sizeof(db_func_t));

	dbb->use_table = db_postgres_use_table;
	dbb->init = db_postgres_init;
	dbb->init2 = db_postgres_init2;
	dbb->close = db_postgres_close;
	dbb->query = db_postgres_query;
	dbb->fetch_result = db_postgres_fetch_result;
	dbb->raw_query = db_postgres_raw_query;
	dbb->free_result = db_postgres_free_result;
	dbb->insert = db_postgres_insert;
	dbb->insert_update = db_postgres_insert_update;
	dbb->delete = db_postgres_delete;
	dbb->update = db_postgres_update;
	dbb->replace = db_postgres_replace;
	dbb->affected_rows = db_postgres_affected_rows;
	dbb->start_transaction = db_postgres_start_transaction;
	dbb->end_transaction = db_postgres_end_transaction;
	dbb->abort_transaction = db_postgres_abort_transaction;
	dbb->query_lock = db_postgres_query_lock;
	dbb->raw_query_async = db_postgres_raw_query_async;
	dbb->insert_async = db_postgres_insert_async;

	return 0;
}
