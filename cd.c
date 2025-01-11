/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:20 by spascual          #+#    #+#             */
/*   Updated: 2025/01/11 13:15:52 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_cd(t_command *command)
{
	t_token		*arg;
	const char	*path;

	arg = command->tokens->next;
	if (!arg)
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("cd: HOME not set\n");
			return ;
		}
	}
	else
		path = arg->value;
	if (chdir(path) != 0)
		perror("cd");
}
