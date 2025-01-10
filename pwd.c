/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:46 by spascual          #+#    #+#             */
/*   Updated: 2025/01/09 16:49:08 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// cuento como edge case que el directorio pueda ser >1024 ?
void builtin_pwd(void)
{
	char *cwd;
	size_t size = 1024;

	// Reservar espacio inicial para el buffer
	cwd = malloc(size);
	if (!cwd)
	{
		perror("malloc");
		return;
	}

	// Obtener el directorio actual
	if (getcwd(cwd, size) == NULL)
	{
		perror("pwd");
		free(cwd);
		return;
	}

	// Imprimir el directorio actual
	printf("%s\n", cwd);
	free(cwd); // Liberar memoria reservada
}