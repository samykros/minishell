/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:37:04 by spascual          #+#    #+#             */
/*   Updated: 2024/12/11 12:11:46 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_command *command)
{
	if (!command || !command->tokens || !command->tokens->value)
		return 0; // Si es nulo o no tiene tokens, no es builtin
	if (ft_strcmp(command->tokens->value, "cd") == 0 ||
		ft_strcmp(command->tokens->value, "echo") == 0 ||
		ft_strcmp(command->tokens->value, "env") == 0 ||
		ft_strcmp(command->tokens->value, "export") == 0 ||
		ft_strcmp(command->tokens->value, "unset") == 0 ||
		ft_strcmp(command->tokens->value, "exit") == 0 ||
		ft_strcmp(command->tokens->value, "pwd") == 0)
	{
		return (1); // Es builtin
	}
	return (0); // No es builtin
}

void execute_builtin(t_command *command, t_env *env_list)
{
	if (ft_strcmp(command->tokens->value, "cd") == 0)
		builtin_cd(command);
	else if (ft_strcmp(command->tokens->value, "echo") == 0)
		builtin_echo(command);
	else if (ft_strcmp(command->tokens->value, "env") == 0)
		builtin_env(env_list);
	else if (ft_strcmp(command->tokens->value, "export") == 0)
		builtin_export(command, env_list);
	else if (ft_strcmp(command->tokens->value, "unset") == 0)
		builtin_unset(command, env_list);
	else if (ft_strcmp(command->tokens->value, "exit") == 0)
		builtin_exit(command);
	else if (ft_strcmp(command->tokens->value, "pwd") == 0)
		builtin_pwd();
}

void	execute_commands(t_command *commands, t_env *env_list)
{
	t_command *current = commands;

	while (current)
	{
		if (current->tokens)
		{
			if (is_builtin(current)) //->tokens->value
				execute_builtin(current, env_list);
			else
				execute_external(current, env_list);
		}
		current = current->next;
	}
}
