NAME = minishell
INCLUDE = ./liba.h
OBJS = $(SRCS:%.c=%.o)
FLAGS_W = -Wall -Wextra -Werror
FLAGS_LIB = -Iincludes
GREEN        := $(shell tput -Txterm setaf 2)
YELLOW       := $(shell tput -Txterm setaf 3)
LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
PURPLE       := $(shell tput -Txterm setaf 5)
BLUE         := $(shell tput -Txterm setaf 6)
RESET 		 := $(shell tput -Txterm sgr0)
SRCS			=	main.c \
					string_parsing.c \
					elements_parsing.c \
					enviroment_parse.c \
					execve.c \
					tilda_parse.c \
					./signal/signal_in_child.c \
					./signal/signal_in_parent.c \
					./pipes/pipes.c \
					./pipes/pipes_utils.c \
					./pipes/modified_functions.c \
					./pipes/modified_functions_else.c \
					./termcap/history.c \
					./termcap/term_navigation.c \
					./builtin/echo.c \
					./builtin/env.c \
					./termcap/utils.c \
					./termcap/term_utils.c \
					./builtin/pwd.c \
					./builtin/export.c \
					./builtin/cd.c \
					./builtin/exit.c \
					./builtin/unset.c \
					./gnl/get_next_line.c \
					./libfuncs/ft_itoa.c \
					./libfuncs/ft_strchr.c \
					./libfuncs/ft_putchar.c \
					./libfuncs/ft_strcpy.c \
					./libfuncs/ft_putnbr_fd.c \
					./libfuncs/ft_strjoin.c \
					./libfuncs/ft_strtrim.c \
					./libfuncs/ft_split.c \
					./libfuncs/ft_substr.c \
					./libfuncs/ft_strdup.c \
					./libfuncs/ft_atoi.c \
					./libfuncs/ft_strlen.c \
					./libfuncs/cmpp.c \
					./libfuncs/ft_calloc.c \
					./own_utils/print_error.c \
					./own_utils/utils.c \
					./own_utils/utils2.c \
					./own_utils/allocate_memory.c \
					./own_utils/free_memory.c \
					./own_utils/free_memory_else.c \
					./redirect/redirecting_utils.c \
					./redirect/redirecting.c \
					./struct_functions/struct_funcs.c \
					./struct_functions/sort_struct.c \

.PHONY: all clean fclean re run

all: $(NAME)
	@echo ✅ Ready

$(NAME): $(INCLUDE) $(OBJS)
	@echo '❎ Compiling...'`clang $(OBJS) -o $(NAME) -ltermcap`''

%.o: %.c $(INCLUDE)
	@echo '❎ Making objects${RESET}'`clang $(FLAGS_LIB) -c $< -o $@`''	

clean:
	@echo 'Cleaned'`rm -rf $(OBJS)`''

fclean: clean
	@echo 'Full cleaned'`rm -f $(NAME)`''

re: fclean all