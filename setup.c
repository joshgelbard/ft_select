/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:18:38 by jgelbard          #+#    #+#             */
/*   Updated: 2018/05/16 19:52:42 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void terminit(int *init_fd)
{
	static struct termios *new;
	static int fd;

	if (init_fd)
		fd = *init_fd;
	if (!new)
	{
		new = malloc(sizeof *new);
		tcgetattr(fd, new);
		tcgetattr(fd, &g_oldterm);
		new->c_lflag &= ~(ICANON | ECHO);
		new->c_cc[VMIN] = 1;
		new->c_cc[VTIME] = 0;
	}
	tcsetattr(fd, TCSADRAIN, new);
	PC = _cname("pc") ? *(_cname("pc")) : 0;
	BC = _cname("le");
	UP = _cname("up");
	
	ospeed = new->c_ospeed;
	_do("ti"); /* enter fullscreen mode */
	_do("ks"); /* interpret arrow keys */
	_do("vi"); /* make cursor disappear */
}

void deinit(int *init_fd)
{
	static int fd;
	if (init_fd)
		fd = *init_fd;
	_do("te"); /* exit fullscreen mode */
	_do("ke"); /* stop interpreting arrow keys */
	_do("ve"); /* bring back cursor */
	ospeed = g_oldterm.c_ospeed;
	tcsetattr(fd, TCSADRAIN, &g_oldterm);
}
