/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:54:18 by jgelbard          #+#    #+#             */
/*   Updated: 2018/05/16 19:42:27 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "libft.h"
# define DEBUG

# ifdef DEBUG
#  include <stdio.h>
struct termios g_oldterm;
#  define _tputs(s) tputs(s, 1, writechar) 
#  define _tputsn(s, n) tputs(s, n, writechar)
#  define _cname(cmd) tgetstr(cmd, NULL)
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
# include <sys/ioctl.h>
# if __APPLE__
#  include <sys/ttycom.h>
# endif

#define FLAG_SELECTED 1
#define FLAG_HOVERED 2
#define FLAG_DELETED 4

#define IS_SELECTED(g) ((g->status) & FLAG_SELECTED)
#define IS_HOVERED(g) ((g->status) & FLAG_HOVERED)
#define IS_DELETED(g) ((g->status) & FLAG_DELETED)

#define SELECT(g) g->status |= FLAG_SELECTED
#define HOVER(g) g->status |= FLAG_HOVERED
#define DELETE(g) g->status = FLAG_DELETED

#define UNHOVER(g) g->status &= (~(FLAG_HOVERED))
#define TOGGLE_SELECT(g) g->status ^= FLAG_SELECTED

typedef struct		s_arg
{
	int				idx;
	int				row;
	int				col;
	int				len;
	char			*s;
	int				status;
}					t_arg;

typedef struct		s_args
{
	int				argc;
	t_arg			**args;
}					t_args;

typedef struct		s_state
{
	t_arg			**all_args;
	t_arg			**args;
	int				*col_widths;
	int				ncols;
	int				argc;
	int				remaining;
	int				fd;
	t_arg			*hovered;
}					t_state;

void	terminit(int *init_fd);
int		writechar(int);
int		write_state_fd(int c, t_state *init_state);
void	deinit(int *init_fd);
void	siglisten(void);
void	print_arg(t_arg *g, int v);
void	handle_signal(int sig);
void	loop(t_state *state);
void	basictest(void);
void	test_get_input(void);
void	print_at_location(char *s, int h, int v);
void	print_state(t_state *state);
struct s_args *init_args(int argc, char **argv);
t_state		*init_state(int argc, char **argv, int fd);
void		move_cursor(t_state *state, int h, int v);
void		update_columns_view(t_state *state); //...window info
t_arg		*find_nondeleted(t_state *state, int idx, int dir);
t_arg		*arg_at(t_state *state, int r, int c);

#endif
