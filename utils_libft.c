#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (s1[i] - s2[i]);
}

#include <stdlib.h>

char *ft_strndup(const char *s, size_t n)
{
	size_t i;
	char *dup;

	// Reservar memoria para la nueva cadena (+1 para el terminador '\0')
	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return NULL;

	// Copiar los primeros n caracteres o hasta que termine la cadena
	i = 0;
	while (i < n && s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}

	// Asegurarse de que la cadena esté terminada con '\0'
	dup[i] = '\0';

	return dup;
}
