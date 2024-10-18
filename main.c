#include "minishell.h"

volatile sig_atomic_t g_exit_status = 0; // Variable global para manejar el estado de salida

void handle_sigint(int sig)
{
	(void)sig;
	g_exit_status = 1; // Cambia el estado para indicar que Ctrl-C fue recibido
	printf("\n\033[0;32m➜ \033[0;36m\033[1m minishell > \033[0;37m");
}

int main(void)
{
	int pos;
	char *input;
	t_token *tokens;
	t_command *command_history = NULL;  // Lista para almacenar los comandos completos

	signal(SIGINT, handle_sigint);
	while (1)
	{
		if (g_exit_status)
			g_exit_status = 0; // Reiniciar el estado

		// Leer la entrada del usuario
		input = readline("\033[0;32m➜ \033[0;36m\033[1m minishell > \033[0;37m");

		if (!input)
			break; // si el usuario presiona Ctrl-D, readline devuelve NULL, de ahi if !input

		pos = 0;
		tokens = NULL;

		// Proceso de tokenización
		while (!is_end_of_input(input, pos))
		{
			if (is_quote(input[pos]))
			{
				t_token *token = handle_quoted_string(input, &pos);
				add_token_to_list(&tokens, token);
			}
			else if (is_operator(input[pos]))
			{
				t_token *token = handle_operator(input, &pos);
				add_token_to_list(&tokens, token);
			}
			else if (is_envvariable(input[pos]))
			{
				t_token *token = handle_envvariable(input, &pos);
				add_token_to_list(&tokens, token);
			}
			else
			{
				t_token *token = get_next_token(input, &pos);
				add_token_to_list(&tokens, token);
			}
		}

		// Concatenar tokens en un string y añadirlo a la lista de comandos
		char *command_str = concatenar_tokens(tokens);
		if (command_str)
			add_command_to_list(&command_history, command_str);

		if (validate_token_sequence(tokens) == 0)
		{
			printf("command not found\n");
		}
		// Imprimir la lista de tokens para verificar que funciona
		print_tokens(tokens);

		// Imprimir la lista de comandos completos
		print_commands(command_history);

		// Liberar la lista de tokens después de cada iteración
		free_tokens(tokens);

		// Liberar la memoria del input después de cada iteración
		free(input);
	}

	// Liberar la memoria de command_history si es necesario antes de salir
	// free_command_history(command_history);

	return (0);
}
