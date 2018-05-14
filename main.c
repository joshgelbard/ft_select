#define DEBUG

#ifdef DEBUG
# include "dev_util.h"
# include <stdio.h>
char _buf[40];
struct termios g_oldterm;
# define ft_putchar putchar
# define _tputs(s) tputs(s, 1, ft_putchar) 
# define _tputsn(s, n) tputs(s, n, ft_putchar)
# define _cname(cmd) tgetstr(cmd, (char **)&_buf)
# define _do(cmd) _tputs(_cname(cmd))
# define _dogoto(cmd, h, v) _tputs(tgoto(_cname(cmd), h, v))
# include <assert.h>
#endif

#include <stdlib.h>
#include <termcap.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

void deinit(void);
void handle_signal(int);
void loop(void);
void basictest()
{
	_do("cl");
	_dogoto("cm", 22, 22);
	printf("here we are");
	_do("ho");
}

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

void handle_signal(int sig)
{

	static int is_terminating;
	psignal(sig);
	sleep(1);
	if (sig == SIGTERM || sig == SIGINT || sig == SIGQUIT || sig == SIGHUP)
	{
		if (is_terminating == 0)
		{
			is_terminating = 1;
			deinit();
			signal(sig, SIG_DFL);
		}
		raise(sig);
	}
	else if (sig == SIGCHLD)
	{
		puts("A CHILD APPEARS");
		;
	}
	else if (sig == SIGCONT)
	{
		puts("SIGCONT");
		signal(SIGTSTP, handle_signal);
		siglisten();
		loop();
		;
	}
	else if (sig == SIGTSTP)
	{
		puts("SIGTSTP");
		signal(SIGCONT, handle_signal);
		deinit();
		signal(sig, SIG_DFL);
		raise(sig);
	}
	/* window resizing stuff will likely happen here */
	else if (sig == SIGINFO)
	{
		puts("SIGINFO");
		;
	}
	else
	{
		puts("THIS DOES NOT HAPPEN");
		assert(0);
	}
}


void siglisten()
{
	for (int i = 1; i < 32; ++i)
	{
		if (i == SIGTERM
				|| i == SIGINT
				|| i == SIGHUP
				|| i == SIGCHLD
				|| i == SIGCONT
				|| i == SIGTSTP
				|| i == SIGINFO)
		signal(i, handle_signal);
	}
}

void test_get_input(void)
{
	static char buf[3];

	char *up = _cname("ku");
	char *dn = _cname("kd");
	char *rt = _cname("kr");
	char *le = _cname("kl");

	while (1)
	{
		bzero(buf, 3);
		read(STDIN_FILENO, buf, 3);
		print_raw(buf);
		if (!memcmp(up, buf, 3))
			printf("UP ARROW\n");
		else if (!memcmp(dn, buf, 3))
			printf("DOWN ARROW\n");
		else if (!memcmp(rt, buf, 3))
			printf("RIGHT ARROW\n");
		else if (!memcmp(le, buf, 3))
			printf("LEFT ARROW\n");
		else if (!memcmp("\E", buf, 2))
			printf("ESC\n");
	}
}

void deinit(void)
{
	_do("te"); /* exit fullscreen mode */
	_do("me"); /* exit alternate text appearance modes */
	_do("ei"); /* exit insert mode */
	ospeed = g_oldterm.c_ospeed;
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_oldterm);
}

void loop(void)
{
	terminit();
	_dogoto("cm", 22, 22);
	_do("im");
	puts("here we are");
	_do("ei");
	test_get_input();
}

int main(int argc, char **argv)
{
#define DEBUG // just a reminder
	char termbuf[2048];

	tgetent(termbuf, getenv("TERM"));
	siglisten();
	loop();
}
