/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:08:52 by maamine           #+#    #+#             */
/*   Updated: 2024/12/17 21:08:59 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/collision.h>

bool	cylinder_collide_function(struct s_ray ray,
		struct s_cylinder *cylinder, t_collision *coll, t_matrices *m)	// Unfinished, end caps missing
{
	float	radius;
	float	determinant;
	t_vec3	away_from_axis;
	t_vec3	ray_to_base;
	t_vec3	base_to_coll;

	(void) m;
	radius = cylinder->diameter / 2;
	away_from_axis = vec3_cross(ray.direction, cylinder->axis);
	ray_to_base = vec3_sub(cylinder->base.position, ray.origin);
	determinant = -vec3_dot(ray_to_base, away_from_axis);
	determinant *= determinant;
	determinant += vec3_lenght_sq(away_from_axis) * radius * radius;
	if (determinant < 0)
		return (false);
	if (coll)
	{
		coll->dist = vec3_dot(away_from_axis, vec3_cross(ray_to_base, cylinder->axis));
		coll->dist = (coll->dist - sqrtf(determinant)) / vec3_lenght_sq(away_from_axis);
		coll->position = vec3_add(ray.origin, vec3_scal_mul(ray.direction, coll->dist));
		base_to_coll = vec3_sub(coll->position, cylinder->base.position);
		coll->normal = vec3_normalise(
				vec3_sub(base_to_coll,
					vec3_scal_mul(cylinder->axis,
						vec3_dot(base_to_coll, cylinder->axis))));
		coll->object = ((struct s_object *) cylinder);
	}
	return (true);
}
