/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:30:16 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 18:18:32 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/la.h"
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
			&& test_collision(mlx->scene.map_objects[i], &ray, &new_coll)
			&& new_coll.dist > 0 && new_coll.dist < light_dist)
			return (false);
		i++;
	}
	return (true);
}

static float	lambert(t_collision *coll, t_vec3 coll_to_light)
{
	float	light_per_area;

	light_per_area = vec3_dot(coll->normal, coll_to_light);
	if (light_per_area <= 0)
		return (0.0f);
	return (light_per_area);
}

static float	blinn_phong(t_collision *coll, t_vec3 coll_to_light)
{
	t_vec3	reflect_normal;
	float	light_per_area;

	reflect_normal = vec3_normalise(vec3_sub(coll_to_light,
			coll->ray.direction));
	light_per_area = vec3_dot(coll->normal, reflect_normal);
	light_per_area = light_per_area * light_per_area * light_per_area;
	if (light_per_area <= 0)
		return (0.0f);
	return (light_per_area);
}

#define DIST_FACTOR 0.004f

t_render_color	lit_color(struct s_mlx *mlx, t_collision *collision,
		struct s_light *light)
{
	t_vec3	coll_to_light;
	float	dist_to_light_sq;
	float	light_amount;

	coll_to_light = vec3_sub(light->base.position, collision->position);
	if (!is_lit(mlx, collision, coll_to_light))
		return (render_color_black());
	dist_to_light_sq = vec3_lenght_sq(coll_to_light);
	coll_to_light = vec3_normalise(coll_to_light);
	light_amount = lambert(collision, coll_to_light);
	if (light_amount <= 0.0f)
		return (render_color_black());
	light_amount += blinn_phong(collision, coll_to_light);
	light_amount /= dist_to_light_sq * DIST_FACTOR;
	return (color_scal_mul(rgb_to_render_color(light->base.color), light_amount
			/ 2));
}
