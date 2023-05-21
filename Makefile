CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g
LIBC	= ar -rc
RM		= rm -f
NAME	= minishell
SRC		= main.c \
			ft_split.c \
			libft_helpers.c \
			builtins/ft_cd.c \
			builtins/ft_echo.c \
			builtins/ft_env.c \
			builtins/ft_pwd.c \
			builtins/ft_unset.c \
			list_utils.c \
			builtins/ft_export.c \
			builtins/ft_error.c \
			builtins/ft_exit.c \
			execution/pipes.c \
			execution/heredoc.c \
			add_to_list.c \
			test_split.c \
			creat_list_command.c \
			execution/signals.c \
			execution/free_fct.c \
			quotes.c\
			new_env.c\
			free.c\

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)  -lreadline -L /Users/rbouissa/goinfre/homebrew/opt/readline/lib -I /Users/rbouissa/goinfre/homebrew/opt/readline/include 

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME) 

re:	fclean all

b: all clean
