NAME=ft_select

all: $(NAME)

$(NAME): main.c setup.c signal.c state.c print.c
	git submodule update --init
	make -C libft
	gcc -Wall -Wextra -Llibft -Ilibft -o $@ $^ -lft -ltermcap
