/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termsetup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:18:38 by jgelbard          #+#    #+#             */
/*   Updated: 2018/05/14 20:14:06 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void terminit()
{
	static struct termios *new;

	if (!new)
	{
		new = malloc(sizeof *new);
		tcgetattr(STDOUT_FILENO, new);
		tcgetattr(STDOUT_FILENO, &g_oldterm);
		new->c_lflag &= ~(ICANON | ECHO);
		new->c_cc[VMIN] = 1;
		new->c_cc[VTIME] = 0;
	}
	PC = _cname("pc") ? *(_cname("pc")) : 0;
	BC = _cname("le");
	UP = _cname("up");
	ospeed = new->c_ospeed;
	_do("ti"); /* enter fullscreen mode */
	_do("ks"); /* interpret arrow keys */
	tcsetattr(STDOUT_FILENO, TCSADRAIN, new);
}

void deinit(void)
{
	_do("te"); /* exit fullscreen mode */
	_do("ke"); /* stop interpreting arrow keys */
	ospeed = g_oldterm.c_ospeed;
	tcsetattr(STDOUT_FILENO, TCSADRAIN, &g_oldterm);
}
