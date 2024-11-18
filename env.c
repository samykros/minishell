#include "minishell.h"

// No hecho !!!!!!!

// t_env *init_env(char **env)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (env[i][j])
// 	{
// 		j = 0;
		
// 	}
// }

void free_env(t_env *env)
{
	while (env)
	{
		t_env *tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}
