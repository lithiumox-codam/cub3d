/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/17 16:20:25 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/17 17:52:11 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCould not open file\n"), 1);
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}