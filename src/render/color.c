/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:30:16 by maamine           #+#    #+#             */
/*   Updated: 2025/01/27 19:40:45 by maamine          ###   ########.fr       */
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

t_render_color	render_color_black(void)
{
	return ((t_render_color)
	{
		.r = 0.0f,
		.g = 0.0f,
		.b = 0.0f,
	});
}

mlx_color	rgb_to_mlx_color(union u_color color)
{
	mlx_color	ret_color;

	ret_color.a = 0xFF;
	ret_color.r = color.r;
	ret_color.g = color.g;
	ret_color.b = color.b;
	return (ret_color);
}

t_render_color	rgb_to_render_color(union u_color color)
{
	t_render_color	ret_color;

	ret_color.r = color.r;
	ret_color.g = color.g;
	ret_color.b = color.b;
	return (ret_color);
}

mlx_color	render_to_mlx_color(t_render_color color)
{
	mlx_color	ret_color;

	ret_color.a = 0xFF;
	if (color.r > 0xFF)
		ret_color.r = 0xFF;
	else
		ret_color.r = color.r;
	if (color.g > 0xFF)
		ret_color.g = 0xFF;
	else
		ret_color.g = color.g;
	if (color.b > 0xFF)
		ret_color.b = 0xFF;
	else
		ret_color.b = color.b;
	return (ret_color);
}

t_render_color	filter_color(t_render_color color, t_render_color filter)
{
	t_render_color	ret_color;

	ret_color.r = (color.r * filter.r) / 0xFF;
	ret_color.g = (color.g * filter.g) / 0xFF;
	ret_color.b = (color.b * filter.b) / 0xFF;
	return (ret_color);
}

t_render_color	color_scal_mul(t_render_color color, float f)
{
	t_render_color	ret_color;

	ret_color.r = color.r * f;
	ret_color.g = color.g * f;
	ret_color.b = color.b * f;
	return (ret_color);
}

t_render_color	color_add(t_render_color a, t_render_color b)
{
	t_render_color	color;

	color.r = a.r + b.r;
	color.g = a.g + b.g;
	color.b = a.b + b.b;
	return (color);
}

mlx_color	get_light_color(struct s_mlx *mlx)
{
	return (rgb_to_mlx_color(get_real_light(&mlx->scene)->color));
}

static bool	is_lit(struct s_mlx *mlx, t_collision *starting_point,
		t_vec3 light_dir)
{
	t_ray		ray;
	t_collision	new_coll;
	float		light_dist;
	size_t		i;

	ray.origin = starting_point->position;
	ray.direction = vec3_normalise(light_dir);
	light_dist = vec3_lenght(light_dir);
	i = 0;
	while (i < mlx->scene.len)
	{
		if (mlx->scene.map_objects[i] != starting_point->object
			&& test_collision(mlx, mlx->scene.map_objects[i], &ray, &new_coll)
			&& new_coll.dist > 0 && new_coll.dist < light_dist)
			return (false);
		i++;
	}
	return (true);
}

static t_render_color	lambert(t_collision *coll, t_vec3 coll_to_light)
{
	float	light_per_area;
	float	diffuse_coeff;
	float	light_amount;

	light_per_area = vec3_dot(coll->normal, vec3_normalise(coll_to_light));
	if (light_per_area <= 0)
		return (render_color_black());
	diffuse_coeff = 1.0f;
	// light_amount = diffuse_coeff * light_per_area / vec3_lenght_sq(coll_to_light);
	// light_amount = diffuse_coeff / vec3_lenght_sq(coll_to_light);
	light_amount = diffuse_coeff * light_per_area;
	return (color_scal_mul(rgb_to_render_color(coll->object->color),
				light_amount));
}

static t_render_color	blinn_phong(t_collision *coll, t_vec3 coll_to_light)
{
	t_vec3			reflect_normal;
	float			light_per_area;
	float			diffuse_coeff;
	float			light_amount;

	reflect_normal = vec3_normalise(vec3_sub(vec3_normalise(coll_to_light),
				coll->ray.direction));
	light_per_area = vec3_dot(coll->normal, reflect_normal);
	light_per_area = light_per_area * light_per_area * light_per_area;
	if (light_per_area <= 0)
		return (render_color_black());
	diffuse_coeff = 1.0f;
	// light_amount = diffuse_coeff * light_per_area / vec3_lenght_sq(coll_to_light);
	// light_amount = diffuse_coeff / vec3_lenght_sq(coll_to_light);
	light_amount = diffuse_coeff * light_per_area;
	return (color_scal_mul(rgb_to_render_color(coll->object->color),
				light_amount));
}

t_render_color	lit_color(struct s_mlx *mlx, t_collision *collision)
{
	t_vec3	coll_to_light;

	coll_to_light = vec3_sub(get_map_light(&mlx->scene)->position,
			collision->position);
	if (!is_lit(mlx, collision, coll_to_light))
		return (render_color_black());
	return (
		color_add(
			color_scal_mul(lambert(collision, coll_to_light), 0.5f),
			color_scal_mul(blinn_phong(collision, coll_to_light), 0.5f)));
}
