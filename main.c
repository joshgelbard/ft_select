/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 02:02:25 by jgelbard          #+#    #+#             */
/*   Updated: 2018/05/16 03:13:54 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		writechar(int c)
{
	return (write(1, &c, 1));
}

int		handle_movement_key(t_state *state, char *buf)
{
	static char **dirs;
	int			match;

	if (!dirs)
	{
		dirs = ft_memalloc(sizeof(*dirs) * 4);
		dirs[0] = _cname("ku");
		dirs[1] = _cname("kr");
		dirs[2] = _cname("kd");
		dirs[3] = _cname("kl");
	}
	match = 0;
	if ((match = !ft_memcmp(dirs[0], buf, 3)))
		move_cursor(state, 0, -1);
	else if ((match = !ft_memcmp(dirs[1], buf, 3)))
		move_cursor(state, 1, 0);
	else if ((match = !ft_memcmp(dirs[2], buf, 3)))
		move_cursor(state, 0, 1);
	else if ((match = !ft_memcmp(dirs[3], buf, 3)))
		move_cursor(state, -1, 0);
	return (match);
}

int		handle_quit_key(t_state *state, char *buf)
{
	if (!ft_memcmp(buf, "\E", 2))
	{
		puts("ESC");
		sleep(1);
		return (1);
	}
	return (0);
}

int		handle_done_key(t_state *state, char *buf)
{
	if (!ft_memcmp(buf, "\n", 2))
	{
		puts("RETURN");
		sleep(1);
		return (1);
	}
	return (0);
}

int		handle_delete_key(t_state *state, char *buf)
{
	static char		*del;
	t_arg			*g;
	t_arg			*replace;

	if (!del)
		del = _cname("kD");
	if (!ft_memcmp(buf, del, 3) || !ft_memcmp(buf, "\b", 2))
	{
		if (state->remaining == 1)
		{
			deinit();
			exit(0);
		}
		g = state->hovered;
		;
		if (!(replace = find_nondeleted(state, g->idx, 1)))
			replace = find_nondeleted(state, g->idx, -1);
		state->hovered = replace;
		HOVER(replace);
		DELETE(g);
		state->remaining -= 1;
		g->row = -1;
		g->col = -1;
		return (1);
	}
	return (0);
}

int		handle_select_key(t_state *state, char *buf)
{
	if (!ft_memcmp(buf, " ", 2))
	{
		TOGGLE_SELECT(state->hovered);
		return (1);
	}
	return (0);
}

void loop(t_state *init_state)
{
	static char		buf[3];
	static t_state	*state;

	if (init_state)
		state = init_state;
	while (1)
	{
		ft_bzero(buf, sizeof(buf));
		_do("cl");
		update_columns_view(state);
		print_state(state);
		read(STDIN_FILENO, buf, sizeof(buf));
		handle_movement_key(state, (char *)buf) ||
		handle_select_key(state, (char *)buf) ||
		handle_delete_key(state, (char *)buf) ||
		handle_done_key(state, (char *)buf) ||
		handle_quit_key(state, (char *)buf);
	}
}

int main(int argc, char **argv)
{
#define DEBUG // just a reminder
	char termbuf[2048];
	t_state *state;

	if (argc < 2)
		return (0);
	tgetent(termbuf, getenv("TERM"));
	siglisten();
	terminit();
	state = init_state(argc - 1, argv + 1);
	update_columns_view(state);
	print_state(state);
	loop(state);
	deinit();
}
