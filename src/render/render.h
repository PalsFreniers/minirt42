/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 04:16:46 by maamine           #+#    #+#             */
/*   Updated: 2025/01/31 23:33:09 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <mlx/mmlx.h>
# include <render/collision.h>

# define EASE_OUT_ATTENUATION 0.01f
# define PHONG_EXPONENT 20
# define LIGHT_ATTENUATION 0.004f
# define MAX_DEPTH 25000.0f
# define NO_COLLIDE_DIST 0.01f

typedef struct s_render_color
{
	float		r;
	float		g;
	float		b;
}				t_render_color;

void			loop_render(struct s_mlx *mlx);

t_render_color	render_color_black(void);
mlx_color		rgb_to_mlx_color(union u_color color);
t_render_color	rgb_to_render_color(union u_color color);
mlx_color		render_to_mlx_color(t_render_color color);
t_render_color	filter_color(t_render_color color, t_render_color filter);
t_render_color	color_scal_mul(t_render_color color, float f);
t_render_color	color_add(t_render_color a, t_render_color b);
mlx_color		get_light_color(struct s_mlx *mlx);
t_render_color	lit_color(struct s_mlx *mlx, t_collision *collision,
					struct s_light *light);
struct s_object	*get_map_light(struct s_scene *scene);
struct s_object	*get_real_light(struct s_scene *scene);
void			draw_pixel(struct s_mlx *mlx, int x, int y,
					t_collision *collision);
void			get_collision(struct s_scene *scene, struct s_ray *ray,
					t_collision *collision);

#endif // RENDER_H
