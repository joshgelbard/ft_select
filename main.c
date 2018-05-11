#define DEBUG

#ifdef DEBUG
# include "dev_util.h"
# include <stdio.h>
char _buf[40];
# define _tputs(s) printf("%s", s)
# define _cname(cmd) tgetstr(cmd, (char **)&_buf)
# define _do(cmd) _tputs(_cname(cmd))
# define _dogoto(cmd, h, v) _tputs(tgoto(_cname(cmd), h, v))
#endif

#include <stdlib.h>
#include <termcap.h>
#include <string.h>

static void basictest()
{
	_do("cl");
	_dogoto("cm", 22, 22);
	printf("here we are");
	_do("ho");
}

int main()
{
#define DEBUG // just a reminder
	char termbuf[2048];
	tgetent(termbuf, getenv("TERM"));
	basictest();
}
