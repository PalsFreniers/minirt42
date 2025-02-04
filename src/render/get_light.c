/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:27:35 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 00:42:44 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

mlx_color	get_light_color(struct s_light *light)
{
	return (rgb_to_mlx_color(light->base.color));
}

float	get_lights_ratio(struct s_mlx *mlx)
{
	float	ratio = 0.0f;

	for (size_t i = 0; i < mlx->scene.len; i++)
	{
		struct s_light	*light = (struct s_light *)mlx->scene.map_objects[i];

		if (light->base.type == OBJ_LIGHT)
			ratio += light->ratio;
	}
	return (ratio);
}

t_render_color	get_lit_color(struct s_mlx *mlx, t_collision *coll)
{
	t_render_color	color;

	color = render_color_black();
	for (size_t i = 0; i < mlx->scene.len; i++)
	{
		struct s_light	*light = (struct s_light *)mlx->scene.map_objects[i];

		if (light->base.type == OBJ_LIGHT)
			color = color_add(color,
					color_scal_mul(lit_color(mlx, coll, light), light->ratio));
	}
	return (color);
}
