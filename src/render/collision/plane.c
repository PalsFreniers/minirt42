/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:33:17 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/30 03:36:39 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object/objects.h"
#include <libft.h>
#include <math/la.h>
#include <render/collision.h>

bool	plane_collide(struct s_ray *ray, struct s_plane *plane,
		t_collision *coll)
{
	t_vec3	norm;
	float	determinant;
	float	distance;

	norm = vec3_normalise(plane->normal);
	determinant = vec3_dot(ray->direction, norm);
	if (determinant == 0)
		return (false);
	distance = vec3_dot(vec3_sub(plane->base.position, ray->origin), norm)
		/ determinant;
	if (coll)
	{
		coll->dist = distance;
		coll->position = vec3_add(ray->origin, vec3_scal_mul(ray->direction,
				distance));
		if (determinant > 0.0f)
			coll->normal = vec3_scal_mul(norm, -1.0f);
		else
			coll->normal = norm;
		coll->object = (void *)plane;
	}
	return (true);
}
