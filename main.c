#include "ft_select.h"

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
	test_get_input();
}

int main(int argc, char **argv)
{
#define DEBUG // just a reminder

	char termbuf[2048];

	tgetent(termbuf, getenv("TERM"));
	siglisten();
	terminit();
	loop();
}
