/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:33:17 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 02:34:35 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/collision.h>

bool	plane_collide(struct s_ray *ray, struct s_plane *plane, t_collision *coll)
{
	float	determinant;
	float	distance;

	determinant = vec3_dot(ray->direction, plane->normal);
	if (determinant == 0)
		return (false);
	distance = vec3_dot(vec3_sub(plane->base.position, ray->origin), plane->normal) / determinant;
	if (!coll)
		return (true);
	coll->dist = distance;
	coll->position = ray_collision(ray, coll->dist);
	coll->normal = plane->normal;
	if (determinant > 0.0f)
		coll->normal = vec3_scal_mul(plane->normal, -1.0f);
	return (true);
}
