/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:20 by spascual          #+#    #+#             */
/*   Updated: 2024/12/11 12:04:41 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void builtin_cd(t_command *command)
{
	t_token *arg = command->tokens->next; // Argumento después de "cd"
	const char *path;

	if (!arg)
	{
		// Si no se especifica un argumento, usar $HOME
		path = getenv("HOME");
		if (!path)
		{
			printf("cd: HOME not set\n");
			return;
		}
	}
	else
		path = arg->value;
	if (chdir(path) != 0)
		perror("cd");
}
