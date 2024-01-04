/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/17 16:08:19 by mdekker       #+#    #+#                 */
/*   Updated: 2024/01/04 18:08:36 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <structs.h>
# include <unistd.h>

bool	init(t_data *data, char *file);
bool	check_floor(t_data *data);

/*
 ** Parser
 */
bool	parse(t_data *data);
bool	apply_strings_to_array(t_data *data, size_t *i);
bool	create_2d_arr(t_data *data);
void	get_w_and_h(t_data *data, size_t *i);
bool	handle_NO(char *str, t_data *data);
bool	handle_SO(char *str, t_data *data);
bool	handle_WE(char *str, t_data *data);
bool	handle_EA(char *str, t_data *data);
bool	handle_S(char *str, t_data *data);
bool	handle_F(char *str, t_data *data);
bool	handle_C(char *str, t_data *data);

/*
 ** Debug
 */
void	print_array(t_data *data);
#endif
