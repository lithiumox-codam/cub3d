/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/17 16:20:25 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/17 20:35:31 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*return_string(t_vector *v)
{
	char	*str;

	vec_resize(v, v->length + 1);
	vec_char_push(v, '\0');
	str = (char *)v->data;
	return (str);
}

void	push_string(t_vector *v, char *str)
{
	while (*str != '\0')
	{
		vec_char_push(v, *str);
		str++;
	}
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_vector	v;

	vec_init(&v, 50, sizeof(char), NULL);
	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCould not open file\n"), 1);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		push_string(&v, line);
		free(line);
	}
	printf("string: %s\n", return_string(&v));
	free(v.data);
	close(fd);
	return (0);
}
