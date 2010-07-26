/*
 * gitg-terminal.h
 * This file is part of gitg - git repository viewer
 *
 * Copyright (C) 2010 - Vincent Petithory
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, 
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GITG_TERMINAL_H__
#define __GITG_TERMINAL_H__

#include <gtk/gtk.h>
#include <vte/vte.h>
#include <libgitg/gitg-repository.h>

G_BEGIN_DECLS

#define GITG_TYPE_TERMINAL			(gitg_terminal_get_type ())
#define GITG_TERMINAL(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), GITG_TYPE_TERMINAL, GitgTerminal))
#define GITG_TERMINAL_CONST(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), GITG_TYPE_TERMINAL, GitgTerminal const))
#define GITG_TERMINAL_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass), GITG_TYPE_TERMINAL, GitgTerminalClass))
#define GITG_IS_TERMINAL(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GITG_TYPE_TERMINAL))
#define GITG_IS_TERMINAL_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), GITG_TYPE_TERMINAL))
#define GITG_TERMINAL_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), GITG_TYPE_TERMINAL, GitgTerminalClass))

typedef struct _GitgTerminal		GitgTerminal;
typedef struct _GitgTerminalClass		GitgTerminalClass;
typedef struct _GitgTerminalPrivate	GitgTerminalPrivate;

struct _GitgTerminal {
	GtkVBox parent;

	GitgTerminalPrivate *priv;
};

struct _GitgTerminalClass {
	GtkVBoxClass parent_class;
};

GType gitg_terminal_get_type (void) G_GNUC_CONST;
void gitg_terminal_set_repository(GitgTerminal *terminal, GitgRepository *repository);
void gitg_terminal_init_term(GitgTerminal *terminal);

G_END_DECLS

#endif /* __GITG_TERMINAL_H__ */
