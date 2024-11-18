#include "minishell.h"

void add_token_to_list(t_token **token_list, t_token *new_token, const char *input, int *pos)
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
	while (input[*pos] == ' ') // salta espacios blancos
		(*pos)++;
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

	return (crear_token(value, 1));
}
