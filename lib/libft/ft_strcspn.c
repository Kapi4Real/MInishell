#include "libft.h" 

size_t ft_strcspn(const char *s, const char *reject)
{
    size_t len = 0;

    while (s[len] && !ft_strchr(reject, s[len]))
        len++;

    return (len);
}
