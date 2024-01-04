/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/17 16:30:43 by mdekker       #+#    #+#                 */
/*   Updated: 2024/01/04 19:12:11 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

typedef struct s_func
{
	char		*str;
	bool		(*func_ptr)(char *, t_data *);
}				t_func;

static t_func	*return_arr(t_data *data)
{
	static t_func	func_array[] = {{"NO", handle_NO}, {"SO", handle_SO}, {"WE",
			handle_WE}, {"EA", handle_EA}, {"F ", handle_F}, {"C ", handle_C},
			{NULL, NULL}};

	return (func_array);
}

static bool	info_helper(t_data *data, char *str, t_func *arr, size_t *j)
{
	while (*str == ' ')
		str++;
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
	if (arr[*j].str == NULL)
		return (printf("Error\nWrong argument type: %.2s\n", str), false);
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

	func_array = return_arr(data);
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
		return (false);
	if (!parse_map(data, &i))
		return (false);
	return (true);
}
