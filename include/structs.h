/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/17 19:33:48 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/17 19:48:50 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	EMPTY = -1,
	FLOOR = 0,
	WALL = 1,
	PLAYER = 2,
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
	t_map_types	**map;
	int			width;
	int			height;
}				t_map;
