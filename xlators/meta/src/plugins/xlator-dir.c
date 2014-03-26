/*
   Copyright (c) 2014 Red Hat, Inc. <http://www.redhat.com>
   This file is part of GlusterFS.

   This file is licensed to you under your choice of the GNU Lesser
   General Public License, version 3 or any later version (LGPLv3 or
   later), or the GNU General Public License, version 2 (GPLv2), in all
   cases as published by the Free Software Foundation.
*/

#ifndef _CONFIG_H
#define _CONFIG_H
#include "config.h"
#endif

#include "xlator.h"
#include "defaults.h"

#include "meta-mem-types.h"
#include "meta.h"
#include "meta-hooks.h"


static struct meta_dirent xlator_dir_dirents[] = {
	DOT_DOTDOT,

	{ .name = "view",
	  .type = IA_IFDIR,
	  .hook = meta_view_dir_hook,
	},
	{ .name = "type",
	  .type = IA_IFREG,
	  .hook = meta_type_file_hook,
	},
	{ .name = "name",
	  .type = IA_IFREG,
	  .hook = meta_name_file_hook,
	},
	{ .name = "subvolumes",
	  .type = IA_IFDIR,
	  .hook = meta_subvolumes_dir_hook,
	},
	{ .name = "options",
	  .type = IA_IFDIR,
	  .hook = meta_options_dir_hook,
	},
	{ .name = NULL }
};


static struct meta_ops xlator_dir_ops = {
	.fixed_dirents = xlator_dir_dirents
};


int
meta_xlator_dir_hook (call_frame_t *frame, xlator_t *this, loc_t *loc,
		      dict_t *xdata)
{
	glusterfs_graph_t *graph = NULL;
	xlator_t *xl = NULL;

	graph = meta_ctx_get (loc->parent, this);

	xl = xlator_search_by_name (graph->first, loc->name);

	meta_ctx_set (loc->inode, this, xl);

	meta_ops_set (loc->inode, this, &xlator_dir_ops);

	return 0;
}