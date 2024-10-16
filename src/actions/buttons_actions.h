/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:13:57 by tdelage           #+#    #+#             */
/*   Updated: 2024/09/12 04:01:27 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTONS_ACTIONS_H
# define BUTTONS_ACTIONS_H

# include <mlx/mmlx.h>

struct	s_vec2i
{
	int	x;
	int	y;
};

void	ufloat_dec(float *ptr);
void	button_quit(struct s_mlx *mlx);
void	button_add_scene(struct s_mlx *mlx);
void	button_scene_modify_sphere(struct s_mlx *mlx, int index);
void	button_scene_modify_plane(struct s_mlx *mlx, int index);
void	button_scene_modify_light(struct s_mlx *mlx, int index);
void	button_scene_modify_cylinder(struct s_mlx *mlx, int index);
void	button_scene_modify_ambient(struct s_mlx *mlx, int index);
void	button_scene_modify_float(struct s_mlx *mlx, struct s_vec2i pos,
			float *data, char *text);
void	button_scene_modify_float_0_1(struct s_mlx *mlx, struct s_vec2i pos,
			float *data, char *text);
void	button_scene_modify_float_1_1(struct s_mlx *mlx, struct s_vec2i pos,
			float *data, char *text);
void	button_scene_modify_float_full(struct s_mlx *mlx, struct s_vec2i pos,
			float *data, char *text);
void	button_scene_modify_color(struct s_mlx *mlx, struct s_vec2i pos,
			union u_color *color);
void	button_scene_modify_vec3(struct s_mlx *mlx, struct s_vec2i pos,
			struct s_vec3 *pos_p);
void	button_scene_reset(struct s_mlx *mlx);
void	button_add_sphere(struct s_mlx *mlx);
void	button_add_light(struct s_mlx *mlx);
void	button_add_plane(struct s_mlx *mlx);
void	button_add_cylinder(struct s_mlx *mlx);
void	button_save(struct s_scene *scene);
void	button_list(struct s_mlx *mlx);
void	set_list_button(struct s_mlx *mlx, int start, int base, int number);
void	button_screen(struct s_mlx *mlx);

#endif // BUTTONS_ACTIONS_H
