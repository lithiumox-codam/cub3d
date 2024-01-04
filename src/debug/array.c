/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 13:32:43 by mdekker       #+#    #+#                 */
/*   Updated: 2024/01/04 13:33:01 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * @brief Prints the array to the terminal
 *
 * @param data The main struct
 */
void	print_array(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.array[i][j] == WALL)
				printf("🟥");
			else if (data->map.array[i][j] == FLOOR)
				printf("⬜️");
			else if (data->map.array[i][j] == PLAYER)
				printf("👶");
			else if (data->map.array[i][j] == EMPTY)
				printf("⬛️");
			j++;
		}
		printf("\n");
		i++;
	}
}
