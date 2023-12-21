/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:25:05 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/21 02:06:55 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	free_strings(void *data)
{
	free(*(char **)data);
}

/**
 * @brief The init function reads the file and puts the read strings into
 * a vector so I dont have to read the file twice.
 *
 * @param cub3d The main struct
 * @param file
 * @return true
 * @return false
 */
bool	init(t_data *data, char *file)
{
	int		fd;
	char	*line;

	vec_init(&data->strings, 10, sizeof(void **), free_strings);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCould not open file\n"), 1);
	line = "\0";
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (data->strings.length > 6 && line[0] == '\n')
			return (printf("Error\nMap contains enters\n"), false);
		if (line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		vec_push(&data->strings, &line);
	}
	return (true);
}
