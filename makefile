all: main

%: %.c dev_util.c
	gcc -Wall -ltermcap $^
