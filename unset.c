/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:57 by spascual          #+#    #+#             */
/*   Updated: 2024/12/10 18:02:43 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void builtin_unset(t_command *command, t_env *env_list)
{
	t_token *arg = command->tokens->next;

	if (!arg)
	{
		printf("unset: No arguments provided\n");
		return;
	}

	while (arg)
	{
		t_env *prev = NULL;
		t_env *current = env_list;

		while (current)
		{
			if (strcmp(current->name, arg->value) == 0)
			{
				if (prev)
					prev->next = current->next;
				else
					env_list = current->next;

				free(current->name);
				free(current->value);
				free(current);
				break;
			}
			prev = current;
			current = current->next;
		}

		arg = arg->next;
	}
}
