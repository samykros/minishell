#include "minishell.h"

volatile sig_atomic_t g_exit_status = 0; // Variable global para manejar el estado de salida

void handle_sigint(int sig)
{
	(void)sig;
	g_exit_status = 1; // Cambia el estado para indicar que Ctrl-C fue recibido
	printf("\n\033[0;32m➜ \033[0;36m\033[1m minishell > \033[0;37m");
}

t_token *tokenizer(char *input)
{
	int pos = 0;
	t_token *tokens = NULL;

	// Proceso de tokenización
	while (!is_end_of_input(input, pos))
	{
		if (is_quote(input[pos]))
		{
			t_token *token = handle_quoted_string(input, &pos);
			add_token_to_list(&tokens, token);
		} else if (is_operator(input[pos]))
		{
			t_token *token = handle_operator(input, &pos);
			add_token_to_list(&tokens, token);
		} else if (is_envvariable(input[pos]))
		{
			t_token *token = handle_envvariable(input, &pos);
			add_token_to_list(&tokens, token);
		} else
		{
			t_token *token = get_next_token(input, &pos);
			add_token_to_list(&tokens, token);
		}
	}
	return (tokens); // Devolver la lista de tokens
}

int main(void)
{
	char *input;
	t_token *tokens;

	signal(SIGINT, handle_sigint);
	while (1)
	{
		if (g_exit_status)
			g_exit_status = 0; // Reiniciar el estado
		input = readline("\033[0;32m➜ \033[0;36m\033[1m minishell > \033[0;37m");
		if (!input)
			break; // si el usuario presiona Ctrl-D, readline devuelve NULL
		if (*input) // Añadir solo si el input no está vacío, esto hace que flechas funcionen con readline
			add_history(input);
		tokens = tokenizer(input);

		if (validate_token_sequence(tokens) == 0)
			printf("command not found\n");
		
		// Imprimir la lista de tokens para verificar que funciona
		print_tokens(tokens);
		free_tokens(tokens);
		free(input);
	}

	// Liberar la memoria de command_history
	// free_command_history(command_history);

	return (0);
}
