/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:11:19 by spascual          #+#    #+#             */
/*   Updated: 2024/12/15 16:51:28 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_pipeline(t_command *commands, int num_commands, t_env *env_list)
{
    int i = 0;
    int pipefd[2]; // almacenar identificadores de extremos de un pipe. pipefd[0] lectura, pipefd[1] escritura
    int last_fd = 0; // para mantener el extremo de lectura del último pipe abierto
    t_command *current_cmd = commands;

    while (current_cmd != NULL && i < num_commands)
    {
        if (i < num_commands - 1)
		{
            if (pipe(pipefd) == -1)
			{
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid_t pid = fork();
        if (pid == 0) // Proceso hijo
        {
            if (i > 0)
			{
                dup2(last_fd, 0); // Establece stdin al extremo de lectura del pipe anterior
                close(last_fd);
            }

            if (i < num_commands - 1)
			{
                close(pipefd[0]); // Cierra el extremo de lectura del nuevo pipe
                dup2(pipefd[1], 1); // Establece stdout al extremo de escritura del nuevo pipe
                close(pipefd[1]);
            }

            // Convierte los tokens a array para execve
            char **args = convert_tokens_to_arr(current_cmd->tokens);
            if (execve(args[0], args, convert_env_list_to_array(env_list)) == -1)
			{
                perror("execve");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else if (pid < 0)
		{
            perror("fork");
            exit(EXIT_FAILURE);
        }

        // Proceso padre
        if (i > 0) // no tendria q ser pid en vez de i ?
            close(last_fd);
        if (i < num_commands - 1)
		{
            close(pipefd[1]); // Cierra el extremo de escritura del nuevo pipe en el padre
            last_fd = pipefd[0];
        }
		else
            close(pipefd[0]);
        current_cmd = current_cmd->next;
        i++;
    }

    // Esperar a que todos los hijos terminen
    while (wait(NULL) > 0);
}
