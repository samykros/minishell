#include "minishell.h"

// ejemplo

int is_echo(t_token *tokens)
{
	// El primer token debería ser el comando "echo"
	if (tokens != NULL && strcmp(tokens->value, "echo") == 0) {
		tokens = tokens->next;
		// Verificar si el siguiente token es "-n"
		if (tokens != NULL && strcmp(tokens->value, "-n") == 0) {
			return 1;  // echo con la opción -n
		}
		return 1;  // echo sin opciones
	}
	return 0;
}