/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skesuma <skesuma@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:21:56 by skesuma           #+#    #+#             */
/*   Updated: 2022/02/15 14:21:56 by skesuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Print map
*/
void	print_map(char *s, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (j == size)
		{
			ft_putchar('\n');
			j = 0;
		}
		ft_putchar(s[i]);
		j++;
		i++;
	}
	ft_putchar('\n');
}

/*
** Free map
*/

void	free_map(t_map *map, t_coord *coord, size_t i)
{
	size_t	map_width;
	size_t	map_height;
	size_t	j;
	size_t	x;
	size_t	y;

	j = 0;
	map_width = i % map->size;
	map_height = i / map->size;
	while (j < 4)
	{
		x = map_width + coord[j].x;
		y = map_height + coord[j].y;
		if (map->new_map[x + y * map->size] == coord[0].letter)
		{
			map->new_map[x + y * map->size] = '.';
		}
		j++;
	}
}

/*
** Create new map
*/

t_map	*create_map(int size)
{
	t_map	*map;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	if (!map)
	{
		return (NULL);
	}
	map->size = size;
	map->new_map = ft_strnew(size * size);
	ft_memset(map->new_map, '.', size * size);
	if (map->new_map == NULL)
	{
		return (NULL);
	}
	return (map);
}
