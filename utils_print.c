/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:08:08 by spascual          #+#    #+#             */
/*   Updated: 2024/12/10 12:35:25 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_tokens(t_token *tokens)
{
	t_token *temp = tokens;
	while (temp != NULL)
	{
		printf("Token: %s Tipo: %d\n", temp->value, temp->type);
		temp = temp->next;
	}
}

void print_commands(t_command *commands)
{
	t_command *temp = commands;
	while (temp != NULL)
	{
		printf("Command: ");
		t_token *token_temp = temp->tokens;
		while (token_temp != NULL)
		{
			printf("%s ", token_temp->value);
			token_temp = token_temp->next;
		}
		printf("\n");
		temp = temp->next;
	}
}

void print_env_list(t_env *env)
{
	t_env *current = env;  // Comienza en el primer nodo de la lista
	while (current != NULL)
	{
		printf("Name: %s, Value: %s\n", current->name, current->value);
		current = current->next;  // Avanza al siguiente nodo
	}
}


