/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skesuma <skesuma@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:21:50 by skesuma           #+#    #+#             */
/*   Updated: 2022/02/15 14:21:50 by skesuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_map
{
	size_t	size;
	char	*new_map;
}			t_map;

typedef struct s_coord
{
	size_t	x;
	size_t	y;
	char	letter;
}			t_coord;

typedef struct s_blocks
{
	size_t	nb_blocks;
	t_coord	**blocks;
}			t_blocks;

t_blocks	*init_blocks(char *s);
void		free_block(t_blocks *blocks);
int			lets_check(char *argv[]);
char		*read_file(char *filename);
void		print_map(char *s, int size);
void		free_map(t_map *map, t_coord *coord, size_t i);
t_map		*create_map(int size);
int			final_solution(char *s);

#endif
