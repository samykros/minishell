/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:29 by spascual          #+#    #+#             */
/*   Updated: 2024/12/10 12:07:30 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *new_env_node(const char *name, const char *value)
{
	t_env *node = malloc(sizeof(t_env));
	if (!node)
		return NULL;
	node->name = strdup(name);
	node->value = strdup(value);
	node->next = NULL;
	return node;
}

t_env *init_env(char **env)
{
	t_env *head = NULL;
	t_env *current = NULL;
	int i = 0;
	int j;

	while (env[i])
	{
		j = 0;
		// Encuentra la posición del '='
		while (env[i][j] && env[i][j] != '=')
			j++;

		if (env[i][j] == '=')
		{
			// Crea un nodo nuevo con el nombre y valor extraídos
			char *name = strndup(env[i], j);
			char *value = strdup(&env[i][j + 1]);

			t_env *new_node = new_env_node(name, value);
			free(name);  // Limpia memoria de la cadena temporal
			free(value);

			// Inserta el nodo en la lista
			if (!head) {
				head = new_node;
				current = new_node;
			} else {
				current->next = new_node;
				current = new_node;
			}
		}
		i++;
	}

	return head;
}

