/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:40 by spascual          #+#    #+#             */
/*   Updated: 2024/12/10 13:43:37 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *handle_quoted_string(const char *input, int *pos)
{
	int start;
	char *value;

	(*pos)++; // Ignorar la primera comilla
	start = *pos;
	while (input[*pos] && !is_quote(input[*pos]))
		(*pos)++;
	value = ft_strndup(&input[start], *pos - start);
	(*pos)++; // Ignorar la comilla de cierre
	return (crear_token(value, 2)); // Tipo 2 es un string con comillas
}

t_token *handle_operator(const char *input, int *pos)
{
	char *value;
	
	value = ft_strndup(&input[*pos], 1); // Copia el operador
	(*pos)++; // Avanzar posición
	return (crear_token(value, 3)); // Tipo 3 es un operador
}

char *get_env_value(t_env *env_list, const char *name)
{
	while (env_list != NULL)
	{
		if (strcmp(env_list->name, name) == 0)
			return env_list->value;
		env_list = env_list->next;
	}
	return NULL; // Retorna NULL si no se encuentra la variable
}

t_token *handle_envvariable(const char *input, int *pos, t_env *env_list)
{
	int start;
	char *variable_name;
	char *value;

	// Avanza después del '$'
	(*pos)++;
	start = *pos;

	// Avanza hasta que el carácter no sea parte de la variable
	while (input[*pos] && (isalnum(input[*pos]) || input[*pos] == '_')) // puedo poner !isspace en vez de eso?
		(*pos)++;

	// Copia el nombre de la variable
	variable_name = ft_strndup(&input[start], *pos - start);

	// Busca el valor de la variable de entorno
	value = get_env_value(env_list, variable_name);
	free(variable_name); // Libera el nombre de la variable

	if (value == NULL)
	{
		// Maneja la no existencia de la variable de entorno de forma que no se libere incorrectamente
		value = strdup(""); // Asegúrate de duplicar la cadena vacía para mantener la consistencia de memoria
	}

	// Crea un token para la variable de entorno (tipo 4 es solo un ejemplo)
	return (crear_token(value, 4));  // Tipo 4 es para variables de entorno
}

