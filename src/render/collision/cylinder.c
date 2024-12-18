/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:08:52 by maamine           #+#    #+#             */
/*   Updated: 2024/12/18 23:46:15 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/collision.h>

static float	get_determinant(float radius, t_vec3 ray_to_base, t_vec3 away_from_axis)
{
	float	determinant;

	determinant = vec3_dot(ray_to_base, away_from_axis);
	determinant *= determinant;
	determinant = vec3_lenght_sq(away_from_axis) * radius * radius - determinant;
	return (determinant);
}

static t_vec3	get_normal(struct s_cylinder *cylinder, t_collision *coll)
{
	t_vec3	normal;
	t_vec3	base_to_coll;
	t_vec3	offset;

	base_to_coll = vec3_sub(coll->position, cylinder->base.position);
	offset = vec3_scal_mul(cylinder->axis,
			vec3_dot(base_to_coll, cylinder->axis));
	normal = vec3_normalise(vec3_sub(base_to_coll, offset));
	return (normal);
}

bool	cylinder_collide_function(struct s_ray *ray,
		struct s_cylinder *cylinder, t_collision *coll)	// Unfinished, end caps missing
{
	float	determinant;
	t_vec3	away_from_axis;
	t_vec3	ray_to_base;

	away_from_axis = vec3_cross(ray->direction, cylinder->axis);
	ray_to_base = vec3_sub(cylinder->base.position, ray->origin);
	determinant = get_determinant(cylinder->diameter / 2, ray_to_base, away_from_axis);
	if (determinant < 0)
		return (false);
	// end caps
	if (coll)
	{
		coll->dist = vec3_dot(away_from_axis, vec3_cross(ray_to_base, cylinder->axis));
		coll->dist = (coll->dist - sqrtf(determinant)) / vec3_lenght_sq(away_from_axis);
		coll->position = vec3_add(ray->origin, vec3_scal_mul(ray->direction, coll->dist));
		coll->normal = get_normal(cylinder, coll);
	}
	return (true);
}
