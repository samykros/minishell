#include "minishell.h"

// Verifica si el carácter actual es una comilla
int is_quote(char c)
{
    if (c == '\'' || c == '"') // ESTO '\'' ??
        return 1;
    return 0;
}

int is_operator(char c)
{
    if (c == '>' || c == '<' || c == '|')
        return 1;
    return 0;
}

int is_envvariable(char c)
{
    if (c == '$')
        return 1;
    return 0;
}

int is_end_of_input(const char *input, int pos)
{
    if (input[pos] == '\0')
        return 1;
    return 0;
}

void free_tokens(t_token *tokens)
{
    t_token *temp;
    while (tokens) {
        temp = tokens;
        tokens = tokens->next;
        free(temp->value);  // Liberar el valor del token
        free(temp);         // Liberar el nodo del token
    }
}

char *concatenar_tokens(t_token *tokens)
{
    t_token *temp = tokens;
    int total_length = 0;

    // Calcular la longitud total de los strings de los tokens
    while (temp) {
        total_length += strlen(temp->value) + 1;  // +1 para el espacio entre tokens
        temp = temp->next;
    }

    // Reservar memoria para el string concatenado
    char *command_str = malloc(total_length + 1);  // +1 para el null terminator
    if (!command_str)
        return NULL;

    // Concatenar los valores de los tokens en command_str
    command_str[0] = '\0';  // Iniciar con una cadena vacía
    temp = tokens;
    while (temp) {
        strcat(command_str, temp->value);  // Añadir el token al string
        if (temp->next)
            strcat(command_str, " ");     // Añadir un espacio entre tokens
        temp = temp->next;
    }

    return command_str;
}

void add_command_to_list(t_command **command_list, char *command_str)
{
    t_command *new_command = malloc(sizeof(t_command));
    if (!new_command)
        return;
    new_command->command_str = command_str;
    new_command->next = NULL;

    // Si la lista está vacía, el nuevo comando es el primero
    if (!*command_list) {
        *command_list = new_command;
    } else {
        // Si no, agregar al final de la lista
        t_command *temp = *command_list;
        while (temp->next)
            temp = temp->next;
        temp->next = new_command;
    }
}
