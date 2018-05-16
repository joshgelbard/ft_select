/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:19:58 by jgelbard          #+#    #+#             */
/*   Updated: 2018/05/16 03:15:40 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		print_at_location(char *s, int h, int v)
{
	int l = strlen(s);
	_dogoto("cm", h, v);
	ft_putstr(s);
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
