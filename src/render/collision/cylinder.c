/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:08:52 by maamine           #+#    #+#             */
/*   Updated: 2025/01/31 23:16:25 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/la.h"
#include <math.h>
#include <render/collision.h>

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

static bool	body(t_vec3 values, struct s_ray *ray, struct s_cylinder *cylinder,
		t_collision *coll)
{
	float	dist;
	float	inside;
	t_vec3	base_to_coll;
	t_vec3	offset;
	float	height_back;

	dist = values.x;
	inside = values.y;
	height_back = vec3_dot(cylinder->axis, vec3_add(
				vec3_sub(ray->origin, cylinder->base.position),
				vec3_scal_mul(ray->direction, dist + inside)));
	t_vec3	base_to_ray = vec3_sub(ray->origin, cylinder->base.position);
	if (dist < 0 && (height_back < 0 || height_back > cylinder->height
		|| vec3_lenght_sq(base_to_ray) - powf(vec3_dot(base_to_ray, cylinder->axis), 2.0) > powf(cylinder->diameter / 2, 2)))
		return (false);
	if (!coll)
		return (true);
	coll->dist = dist;
	if (dist < 0)
		coll->dist += inside;
	if (coll->dist < 0)
		coll->dist = 0.1f;
	coll->position = vec3_add(ray->origin,
			vec3_scal_mul(ray->direction, coll->dist));
	base_to_coll = vec3_sub(coll->position, cylinder->base.position);
	offset = vec3_scal_mul(cylinder->axis,
			vec3_dot(base_to_coll, cylinder->axis));
	coll->normal = vec3_normalise(vec3_sub(base_to_coll, offset));
	if (dist < 0)
		coll->normal = vec3_scal_mul(coll->normal, -1.0f);
	return (true);
}

static bool	cap_collide(struct s_ray *ray, struct s_plane *plane,
		t_collision *coll, float diameter)
{
	t_vec3	norm;
	t_vec3	pos;
	float	determinant;
	float	distance;

	if (coll)
		coll->dist = INFINITY;
	norm = vec3_normalise(plane->normal);
	determinant = vec3_dot(ray->direction, norm);
	if (determinant == 0)
		return (false);
	distance = vec3_dot(vec3_sub(plane->base.position, ray->origin), norm)
		/ determinant;
	pos = vec3_add(ray->origin, vec3_scal_mul(ray->direction, distance));
	if (distance < 0 || vec3_lenght_sq(vec3_sub(plane->base.position, pos))
		> diameter * diameter / 4)
		return (false);
	if (coll)
	{
		coll->dist = distance;
		coll->position = pos;
		if (determinant > 0.0f)
			coll->normal = vec3_scal_mul(norm, -1.0f);
		else
			coll->normal = norm;
	}
	return (true);
}

static bool	end_caps(t_vec3 values, struct s_ray *ray,
		struct s_cylinder *cylinder, t_collision *coll)
{
	struct s_plane	cap;
	t_collision		coll_top;
	float			dist;
	bool			cap_collid;

	dist = values.x;
	cap.normal = cylinder->axis;
	cap.base.position = vec3_add(cylinder->base.position,
			vec3_scal_mul(cylinder->axis, cylinder->height));
	cap_collid = cap_collide(ray, &cap, &coll_top, cylinder->diameter);
	cap.normal = vec3_scal_mul(cap.normal, -1.0f);
	cap.base.position = cylinder->base.position;
	cap_collid |= cap_collide(ray, &cap, coll, cylinder->diameter);
	if(cap_collid) {
		if(coll->dist > coll_top.dist) {
			*coll = coll_top;
		}
		return (true);
	}
	if (dist < 0)
		return (body(values, ray, cylinder, coll));
	return (false);
}

// static bool	end_caps(t_vec3 values, struct s_ray *ray,
// 		struct s_cylinder *cylinder, t_collision *coll)
// {
// 	float	height_back;
// 	float	height_front;
// 	float	dist_front;
// 	float	inside;
// 
// 	dist_front = values.x;
// 	height_front = values.y;
// 	inside = values.z;
// 	height_back = vec3_dot(cylinder->axis,
// 			vec3_add(
// 				vec3_sub(ray->origin, cylinder->base.position),
// 				vec3_scal_mul(ray->direction, dist_front + inside)));
// 	if ((height_back < 0 && height_front < 0)
// 		|| (height_back > cylinder->height && height_front > cylinder->height))
// 		return (false);
// 	if (!coll)
// 		return (true);
// 	cylinder_get_collision_normal_position(
// 		vec3_new(height_front, height_back, inside),
// 		dist_front, cylinder, coll);
// 	coll->position = vec3_add(ray->origin,
// 			vec3_add(vec3_scal_mul(ray->direction, coll->dist), ray->origin));
// 	return (true);
// }

bool	cylinder_collide(struct s_ray *ray, struct s_cylinder *cylinder,
		t_collision *coll)
{
	t_vec3	away_from_axis;
	t_vec3	ray_to_base;
	float	determinant;
	float	dist;
	float	height;

	away_from_axis = vec3_cross(ray->direction, cylinder->axis);
	ray_to_base = vec3_sub(cylinder->base.position, ray->origin);
	determinant = get_determinant(cylinder, ray_to_base, away_from_axis);
	if (determinant < 0)
		return (false);
	dist = vec3_dot(away_from_axis, vec3_cross(ray_to_base, cylinder->axis));
	dist = (dist - sqrtf(determinant)) / vec3_lenght_sq(away_from_axis);
	height = vec3_dot(cylinder->axis,
			vec3_sub(vec3_add(vec3_scal_mul(ray->direction, dist), ray->origin),
				cylinder->base.position));
	determinant = 2 * sqrtf(determinant) / vec3_lenght_sq(away_from_axis);
	if (dist > 0 && height > 0 && height < cylinder->height)
		return (body(vec3_new(dist, determinant, 0), ray, cylinder, coll));
	return (end_caps(vec3_new(dist, determinant, 0), ray, cylinder, coll));
}
