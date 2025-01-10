/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:07:33 by spascual          #+#    #+#             */
/*   Updated: 2025/01/09 16:20:24 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// cuando tengas libft quita isdigit y atoi
int	ft_isdigit(int s)
{
	if (s >= '0' && s <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = sign * (-1);
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int is_numeric(const char *str)
{
	int	i;

	i = 0;

	if (str[i] == '-' || str[i] == '+')
		i++;  // Permitir un signo opcional al principio
	if (!str[i])
		return (0);  // La cadena solo tenía un signo
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);  // Carácter que no es dígito
		i++;
	}
	return (1);
}

void builtin_exit(t_command *command)
{
	t_token *arg = command->tokens->next;
	int exit_code;

	if (arg && arg->next)
	{
		printf("exit\nexit: too many arguments\n"); // Bash pone exit y luego el error
		return;
	}
	if (arg)
	{
		if (is_numeric(arg->value))
		{
			exit_code = ft_atoi(arg->value); // Convertir el argumento a un número
			printf("exit\n");
			exit(exit_code);
		}
		else
		{
			printf("exit\nexit: numeric argument required\n");
			exit(0);  // Salir con código 0 si arg no es numerico
		}
	}
	printf("exit\n");
	exit(0);  // Salir con código 0 si no hay argumentos
}
