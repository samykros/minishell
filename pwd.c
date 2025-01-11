/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:46 by spascual          #+#    #+#             */
/*   Updated: 2025/01/11 13:45:35 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// cuento como edge case que el directorio pueda ser >1024 ?
void	builtin_pwd(void)
{
	char	*cwd;
	size_t	size;

	size = 1024;
	cwd = malloc(size);
	if (!cwd)
	{
		perror("malloc");
		return ;
	}
	if (getcwd(cwd, size) == NULL)
	{
		perror("pwd");
		free(cwd);
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}
