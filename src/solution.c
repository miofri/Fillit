/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skesuma <skesuma@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:03:16 by skesuma           #+#    #+#             */
/*   Updated: 2022/03/08 18:03:16 by skesuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Round up number to get a square
*/
static int	round_up_sqrt(int i)
{
	int	size;

	size = 1;
	if (i == 1)
		return (1);
	while (size * size + 1 < i)
		size++;
	return (size);
}

/*
** Installs tetro pieces to the map after checking if
** the current position is empty.
*/
static int	install_blocks(t_map *map, t_coord *coor, size_t i)
{
	size_t	map_x;
	size_t	map_y;
	size_t	k;
	size_t	m;
	size_t	n;

	k = 0;
	map_x = i % map->size;
	map_y = i / map->size;
	while (k < 4)
	{
		m = map_x + coor[k].x;
		n = map_y + coor[k].y;
		if (map->new_map[m + n * map->size] != '.' || m >= map->size \
		|| n >= map->size)
			return (0);
		k++;
	}
	while (k > 0)
	{
		m = map_x + coor[--k].x;
		n = map_y + coor[k].y;
		map->new_map[m + n * map->size] = coor[0].letter;
	}
	return (1);
}

/*
** Check for the smallest square without overlap.
** Use recursion to check is there any block will fit the place.
** If solution didn't found, free map to avoid memory leak.
*/
static void	searching_solution(t_map *map, t_blocks *blocks,
size_t nb_blocks, size_t *found)
{
	size_t	i;
	size_t	count;

	count = 0;
	if (nb_blocks == blocks->nb_blocks)
		*found = 1;
	if (*found == 1)
		return ;
	i = -1;
	while (++i < (map->size * map->size) && !(*found))
	{
		if (install_blocks(map, blocks->blocks[nb_blocks], i))
		{
			if (count < 22)
			{
				searching_solution(map, blocks, nb_blocks + 1, found);
				count++;
			}
			else
				return ;
			if (*found == 0)
				free_map(map, blocks->blocks[nb_blocks], i);
		}
	}
	return ;
}

/*
** Part of searching solution, create map based on number of tetros and start
** the recursive loop to find the smallest square. if solution was not found,
** increase the map size and print out the correct solution and free
** unnecessary blocks and map memory.
*/
static int	output(t_blocks *blocks, size_t map_size)
{
	t_map	*map;
	size_t	found;
	size_t	nb_blocks;

	found = 0;
	nb_blocks = 0;
	while (!found)
	{
		map = create_map(map_size);
		if (!map)
			return (0);
		searching_solution(map, blocks, nb_blocks, &found);
		if (!found)
		{
			free(map->new_map);
			free(map);
			map_size++;
		}
	}
	print_map(map->new_map, map_size);
	free_block(blocks);
	free(map->new_map);
	free(map);
	return (1);
}

/*
** Searching for the solution to find the smallest square.
*/
int	final_solution(char **s)
{
	t_blocks	*blocks;
	size_t		map_size;

	blocks = parse(s);
	if (!blocks)
		return (0);
	map_size = round_up_sqrt(blocks->nb_blocks) * 2;
	output(blocks, map_size);
	return (1);
}
