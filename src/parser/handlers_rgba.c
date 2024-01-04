/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handlers_rgba.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 17:48:13 by mdekker       #+#    #+#                 */
/*   Updated: 2024/01/04 17:49:13 by mdekker       ########   odam.nl         */
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
	if (split == NULL || count_arr(split) != 3)
		return (printf("Error\nRGBA function failed. Wrong input.\n"), -1);
	while (i < 3)
	{
		if (checkstr(split[i], "0123456789") == 0)
			return (printf("Error\nWrong argument type\n"), -1);
		rgba[i] = ft_atoi(split[i]);
		if (rgba[i] < 0 || rgba[i] > 255)
			return (printf("Error\nWrong argument type\n"), -1);
		i++;
	}
	ft_free(split);
	return (rgba[0] << 24 | rgba[1] << 16 | rgba[2] << 8 | 255);
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

bool	handle_F(char *str, t_data *data)
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

bool	handle_C(char *str, t_data *data)
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
