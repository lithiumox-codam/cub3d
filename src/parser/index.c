/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/17 16:30:43 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/18 23:43:48 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	count_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

static int	get_rgba(char *str)
{
	char	**split;
	int		rgba[3];
	int		i;

	i = 0;
	split = ft_split(str, ',');
	if (split == NULL)
		return (printf("Error\nMalloc failed\n"), -1);
	if (count_arr(split) != 3)
		return (printf("Error\nWrong argument type\n"), -1);
	while (i < 3)
	{
		if (!ft_isdigit(split[i][0]))
			return (printf("Error\nWrong argument type\n"), -1);
		rgba[i] = ft_atoi(split[i]);
		if (rgba[i] < 0 || rgba[i] > 255)
			return (printf("Error\nWrong argument type\n"), -1);
		i++;
	}
	ft_free(split);
	return (rgba[0] << 24 | rgba[1] << 16 | rgba[2] << 8 | 255);
}

static bool	handle_NO(char *str, t_data *data)
{
	char	*path;

	path = ft_strtrim(str, "NO \n");
	if (path == NULL)
		return (printf("Error\nMalloc failed\n"), false);
	data->textures.north = path;
	return (true);
}

static bool	handle_SO(char *str, t_data *data)
{
	char	*path;

	path = ft_strtrim(str, "SO \n");
	if (path == NULL)
		return (printf("Error\nMalloc failed\n"), false);
	data->textures.south = path;
	return (true);
}

static bool	handle_WE(char *str, t_data *data)
{
	char	*path;

	path = ft_strtrim(str, "WE \n");
	if (path == NULL)
		return (printf("Error\nMalloc failed\n"), false);
	data->textures.west = path;
	return (true);
}

static bool	handle_EA(char *str, t_data *data)
{
	char	*path;

	path = ft_strtrim(str, "EA \n");
	if (path == NULL)
		return (printf("Error\nMalloc failed\n"), false);
	data->textures.east = path;
	return (true);
}

static bool	check_rgbstring(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (false);
		i++;
	}
	return (true);
}

static bool	handle_F(char *str, t_data *data)
{
	int		rgba;
	char	*rgba_str;

	rgba_str = ft_strtrim(str, "F \n");
	if (rgba_str == NULL)
		return (printf("Error\nMalloc failed\n"), false);
	if (!check_rgbstring(rgba_str))
		return (free(rgba_str), printf("Error\nWrong argument type\n"), false);
	rgba = get_rgba(rgba_str);
	free(rgba_str);
	if (rgba == -1)
		return (printf("Error\nMalloc failed\n"), false);
	data->textures.floor = rgba;
	return (true);
}

static bool	handle_C(char *str, t_data *data)
{
	int		rgba;
	char	*rgba_str;

	rgba_str = ft_strtrim(str, "C \n");
	if (rgba_str == NULL)
		return (printf("Error\nMalloc failed\n"), false);
	if (!check_rgbstring(rgba_str))
		return (free(rgba_str), printf("Error\nWrong argument type\n"), false);
	rgba = get_rgba(rgba_str);
	free(rgba_str);
	if (rgba == -1)
		return (printf("Error\nMalloc failed\n"), false);
	data->textures.ceiling = rgba;
	return (true);
}

typedef struct s_func
{
	char		*str;
	bool		(*func_ptr)(char *, t_data *);
}				t_func;

static t_func	*return_arr(void)
{
	static t_func func_array[] =
		{
			{"NO", handle_NO},
			{"SO", handle_SO},
			{"WE", handle_WE},
			{"EA", handle_EA},
			{"F ", handle_F},
			{"C ", handle_C},
			{NULL, NULL}};
	return (func_array);
}

static bool	info_helper(t_data *data, char *str, t_func *arr, size_t *j)
{
	while (arr[*j].str != NULL)
	{
		if (ft_strncmp(str, arr[*j].str, 2) == 0)
		{
			if (!arr[*j].func_ptr(str, data))
				return (false);
			else
				(*j) = 0;
			break ;
		}
		(*j)++;
	}
	return (true);
}

/**
 * @brief Parse non-map info from the file.
 * The function loops through the vector of strings and calls the correct
 * function for each string. Returns false if it encounters an error.
 *
 * @param data The main struct containing the vector with strings
 * @return true When all strings are parsed succesfully
 * @return false When an error occurs
 */
