#include <stdio.h>
#include <stdlib.h>  // Para malloc y free
#include <string.h>  // Para strdup, strlen, strndup
#include <ctype.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// Estructura para un token
typedef struct s_token {
	char *value;	// Valor del token
	int type;		// Tipo de token (comando, argumento, operador, etc.)
	struct s_token *next;  // Puntero al siguiente token
} t_token;

// Estructura para un node, cada |
typedef struct s_node {
	t_token *tokens;   // Lista de tokens de este comando
	struct s_node *next;  // Puntero al siguiente comando (si lo hay, conectado por un pipe)
} t_node;


// Hacer otra link list con str de los inputs anteriores
// Estructura para un comando completo
typedef struct s_command {
	char *command_str;		// El string del comando completo
	struct s_command *next;	// Puntero al siguiente nodo en la lista
} t_command;

// Env var struct
typedef struct s_env {
	char *name;
	char *value;
	struct s_env *next;
} t_env;


// Obtiene el siguiente token del input
t_token *get_next_token(const char *input, int *pos);

// Verifica si el carácter actual es una comilla
int is_quote(char c);

// Maneja cadenas entre comillas
t_token *handle_quoted_string(const char *input, int *pos);

// Verifica si el carácter actual es un operador (>, <, |)
int is_operator(char c);

// Maneja operadores (redirecciones, pipes)
t_token *handle_operator(const char *input, int *pos);

// Verifica si el carácter actual es una variable de entorno ($)
int is_envvariable(char c);

// Maneja las variables de entorno ($VAR)
t_token *handle_envvariable(const char *input, int *pos);

// Añade un token a la lista de tokens
void add_token_to_list(t_token **token_list, t_token *new_token, const char *input, int *pos);

t_token *crear_token(char *value, int type);

// Verifica si se ha llegado al final del input
int is_end_of_input(const char *input, int pos);

void print_tokens(t_token *tokens);
void print_commands(t_node *commands);

// Función para liberar la lista de tokens
void free_tokens(t_token *tokens);

t_token *tokenizer(char *input);
int is_pipe(t_token *token);
t_node *node_list(t_token *tokens);
t_node *create_command_node(t_token *start, t_token *end);

// Identificar echo, cd, pwd, export, unset, exit
int identify_command(char *command);

int validate_token_sequence(t_token *tokens);

// libft commands
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

// signals
void handle_sigint(int sig);

// env variables
t_env *init_env(char **env);

// Prototipos
int is_echo(t_token *tokens);
int is_cd(t_token *tokens);
int is_pwd(t_token *tokens);
int is_export(t_token *tokens);
int is_unset(t_token *tokens);
int is_env(t_token *tokens);
int is_exit(t_token *tokens);