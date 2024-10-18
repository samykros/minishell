#include "minishell.h"

void add_token_to_list(t_token **token_list, t_token *new_token)
{
	if (!*token_list)
		*token_list = new_token;  // Si la lista está vacía, el nuevo token es el primero
	else
	{
		t_token *temp = *token_list;
		while (temp->next)
		{
			temp = temp->next;  // Recorre hasta el final de la lista
		}
		temp->next = new_token;  // Añade el nuevo token al final
	}
}

t_token *crear_token(char *value, int type)
{
	t_token *new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

t_token *get_next_token(const char *input, int *pos)
{
	// Saltar espacios en blanco
	while (input[*pos] == ' ')
		(*pos)++;

	int start = *pos;

	// Avanzar hasta encontrar un espacio o un carácter especial
	while (input[*pos] && input[*pos] != ' ' && !is_operator(input[*pos]) && !is_quote(input[*pos]))
		(*pos)++;

	// No crear tokens vacíos
	if (*pos == start)
		return (NULL);

	// Copiar el token desde la posición inicial hasta donde se detuvo
	char *value = ft_strndup(&input[start], *pos - start);

	if (identify_command(value) == 1)
	{
		// Crear y devolver un nuevo token
		return (crear_token(value, 1));
	}
	return (crear_token(value, -1));
}

t_token *handle_quoted_string(const char *input, int *pos)
{
	(*pos)++; // Ignorar la primera comilla
	int start = *pos;
	while (input[*pos] && !is_quote(input[*pos]))
		(*pos)++;
	char *value = ft_strndup(&input[start], *pos - start);
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