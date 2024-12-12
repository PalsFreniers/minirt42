/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:30:16 by maamine           #+#    #+#             */
/*   Updated: 2024/12/12 18:10:28 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/render.h>
#include <object/objects.h>
#include <render/collision.h>

t_acolor	rgb_to_rgba(t_color color)
{
	t_acolor	acolor;

	acolor.a = 0XFF;
	acolor.r = color.r;
	acolor.g = color.g;
	acolor.b = color.b;
	return (acolor);
}

t_acolor	filter_acolor(t_acolor light, t_acolor filter)
{
	t_acolor	color;

	color.a = 0XFF;
	color.r = (light.r * filter.r) / 0XFF;
	color.g = (light.g * filter.g) / 0XFF;
	color.b = (light.b * filter.b) / 0XFF;
	return (color);
}

t_acolor	blend_acolor(t_acolor a, t_acolor b)
{
	t_acolor	blend;

	blend.a = 0xFF;
	if (a.r > 0XFF - b.r)
		blend.r = 0XFF;
	else
		blend.r = a.r + b.r;
	if (a.g > 0XFF - b.g)
		blend.g = 0XFF;
	else
		blend.g = a.g + b.g;
	if (a.b > 0XFF - b.b)
		blend.b = 0XFF;
	else
		blend.b = a.b + b.b;
	return (blend);
}

t_acolor	get_light_acolor(struct s_mlx *mlx)
{
	t_acolor	color;

	if (mlx->scene.objects[0]->type != OBJ_LIGHT)
		color.argb = 0XFFFFFFFF;
	else
		color = rgb_to_rgba(mlx->scene.objects[0]->color);
	return (color);
}

// static bool	lit_angle(struct s_mlx *mlx, t_collision collision)
// {
// 	t_vec3	collision_to_light;
// 
// 	collision_to_light = vec3_sub(mlx->scene.objects[0]->position, collision.position);
// 	return (vec3_dot(collision.normal, vec3_normalise(collision_to_light)) >= 0);
// }

t_acolor	lit_color(struct s_mlx *mlx, t_collision collision)
{
	t_acolor	color;
	t_vec3		collision_to_light;
	float		cos_angle;

	collision_to_light = vec3_sub(mlx->scene.objects[0]->position, collision.position);
	cos_angle = vec3_dot(collision.normal, vec3_normalise(collision_to_light));
	// if (cos_angle < 0 || !lit_collision(mlx, collision))
	if (cos_angle < 0)
	{
		color.argb = 0XFF000000;
		return (color);
	}
	color = rgb_to_rgba(collision.object->color);
	return (color);
}
