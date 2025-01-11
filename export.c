/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:36 by spascual          #+#    #+#             */
/*   Updated: 2025/01/11 14:46:58 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_variable_name(const char *name)
{
	if (!name || (!isalpha(*name) && *name != '_'))
		return (0);
	name++;
	while (*name)
	{
		if (!isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

int	extract_name_value(char *arg_value, char **name, char **value)
{
	char	*equal_sign;

	equal_sign = strchr(arg_value, '=');
	if (equal_sign)
	{
		*name = strndup(arg_value, equal_sign - arg_value);
		*value = strdup(equal_sign + 1);
	}
	else
	{
		*name = strdup(arg_value);
		*value = strdup("");
	}
	return (equal_sign != NULL);
}

void	add_or_update_env(t_env *env_list, char *name, char *value)
{
	t_env	*current;
	t_env	*new_env;

	current = env_list;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = value;
			return ;
		}
		current = current->next;
	}
	new_env = malloc(sizeof(t_env));
	if (!new_env)
	{
		perror("malloc");
		return ;
	}
	new_env->name = name;
	new_env->value = value;
	new_env->next = env_list->next;
	env_list->next = new_env;
}

void	handle_export_argument(t_env *env_list, t_token *arg)
{
	char	*name;
	char	*value;

	if (!extract_name_value(arg->value, &name, &value))
	{
		printf("export: `%s': not a valid identifier\n", arg->value);
		free(name);
		free(value);
		return ;
	}
	if (!is_valid_variable_name(name))
	{
		printf("export: `%s': not a valid identifier\n", arg->value);
		free(name);
		free(value);
	}
	else
		add_or_update_env(env_list, name, value);
}

void	builtin_export(t_command *command, t_env *env_list)
{
	t_token	*arg;

	arg = command->tokens->next;
	if (!arg)
	{
		print_env_list(env_list);
		return ;
	}
	while (arg)
	{
		handle_export_argument(env_list, arg);
		arg = arg->next;
	}
}
