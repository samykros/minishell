/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:48 by spascual          #+#    #+#             */
/*   Updated: 2024/12/10 12:38:12 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*create_command_command(t_token *start, t_token *end)
{
	t_command *command = malloc(sizeof(t_command));
	if (!command)
		return NULL;
	command->tokens = NULL;
	command->next = NULL;

	// Copiar tokens desde start hasta end (exclusivo)
	t_token *current = start;
	t_token *last = NULL, *copy_head = NULL;
	while (current != end)
	{
		t_token *new_token = malloc(sizeof(t_token));
		if (!new_token)
		{
			// Manejo de error, liberar memoria
			free_tokens(copy_head);
			free(command);
			return (NULL);
		}
		*new_token = *current;  // Copiar contenido
		new_token->next = NULL;
		if (!copy_head)
			copy_head = new_token;  // Este es el primer token
		else
			last->next = new_token;

		last = new_token;
		current = current->next;
	}
	command->tokens = copy_head;
	return (command);
}

t_command	*command_list(t_token *tokens)
{
	t_command *head = NULL;
	t_command *current = NULL;
	t_token *command_start = tokens;  // Inicio del comando actual
	t_token *token_iter = tokens;  // Iterador para tokens

	while (token_iter != NULL)
	{
		if (is_pipe(token_iter))
		{
			if (command_start != token_iter)
			{  // Evitar nodos vacíos en caso de pipes consecutivos
				t_command *new_command = create_command_command(command_start, token_iter);
				if (!new_command)
				{
					free_commands(head);
					return (NULL);
				}
				if (!head)
					head = new_command;
				else
					current->next = new_command;
				current = new_command;
			}
			command_start = token_iter->next;  // Comenzar un nuevo comando después del pipe
		}
		token_iter = token_iter->next;
	}
	// Último comando después del último pipe
	if (command_start != NULL)
	{
		t_command *new_command = create_command_command(command_start, NULL); // Hasta el final de la lista
		if (!new_command)
		{
			free_commands(head);
			return (NULL);
		}
		if (!head)
			head = new_command;
		else
			current->next = new_command;
	}
	return (head);
}

t_token	*tokenizer(char *input, t_env *env_list)
{
	int pos = 0;
	t_token *tokens = NULL;  //malloc(sizeof(t_token) + 1); // ?
	t_token *token;

	while (!is_end_of_input(input, pos))
	{
		if (is_quote(input[pos]))
		{
			token = handle_quoted_string(input, &pos);
			add_token_to_list(&tokens, token, input, &pos);  // & direccion memoria, permite modificar, que no se te olvide
		}
		else if (is_operator(input[pos]))
		{
			if (is_operator(input[pos]) == 2) // pipe
				command_list(tokens);
			token = handle_operator(input, &pos);
			add_token_to_list(&tokens, token, input, &pos);
		}
		else if (is_envvariable(input[pos]))
		{
			token = handle_envvariable(input, &pos, env_list);
			add_token_to_list(&tokens, token, input, &pos);
		}
		else
		{
			token = get_next_token(input, &pos);
			add_token_to_list(&tokens, token, input, &pos);
		}
	}
	return (tokens); // Devolver la lista de tokens
}
