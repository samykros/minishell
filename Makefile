# Nombre del ejecutable
NAME = minishell

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

# Directorios de readline
LDFLAGS = -L/opt/homebrew/opt/readline/lib
CPPFLAGS = -I/opt/homebrew/opt/readline/include
LIBS = -lreadline

# Archivos fuente
SRC =	src/main.c \
		src/handlers.c \
		src/utils.c \
		src/utils_2.c \
		src/utils_print.c \
		src/utils_libft.c \
		src/tokenizer.c \
		src/tokens_help.c \
		src/env.c \
		src/free.c \
		src/execution.c \
		src/execution_2.c \
		src/cd.c \
		src/echo.c \
		src/exit.c \
		src/export.c \
		src/pwd.c \
		src/unset.c \

# Archivos objeto generados
OBJ = $(SRC:.c=.o)

# Regla por defecto, crea el ejecutable
all: $(NAME)

# Compilación del ejecutable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) $(OBJ) $(LIBS) -o $(NAME)

# Regla para limpiar archivos objeto y ejecutable
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

# Regla para recompilar todo
re: fclean all
