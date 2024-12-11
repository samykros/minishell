/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:27 by spascual          #+#    #+#             */
/*   Updated: 2024/12/10 18:00:00 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void builtin_echo(t_command *command)
{
	t_token *current = command->tokens->next; // Saltar el nombre del comando
	int newline = 1; // Por defecto, incluir salto de línea

	if (current && ft_strcmp(current->value, "-n") == 0)
	{
		newline = 0; // Si el primer argumento es "-n", desactiva el salto de línea
		current = current->next; // Saltar la opción
	}
	while (current)
	{
		printf("%s", current->value);
		if (current->next)
			printf(" "); // Añadir espacio entre argumentos
		current = current->next;
	}
	if (newline)
		printf("\n");
}