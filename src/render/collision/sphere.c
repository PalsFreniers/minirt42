/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:17:56 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/03 00:17:06 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/collision.h>

bool	sphere_collide(struct s_ray *ray, struct s_sphere *sphere,
		t_collision *coll)
{
	const float	radius = sphere->diameter / 2;
	float		determinant;
	t_vec3		ray_to_sphere;
	float		rtsp_dist_sq;
	float		middle_dist;

	ray_to_sphere = vec3_sub(sphere->base.position, ray->origin);
	rtsp_dist_sq = vec3_lenght_sq(ray_to_sphere);
	middle_dist = vec3_dot(ray->direction, ray_to_sphere);
	determinant = powf(middle_dist, 2) - (rtsp_dist_sq - powf(radius, 2));
	if (determinant < 0)
		return (false);
	if (!coll)
		return (true);
	determinant = sqrtf(determinant);
	coll->dist = middle_dist - determinant;
	coll->position = ray_collision(ray, coll->dist);
	coll->normal = vec3_normalise(vec3_sub(coll->position,
				sphere->base.position));
	if (middle_dist < determinant)
		coll->normal = vec3_scal_mul(coll->normal, -1.0f);
	return (true);
}
