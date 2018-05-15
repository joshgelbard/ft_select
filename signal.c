/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 20:07:32 by jgelbard          #+#    #+#             */
/*   Updated: 2018/05/14 20:08:48 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void handle_signal(int sig)
{
#ifdef DEBUG
	psignal(sig, "");
#endif

	if (sig == SIGTERM || sig == SIGINT || sig == SIGQUIT || sig == SIGHUP)
	{
		deinit();
		exit(1);
	}
	else if (sig == SIGCONT)
	{
		siglisten();
		terminit();
		loop();
	}
	else if (sig == SIGTSTP)
	{
		deinit();
		signal(sig, SIG_DFL);
		raise(sig);
	}
	/* window resizing stuff will likely happen here */
	else if (sig == SIGINFO)
	{
		raise(sig);
	}
	else
	{
		puts("THIS DOES NOT HAPPEN");
		assert(0);
	}
}

void siglisten()
{
	signal(SIGTERM, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGCONT, handle_signal);
	signal(SIGTSTP, handle_signal);
	signal(SIGINFO, handle_signal);
	signal(SIGHUP, handle_signal);
	signal(SIGQUIT, handle_signal);
}
