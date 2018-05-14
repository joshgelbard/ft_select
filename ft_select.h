/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:54:18 by jgelbard          #+#    #+#             */
/*   Updated: 2018/05/14 14:14:23 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# define DEBUG

# ifdef DEBUG
#  include "dev_util.h"
#  include <stdio.h>
char _buf[40];
struct termios g_oldterm;
#  define ft_putchar putchar
#  define _tputs(s) tputs(s, 1, ft_putchar) 
#  define _tputsn(s, n) tputs(s, n, ft_putchar)
#  define _cname(cmd) tgetstr(cmd, (char **)&_buf)
#  define _do(cmd) _tputs(_cname(cmd))
#  define _dogoto(cmd, h, v) _tputs(tgoto(_cname(cmd), h, v))
#  include <assert.h>
# endif

# include <stdlib.h>
# include <termcap.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>

void terminit(void);
void deinit(void);
void siglisten(void);
void handle_signal(int sig);
void loop(void);
void basictest(void);
void test_get_input(void);

#endif
