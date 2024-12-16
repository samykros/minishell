/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:37:04 by spascual          #+#    #+#             */
/*   Updated: 2024/12/15 16:02:45 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_executable(const char *cmd, t_env *env_list)
{
	char *path = get_env_value(env_list, "PATH"); // Obtener la variable PATH
	if (!path)
		return NULL;

	char *full_path = NULL;
	size_t cmd_len = ft_strlen(cmd);
	size_t start = 0;

	// Iterar sobre cada directorio en PATH
	for (size_t i = 0; path[i] != '\0'; i++)
	{
		if (path[i] == ':' || path[i + 1] == '\0')
		{
			// Calcular el final del token actual
			size_t end = (path[i] == ':') ? i : i + 1;

			// Calcular la longitud del token actual
			size_t dir_len = end - start;

			// Reservar memoria para construir el camino completo
			full_path = malloc(dir_len + cmd_len + 2); // "/" + NULL
			if (!full_path)
				return NULL;

			// Copiar el directorio actual al buffer
			ft_strncpy(full_path, path + start, dir_len);
			full_path[dir_len] = '\0'; // Asegurarnos de terminar la cadena

			// Añadir "/" y el nombre del comando
			ft_strcat(full_path, "/");
			ft_strcat(full_path, cmd);

			// Comprobar si el archivo es ejecutable
			if (access(full_path, X_OK) == 0)
				return full_path; // Encontrado

			// Si no es ejecutable, liberar memoria
			free(full_path);
			full_path = NULL;

			// Actualizar el inicio del próximo token
			start = i + 1;
		}
	}

	return NULL; // No se encontró el ejecutable
}

void execute_external(t_command *command, t_env *env_list)
{
	char **arr = convert_tokens_to_arr(command->tokens);
	if (!arr)
	{
		perror("malloc");
		return;
	}

	char *executable = find_executable(arr[0], env_list);
	if (!executable)
	{
		printf("%s: command not found\n", arr[0]);
		free(arr);
		return;
	}

	pid_t pid = fork(); // fork hace que el programa pase de - a =
	if (pid == 0)
	{
		// Proceso hijo: ejecutar el comando
		char **envp = convert_env_list_to_array(env_list); // Convierte env_list a un array
		if (execve(executable, arr, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);  // Proceso padre: esperar al hijo
	else
		perror("fork");

	free(executable);
	free(arr);
}

int	is_builtin(t_command *command)
{
	if (!command || !command->tokens || !command->tokens->value)
		return 0; // Si es nulo o no tiene tokens, no es builtin
	if (ft_strcmp(command->tokens->value, "cd") == 0 ||
		ft_strcmp(command->tokens->value, "echo") == 0 ||
		ft_strcmp(command->tokens->value, "env") == 0 ||
		ft_strcmp(command->tokens->value, "export") == 0 ||
		ft_strcmp(command->tokens->value, "unset") == 0 ||
		ft_strcmp(command->tokens->value, "exit") == 0 ||
		ft_strcmp(command->tokens->value, "pwd") == 0)
	{
		return (1); // Es builtin
	}
	return (0); // No es builtin
}

void	execute_builtin(t_command *command, t_env *env_list)
{
	if (ft_strcmp(command->tokens->value, "cd") == 0)
		builtin_cd(command);
	else if (ft_strcmp(command->tokens->value, "echo") == 0)
		builtin_echo(command);
	else if (ft_strcmp(command->tokens->value, "env") == 0)
		builtin_env(env_list);
	else if (ft_strcmp(command->tokens->value, "export") == 0)
		builtin_export(command, env_list);
	else if (ft_strcmp(command->tokens->value, "unset") == 0)
		builtin_unset(command, env_list);
	else if (ft_strcmp(command->tokens->value, "exit") == 0)
		builtin_exit(command);
	else if (ft_strcmp(command->tokens->value, "pwd") == 0)
		builtin_pwd();
}

int commands_contain_pipes(t_command *commands)
{
	t_command *current = commands;

	while (current)
	{
		t_token *token = current->tokens;
		while (token)
		{
			if (ft_strcmp(token->value, "|") == 0)
				return (1);
			token = token->next;
		}
		current = current->next;
	}
	return (0);
}

void	execute_commands(t_command *commands, t_env *env_list)
{
	t_command *current = commands;

	if (commands_contain_pipes(commands))
		execute_pipeline(commands, count_commands(commands), env_list);
	else
	{
		while (current)
		{
			if (current->tokens)
			{
				if (is_builtin(current))
					execute_builtin(current, env_list);
				else
					execute_external(current, env_list);
			}
			current = current->next;
		}
	}
}