static bool	parse_info(t_data *data, size_t *i)
{
	t_func	*func_array;
	char	*str;
	size_t	j;

	func_array = return_arr();
	j = 0;
	while (*i < data->strings.length && *i < 6)
	{
		str = *(char **)vec_get(&data->strings, *i);
		if (!info_helper(data, str, func_array, &j))
			return (false);
		(*i)++;
	}
	if (*i != 6)
		return (printf("Error\nMissing arguments\n"), false);
	return (true);
}

/**
 * @brief Get the w maximum and h of the map
 *
 * @param data The main struct
 * @param i The index of the first string after the info
 */
void	get_w_and_h(t_data *data, size_t *i)
{
	char	*str;
	size_t	j;
	size_t	start;

	j = 0;
	start = *i;
	while (*i < data->strings.length)
	{
		str = *(char **)vec_get(&data->strings, *i);
		if (ft_strlen(str) > j)
			j = ft_strlen(str) - 1;
		(*i)++;
	}
	data->map.width = j;
	data->map.height = ((*i) - start);
	(*i) = start;
}

bool	create_2d_arr(t_data *data)
{
	int	i;

	i = 0;
	data->map.array = ft_calloc(data->map.height, sizeof(t_map_types **));
	if (data->map.array == NULL)
		return (printf("Error\nMalloc failed\n"), false);
	while ((size_t)i < data->map.height)
	{
		data->map.array[i] = ft_calloc(data->map.width, sizeof(t_map_types));
		if (data->map.array[i] == NULL)
		{
			while (i > 0)
			{
				free(data->map.array[i]);
				i--;
			}
			free(data->map.array);
			return (printf("Error\nMalloc failed\n"), false);
		}
		i++;
	}
	return (true);
}

static bool	player_helper(t_data *data, char p, size_t *j, size_t *k)
{
	if (data->player.x != 0 || data->player.y != 0)
		return (printf("Error\nMultiple players\n"), false);
	if (checkchar(p, "NSEW"))
	{
		if (p == 'N')
			data->player.dir = 0;
		else if (p == 'E')
			data->player.dir = 90;
		else if (p == 'S')
			data->player.dir = 180;
		else if (p == 'W')
			data->player.dir = 270;
	}
	data->player.x = *j;
	data->player.y = *k;
	data->map.array[*j][*k] = PLAYER;
	return (true);
}

/**
 * @brief Apply the strings to the map array
 *
 * @param data The main struct
 * @param i The index of the first string after the info
 * @return true When all strings are applied succesfully
 * @return false When an error occurs
 */
static bool	apply_strings_to_array(t_data *data, size_t *i)
{
	char	*str;
	size_t	j;
	size_t	k;

	j = 0;
	while (*i < data->strings.length)
	{
		str = *(char **)vec_get(&data->strings, *i);
		k = 0;
		while (str[k] != '\0')
		{
			if (str[k] == '1')
				data->map.array[j][k] = WALL;
			else if (str[k] == '0')
				data->map.array[j][k] = FLOOR;
			else if (str[k] != ' ' && checkchar(str[k], "NSEW"))
				if (!player_helper(data, str[k], &j, &k))
					return (false);
			k++;
		}
		j++;
		(*i)++;
	}
	return (true);
}

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

/**
 * @brief Parse the map from the file.
 * The function loops through the vector of strings and calls the correct
 * function for each string. Returns false if it encounters an error.
 *
 * @param data The main struct containing the vector with strings
 * @return true When all strings are parsed succesfully
 * @return false When an error occurs
 */
static bool	parse_map(t_data *data, size_t *i)
{
	get_w_and_h(data, i);
	if (!create_2d_arr(data))
		return (false);
	if (!apply_strings_to_array(data, i))
		return (false);
	if (!check_floor(data))
		return (false);
	print_array(data);
	return (true);
}

bool	parse(t_data *data)
{
	size_t	i;

	i = 0;
	if (!parse_info(data, &i))
		return (printf("ERROR: Map info is invalid\n"), false);
	if (!parse_map(data, &i))
		return (false);
	return (true);
}
