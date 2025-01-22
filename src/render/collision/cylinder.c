/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:08:52 by maamine           #+#    #+#             */
/*   Updated: 2025/01/22 04:20:43 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/la.h"
#include <render/collision.h>

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

/**
 * Not finished, but the idea is here.
 */
static bool	end_caps(float dist, float t_front, float determinant, struct s_ray *ray,
	struct s_cylinder *cylinder, t_collision *coll)
{
	float	inside;
	float	t_back;

	inside = 2 * sqrtf(determinant);
	t_back = vec3_dot(cylinder->axis, vec3_sub(vec3_scal_mul(ray->direction,
				dist + inside), cylinder->base.position));
	if (t_back < 0 || t_back > cylinder->height)
		return (false);
	if (coll)
	{
		if (t_front < 0)
		{
			coll->dist = dist + (inside * t_front / (t_front - t_back));
			coll->position = vec3_add(ray->origin, vec3_scal_mul(ray->direction, coll->dist));
			coll->normal = vec3_scal_mul(cylinder->axis, -1.0f);
		}
		else
		{
			coll->dist = dist + (inside * (t_front - cylinder->height) / (t_front - t_back));
			coll->position = vec3_add(ray->origin, vec3_scal_mul(ray->direction, coll->dist));
			coll->normal = cylinder->axis;
		}
	}
	return (true);
}

static void	body(float dist, struct s_ray *ray,
	struct s_cylinder *cylinder, t_collision *coll)
{
	if (coll)
	{
		coll->dist = dist;
		coll->position = vec3_add(ray->origin, vec3_scal_mul(ray->direction,
				coll->dist));
		coll->normal = get_normal(cylinder, coll);
	}
}

bool	cylinder_collide_function(struct s_ray *ray,
		struct s_cylinder *cylinder, t_collision *coll) // Unfinished, end caps missing
{
	float	determinant;
	t_vec3	away_from_axis;
	t_vec3	ray_to_base;
	float	dist;
	float	t;

	away_from_axis = vec3_cross(ray->direction, cylinder->axis);
	ray_to_base = vec3_sub(cylinder->base.position, ray->origin);
	determinant = get_determinant(cylinder->diameter / 2, ray_to_base,
		away_from_axis);
	if (determinant < 0)
		return (false);
	dist = vec3_dot(away_from_axis, vec3_cross(ray_to_base, cylinder->axis));
	dist = (dist - sqrtf(determinant)) / vec3_lenght_sq(away_from_axis);
	t = vec3_dot(cylinder->axis, vec3_sub(vec3_scal_mul(ray->direction,
				dist), cylinder->base.position));
	if (t < 0 || t > cylinder->height)
		return (end_caps(dist, t, determinant, ray, cylinder, coll));
	else
		body(dist, ray, cylinder, coll);
	return (true);
}
