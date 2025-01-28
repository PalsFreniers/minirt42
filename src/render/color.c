/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:30:16 by maamine           #+#    #+#             */
/*   Updated: 2025/01/28 12:41:44 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object/objects.h>
#include <render/collision.h>
#include <render/render.h>

static bool	is_lit(struct s_mlx *mlx, t_collision *starting_point,
		t_vec3 light_dir)
{
	t_ray		ray;
	t_collision	new_coll;
	float		light_dist;
	size_t		i;

	light_dist = vec3_lenght(light_dir);
	ray.origin = starting_point->position;
	ray.direction = vec3_normalise(light_dir);
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
	light_amount = diffuse_coeff * light_per_area;
	return (color_scal_mul(rgb_to_render_color(coll->object->color),
			light_amount));
}

static t_render_color	blinn_phong(t_collision *coll, t_vec3 coll_to_light)
{
	t_vec3	reflect_normal;
	float	light_per_area;
	float	diffuse_coeff;
	float	light_amount;

	reflect_normal = vec3_normalise(vec3_sub(vec3_normalise(coll_to_light),
				coll->ray.direction));
	light_per_area = vec3_dot(coll->normal, reflect_normal);
	light_per_area = light_per_area * light_per_area * light_per_area;
	if (light_per_area <= 0)
		return (render_color_black());
	diffuse_coeff = 1.0f;
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
	return (color_add(color_scal_mul(lambert(collision, coll_to_light), 0.5f),
			color_scal_mul(blinn_phong(collision, coll_to_light), 0.5f)));
}
