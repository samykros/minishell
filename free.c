/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:08 by spascual          #+#    #+#             */
/*   Updated: 2024/12/10 13:43:45 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens;
		tokens = tokens->next;
		//free(tmp->value); // TODO mira strdup value
		free(tmp);
		tmp = NULL;
	}
}

void	free_commands(t_command *commands)
{
	t_command	*current_command;

	while (commands)
	{
		current_command = commands;
		commands = commands->next;
		free_tokens(current_command->tokens);
		free(current_command);
		current_command = NULL;
	}
}
