# Nombre del ejecutable
NAME = minishell

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Directorios de readline
LDFLAGS = -L/opt/homebrew/opt/readline/lib
CPPFLAGS = -I/opt/homebrew/opt/readline/include
LIBS = -lreadline

# Archivos fuente
SRC =	main.c \
		lexer.c utils.c \
		utils_print.c \
		check_commands.c \
		utils_libft.c \

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
