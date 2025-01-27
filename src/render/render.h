/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwan <marwan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 04:16:46 by maamine           #+#    #+#             */
/*   Updated: 2025/01/27 01:53:21 by marwan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <mlx/mmlx.h>
# include <render/collision.h>

void			loop_render(struct s_mlx *mlx);

mlx_color		rgb_to_rgba(t_color color);
mlx_color		filter_acolor(mlx_color light, mlx_color filter);
mlx_color		blend_color(mlx_color a, mlx_color b, float ratio);
mlx_color		blend_color_safe(mlx_color a, mlx_color b, float ratio);
mlx_color		get_light_color(struct s_mlx *mlx);
mlx_color		lit_color(struct s_mlx *mlx, t_collision *collision);
struct s_object	*get_map_light(struct s_scene *scene);
struct s_object *get_real_light(struct s_scene *scene);

#endif // RENDER_H
