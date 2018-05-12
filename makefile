all: main

%: %.c dev_util.c
	gcc -Wall -Wno-unused-function -Wno-unused-variable -ltermcap $^
