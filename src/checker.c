/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skesuma <skesuma@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:21:33 by skesuma           #+#    #+#             */
/*   Updated: 2022/02/15 14:21:33 by skesuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
checks that: 1. there are exactly 21 lines for each grid.
2. there's \n at every 20th array item.
3. there's \n at the end of each line.
4. there's no other char except '.', '#' and '\n'.
*/
static int	format_checker(int ret, char *buf)
{
	int	i;

	buf[ret] = '\0';
	if ((ret + 1) % 21 != 0 || ret == 0 || ret == -1 || ret > 545)
		return (-1);
	i = 0;
	if (buf[i] != '.' && buf[i] != '#')
		return (-1);
	while (buf[++i] != '\0')
	{
		if (i % 21 == 0 && buf[i - 1] != '\n')
			return (-1);
		else if ((i % 21) % 5 == 0 && buf[i - 1] != '\n')
			return (-1);
		else if (buf[i] != '.' && buf[i] != '#' && buf[i] != '\n')
			return (-1);
	}
	return (i);
}

/*
Executed specifically on the last line of a tetros using call by reference
in order to solve out-of-range issues, and also eliminating the need to return
multiple values as we're changing the variable's value by accessing them via
address instead of passing copies of them.
*/
static void	touching_lastline(int *y, char *buf, int *t2, int *t1)
{
	if (buf[*y] == '#')
	{
		if (buf[*y + 1] == '#' && buf[*y - 1] == '#')
			(*t2)++;
		else if ((buf[*y + 1] == '#' || buf[*y - 1] == '#') && \
				(buf[*y - 5] == '#'))
			(*t2)++;
		else if (buf[*y + 1] == '#' || buf[*y - 1] == '#' || \
				buf[*y - 5] == '#')
			(*t1)++;
		else
			*y = 21;
	}
}

/*
t2 = touching 2 blocks. t1 = touching 1 block.
checking how many blocks touch each other and fulfil the conditions for
a valid tetros.
*/
static int	touching(int t2, char *buf, int t1, int y)
{
	while (++y < 21)
	{
		if (buf[y] == '#')
		{
			if (y > 14)
				touching_lastline(&y, buf, &t2, &t1);
			else if (buf[y + 5] == '#' && buf[y - 5] == '#')
				t2++;
			else if (buf[y + 1] == '#' && buf[y - 1] == '#')
				t2++;
			else if ((buf[y + 1] == '#' || buf[y - 1] == '#') && \
					(buf[y - 5] == '#' || buf[y + 5] == '#'))
				t2++;
			else if (buf[y + 1] == '#' || buf[y - 1] == '#' || \
					buf [y + 5] == '#' || buf[y - 5] == '#')
				t1++;
			else
				return (-1);
		}
	}
	if ((t1 == t2) || (t1 == 3 && t2 == 1) || (t1 == 0 && t2 == 4))
		return (0);
	return (-1);
}

/*
checks that for every 21 chars, there are four '#'.
*/
static int	block_checker(int i, char *buf, int fd, int ret)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y <= i)
	{
		if (buf[y] == '#')
			x++;
		if ((y + 1) % 21 == 0 && x != 4)
			return (-1);
		else if ((y + 1) % 21 == 0 && x == 4)
			x = 0;
		y++;
	}
	y = -1;
	i = 0;
	while (read(fd, buf, 21) && ret != -1)
	{
		buf[21] = '\0';
		ret = touching(i, buf, x, y);
	}
	return (ret);
}

int	lets_check(char *argv[])
{
	int		check;
	int		fd;
	char	buf[546];
	int		ret;

	fd = open(argv[1], O_RDONLY);
	ret = read(fd, buf, 546);
	if (fd == -1 || ret == -1)
		return (-1);
	check = format_checker(ret, buf);
	if (check == -1)
		return (-1);
	close(fd);
	ret = 0;
	fd = open(argv[1], O_RDONLY);
	check = block_checker(check, buf, fd, ret);
	if (check == -1)
		return (-1);
	close(fd);
	return (0);
}
