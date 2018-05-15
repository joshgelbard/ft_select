all: main

%: %.c setup.c signal.c state.c print.c
	make -C libft
	gcc -Wall -Wno-unused-function -Wno-unused-variable -lft -L./libft -ltermcap $^
