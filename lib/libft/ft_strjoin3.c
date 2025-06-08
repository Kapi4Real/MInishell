#include "libft.h"

char *ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
    char *tmp;
    char *result;

    if (!s1 || !s2 || !s3)
        return NULL;
    tmp = ft_strjoin(s1, s2);
    result = ft_strjoin(tmp, s3);
    free(tmp);
    return result;
}
