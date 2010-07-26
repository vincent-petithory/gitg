/*
 * gitg-terminal.c
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

#include "gitg-terminal.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define GITG_TERMINAL_GET_PRIVATE(object)(G_TYPE_INSTANCE_GET_PRIVATE((object), GITG_TYPE_TERMINAL, GitgTerminalPrivate))

struct _GitgTerminalPrivate
{
	GitgRepository *repository;
	VteTerminal *term;
};

G_DEFINE_TYPE(GitgTerminal, gitg_terminal, GTK_TYPE_VBOX);

static void on_term_exit(VteTerminal *term, gpointer *user_data);

static void
gitg_terminal_finalize (GObject *object)
{
	G_OBJECT_CLASS(gitg_terminal_parent_class)->finalize (object);
}

static void
gitg_terminal_class_init(GitgTerminalClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	
	object_class->finalize = gitg_terminal_finalize;

	g_type_class_add_private(object_class, sizeof(GitgTerminalPrivate));
}

static void
gitg_terminal_init(GitgTerminal *self)
{
	self->priv = GITG_TERMINAL_GET_PRIVATE (self);
	
	self->priv->term = g_object_ref(vte_terminal_new());
	gtk_container_add((GtkContainer*) self, (GtkWidget*) self->priv->term);
	
	g_signal_connect(self->priv->term, "child-exited", G_CALLBACK(on_term_exit), self);
}

void
gitg_terminal_init_term(GitgTerminal *terminal)
{
    g_return_if_fail(GITG_IS_TERMINAL(terminal));
	const char *directory;
	const char *shell;
	
	if (terminal->priv->repository && gitg_repository_exists(terminal->priv->repository))
	{
		GFile *dir = gitg_repository_get_git_dir(terminal->priv->repository);
		directory = g_file_get_path(g_file_get_parent(dir));
	}
	else
	{
		// fall back on $HOME if no repository defined
		directory = g_getenv ("HOME");
	}
	
	shell = g_getenv ("SHELL");
	vte_terminal_fork_command(VTE_TERMINAL (terminal->priv->term),
			shell ? shell : "/bin/sh",
			NULL, NULL, directory, 
			FALSE, FALSE, FALSE);
}

void 
gitg_terminal_set_repository(GitgTerminal *terminal, GitgRepository *repository)
{
	g_return_if_fail(GITG_IS_TERMINAL(terminal));
	g_return_if_fail(repository == NULL || GITG_IS_REPOSITORY(repository));

	if (terminal->priv->repository)
	{
		g_object_unref(terminal->priv->repository);
		terminal->priv->repository = NULL;
	}
	
	terminal->priv->repository = g_object_ref(repository);
	gitg_terminal_init_term(terminal);
	//g_object_notify(G_OBJECT(terminal), "repository");
}

static void
on_term_exit(VteTerminal *term, gpointer *user_data)
{
    g_return_if_fail(GITG_IS_TERMINAL(user_data));
    gitg_terminal_init_term(GITG_TERMINAL(user_data));
}
