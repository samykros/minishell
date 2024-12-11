/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:33 by spascual          #+#    #+#             */
/*   Updated: 2024/12/10 18:04:31 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void builtin_exit(t_command *command)
{
	t_token *arg = command->tokens->next;

	if (arg)
	{
		int exit_code = atoi(arg->value); // Convertir el argumento a un número
		printf("exit\n");
		exit(exit_code);
	}

	printf("exit\n");
	exit(0);
}
