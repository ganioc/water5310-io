/*
 * at_list.c
 *
 *  Created on: 2023 Feb 20
 *      Author: ruffman
 */

#include "at_struct.h"

#include "cmds.h"

struct AT_CALLBACK at_cmd_list[] = {
	{
		name:     "",
		hash:     0,
		test_cb:  NULL,
		read_cb:  NULL,
		write_cb: NULL,
		exec_cb:  cmd_at_exec
	},
	{
		name:     "VER",
		hash:     0,
		test_cb:  cmd_version_test,
		read_cb:  cmd_version_read,
		write_cb: cmd_version_write,
		exec_cb:  cmd_version_exec
	},
	{
		name:     "RST",
		hash:     0,
		test_cb:  NULL,
		read_cb:  NULL,
		write_cb: NULL,
		exec_cb:  cmd_rst_exec
	},
	{
		name:     "RESTORE",
		hash:     0,
		test_cb:  NULL,
		read_cb:  NULL,
		write_cb: NULL,
		exec_cb:  cmd_restore_exec
	},
	{
		name:     "CDATE",
		hash:     0,
		test_cb:  NULL,
		read_cb:  cmd_cdate_read,
		write_cb: cmd_cdate_write,
		exec_cb:  NULL
	},
	{
		name:     "IOVO",
		hash:     0,
		test_cb:  NULL,
		read_cb:  cmd_iovo_read,
		write_cb: cmd_iovo_write,
		exec_cb:  NULL
	},
	{
		name: "IORLY",
		hash: 0,
		test_cb: NULL,
		read_cb: cmd_iorly_read,
		write_cb: cmd_iorly_write,
		exec_cb: NULL
	},
	{
		name: "IOADCPWR",
		hash: 0,
		test_cb: NULL,
		read_cb: NULL,
		write_cb: cmd_ioadcpwr_write,
		exec_cb: NULL
	},
	{
		name: "IOADCMODE",
		hash: 0,
		test_cb: NULL,
		read_cb: cmd_ioadcmode_read,
		write_cb: cmd_ioadcmode_write,
		exec_cb: NULL
	},
	{
		name: "IOADCREAD",
		hash: 0,
		test_cb: NULL,
		read_cb: NULL,
		write_cb: cmd_ioadcread_write,
		exec_cb: NULL
	},
	{
		name: "IODIMODE",
		hash: 0,
		test_cb: NULL,
		read_cb: cmd_iodimode_read,
		write_cb: cmd_iodimode_write,
		exec_cb: NULL
	},
	{
		name: "IODICNT",
		hash: 0,
		test_cb: NULL,
		read_cb: NULL,
		write_cb: cmd_iodicnt_write,
		exec_cb: NULL
	},
	{
		name: "IODIREAD",
		hash: 0,
		test_cb: NULL,
		read_cb: NULL,
		write_cb: cmd_iodiread_write,
		exec_cb: NULL
	},
	{
		name: "IODO",
		hash: 0,
		test_cb: NULL,
		read_cb: cmd_iodo_read,
		write_cb: cmd_iodo_write,
		exec_cb: NULL
	},
	{
		name: "IOBTNSUB",
		hash: 0,
		test_cb: NULL,
		read_cb: cmd_iobtnsub_read,
		write_cb: cmd_iobtnsub_write,
		exec_cb: NULL
	},
	{
		name: "IOBTNUNSUB",
		hash: 0,
		test_cb: NULL,
		read_cb: NULL,
		write_cb: cmd_iobtnunsub_write,
		exec_cb: NULL
	},
	{
		name: "IORAINMODE",
		hash: 0,
		test_cb: NULL,
		read_cb: cmd_iorainmode_read,
		write_cb: cmd_iorainmode_write,
		exec_cb: NULL
	},
	{
		name: "IORAINCNT",
		hash: 0,
		test_cb: NULL,
		read_cb: NULL,
		write_cb: cmd_ioraincnt_write,
		exec_cb: NULL
	},
	{
		name: "IORAINREAD",
		hash: 0,
		test_cb: NULL,
		read_cb: NULL,
		write_cb: cmd_iorainread_write,
		exec_cb: NULL
	},
	{
		name: "INVOL",
		hash: 0,
		test_cb: NULL,
		read_cb: cmd_invol_read,
		write_cb: NULL,
		exec_cb: NULL
	},
	{
		name: "CGSN",
		hash: 0,
		test_cb: NULL,
		read_cb: NULL,
		write_cb: NULL,
		exec_cb: cmd_cgsn
	},
	{
		name: "IOLEDONOFF",
		hash: 0,
		test_cb: NULL,
		read_cb: cmd_ioledonoff_read,
		write_cb: cmd_ioledonoff_write,
		exec_cb: NULL
	},
	{
		name: "IOLEDBLINK",
		hash: 0,
		test_cb: NULL,
		read_cb: cmd_ioledblink_read,
		write_cb: cmd_ioledblink_write,
		exec_cb: NULL
		},
};

int NUM_AT_CALLBACK = sizeof(at_cmd_list)/sizeof(at_cmd_list[0]);
