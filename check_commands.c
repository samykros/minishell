#include "minishell.h"

int identify_command(char *command)
{
	char *commands[] = {"echo", "cd", "pwd", "export", "unset", "exit", NULL};
	int i = 0;

	while (commands[i])
	{
		if (ft_strcmp(command, commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

// Maybe not the best way..? Personalizar para cada comando
int validate_token_sequence(t_token *tokens)
{
	int expect_type = 1;

	while (tokens != NULL)
	{
		if (tokens->type == expect_type)
		{
			if (tokens->type == 1)  // Comando
			{
				if (ft_strcmp(tokens->value, "echo") == 0)
				{
					if (tokens->next && tokens->next->type == 2 && ft_strcmp(tokens->next->value, "-n") == 0)
						tokens = tokens->next;  // Saltar la opción -n
					expect_type = 2;  // Después de echo, puede venir un argumento
				}
				else if (ft_strcmp(tokens->value, "cd") == 0)
					expect_type = 2;  // cd debe seguirse por un argumento (ruta)
				else
					expect_type = 2;  // Otros comandos esperan argumentos o operadores
			}
			else if (tokens->type == 2)  // Argumento
				expect_type = 3;  // Después de un argumento, esperamos un operador o final de comando
			else if (tokens->type == 3)  // Operador
				expect_type = 1;  // Después de un operador, debe venir un comando
		}
		else
			return (0);  // Secuencia inválida
		tokens = tokens->next;
	}
	return (1);
}
