
#include "fillit.h"

char	*read_file(char *filename)
{
	int		fd;
	char	*content;
	int		ret;

	content = ft_strnew(546);
	if (!content)
	{
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	ret = read(fd, content, 546);
	if (fd == -1 || ret == -1)
	{
		ft_putstr("error\n");
		return (NULL);
	}
	close(fd);
	return (content);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		ft_putstr("usage: fillit source_file\n");
	if (read_file(argv[1]) == NULL)
		return (0);
	if (lets_check(argv) != 0)
	{
		ft_putstr("error\n");
		return (0);
	}
	if (!final_solution(argv))
		return (0);
	return (0);
}
