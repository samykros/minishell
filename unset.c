/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:57 by spascual          #+#    #+#             */
/*   Updated: 2025/01/11 14:02:50 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_variable(t_env **env_list, const char *name)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = *env_list;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	handle_unset_argument(t_env **env_list, t_token *arg)
{
	if (!arg || !arg->value || !*arg->value)
	{
		printf("unset: `%s': not a valid identifier\n", arg->value);
		return ;
	}
	unset_variable(env_list, arg->value);
}

void	builtin_unset(t_command *command, t_env *env_list)
{
	t_token	*arg;

	arg = command->tokens->next;
	if (!arg)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	while (arg)
	{
		handle_unset_argument(&env_list, arg);
		arg = arg->next;
	}
}
