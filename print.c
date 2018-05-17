/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:19:58 by jgelbard          #+#    #+#             */
/*   Updated: 2018/05/16 19:48:38 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		print_at_location(char *s, int h, int v)
{
	static int fd;

	if (s == NULL)
		fd = h;
	else
	{
		int l = strlen(s);
		_dogoto("cm", h, v);
		ft_putstr_fd(s, fd);
	}
}

void		print_col(t_state *state, int col, int v)
{
	t_arg **all;
	t_arg *g;

	all = state->all_args;
	while (*all)
	{
		g = *all;
		if (!IS_DELETED(g) && g->col == col)
		{
			print_arg(g, v);
		}
		++all;
	}
}

int			write_state_fd(int c, t_state *init_state)
{
	static t_state	*state;

	if (init_state)
	{
		state = init_state;
		return (1);
	}
	return (write(state->fd, &c, 1));
}

void		print_arg(t_arg *g, int v)
{
	assert(!IS_DELETED(g));
	if (IS_SELECTED(g))
		_do("mr");
	if (IS_HOVERED(g))
		_do("us");
	print_at_location(g->s, v + g->col, g->row);
	_do("me");
	_do("ue");
}

void		print_state(t_state *state)
{
	int		i;
	int		v;

	i = 0;
	v = 0;
	while (i < state->ncols)
	{
		print_col(state, i, v);
		v += state->col_widths[i] + 1;
		++i;
	}
}
