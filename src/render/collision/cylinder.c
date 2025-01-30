/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:08:52 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 01:58:05 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/la.h"
#include <math.h>
#include <render/collision.h>
#include <stdio.h>

static float	get_determinant(struct s_cylinder *cyl, t_vec3 ray_to_base,
		t_vec3 away_from_axis)
{
	float	determinant;
	float	radius;

	determinant = vec3_dot(ray_to_base, away_from_axis);
	determinant *= determinant;
	radius = cyl->diameter / 2;
	determinant = vec3_lenght_sq(away_from_axis) * radius * radius
		- determinant;
	return (determinant);
}

static void	fill_cyl_coll(struct s_cylinder_collision *check,
		t_vec3 away_from_axis, t_vec3 ray_to_base, float determinant)
{
	check->dist = vec3_dot(away_from_axis,
			vec3_cross(ray_to_base, check->cyl->axis));
	check->dist -= sqrtf(determinant);
	check->dist /= vec3_lenght_sq(away_from_axis);
	check->hght_front = vec3_dot(
			check->cyl->axis,
			vec3_sub(vec3_add(
					vec3_scal_mul(check->ray->direction, check->dist),
					check->ray->origin),
				check->cyl->base.position));
	check->dist_inside = 2 * sqrtf(determinant)
		/ vec3_lenght_sq(away_from_axis);
	check->hght_back = vec3_dot(
			check->cyl->axis,
			vec3_sub(vec3_add(
					vec3_scal_mul(
						check->ray->direction,
						check->dist + check->dist_inside),
					check->ray->origin),
				check->cyl->base.position));
}

static bool	end_caps(struct s_cylinder_collision *check, t_collision *coll)
{
	if ((check->hght_back < 0 && check->hght_front < 0)
		|| (check->hght_back > check->cyl->height
			&& check->hght_front > check->cyl->height))
		return (false);
	if (!coll)
		return (true);
	if (check->hght_front < 0)
	{
		coll->dist = check->dist + (check->dist_inside * check->hght_front
				/ (check->hght_front - check->hght_back));
		coll->normal = vec3_scal_mul(check->cyl->axis, -1.0f);
	}
	else
	{
		coll->dist = check->dist + (check->dist_inside
				* (check->hght_front - check->cyl->height)
				/ (check->hght_front - check->hght_back));
		coll->normal = check->cyl->axis;
	}
	coll->position = vec3_add(
			check->ray->origin,
			vec3_add(
				vec3_scal_mul(check->ray->direction, coll->dist),
				check->ray->origin));
	return (true);
}

static void	body(struct s_cylinder_collision *check, t_collision *coll)
{
	t_vec3	base_to_coll;
	t_vec3	offset;

	if (!coll)
		return ;
	coll->dist = check->dist;
	coll->position = vec3_add(
			check->ray->origin,
			vec3_add(
				vec3_scal_mul(check->ray->direction, coll->dist),
				check->ray->origin));
	base_to_coll = vec3_sub(coll->position, check->cyl->base.position);
	offset = vec3_scal_mul(check->cyl->axis,
			vec3_dot(base_to_coll, check->cyl->axis));
	coll->normal = vec3_normalise(vec3_sub(base_to_coll, offset));
}

bool	cylinder_collide(struct s_ray *ray,
		struct s_cylinder *cylinder, t_collision *coll)
{
	struct s_cylinder_collision	check;
	t_vec3						away_from_axis;
	t_vec3						ray_to_base;
	float						determinant;

	away_from_axis = vec3_cross(ray->direction, cylinder->axis);
	ray_to_base = vec3_sub(cylinder->base.position, ray->origin);
	determinant = get_determinant(cylinder, ray_to_base,
			away_from_axis);
	if (determinant < 0)
		return (false);
	check.ray = ray;
	check.cyl = cylinder;
	fill_cyl_coll(&check, away_from_axis, ray_to_base, determinant);
	if (check.hght_front < 0 || check.hght_front > cylinder->height)
		return (end_caps(&check, coll));
	else
		body(&check, coll);
	return (true);
}
