

#include "libft.h"

int ft_rounded(int i)
{
    int j;

    j = 0;
    if (i <= 0)
    {
        return (0);
    }
    if (i == 1)
    {
        return (1);
    }
    while (j <= i && j <= 46340)
    {
        if (j * j >= i)
        {
            return (j);
        }
        j++;
    }
    return (0);
}
