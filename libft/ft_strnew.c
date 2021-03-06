/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfum <kfum@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:45:59 by kfum              #+#    #+#             */
/*   Updated: 2021/12/08 13:11:12 by kfum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t n)
{
	char	*p;

	p = (char *)ft_memalloc(sizeof(char) * (n + 1));
	if (p == NULL)
	{
		return (NULL);
	}
	p[n] = '\0';
	while (n--)
	{
		p[n] = '\0';
	}
	return (p);
}
