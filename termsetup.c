/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termsetup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:18:38 by jgelbard          #+#    #+#             */
/*   Updated: 2018/05/14 14:19:52 by jgelbard         ###   ########.fr       */
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
	}
	PC = _cname("pc") ? *(_cname("pc")) : 0;
	BC = _cname("le");
	UP = _cname("up");
	ospeed = new->c_ospeed;
	_do("ti"); /* enter fullscreen mode */
	_do("ks"); /* allow arrow keys */
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, new);
}

void deinit(void)
{
	_do("te"); /* exit fullscreen mode */
	_do("me"); /* exit alternate text appearance modes */
	_do("ei"); /* exit insert mode */
	ospeed = g_oldterm.c_ospeed;
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_oldterm);
}

void siglisten()
{
	signal(SIGTERM, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGCHLD, handle_signal);
	signal(SIGCONT, handle_signal);
	signal(SIGTSTP, handle_signal);
	signal(SIGINFO, handle_signal);
	signal(SIGHUP, handle_signal);
	signal(SIGQUIT, handle_signal);
}
