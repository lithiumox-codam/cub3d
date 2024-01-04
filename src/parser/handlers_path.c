/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handlers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 21:13:18 by mdekker       #+#    #+#                 */
/*   Updated: 2024/01/04 17:47:08 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	handle_NO(char *str, t_data *data)
{
	char	*path;

	path = ft_strtrim(str, "NO \n");
	if (path == NULL)
		return (printf("Error\nMalloc failed\n"), false);
	data->textures.north = path;
	return (true);
}

bool	handle_SO(char *str, t_data *data)
{
	char	*path;

	path = ft_strtrim(str, "SO \n");
	if (path == NULL)
		return (printf("Error\nMalloc failed\n"), false);
	data->textures.south = path;
	return (true);
}

bool	handle_WE(char *str, t_data *data)
{
	char	*path;

	path = ft_strtrim(str, "WE \n");
	if (path == NULL)
		return (printf("Error\nMalloc failed\n"), false);
	data->textures.west = path;
	return (true);
}

bool	handle_EA(char *str, t_data *data)
{
	char	*path;

	path = ft_strtrim(str, "EA \n");
	if (path == NULL)
		return (printf("Error\nMalloc failed\n"), false);
	data->textures.east = path;
	return (true);
}
