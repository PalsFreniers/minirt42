/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:30:16 by maamine           #+#    #+#             */
/*   Updated: 2024/12/18 21:42:16 by maamine          ###   ########.fr       */
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

t_acolor	mul_acolor(t_acolor color, float f)
{
	color.r *= f;
	if (color.r > 0XFF)
		color.r = 0XFF;
	color.g *= f;
	if (color.g > 0XFF)
		color.g = 0XFF;
	color.b *= f;
	if (color.b > 0XFF)
		color.b = 0XFF;
	return (color);
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

	if (mlx->scene.map_objects[0]->type != OBJ_LIGHT)
		color.argb = 0XFFFFFFFF;
	else
		color = rgb_to_rgba(mlx->scene.map_objects[0]->color);
	return (color);
}

static bool	is_lit(struct s_mlx *mlx, t_collision *starting_point, t_vec3 light_dir)
{
	t_ray		ray;
	t_collision	new_collision;
	float		light_dist;
	size_t		i;

	ray.origin = starting_point->position;
	ray.direction = vec3_normalise(light_dir);
	light_dist = vec3_lenght(light_dir);
	i = 0;
	while (i < mlx->scene.len)
	{
		if (mlx->scene.map_objects[i] != starting_point->object
			&& test_collision(mlx, mlx->scene.map_objects[i], &ray, &new_collision)
			&& new_collision.dist > 0 && new_collision.dist < light_dist)
			return (false);
		i++;
	}
	return (true);
}

static t_acolor	lambert_shading(t_collision *coll, t_vec3 coll_to_light)
{
	t_acolor	color;
	float		light_per_area;
	float		diffuse_coeff;
	float		light_amount;

	light_per_area = vec3_dot(coll->normal, vec3_normalise(coll_to_light));
	if (light_per_area <= 0)
	{
		color.argb = 0XFF000000;
		return (color);
	}
	diffuse_coeff = 1.0f;
	// light_amount = diffuse_coeff * light_per_area / vec3_lenght_sq(coll_to_light);
	// light_amount = diffuse_coeff / vec3_lenght_sq(coll_to_light);
	light_amount = diffuse_coeff * light_per_area;
	color = mul_acolor(rgb_to_rgba(coll->object->color), light_amount);
	return (color);
}

static t_acolor	blinn_phong_shading(t_collision *coll, t_vec3 coll_to_light)
{
	t_acolor	color;
	t_vec3		reflect_normal;
	float		light_per_area;
	float		diffuse_coeff;
	float		light_amount;

	reflect_normal = vec3_sub(vec3_normalise(coll_to_light), coll->ray.direction);
	reflect_normal = vec3_normalise(reflect_normal);
	light_per_area = vec3_dot(coll->normal, reflect_normal);
	light_per_area = light_per_area * light_per_area * light_per_area;
	if (light_per_area <= 0)
	{
		color.argb = 0XFF000000;
		return (color);
	}
	diffuse_coeff = 1.0f;
	// light_amount = diffuse_coeff * light_per_area / vec3_lenght_sq(coll_to_light);
	// light_amount = diffuse_coeff / vec3_lenght_sq(coll_to_light);
	light_amount = diffuse_coeff * light_per_area;
	color = mul_acolor(rgb_to_rgba(coll->object->color), light_amount);
	return (color);
}

t_acolor	lit_color(struct s_mlx *mlx, t_collision *collision)
{
	t_acolor	color;
	t_vec3		coll_to_light;

	coll_to_light = vec3_sub(mlx->scene.map_objects[0]->position, collision->position);
	if (!is_lit(mlx, collision, coll_to_light))
	{
		color.argb = 0XFF000000;
		return (color);
	}
	// color = rgb_to_rgba(collision->object->color);
	// color = lambert_shading(collision, coll_to_light);
	color = blend_acolor(lambert_shading(collision, coll_to_light),
			blinn_phong_shading(collision, coll_to_light));
	return (color);
}
