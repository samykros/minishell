/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:17 by spascual          #+#    #+#             */
/*   Updated: 2024/12/10 12:17:13 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile	sig_atomic_t g_exit_status = 0; // Variable global para manejar el estado de salida

void	handle_sigint(int sig)
{
	(void)sig;
	g_exit_status = 1; // Cambia el estado para indicar que Ctrl-C fue recibido
	printf("\n\033[0;32m➜ \033[0;36m\033[1m minishell > \033[0;37m");
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*tokens = NULL;
	t_node	*nodes = NULL;
	t_env	*env_list = NULL;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_sigint);
	env_list = init_env(env);
	while (1)
	{
		if (g_exit_status)
			g_exit_status = 0; // Reiniciar el estado
		input = readline("\033[0;32m➜ \033[0;36m\033[1m minishell > \033[0;37m");
		if (!input)
			break; // si el usuario presiona Ctrl-D, readline devuelve NULL
		if (*input) // Añadir solo si el input no está vacío, esto hace que flechas funcionen con readline
			add_history(input);
		tokens = tokenizer(input, env_list);
		nodes = node_list(tokens);

		print_tokens(tokens);
		//printf("\n");
		print_commands(nodes);
		//print_env_list(env_list);
		free_nodes(nodes); // utiliza free_tokens
		free(input);
		if (!input)
			break;
	}
	free_env(env_list); 
	return (0);
}
