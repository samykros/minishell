/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:27 by spascual          #+#    #+#             */
/*   Updated: 2025/01/09 19:34:26 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void builtin_echo(t_command *command)
{
	t_token *current = command->tokens->next;  // Saltar el nombre del comando
	int newline = 1;  // Por defecto, incluir salto de línea

	while (current && ft_strcmp(current->value, "-n") == 0)
	{
		newline = 0;
		current = current->next;
	}
	while (current)
	{
		printf("%s", current->value);
		// Añadir espacio entre argumentos si no es el último y el próximo token no empieza ni termina con una comilla
		if (current->next)
		{
			char *next_value = current->next->value;
			if (!(next_value[0] == '\'' || next_value[0] == '"' || 
				  current->value[strlen(current->value) - 1] == '\'' ||
				  current->value[strlen(current->value) - 1] == '"'))
				printf(" ");
		}
		current = current->next;
	}
	if (newline)
		printf("\n");
}


