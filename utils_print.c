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

void print_commands(t_node *commands)
{
    t_node *temp = commands;
    while (temp != NULL)
    {
        printf("Command: ");
        t_token *token_temp = temp->tokens;
        while (token_temp != NULL)
		{
            printf("%s ", token_temp->value);
            token_temp = token_temp->next;
        }
        printf("\n");
        temp = temp->next;
    }
}


