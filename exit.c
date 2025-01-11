/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:33 by spascual          #+#    #+#             */
/*   Updated: 2025/01/11 13:25:28 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(t_command *command)
{
	t_token	*arg;
	int		exit_code;

	arg = command->tokens->next;
	if (arg && arg->next)
	{
		printf("exit\nexit: too many arguments\n");
		return ;
	}
	if (arg)
	{
		if (is_numeric(arg->value))
		{
			exit_code = atoi(arg->value);
			printf("exit\n");
			exit(exit_code);
		}
		else
		{
			printf("exit\nexit: numeric argument required\n");
			exit(0);
		}
	}
	printf("exit\n");
	exit(0);
}
