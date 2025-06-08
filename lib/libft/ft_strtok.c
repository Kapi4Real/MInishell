#include "libft.h"

static char *save_ptr = NULL;

char *ft_strtok(char *str, const char *delim)
{
    char *token_start;
    char *token_end;

    if (str == NULL)
    {
        if (save_ptr == NULL)
            return (NULL);
        str = save_ptr;
    }

    // Skip leading delimiters
    while (*str && ft_strchr(delim, *str))
        str++;
    if (*str == '\0')
    {
        save_ptr = NULL;
        return (NULL);
    }

    // Find end of token
    token_start = str;
    while (*str && !ft_strchr(delim, *str))
        str++;
    token_end = str;

    if (*token_end != '\0')
    {
        *token_end = '\0';
        save_ptr = token_end + 1;
    }
    else
    {
        save_ptr = NULL;
    }

    return (token_start);
}
