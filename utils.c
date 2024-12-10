/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:08:10 by spascual          #+#    #+#             */
/*   Updated: 2024/12/10 12:12:22 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Verifica si el carácter actual es una comilla
int	is_quote(char c)
{
	if (c == '\'' || c == '"') // ESTO '\'' ?? supongo que para poner '
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else if (c == '|')
		return (2);
	return (0);
}

int	is_envvariable(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

int	is_end_of_input(const char *input, int pos)
{
	if (input[pos] == '\0')
		return (1);
	return (0);
}

