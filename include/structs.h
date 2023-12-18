/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/17 19:33:48 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/18 20:20:23 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <cub3d.h>

/**
 * @brief The different types of map elements
 *
 * EMPTY is used for the map array to indicate that the element is empty
 * FLOOR is used for the map array to indicate that the element is a floor
 * WALL is used for the map array to indicate that the element is a wall
 * PLAYER is used for the map array to indicate that the element is the player
 */
typedef enum e_map_types
{
	EMPTY = 0,
	FLOOR = 1,
	WALL = 2,
	PLAYER = 3,
}				t_map_types;

/**
 * @brief The struct that holds the map
 *
 * @param map The map array
 * @param width The width of the map
 * @param height The height of the map
 */
typedef struct s_map
{
	t_map_types	**array;
	int			width;
	int			height;
}				t_map;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir;
}				t_player;

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	int			floor;
	int			ceiling;
}				t_textures;

typedef struct s_data
{
	t_map		map;
	t_player	player;
	t_vector	strings;
	t_textures	textures;
}				t_data;

#endif
