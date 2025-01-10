/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:40 by spascual          #+#    #+#             */
/*   Updated: 2025/01/10 18:08:00 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *handle_quoted_string(const char *input, int *pos)
{
	char	*value = NULL; // Acumula el resultado final
	char	*tmp;
	char	quote_type;
	int		start;
	int		len;

	while (input[*pos]) // Procesar hasta el final del input
	{
		// Manejar comillas
		if (input[*pos] == '"' || input[*pos] == '\'')
		{
			quote_type = input[*pos];
			(*pos)++;
			start = *pos; // puedo poner aqui pos++ y tener menos lineas ?
			// Buscar la comilla de cierre o falta de ella
			while (input[*pos] && input[*pos] != quote_type)
				(*pos)++;
			if (input[*pos] != quote_type)
			{
				printf("Error: unclosed quote\n");
				free(value);
				return NULL;
			}
			// Copiar el contenido entre las comillas
			len = *pos - start;
			tmp = malloc(len + 1); // +1 para '\0'
			if (!tmp)
			{
				perror("malloc failed");
				free(value);
				return NULL;
			}
			strncpy(tmp, &input[start], len);
			tmp[len] = '\0';
			(*pos)++; // Saltar la comilla de cierre
		}
		else // Manejar texto fuera de las comillas
		{
			start = *pos;
			while (input[*pos] && input[*pos] != '"' && input[*pos] != '\'')
				(*pos)++;
			len = *pos - start;
			tmp = malloc(len + 1); // +1 para '\0'
			if (!tmp)
			{
				perror("malloc failed");
				free(value);
				return NULL;
			}
			strncpy(tmp, &input[start], len);
			tmp[len] = '\0';
		}
		// Concatenar tmp al resultado final
		if (value == NULL)
			value = strdup(tmp); // Primera asignación
		else
		{
			char *new_value = malloc(ft_strlen(value) + ft_strlen(tmp) + 1);
			if (!new_value)
			{
				perror("malloc failed");
				free(tmp);
				free(value);
				return NULL;
			}
			strcpy(new_value, value);
			strcat(new_value, tmp);
			free(value);
			value = new_value;
		}
		free(tmp); // Liberar tmp después de usarlo
	}
/*
	// en mi cabeza tiene sentido que funcione solo con eso sin el ultimo if else...
		strcat(value, tmp);
		free(tmp);
	}
*/
	return (crear_token(value, 2)); // Crear el token final con el contenido acumulado
}

t_token *handle_operator(const char *input, int *pos)
{
	char	*value;
	
	value = ft_strndup(&input[*pos], 1); // Copia el operador
	(*pos)++; // Avanzar posición
	return (crear_token(value, 3)); // Tipo 3 es un operador
}

char *get_env_value(t_env *env_list, const char *name)
{
	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->name, name) == 0)
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

