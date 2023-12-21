/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 22:53:43 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/21 02:21:44 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * @brief For every floor tile check if it is surrounded by walls
 * or other floor tiles or the player or empty tiles or the edge of the map.
 *
 */
bool	check_floor(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.array[y][x] == FLOOR
				|| data->map.array[y][x] == PLAYER)
			{
				if (x == 0 || x == data->map.width - 1 || y == 0
					|| y == data->map.height - 1)
					return (printf("Error\nMap is not closed\n"), false);
				if (data->map.array[y][x + 1] == EMPTY || data->map.array[y][x
					- 1] == EMPTY || data->map.array[y + 1][x] == EMPTY
					|| data->map.array[y - 1][x] == EMPTY)
					return (printf("Error\nMap is not closed\n"), false);
			}
			x++;
		}
		y++;
	}
	return (true);
}
