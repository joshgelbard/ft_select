all: main

%: %.c dev_util.c setup.c signal.c
	gcc -Wall -Wno-unused-function -Wno-unused-variable -ltermcap $^
