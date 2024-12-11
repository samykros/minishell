/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:11:19 by spascual          #+#    #+#             */
/*   Updated: 2024/12/11 16:20:23 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/wait.h>

// execve necesita array, por eso pasas de link list a array

char **convert_tokens_to_arr(t_token *tokens)
{
    int count = 0;
    t_token *current = tokens;

    // Contar el número de tokens
    while (current)
	{
        count++;
        current = current->next;
    }

    // Reservar memoria para arr
    char **arr = malloc((count + 1) * sizeof(char *));
    if (!arr)
        return NULL;

    // Copiar los valores de los tokens a arr
    current = tokens;
    for (int i = 0; i < count; i++)
	{
        arr[i] = strdup(current->value); // Crear una copia del valor
        current = current->next;
    }
    arr[count] = NULL; // Terminar el array con NULL

    return arr;
}

char *find_executable(const char *cmd, t_env *env_list)
{
    char *path = get_env_value(env_list, "PATH"); // Obtener la variable PATH
    if (!path)
        return NULL;

    char *path_copy = strdup(path);
    char *token = strtok(path_copy, ":");
    char *full_path = NULL;

    while (token)
	{
        full_path = malloc(strlen(token) + strlen(cmd) + 2);
        if (!full_path)
		{
            free(path_copy);
            return NULL;
        }

        sprintf(full_path, "%s/%s", token, cmd);
        if (access(full_path, X_OK) == 0)
		{ // Comprobar si es ejecutable
            free(path_copy);
            return full_path; // Devolver el camino completo
        }

        free(full_path);
        full_path = NULL;
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL; // No se encontró el ejecutable
}

char **convert_env_list_to_array(t_env *env_list)
{
    int count = 0;
    t_env *current = env_list;

    // Contar cuántas variables de entorno hay
    while (current)
	{
        count++;
        current = current->next;
    }

    // Reservar memoria para el array de strings
    char **envp = malloc((count + 1) * sizeof(char *));
    if (!envp)
        return NULL;

    current = env_list;
    for (int i = 0; i < count; i++)
	{
        size_t size = strlen(current->name) + strlen(current->value) + 2; // pq +2? (=, \0) ?
        envp[i] = malloc(size);
        if (!envp[i])
		{
            for (int j = 0; j < i; j++) // Liberar memoria en caso de error
                free(envp[j]);
            free(envp);
            return NULL;
        }
        sprintf(envp[i], "%s=%s", current->name, current->value); // Formato "NOMBRE=VALOR"
        current = current->next;
    }
    envp[count] = NULL; // Terminar con NULL

    return envp;
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
	{
        // Proceso padre: esperar al hijo
        waitpid(pid, NULL, 0);
    }
	else
	{
        perror("fork");
    }

    free(executable);
    free(arr);
}