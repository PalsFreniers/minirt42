/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:27:35 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/04 21:19:15 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

mlx_color	get_light_color(struct s_light *light)
{
	return (rgb_to_mlx_color(light->base.color));
}

float	get_lights_ratio(struct s_mlx *mlx)
{
	float			ratio;
	size_t			i;
	struct s_light	*light;

	ratio = 0.0f;
	i = 0;
	while (i < mlx->scene.len)
	{
		light = (struct s_light *)mlx->scene.map_objects[i];
		if (light->base.type == OBJ_LIGHT)
			ratio += light->ratio;
		i++;
	}
	return (ratio);
}

t_render_color	get_lit_color(struct s_mlx *mlx, t_collision *coll)
{
	t_render_color	color;
	size_t			i;
	struct s_light	*light;

	color = render_color_black();
	i = 0;
	while (i < mlx->scene.len)
	{
		light = (struct s_light *)mlx->scene.map_objects[i];
		if (light->base.type == OBJ_LIGHT)
			color = color_add(color,
					color_scal_mul(lit_color(mlx, coll, light), light->ratio));
		i++;
	}
	return (color);
}
