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

t_blocks	*file_reader(char *argv[], t_blocks *block, char *buf)
{
	int		fd;
	int		ret;
	int		count;

	count = 0;
	if (block == NULL)
		return (NULL);
	fd = open(argv[1], O_RDONLY);
	ret = read(fd, buf, 21);
	while (ret > 0)
	{
		count++;
		ret = read(fd, buf, 21);
	}
	close(fd);
	block->nb_blocks = count;
	block->blocks = (t_coord **)malloc(sizeof(t_coord *) * count);
	if (block->blocks == NULL)
		return (NULL);
	return (block);
}

int	take_coor(int fd, char *buf, t_blocks *block, size_t o)
{
	char	letter;
	int		i;
	size_t	k;

	letter = 'A';
	while (read(fd, buf, 21))
	{
		block->blocks[o] = (t_coord *)malloc(sizeof(t_coord) * 4);
		if (block->blocks[o] == NULL)
			return (0);
		buf[21] = '\0';
		k = 0;
		i = -1;
		while (++i < 21)
		{
			if (buf[i] == '#')
			{
				block->blocks[o][k].x = i % 5;
				block->blocks[o][k].y = i / 5;
				block->blocks[o][k++].letter = letter + o;
			}
		}
		o++;
	}
	return (1);
}

/*
** Shift blocks to the correct>blocksition
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

t_blocks	*parse(char *argv[])
{
	t_blocks	*block;
	int			fd;
	char		*buf;
	size_t		o;

	o = 0;
	block = (t_blocks *)malloc(sizeof(t_blocks));
	if (!block)
		return (0);
	buf = (char *)malloc(sizeof(char) * 546);
	if (!buf)
		return (0);
	block = file_reader(argv, block, buf);
	fd = open(argv[1], O_RDONLY);
	if (take_coor(fd, buf, block, o) == 0)
		return (0);
	close(fd);
	move_blocks(block);
	return (block);
}
