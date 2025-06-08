#include "libft.h"

int ft_isdigit_str(const char *str)
{
    if (!str)
        return 0;
        
    while (*str) {
        if (!ft_isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}
