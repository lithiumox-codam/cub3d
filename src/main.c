/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/17 16:20:25 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/21 02:30:55 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * @brief A function that clears the map array.
 *
 * @param array The array to clear.
 * @param height The height of the array.
 */
void	clear_2d_array(t_map_types **array, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_all(t_data *data)
{
	free(data->textures.north);
	free(data->textures.south);
	free(data->textures.east);
	free(data->textures.west);
	vec_free(&data->strings);
	clear_2d_array(data->map.array, data->map.height);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (printf("Error\nWrong number of arguments\n"), 1);
	data = ft_calloc(1, sizeof(t_data));
	if (!init(data, av[1]))
		return (free_all(data), 1);
	if (!parse(data))
		return (free_all(data), 1);

	printf("NO: %s\n", data->textures.north);
	printf("SO: %s\n", data->textures.south);
	printf("EA: %s\n", data->textures.east);
	printf("WE: %s\n", data->textures.west);
	printf("F: %d\n", data->textures.floor);
	printf("C: %d\n", data->textures.ceiling);
	printf("Map:\n");
	printf("Width: %d\n", data->map.width);
	printf("Height: %d\n", data->map.height);
	free_all(data);
	return (0);
}
