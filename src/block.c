/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skesuma <skesuma@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:21:22 by skesuma           #+#    #+#             */
/*   Updated: 2022/02/15 14:21:22 by skesuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	Place blocks to the top left corner
**	Set block's letter value to struct
*/
static int	place_blocks(t_blocks *blocks, char *s)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	c;

	i = 0;
	c = 'A';
	while (i < blocks->nb_blocks)
	{
		k = 0;
		blocks->blocks[i] = (t_coord *)ft_memalloc(sizeof(t_coord) * 4);
		if (blocks->blocks[i] == NULL)
			return (0);
		j = i * 21;
		while (j % 21 != 20)
		{
			if (s[j] == '#')
			{
				blocks->blocks[i][k].x = (j - i * 21) % 5;
				blocks->blocks[i][k].y = (j - i * 21) / 5;
				blocks->blocks[i][k++].letter = i + c;
			}
			j++;
		}
		i++;
	}
	return (1);
}

/*
** Shift blocks to the correct position
*/
static void	move_blocks(t_blocks *blocks)
{
	size_t	i;

	i = 0;
	while (i < blocks->nb_blocks)
	{
		while (blocks->blocks[i][0].x && blocks->blocks[i][1].x
			&& blocks->blocks[i][2].x && blocks->blocks[i][3].x)
		{
			blocks->blocks[i][0].x--;
			blocks->blocks[i][1].x--;
			blocks->blocks[i][2].x--;
			blocks->blocks[i][3].x--;
		}
		while (blocks->blocks[i][0].y && blocks->blocks[i][1].y
			&& blocks->blocks[i][2].y && blocks->blocks[i][3].y)
		{
			blocks->blocks[i][0].y--;
			blocks->blocks[i][1].y--;
			blocks->blocks[i][2].y--;
			blocks->blocks[i][3].y--;
		}
		i++;
	}
}

/*
** Free blocks
*/
void	free_block(t_blocks *blocks)
{
	size_t	i;

	i = 0;
	while (i < blocks->nb_blocks)
	{
		free(blocks->blocks[i]);
		i++;
	}
	free(blocks->blocks);
	free(blocks);
}
/*
** Initial blocks
*/

t_blocks	*init_blocks(char *s)
{
	int			i;
	size_t		count;
	t_blocks	*blocks;

	i = 0;
	count = 0;
	blocks = (t_blocks *)ft_memalloc(sizeof(t_blocks));
	if (!blocks)
		return (0);
	while (s[i])
	{
		if (i % 21 == 0)
			count++;
		i++;
	}
	blocks->nb_blocks = count;
	blocks->blocks = (t_coord **)ft_memalloc(sizeof(t_coord *) * count);
	if (blocks->blocks == NULL)
		return (0);
	if (place_blocks(blocks, s) == 0)
		return (0);
	move_blocks(blocks);
	return (blocks);
}
