#include "minishell.h"

t_node *create_command_node(t_token *start, t_token *end)
{
	t_node *node = malloc(sizeof(t_node));
	if (!node)
		return NULL;
	node->tokens = NULL;
	node->next = NULL;

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
			free(node);
			return NULL;
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
	node->tokens = copy_head;
	return node;
}

t_node *node_list(t_token *tokens)
{
	t_node *head = NULL;
	t_node *current = NULL;
	t_token *command_start = tokens;  // Inicio del comando actual
	t_token *token_iter = tokens;	 // Iterador para tokens

	while (token_iter != NULL)
	{
		if (is_pipe(token_iter))
		{
			if (command_start != token_iter)
			{  // Evitar nodos vacíos en caso de pipes consecutivos
				t_node *new_node = create_command_node(command_start, token_iter);
				if (!head)
					head = new_node;
				else
					current->next = new_node;
				current = new_node;
			}
			command_start = token_iter->next;  // Comenzar un nuevo comando después del pipe
		}
		token_iter = token_iter->next;
	}
	// Último comando después del último pipe
	if (command_start != NULL)
	{
		t_node *new_node = create_command_node(command_start, NULL); // Hasta el final de la lista
		if (!head)
			head = new_node;
		else
			current->next = new_node;
	}
	return head;
}

t_token *tokenizer(char *input)
{
	int pos = 0;
	t_token *tokens = NULL;

	// Proceso de tokenización
	while (!is_end_of_input(input, pos))
	{
		if (is_quote(input[pos]))
		{
			t_token *token = handle_quoted_string(input, &pos);
			add_token_to_list(&tokens, token, input, &pos);
		}
		else if (is_operator(input[pos]))
		{
			if (is_operator(input[pos]) == 2) // pipe
				node_list(tokens);
			t_token *token = handle_operator(input, &pos);
			add_token_to_list(&tokens, token, input, &pos);
		}
		else if (is_envvariable(input[pos]))
		{
			t_token *token = handle_envvariable(input, &pos);
			add_token_to_list(&tokens, token, input, &pos);
		}
		else
		{
			t_token *token = get_next_token(input, &pos);
			add_token_to_list(&tokens, token, input, &pos);
		}
	}
	return (tokens); // Devolver la lista de tokens
}
