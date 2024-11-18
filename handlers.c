#include "minishell.h"

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
	char *value = ft_strndup(&input[*pos], 1); // Copia el operador
	(*pos)++; // Avanzar posición
	return (crear_token(value, 3)); // Tipo 3 es un operador
}

// Maneja las variables de entorno ($VAR)
t_token *handle_envvariable(const char *input, int *pos)
{
	// Empieza después del $
	(*pos)++;  // Avanza la posición para saltar el $
	int start = *pos;

	// Sigue avanzando hasta que encuentres un carácter que no sea parte de la variable
	while (input[*pos] && (isalnum(input[*pos]) || input[*pos] == '_'))
		(*pos)++;

	// Copia el nombre de la variable
	char *variable_name = ft_strndup(&input[start], *pos - start);

	// Crea un token para la variable de entorno (tipo 4 es solo un ejemplo)
	return (crear_token(variable_name, 4));  // Tipo 4 es para variables de entorno
}