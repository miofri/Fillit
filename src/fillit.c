/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skesuma <skesuma@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:21:42 by skesuma           #+#    #+#             */
/*   Updated: 2022/02/15 14:21:42 by skesuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char *argv[])
{
	char	*filecontent;

	if (argc != 2)
		ft_putstr("usage: fillit source_file\n");
	filecontent = read_file(argv[1]);
	if (filecontent == NULL)
		return (0);
	if (lets_check(argv) != 0)
	{
		ft_putstr("error\n");
		return (0);
	}
	if (!final_solution(filecontent))
		return (0);
	free(filecontent);
	return (0);
}
