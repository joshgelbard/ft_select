#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termcap.h>
#include <unistd.h>

/*
 * credit github @hio -- https://github.com/hio/c-tty-termcap-sample/blob/master/prog.c
 */

void print_raw(const char* s)
{
	if (!s)
		return ;
	printf("\"");
	for(int i = 0; s[i]; i++)
		if( s[i] == '\033' )
			printf("\\E");
		else if( s[i] == '\\' )
			printf("\\\\");
		else if( s[i] >= '\x21' && s[i] <= '\x7E' )
			printf("%c", s[i]);
		else
			printf("\\x%02x", (unsigned char)s[i]);
	printf("\"\n");
}
