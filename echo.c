/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:27 by spascual          #+#    #+#             */
/*   Updated: 2025/01/11 13:22:56 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(t_command *command)
{
	t_token	*current;
	int		newline;

	current = command->tokens->next;
	newline = 1;
	while (current && ft_strcmp(current->value, "-n") == 0)
	{
		newline = 0;
		current = current->next;
	}
	while (current)
	{
		printf("%s", current->value);
		if (current->next
			&& !(current->next->value[0] == '\''
				|| current->next->value[0] == '"'
				|| current->value[strlen(current->value) - 1] == '\''
				|| current->value[strlen(current->value) - 1] == '"'))
			printf(" ");
		current = current->next;
	}
	if (newline)
		printf("\n");
}
