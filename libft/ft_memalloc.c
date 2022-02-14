/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfum <kfum@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:53:11 by kfum              #+#    #+#             */
/*   Updated: 2021/11/29 11:14:00 by kfum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t n)
{
	char	*p;

	p = malloc(n);
	if (!p)
	{
		return (NULL);
	}
	ft_bzero(p, n);
	return (p);
}