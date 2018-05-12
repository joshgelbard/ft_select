#define DEBUG

#ifdef DEBUG
# include "dev_util.h"
# include <stdio.h>
char _buf[40];
struct termios g_oldterm;
# define _tputs(s) printf("%s", s)
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

static void basictest()
{
	_do("cl");
	_dogoto("cm", 22, 22);
	printf("here we are");
	_do("ho");
}

static void terminit(struct termios *new)
{
	tcgetattr(STDOUT_FILENO, new);
	tcgetattr(STDOUT_FILENO, &g_oldterm);
	new->c_lflag &= ~(ICANON | ECHO);
	new->c_lflag |= ISIG;
	_do("ti"); /* enter fullscreen mode */
	tcsetattr(STDOUT_FILENO, TCSANOW, new);
}

static void deinit(void)
{
	_do("te"); /* exit fullscreen mode */
	_do("me"); /* exit alternate text appearance modes */
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_oldterm);
}

int main(int argc, char **argv)
{
#define DEBUG // just a reminder
	char termbuf[2048];
	struct termios newterm;

	tgetent(termbuf, getenv("TERM"));
#ifdef DEBUG
	atexit(deinit);
#endif
	terminit(&newterm);
	_dogoto("cm", 22, 22);
	_do("im");
	puts("here we are");
	sleep(2);
}
