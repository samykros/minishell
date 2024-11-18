#include "minishell.h"

int is_pipe(t_token *token)
{
	return token && strcmp(token->value, "|") == 0;  // Compara si el valor del token es un pipe
}