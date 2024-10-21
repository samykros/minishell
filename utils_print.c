#include "minishell.h"

void print_tokens(t_token *tokens)
{
	t_token *temp = tokens;
	while (temp != NULL)
	{
		printf("Token: %s Tipo: %d\n", temp->value, temp->type);
		temp = temp->next;
	}
}
