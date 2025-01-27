/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:30:16 by maamine           #+#    #+#             */
/*   Updated: 2025/01/27 04:58:45 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object/objects.h>
#include <render/collision.h>
#include <render/render.h>

struct s_object	*get_map_light(struct s_scene *scene)
{
	size_t	x;

	x = 0;
	while (x < scene->len)
	{
		if (scene->map_objects[x]->type == OBJ_LIGHT)
			return (scene->map_objects[x]);
		x++;
	}
	return (NULL);
}

struct s_object	*get_real_light(struct s_scene *scene)
{
	size_t	x;

	x = 0;
	while (x < scene->len)
	{
		if (scene->objects[x]->type == OBJ_LIGHT)
			return (scene->objects[x]);
		x++;
	}
	return (NULL);
}

mlx_color	rgb_to_rgba(t_color color)
{
	mlx_color	acolor;

	acolor.a = 0XFF;
	acolor.r = color.r;
	acolor.g = color.g;
	acolor.b = color.b;
	return (acolor);
}

mlx_color	mul_acolor(mlx_color color, float f)
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

mlx_color	filter_acolor(mlx_color light, mlx_color filter)
{
	mlx_color	color;

	color.a = 0XFF;
	color.r = (light.r * filter.r) / 0XFF;
	color.g = (light.g * filter.g) / 0XFF;
	color.b = (light.b * filter.b) / 0XFF;
	return (color);
}

mlx_color	blend_color(mlx_color a, mlx_color b, float ratio)
{
	mlx_color	blend;

	blend.a = 0xFF;
	blend.r = (1 - ratio) * a.r + ratio * b.r;
	blend.g = (1 - ratio) * a.g + ratio * b.g;
	blend.b = (1 - ratio) * a.b + ratio * b.b;
	////        blend.r = (a.r + b.r) / 2;
	////        blend.g = (a.g + b.g) / 2;
	////        blend.b = (a.b + b.b) / 2;
	//	if (a.r > 0XFF - b.r)
	//		blend.r = 0XFF;
	//	else
	//		blend.r = a.r + b.r;
	//	if (a.g > 0XFF - b.g)
	//		blend.g = 0XFF;
	//	else
	//		blend.g = a.g + b.g;
	//	if (a.b > 0XFF - b.b)
	//		blend.b = 0XFF;
	//	else
	//		blend.b = a.b + b.b;
	return (blend);
}

mlx_color	get_light_color(struct s_mlx *mlx)
{
	mlx_color	color;

	color = rgb_to_rgba(get_real_light(&mlx->scene)->color);
	return (color);
}

static bool	is_lit(struct s_mlx *mlx, t_collision *starting_point,
		t_vec3 light_dir)
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
			&& test_collision(mlx, mlx->scene.map_objects[i], &ray,
				&new_collision) && new_collision.dist > 0
			&& new_collision.dist < light_dist)
			return (false);
		i++;
	}
	return (true);
}

static mlx_color	lambert_shading(t_collision *coll, t_vec3 coll_to_light)
{
	mlx_color	color;
	float		light_per_area;
	float		diffuse_coeff;
	float		light_amount;

	light_per_area = vec3_dot(coll->normal, vec3_normalise(coll_to_light));
	if (light_per_area <= 0)
	{
		color.rgba = 0X000000FF;
		return (color);
	}
	diffuse_coeff = 1.0f;
	// light_amount = diffuse_coeff * light_per_area / vec3_lenght_sq(coll_to_light);
	// light_amount = diffuse_coeff / vec3_lenght_sq(coll_to_light);
	light_amount = diffuse_coeff * light_per_area;
	color = mul_acolor(rgb_to_rgba(coll->object->color), light_amount);
	return (color);
}

static mlx_color	blinn_phong_shading(t_collision *coll, t_vec3 coll_to_light)
{
	mlx_color	color;
	t_vec3		reflect_normal;
	float		light_per_area;
	float		diffuse_coeff;
	float		light_amount;

	reflect_normal = vec3_sub(vec3_normalise(coll_to_light),
			coll->ray.direction);
	reflect_normal = vec3_normalise(reflect_normal);
	light_per_area = vec3_dot(coll->normal, reflect_normal);
	light_per_area = light_per_area * light_per_area * light_per_area;
	if (light_per_area <= 0)
	{
		color.rgba = 0X000000FF;
		return (color);
	}
	diffuse_coeff = 1.0f;
	// light_amount = diffuse_coeff * light_per_area / vec3_lenght_sq(coll_to_light);
	// light_amount = diffuse_coeff / vec3_lenght_sq(coll_to_light);
	light_amount = diffuse_coeff * light_per_area;
	color = mul_acolor(rgb_to_rgba(coll->object->color), light_amount);
	return (color);
}

mlx_color	lit_color(struct s_mlx *mlx, t_collision *collision, float ratio)
{
	mlx_color	color;
	t_vec3		coll_to_light;

	coll_to_light = vec3_sub(get_map_light(&mlx->scene)->position,
			collision->position);
	if (!is_lit(mlx, collision, coll_to_light))
	{
		color.rgba = 0X000000FF;
		return (color);
	}
	// color = rgb_to_rgba(collision->object->color);
	// color = lambert_shading(collision, coll_to_light);
	color = blend_color(lambert_shading(collision, coll_to_light),
			blinn_phong_shading(collision, coll_to_light), 0.5f);
	color = blend_color(rgb_to_rgba(collision->object->color), color, ratio);
	return (color);
}
