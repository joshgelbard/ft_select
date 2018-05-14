#include "ft_select.h"

void basictest()
{
	_do("cl");
	_dogoto("cm", 22, 22);
	printf("here we are");
	_do("ho");
}

void handle_signal(int sig)
{
	static int is_terminating;
	psignal(sig, "");
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
		;
	}
	else if (sig == SIGCONT)
	{
		signal(SIGTSTP, handle_signal);
		siglisten();
		loop();
		;
	}
	else if (sig == SIGTSTP)
	{
		signal(SIGCONT, handle_signal);
		deinit();
		signal(sig, SIG_DFL);
		raise(sig);
	}
	/* window resizing stuff will likely happen here */
	else if (sig == SIGINFO)
	{
		;
	}
	else
	{
		puts("THIS DOES NOT HAPPEN");
		assert(0);
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
