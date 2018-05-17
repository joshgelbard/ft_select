/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:19:58 by jgelbard          #+#    #+#             */
/*   Updated: 2018/05/16 19:42:09 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		num_reqd_cols()
{
	return (2);
}

static t_arg	**argify(int argc, char **argv)
{
	int		i;
	t_arg	**args;
	t_arg	*g;

	i = 0;
	args = ft_memalloc(sizeof(*args) * (argc + 1));
	while (i < argc)
	{
		g = ft_memalloc(sizeof(*g));
		g->s = ft_strdup(argv[i]);
		g->len = ft_strlen(g->s);
		g->status = 0;
		g->idx = i;
		g->row = 0;
		g->col = 0;
		args[i] = g;
		++i;
	}
	return (args);
}

t_arg		*find_nondeleted(t_state *state, int i, int dir)
{
	t_arg	**all;
	t_arg	*g;

	all = state->all_args;
	i += dir;
	while (i >= 0 && i < state->argc)
	{
		g = all[i];
		if (!IS_DELETED(g))
			return (g);
		i += dir;
	}
	return (NULL);
}

t_arg		*arg_at(t_state *state, int r, int c)
{
	t_arg **all;
	t_arg	*g;

	all = state->all_args;
	while ((g = *all))
	{
		if (g->row == r && g->col == c)
			break;
		++all;
	}
	assert(g->row == r && g->col == c);
	return (g);
}

void		update_columns_view(t_state *state) // ..window info
{
	t_arg	**all;
	t_arg	*g;
	int		i;
	int		*widths;
	int		col_idx;

	all = state->all_args;
	state->ncols = num_reqd_cols(); // will depend on window height and num args
	i = 0;
	while (i < state->ncols)
		state->col_widths[i++] = -1;
	i = 0;
	while ((g = *all))
	{
		if (!IS_DELETED(g))
		{
			col_idx = i % state->ncols;
			if (g->len > state->col_widths[col_idx])
				state->col_widths[col_idx] = g->len;
			g->row = i / state->ncols;
			g->col = col_idx;
			++i;
		}
		++all;
	}
}

t_state			*init_state(int argc, char **argv, int fd)
{
	t_state		*state;

	state = ft_memalloc(sizeof(*state));
	state->all_args = argify(argc, argv);
	state->argc = argc;
	state->remaining = argc;
	state->hovered = state->all_args[0];
	HOVER(state->all_args[0]);
	state->ncols = 1;
	state->fd = fd;
	state->col_widths = ft_memalloc(sizeof(state->col_widths[0]) * argc);
	return (state);
}

void		move_cursor(t_state *state, int h, int v)
{
	int c_row;
	int c_col;
	int max_row;
	int max_col;

	c_row = state->hovered->row;
	c_col = state->hovered->col;
	c_row += v;
	c_col += h;
	max_row = state->remaining / state->ncols - 1;
	if (state->remaining % state->ncols > 0
			&& state->hovered->col < state->remaining % state->ncols)
		++max_row;
	max_col = state->hovered->row == max_row && state->hovered->col < state->remaining % state->ncols ?
		state->remaining % state->ncols - 1 :
		state->ncols - 1;
	if (v && c_row < 0)
		c_row = max_row;
	else if (v && c_row > max_row)
		c_row = 0;
	else if (h && c_col < 0)
		c_col = max_col;
	else if (h && c_col > max_col)
		c_col = 0;
	UNHOVER(state->hovered);
	state->hovered = arg_at(state, c_row, c_col);
	HOVER(state->hovered);
}
