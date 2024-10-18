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

void print_commands(t_command *command_list)
{
	t_command *temp = command_list;
		
	printf("Lista de comandos:\n");
	while (temp != NULL)
	{
		printf("%s\n", temp->command_str);  // Imprimir cada comando
		temp = temp->next;  // Pasar al siguiente comando
	}
}
