#include "minishell.h"

// Verifica si el carácter actual es una comilla
int is_quote(char c)
{
	if (c == '\'' || c == '"') // ESTO '\'' ??
		return (1);
	return (0);
}

int is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int is_envvariable(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

int is_end_of_input(const char *input, int pos)
{
	if (input[pos] == '\0')
		return (1);
	return (0);
}

void free_tokens(t_token *tokens)
{
	t_token *temp;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);	// Liberar el valor del token
		free(temp);		 // Liberar el nodo del token
	}
}
