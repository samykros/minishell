/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:36 by spascual          #+#    #+#             */
/*   Updated: 2024/12/10 18:02:15 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void builtin_export(t_command *command, t_env *env_list)
{
	t_token *arg = command->tokens->next;

	if (!arg)
	{
		printf("export: No arguments provided\n");
		return;
	}

	while (arg)
	{
		char *equal_sign = strchr(arg->value, '=');
		if (!equal_sign)
		{
			printf("export: Invalid argument: %s\n", arg->value);
		}
		else
		{
			char *name = strndup(arg->value, equal_sign - arg->value);
			char *value = strdup(equal_sign + 1);

			// Buscar o añadir a la lista de entorno
			t_env *current = env_list;
			while (current) {
				if (strcmp(current->name, name) == 0)
				{
					free(current->value);
					current->value = value;
					break;
				}
				current = current->next;
			}

			if (!current)
			{
				// Si no se encuentra, añadir una nueva variable
				t_env *new_env = malloc(sizeof(t_env));
				new_env->name = name;
				new_env->value = value;
				new_env->next = env_list->next;
				env_list->next = new_env;
			}

			free(name);
		}
		arg = arg->next;
	}
}