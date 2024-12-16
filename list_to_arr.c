/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:09:19 by spascual          #+#    #+#             */
/*   Updated: 2024/12/12 12:10:58 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// execve necesita array, por eso pasas de link list a array

char **convert_tokens_to_arr(t_token *tokens)
{
	int count = 0;
	t_token *current = tokens;

	// Contar el número de tokens
	while (current)
	{
		count++;
		current = current->next;
	}

	// Reservar memoria para arr
	char **arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return NULL;

	// Copiar los valores de los tokens a arr
	current = tokens;
	for (int i = 0; i < count; i++)
	{
		arr[i] = strdup(current->value); // Crear una copia del valor
		current = current->next;
	}
	arr[count] = NULL; // Terminar el array con NULL

	return arr;
}

char **convert_env_list_to_array(t_env *env_list)
{
	int count = 0;
	t_env *current = env_list;

	// Contar cuántas variables de entorno hay
	while (current)
	{
		count++;
		current = current->next;
	}

	// Reservar memoria para el array de strings
	char **envp = malloc((count + 1) * sizeof(char *));
	if (!envp)
		return NULL;

	current = env_list;
	for (int i = 0; i < count; i++)
	{
		size_t size = strlen(current->name) + strlen(current->value) + 2; // pq +2? (=, \0) ?
		envp[i] = malloc(size);
		if (!envp[i])
		{
			for (int j = 0; j < i; j++) // Liberar memoria en caso de error
				free(envp[j]);
			free(envp);
			return NULL;
		}
		sprintf(envp[i], "%s=%s", current->name, current->value); // Formato "NOMBRE=VALOR"
		current = current->next;
	}
	envp[count] = NULL; // Terminar con NULL

	return envp;
}