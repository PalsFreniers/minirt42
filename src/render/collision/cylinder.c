/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:08:52 by maamine           #+#    #+#             */
/*   Updated: 2025/01/28 13:46:56 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/la.h"
#include <math.h>
#include <render/collision.h>
#include <stdio.h>

static float	get_determinant(float radius, t_vec3 ray_to_base,
		t_vec3 away_from_axis)
{
	float	determinant;

	determinant = vec3_dot(ray_to_base, away_from_axis);
	determinant *= determinant;
	determinant = vec3_lenght_sq(away_from_axis) * radius * radius
		- determinant;
	return (determinant);
}

static t_vec3	get_normal(struct s_cylinder *cylinder, t_collision *coll)
{
	t_vec3	normal;
	t_vec3	base_to_coll;
	t_vec3	offset;

	base_to_coll = vec3_sub(coll->position, cylinder->base.position);
	offset = vec3_scal_mul(cylinder->axis, vec3_dot(base_to_coll,
				cylinder->axis));
	normal = vec3_normalise(vec3_sub(base_to_coll, offset));
	return (normal);
}

static bool	end_caps(float dist_front, float height_front, float inside,
		struct s_ray *ray, struct s_cylinder *cylinder, t_collision *coll)
{
	float	height_back;

	height_back = vec3_dot(cylinder->axis,
			vec3_sub(vec3_add(vec3_scal_mul(ray->direction, dist_front + inside), ray->origin),
				cylinder->base.position));
	if ((height_back < 0 && height_front < 0) || (height_back > cylinder->height
			&& height_front > cylinder->height))
		return (false);
	if (!coll)
		return (true);
	if (height_front < 0)
	{
		coll->dist = dist_front + (inside * height_front / (height_front
					- height_back));
		coll->normal = vec3_scal_mul(cylinder->axis, -1.0f);
	}
	else
	{
		coll->dist = dist_front + (inside * (height_front - cylinder->height)
				/ (height_front - height_back));
		coll->normal = cylinder->axis;
	}
	coll->position = vec3_add(ray->origin, vec3_add(vec3_scal_mul(ray->direction,
				coll->dist), ray->origin));
	return (true);
}

static void	body(float dist, struct s_ray *ray, struct s_cylinder *cylinder,
		t_collision *coll)
{
	if (coll)
	{
		coll->dist = dist;
		coll->position = vec3_add(ray->origin, vec3_add(vec3_scal_mul(ray->direction,
					coll->dist), ray->origin));
		coll->normal = get_normal(cylinder, coll);
	}
}

bool	cylinder_collide_function(struct s_ray *ray,
		struct s_cylinder *cylinder, t_collision *coll)
{
	float	determinant;
	t_vec3	away_from_axis;
	t_vec3	ray_to_base;
	float	dist;
	float	height;

	away_from_axis = vec3_cross(ray->direction, cylinder->axis);
	ray_to_base = vec3_sub(cylinder->base.position, ray->origin);
	determinant = get_determinant(cylinder->diameter / 2, ray_to_base,
			away_from_axis);
	if (determinant < 0)
		return (false);
	dist = vec3_dot(away_from_axis, vec3_cross(ray_to_base, cylinder->axis));
	dist = (dist - sqrtf(determinant)) / vec3_lenght_sq(away_from_axis);
	height = vec3_dot(cylinder->axis, vec3_sub(vec3_add(vec3_scal_mul(ray->direction,
					dist), ray->origin), cylinder->base.position));
	if (height < 0 || height > cylinder->height)
	{
		determinant = 2 * sqrtf(determinant) / vec3_lenght_sq(away_from_axis);
		return (end_caps(dist, height, determinant, ray, cylinder, coll));
	}
	else
		body(dist, ray, cylinder, coll);
	return (true);
}
