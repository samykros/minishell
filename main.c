#include "minishell.h"

volatile sig_atomic_t g_exit_status = 0; // Variable global para manejar el estado de salida

void handle_sigint(int sig)
{
	(void)sig;
	g_exit_status = 1; // Cambia el estado para indicar que Ctrl-C fue recibido
	printf("\n\033[0;32m➜ \033[0;36m\033[1m minishell > \033[0;37m");
}

int main(int argc, char **argv, char **env)
{
	char *input;
	t_token *tokens;
	t_node *commands;
	//t_env *env_list = init_env(env);

	(void)argc;
	(void)argv;
	(void)env;
	signal(SIGINT, handle_sigint);
	//init_env(&env);
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
		commands = node_list(tokens);
		
		// Lista de tokens para verificar que funciona
		print_tokens(tokens);
		printf("\n");
		print_commands(commands);

		free_tokens(tokens);
		// free_commands no hecho
		free(input);
	}

	// Liberar la memoria de command_history
	// free_command_history(command_history);

	return (0);
}
